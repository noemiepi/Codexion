/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:51:08 by npillet           #+#    #+#             */
/*   Updated: 2026/06/19 19:38:08 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define MAX_CODERS 300

# define FIFO "fifo"
# define EDF "edf"

# define DONGLE_TAKEN "%lld, coder %d has taken a dongle\n"
# define COMPILING "%lld, coder %d is compiling\n"
# define DEBUGGING "%lld, coder %d is debugging\n"
# define REFRACTORING "%lld, coder %d is refactoring\n"
# define BURNOUT "%lld, coder %d burned out\n"

/* ----------| LIBRARY |---------- */
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

/* ---------| STRUCTURES |-------- */
typedef struct s_dongle
{
	int				id;
	long long		cooldown;
	pthread_mutex_t	mutex_dongle;
}					t_dongle;

typedef struct s_coder
{
	int				id;
	int				nb_compile;
	long long		burnout_time;
	bool			finish;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_t		thread_id;
}					t_coder;

typedef struct s_simul
{
	long long		start_simul;
}					t_simul;

typedef struct s_data
{
	int				nb_coders;
	long long		time_burnout;
	long long		time_compile;
	long long		time_debug;
	long long		time_refactor;
	int				nb_compiles_req;
	long long		dongle_cooldown;
	char			*scheduler;
	t_coder			*coder;
	t_dongle		*dongle;
	t_simul			*simulation;
	pthread_t		monitoring_id;
	pthread_mutex_t	mutex_print;
}					t_data;

/* ----------| PARSING |---------- */
bool		parsing(int argc, char **argv, t_data *data);

bool		check_number_of_arguments(int nb);
bool		check_number_of_coder(char *coder, t_data *data);
bool		check_given_time(char *given_time);
bool		check_number_of_compiles(char *compiles, t_data *data);
bool		check_scheduler(char *schedule, t_data *data);

/* -----------| CODERS |---------- */
void		*init_structures(t_data *data);
void		*monitor(void *arg);
void		*coders_action(void *arg);
void		create_mutexes(t_data *data);
void		create_threads(t_data *data);
void		join_threads(t_data *data);

/* -----------| UTILS |----------- */
int			ft_atoi(const char *str);
long long	get_time(void);
void		free_structures(t_data *data);
void		terminal_logs(t_data *data);
void		debug_print_struct(t_data *data);

#endif
