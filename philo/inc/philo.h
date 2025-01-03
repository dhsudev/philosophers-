/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:58:40 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/03 20:02:22 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# define ERROR RED "Error: "
# define WRONG_NARGS "wrong number of arguments\n" RESET
# define WRONG_ARG "wrong argument\n" RESET
# define LIMITS "number outside int limits\n" RESET
# define CHARS "not valid chars found in input\n" RESET
# define CHARS "not valid chars found in input\n" RESET
# define WRONG_MALLOC "malloc failed\n" RESET
# define WRONG_MUTEX "mutex failed\n" RESET
# define WRONG_THREAD "creation of a thread failed\n" RESET


#define USAGE_MSG "[USAGE] \n" CYAN "./philo " BLUE \
    "n_philos time_to_die time_to_eat time_to_sleep " YELLOW "[times_to_eat]\n" RESET

# define INT_MAX 2147483647
# define INT_MIN -2147483648

enum e_actions
{
    EAT,
    SLEEP,
    THINK,
    FORK,
    DEAD,
    DEBUG // DELETEEEE
};

typedef struct s_fork
{
    int id;
    pthread_mutex_t mutex;
} t_fork;

typedef struct s_philo
{
    pthread_t thread;
    pthread_mutex_t read;
    int id;
    int n_meals;
    long last_meal;
    struct s_table *table;
    t_fork *first_f;
    t_fork *second_f;
} t_philo;

typedef struct s_table
{
    pthread_mutex_t print;
    pthread_mutex_t read;
    t_philo* philos;
    t_fork*  forks;
    long n_philos;
    unsigned long t_die;
    long t_eat;
    long t_sleep;
    long n_meals; // -1 if no limit
    unsigned long t_start;
    int end_dinner;
} t_table;


int	parse_input(char **args, int argc, t_table *table);
void *start_routine(void *data);
void comunicate(int action, int id, t_table *table);
void	ft_bzero(void *s, size_t n);
unsigned long get_time(t_table *table);
unsigned long	get_current_time(void);
int ft_error(char *msg, int args_err);

#endif