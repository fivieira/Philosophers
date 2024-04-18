/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:01:47 by fivieira          #+#    #+#             */
/*   Updated: 2024/04/18 19:06:46 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	run_threads(t_data *data)
{
	int i;
	int nb_of_philos;

	nb_of_philos = get_nb_philos(data);
	i = -1;
	data->start_time = get_time();
	while (++i < nb_of_philos)
	{
		if(pthread_create(&data->philos[i], NULL,
			 &routine, &data->philos[i]))
			return (1);
	}
	
}

int philosopher(int argc, char **argv)
{
	t_data	data;
	
	if(init_data(&data, argc, argv) != 0)
		return (ERROR_MALLOC);
	init_philos(&data);
	init_forks(&data);
}

int	main(int argc, char **argv)
{
	if(check_input(argc, argv) != 0)
	{
		print_instruction();
		return (WRONG_INPUT);
	}
	
	return (0);
}