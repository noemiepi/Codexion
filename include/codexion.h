/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:51:08 by npillet           #+#    #+#             */
/*   Updated: 2026/06/16 15:45:14 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define MAX_CODERS 300

# define FIFO "fifo"
# define EDF "edf"

# define FALSE 0
# define TRUE 1

/* ----------| LIBRARY |---------- */
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* ---------| STRUCTURES |-------- */
typedef struct s_dongle
{
	int			id;
	long long	cooldown;
}				t_dongle;

typedef struct s_coder
{
	int			id;
	int			nb_compile;
	long long	burnout_time;
	int			finish;
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;
}				t_coder;

typedef struct s_data
{
	t_coder		*coder;
	t_dongle	*dongle;
	int			nb_coders;
	long long	time_burnout;
	long long	time_compile;
	long long	time_debug;
	long long	time_refactor;
	int			nb_compiles_req;
	long long	dongle_cooldown;
	char		*scheduler;
}				t_data;

/* ----------| PARSING |---------- */
int		parsing(int argc, char **argv, t_data *data);

int		args_parsing(int argc, char **argv, t_data *data);
int		time_parsing(char **argv, t_data *data);

int		check_number_of_arguments(int nb);
int		check_number_of_coder(char *coder, t_data *data);
int		check_given_time(char *given_time);
int		check_number_of_compiles(char *compiles, t_data *data);
int		check_scheduler(char *schedule, t_data *data);

/* -----------| CODERS |---------- */
void	*init_coder(t_data *data);

/* -----------| UTILS |----------- */
int		ft_atoi(const char *str);
void	debug_print_struct(t_data *data);

#endif
