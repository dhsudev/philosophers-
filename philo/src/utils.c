/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:09:10 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/03 19:59:45 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>


int ft_error(char *msg, int args_err)
{
    printf("%s", msg);
	if(args_err)
		printf("%s", USAGE_MSG);
    return (1);
}


unsigned long	get_current_time(void)
{
	struct timeval		tmp;
	unsigned long		current_time;

	gettimeofday(&tmp, NULL);
	current_time = (unsigned long)tmp.tv_sec * 1000 + tmp.tv_usec * 0.001;
	return (current_time);
}


unsigned long get_time(t_table *table)
{
	return (get_current_time() - table->t_start);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*rt;

	i = 0;
	rt = (unsigned char *)s;
	while (i < n)
	{
		rt[i] = 0;
		i ++;
	}
}