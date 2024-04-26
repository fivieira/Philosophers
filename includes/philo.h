/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:25:57 by fivieira          #+#    #+#             */
/*   Updated: 2024/04/26 13:59:17 by fivieira         ###   ########.fr       */
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
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	Inactive = 5
}	t_state;

struct	s_data;

typedef struct philo
{
	int				id;
	int				meals_had;
	struct s_data	*data;
	t_state			state;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mut_state;
	pthread_mutex_t	mut_meals_had;
	pthread_mutex_t	mut_last_eat_time;
	u_int64_t		last_eat_time;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_meals;
	int				nb_full_p;
	bool			keep_iterating;
	u_int64_t		start_time;
	u_int64_t		die_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_keep_iterate;
	pthread_mutex_t	mut_nb_philos;
	pthread_mutex_t	mut_start_time;
	pthread_mutex_t	mut_die_time;
	pthread_mutex_t	mut_eat_time;
	pthread_mutex_t	mut_sleep_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		*philo_threads;
	pthread_t		monit_all_alive;
	pthread_t		monit_all_full;			
}	t_data;

// check.c
int			check_input(int argc, char **argv);
int			ft_atoi(char *str);
int			wrong_input_check(int argc, char **argv);
void		print_instruction(void);

// init_data.c
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_data *data);
int			init_forks(t_data *data);

// time.c
u_int64_t	get_time(void);
void		ft_usleep(uint64_t sleep_time);
void		wait_until(u_int64_t wakeup_time);

// monitor.c
void		*all_alive_routine(void *data_p);
void		*all_full_routine(void *data_p);

// eat1.c
void		update_last_meal_time(t_philo *philo);
int			eat(t_philo *philo);

// eat2.c
int			take_forks(t_philo *philo);
int			take_right_fork(t_philo *philo);
int			take_left_fork(t_philo *philo);
void		drop_right_fork(t_philo *philo);
void		drop_left_fork(t_philo *philo);

//sleep.c
int			ft_sleep(t_philo *philo);

// routine.c
void		*routine(void *philo);
bool		philo_died(t_philo *philo);

// getters.c
int			get_nb_philos(t_data *data);
t_state		get_philo_state(t_philo *philo);
int			get_nb_meals_philo_had(t_philo *philo);
uint64_t	get_start_time(t_data *data);
bool		get_keep_iter(t_data *data);
uint64_t	get_die_time(t_data *data);
uint64_t	get_eat_time(t_data *data);
uint64_t	get_sleep_time(t_data *data);
uint64_t	get_last_eat_time(t_philo *philo);

// think.c
int			think(t_philo *philo);

// utils.c
void		print_msg(t_data *data, int id, char *msg);
bool		nb_meals_option(t_data *data);
void		free_data(t_data *data);
int			handle_1_philo(t_philo *philo);
void		print_mut(t_data *data, char *msg);

// setters.c
void		set_philo_state(t_philo *philo, t_state state);
void		set_keep_iterating(t_data *data, bool set_to);

#endif