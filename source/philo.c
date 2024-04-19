/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:01:47 by fivieira          #+#    #+#             */
/*   Updated: 2024/04/19 12:54:48 by fivieira         ###   ########.fr       */
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
	if(pthread_create(&data->monit_all_alive, NULL,
		 &all_alive_routine, data))
		return (1);
	if(nb_meals_option(data) == true
		&& pthread_create(&data->monit_all_full, NULL,
		 &all_full_routine, data))
		return (1);
	return (0);	
	
}

int	join_threads(t_data *data)
{
	int i;
	int nb_of_philos;

	nb_of_philos = get_nb_philos(data);
	i = -1;

	if(pthread_join(data->monit_all_alive, NULL))
		return (1);
	if(nb_meals_option(data) == true
		&& pthread_join(data->monit_all_full, NULL))
		return (1);
	while (++i < nb_of_philos)
	{
		if(pthread_join(data->philo_threads[i], NULL))
			return (1);
	}
	return (0);

}

int philosopher(int argc, char **argv)
{
	t_data	data;
	
	if(init_data(&data, argc, argv) != 0)
		return (ERROR_MALLOC);
	init_philos(&data);
	init_forks(&data);
	run_threads(&data);
	join_threads(&data);
	free_data(&data);
	return (0);
}

int	main(int argc, char **argv)
{
	if(check_input(argc, argv) != 0)
	{
		print_instruction();
		return (WRONG_INPUT);
	}
	if(philosopher(argc, argv) != 0)
	{
		return (ERROR_MALLOC);
	}
	return (0);
}