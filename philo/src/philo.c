/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:31:18 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/03 20:25:39 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int contiue_dinner(t_table *table)
{
    int continue_eating;

    continue_eating = 1;
    pthread_mutex_lock(&table->read);
    if(table->end_dinner == 1)
        continue_eating = 0;
    pthread_mutex_unlock(&table->read);
    return (continue_eating);
}

void comunicate(int action, int id, t_table *table)
{
    if(!contiue_dinner(table))
        return;
    pthread_mutex_lock(&table->print);
    if(!contiue_dinner(table))
        return;
    if (action == EAT)
        printf(GREEN "[%lu] %d is eating" RESET "\n" , get_time(table), id);
    else if (action == SLEEP)
        printf(BLUE "[%lu] %d is sleeping" RESET "\n" , get_time(table), id);
    else if (action == THINK)
        printf(CYAN "[%lu] %d is thinking" RESET "\n" , get_time(table), id);
    else if (action == FORK)
        printf(YELLOW "[%lu] %d has taken a fork %d" RESET "\n", get_time(table), id, table->philos[id - 1].first_f->id);
    else if(action == DEAD)
        printf(RED "[%lu] %d is dead" RESET "\n", get_time(table), id);
    //else if (action == DEBUG)
    //    printf(MAGENTA "[%lu] %d is dropping forks" RESET "\n", get_time(table), id);
    pthread_mutex_unlock(&table->print);
}

void philo_eat(t_philo *philo)
{
    // take fork
    pthread_mutex_lock(&philo->first_f->mutex);
    comunicate(FORK, philo->id, philo->table);
    // take 2nd fork
    pthread_mutex_lock(&philo->second_f->mutex);
    comunicate(FORK, philo->id, philo->table);
    // eat
    comunicate(EAT, philo->id, philo->table);
    usleep(philo->table->t_eat * 1000);
    philo->last_meal = get_time(philo->table);
    // release forks

    pthread_mutex_unlock(&philo->first_f->mutex);
    pthread_mutex_unlock(&philo->second_f->mutex);
    
    //comunicate(DEBUG, philo->id, philo->table);
    philo->n_meals++;
}

void philo_sleep(t_philo *philo)
{
    comunicate(SLEEP, philo->id, philo->table);
    usleep(philo->table->t_sleep * 1000);
}

void philo_think(t_philo *philo)
{
    comunicate(THINK, philo->id, philo->table);
}

void *start_routine(void *data)
{
    t_philo *philo = (t_philo *)data;
    // wait for all philos to be ready
    pthread_mutex_lock(&philo->table->read);
    pthread_mutex_unlock(&philo->table->read);
    // Init loop
    while(contiue_dinner(philo->table))
    {
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}