/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lua.trevin.7e8@itb.cat <lua.trevin.7e8@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:53:21 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/09 08:52:00 by lua.trevin.      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void swap_forks(t_philo *philo)
{
    t_fork *tmp;

    tmp = philo->first_f;
    philo->first_f = philo->second_f;
    philo->second_f = tmp;
}

int prepare_table(t_table *table)
{
    int i;

    i = 0;
    table->forks = malloc(sizeof(t_fork) * table->n_philos);
    table->philos = malloc(sizeof(t_philo) * table->n_philos);
    if(!table->forks || !table->philos)
        return (ft_error(WRONG_MALLOC, 0));
    while(i < table->n_philos)
    {
        table->forks[i].id = i + 1;
        if(pthread_mutex_init(&table->forks[i].mutex, NULL))
            return (ft_error(WRONG_MUTEX, 0));
        i++;
    }
    i = 0;
    while(i < table->n_philos)
    {
        table->philos[i].id = i + 1;
        table->philos[i].n_meals = 0;
        table->philos[i].table = table;
        table->philos[i].first_f = &table->forks[i];
        table->philos[i].second_f = &table->forks[(i + 1) % table->n_philos];
        table->philos[i].last_meal = 0;
        if(table->philos[i].id % 2) // if the philo is odd we swap the forks
            swap_forks(&table->philos[i]);
        if(pthread_mutex_init(&table->philos[i].read, NULL))
            return (ft_error(WRONG_MUTEX, 0));
        i++;
    }
    return (0);
}

void clean_table(t_table table)
{
    int i;

    i = 0;
    while(i < table.n_philos)
    {
        pthread_mutex_destroy(&table.forks[i].mutex);
        pthread_mutex_destroy(&table.philos[i].read);
        i++;
    }
    pthread_mutex_destroy(&table.read);
    pthread_mutex_destroy(&table.print);
    free(table.forks);
    free(table.philos);
}

int continue_dinner(t_table *table)
{
    int continue_eating;

    continue_eating = 1;
    pthread_mutex_lock(&table->read);
    if(table->end_dinner == 1)
        continue_eating = 0;
    pthread_mutex_unlock(&table->read);
    return (continue_eating);
}

void search_full_philos(t_table *table)
{
    int i;
    int full_philos = 0;

    if(table->n_meals == -1)
        return ;
    i = 0;
    while (i < table->n_philos)
    {
        pthread_mutex_lock(&table->philos[i].read);
        if(table->philos[i].n_meals >= table->n_meals)
            full_philos++;
        pthread_mutex_unlock(&table->philos[i].read);
        i++;
    }
    if(full_philos >= table->n_philos)
    {
        
        pthread_mutex_lock(&table->print);
        printf("---------ALL PHILOS ARE FULL---------\n");
        pthread_mutex_unlock(&table->print);
        pthread_mutex_lock(&table->read);
        table->end_dinner = 1;
        pthread_mutex_unlock(&table->read);
    }
}

void search_death_philos(t_table *table)
{
    int i;

    i = 0;
    //pthread_mutex_lock(&table->print);
    //printf("Searching death philos\n");
    //pthread_mutex_unlock(&table->print);
    while (i < table->n_philos)
    {
        pthread_mutex_lock(&table->philos[i].read);
        if(get_time(table) - table->philos[i].last_meal >= table->t_die)
        {
            pthread_mutex_unlock(&table->philos[i].read);
            pthread_mutex_lock(&table->print);
            printf(RED "[%lu] %d is dead" RESET "\n" , get_time(table), table->philos[i].id);
            pthread_mutex_unlock(&table->print);
            pthread_mutex_lock(&table->read);
            table->end_dinner = 1;
            pthread_mutex_unlock(&table->read);
            i = table->n_philos;
        }
        else
            pthread_mutex_unlock(&table->philos[i].read);
        i++;
    }
}

int init_dinner(t_table *table)
{
    int i;

    i = 0;
    pthread_mutex_lock(&table->read);
    table->t_start = get_current_time();
    // create threads
    while(i < table->n_philos)
    {
        if (pthread_create(&table->philos[i].thread, NULL, start_routine, &table->philos[i]) != 0)
            return (ft_error(WRONG_THREAD, 0));
        i++;
    }
    pthread_mutex_unlock(&table->read);
    // dinner, check if the dinner is over
    while(continue_dinner(table))
    {
        
        // check if a philo is dead
        search_death_philos(table);
        if(!continue_dinner(table))
            break;
        // search if all philos are full
        search_full_philos(table);
    }
    pthread_mutex_lock(&table->print);
    printf("dinner ended\n");
    pthread_mutex_unlock(&table->print);
    //join threads
    i = 0;
    while(i < table->n_philos)
    {
        pthread_join(table->philos[i].thread, NULL);
        i++;
    }
    printf("all threads joined\n");
    return (0);
}

void print_table(t_table *table)
{
    printf("n_philos: %ld\n", table->n_philos);
    printf("t_die: %ld\n", table->t_die);
    printf("t_eat: %ld\n", table->t_eat);
    printf("t_sleep: %ld\n", table->t_sleep);
    printf("n_meals: %ld\n", table->n_meals);
    printf("t_start: %ld\n", table->t_start);
    int i = 0;
    while(i < table->n_philos)
    {
        printf("philo %d\n", table->philos[i].id);
        printf("    first_f: %d", table->philos[i].first_f->id);
        printf(" second_f: %d\n", table->philos[i].second_f->id);
        i++;
    }
}


// n_philo time_to_die time_to_eat time_to_sleep [times_to_eat]
int main (int argc, char **argv)
{
    t_table table;

    ft_bzero(&table, sizeof(t_table));
    if (parse_input(argv, argc, &table))
        return (1);
    // init all philos
    if (prepare_table(&table))
        return (1);
    // monitor routine
    print_table(&table);
    init_dinner(&table);
    clean_table(table);
}