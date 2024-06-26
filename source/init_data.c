/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:06:20 by fivieira          #+#    #+#             */
/*   Updated: 2024/04/26 12:47:22 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_forks(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->philos;
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	philo[0].left_f = &data->forks[0];
	philo[0].right_f = &data->forks[data->nb_philo - 1];
	while (++i < data->nb_philo)
	{
		philo[i].left_f = &data->forks[i];
		philo[i].right_f = &data->forks[i - 1];
	}
	return (0);
}

int	init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = data->philos;
	while (++i < data->nb_philo)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].meals_had = 0;
		philos[i].state = Inactive;
		pthread_mutex_init(&philos[i].mut_state, NULL);
		pthread_mutex_init(&philos[i].mut_meals_had, NULL);
		pthread_mutex_init(&philos[i].mut_last_eat_time, NULL);
		update_last_meal_time(&philos[i]);
	}
	return (0);
}

int	malloc_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (data->philos == NULL)
		return (ERROR_MALLOC);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (data->forks == NULL)
		return (free(data->philos), ERROR_MALLOC);
	data->philo_threads = malloc(sizeof(pthread_t) * data->nb_philo);
	if (data->philo_threads == NULL)
	{
		return (free(data->philos), free(data->forks), ERROR_MALLOC);
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_full_p = 0;
	data->keep_iterating = true;
	data->nb_philo = ft_atoi(argv[1]);
	data->die_time = (u_int64_t) ft_atoi(argv[2]);
	data->eat_time = (u_int64_t) ft_atoi(argv[3]);
	data->sleep_time = (u_int64_t) ft_atoi(argv[4]);
	data->nb_meals = -1;
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	pthread_mutex_init(&data->mut_eat_time, NULL);
	pthread_mutex_init(&data->mut_sleep_time, NULL);
	pthread_mutex_init(&data->mut_die_time, NULL);
	pthread_mutex_init(&data->mut_print, NULL);
	pthread_mutex_init(&data->mut_nb_philos, NULL);
	pthread_mutex_init(&data->mut_keep_iterate, NULL);
	pthread_mutex_init(&data->mut_start_time, NULL);
	return (malloc_data(data));
}
