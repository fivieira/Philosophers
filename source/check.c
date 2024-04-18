/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:46:16 by fivieira          #+#    #+#             */
/*   Updated: 2024/04/18 18:32:46 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_instruction(void)
{
	printf("\t\tWRONG INPUT!\n\n");
	printf("./philo nb_philos time_to_die ");
	printf("time_to_eat time_to_sleep ");
	printf("number_of_times_each_philosopher_must_eat ");
	printf("(optional argument)\n");
	printf("Example:\n\n");
	printf("./philo 4 800 200 200 5\n\n");
	printf("nb_philos: 1-200\n");
	printf("time_to_die: 60+\n");
	printf("time_to_eat: 60+\n");
	printf("time_to_sleep: 60+\n");
	printf("number_of_times_each_philosopher_must_eat: ");
	printf("0+\n");
}

int wrong_input_check(int argc, char **argv)
{
	int i;
	
	i = 1;
	if(argc == 6 && ft_atoi(argv[5]) < 0)
		return (WRONG_INPUT);
	if(ft_atoi(argv[1]) < 2 || ft_atoi(argv[1]) > 200)
		return (WRONG_INPUT);
	while (++i < 5)
	{
		if(ft_atoi(argv[i]) < 60)
			return (WRONG_INPUT);
	}
	return (0);
}

int ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int is_input_digit(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while(i < argc)
	{
		j = 0;
		while(argv[i][j])
		{
			if(argv[i][j] < '0' || argv[i][j] > '9')
				return (WRONG_INPUT);
			j++;
		}
		i++;
	}
	return (0);
}

int check_input(int argc, char **argv)
{
	if(argc < 5)
		return (WRONG_INPUT);
	if(argc > 6)
		return (WRONG_INPUT);
	if(is_input_digit(argc, argv))
		return (WRONG_INPUT);
	if(wrong_input_check(argc, argv))
		return (WRONG_INPUT);
	return (0);	
}