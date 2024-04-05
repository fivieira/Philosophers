/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:25:57 by fivieira          #+#    #+#             */
/*   Updated: 2024/04/05 16:49:01 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdint.h>
# include <string.h>

# define WRONG_INPUT 1
# define ERROR_MALLOC 2

# define TAKE_FORKS "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIED "died"

typedef enum philo_state
{
	EATING = 0,
	SLEEPING = 0,
	THINKING = 0,
	DEAD = 3,
	FULL = 4,
	Inactive = 5
}	t_state;

struct s_data;

typedef struct philo
{
	int	id;
	int meals_had;
	struct s_data *data;
	t_state	state;
	pthread_mutex_t *left_f;
	pthread_mutex_t *right_f;
	pthread_mutex_t *mut_state;
	pthread_mutex_t *mut_meals_had;
	pthread_mutex_t *mut_last_eat_time;
	u_int64_t last_eat_time;
} t_philo;









#endif