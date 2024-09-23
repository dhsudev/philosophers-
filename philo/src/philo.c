/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:59:07 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/09/23 13:28:19 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int wrong_arguments(int argc, char **argv, int data[])
{
	int atoi_flag;
	int i;
	
	if(argc != 4 || argc != 5)
		return (1);
	while(argv[i++])
	{
		
		if()
	}
}

int main (int argc, char **argv)
{
	int	arguments[argc];
	if(wrong_arguments(argc, argv, arguments))
		printf("{error message}\n");
	else 
	{
		printf("Philo init\n");
	}
}
