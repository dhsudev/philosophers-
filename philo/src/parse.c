/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:33:31 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/03 19:20:41 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <philo.h>

/*
 *  atol, i need it to check eventual overflows
 *  converting every string into a long value
 */
long	ft_atol(char *str)
{
	long	n;
	int		sign;
	int		i;

	n = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

int	not_valid_chars(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r'
			|| s[i] == '\v' || s[i] == '\f'))
		i++;
	if (s[i] == '+')
	{
		i++;
		if (s[i] == '\0')
			return (1);
	}
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	return (0);
}
void  init_data(long n, int i, t_table *table)
{
    if(i == 1)
        table->n_philos = n;
    else if(i == 2)
        table->t_die = n;
    else if(i == 3)
        table->t_eat = n;
    else if(i == 4)
        table->t_sleep = n;
    else if(i == 5)
        table->n_meals = n;
        
}

int	parse_input(char **args, int argc, t_table *table)
{
	int		i;
	long	n;

	i = 1;
    table->n_meals = -1;
	if(argc < 5 || argc > 6)
        return(ft_error(ERROR WRONG_NARGS, 1));
	while (i < argc)
	{
		if (not_valid_chars(args[i]))
			return(ft_error(ERROR CHARS, 1));
		n = ft_atol(args[i]);
		if (n > INT_MAX || n < INT_MIN)
			return(ft_error(ERROR LIMITS, 1));
		init_data(n, i, table);
        i++;
	}
	return (0);
}