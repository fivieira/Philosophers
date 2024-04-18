/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:06:20 by fivieira          #+#    #+#             */
/*   Updated: 2024/04/18 18:32:32 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_forks(t_data *data)
{
	int	i;
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
	t_philo	*philo;
	int		i;
	
	i = -1;
	philo = data->philos;
	while (++i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].meals_had = 0;
		philo[i].state = Inactive;
		pthread_mutex_init(&philo[i].mut_state, NULL);
		pthread_mutex_init(&philo[i].mut_meals_had, NULL);
		pthread_mutex_init(&philo[i].mut_last_eat_time, NULL);
		update_last_meal_time(&philo[i]);
	}
	
}

int	malloc_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (data->philos == NULL)
		return (ERROR_MALLOC);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (data->forks == NULL)
	{
		free(data->philos);
		return (ERROR_MALLOC);
	}
	if(data->philo_threads == NULL)
	{
		free(data->philos);
		free(data->forks);
		return (ERROR_MALLOC);
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_full_p = 0;
	data->keep_iterating = true;
	data->nb_philo = ft_atoi(argv[1]);
	data->mut_die_time = (u_int64_t) ft_atoi(argv[2]);
	data->mut_eat_time = (u_int64_t) ft_atoi(argv[3]);
	data->mut_sleep_time = (u_int64_t) ft_atoi(argv[4]);
	data->nb_meals = -1;
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	pthread_mutex_init(&data->mut_eat_t, NULL);
	pthread_mutex_init(&data->mut_sleep_t, NULL);
	pthread_mutex_init(&data->mut_die_t, NULL);
	pthread_mutex_init(&data->mut_print, NULL);
	pthread_mutex_init(&data->mut_nb_philos, NULL);
	pthread_mutex_init(&data->mut_keep_iter, NULL);
	pthread_mutex_init(&data->mut_start_time, NULL);
	return (malloc_data(data));
}