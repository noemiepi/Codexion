/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:51:08 by npillet           #+#    #+#             */
/*   Updated: 2026/08/06 11:58:50 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define MAX_CODERS 300

# define FIFO "fifo"
# define EDF "edf"

# define ADD 1
# define REMOVE 2

# define DONGLE_TAKEN "%lld: coder %d has taken a dongle\n"
# define COMPILING "%lld: coder %d is compiling\n"
# define DEBUGGING "%lld: coder %d is debugging\n"
# define REFACTORING "%lld: coder %d is refactoring\n\n"
# define BURNOUT "\n\e[1;31m%lld: coder %d burned out\e[0m\n\n"
# define END "\e[1;32mEvery coders met their quota!\e[0m\n\n"

/* ----------| LIBRARY |---------- */
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

/* ---------| STRUCTURES |-------- */
typedef struct s_data		t_data;
typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;

typedef struct s_queue		t_queue;
typedef struct s_heap		t_heap;
typedef struct s_fifo		t_fifo;
typedef struct s_edf		t_edf;

typedef struct s_dongle
{
	int				id;
	long long		cooldown;

	pthread_mutex_t	mutex_dongle;
}					t_dongle;

typedef struct s_coder
{
	t_data			*data;

	int				id;
	int				nb_compile;
	long long		burnout_time;
	bool			finish;
	bool			has_dongle;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;

	pthread_t		thread_id;
	pthread_mutex_t	mutex_burnout;
}					t_coder;

typedef struct s_data
{
	t_coder			*coder;
	t_dongle		*dongle;
	t_queue			*queue;
	t_heap			*heap;

	int				nb_coders;
	long long		time_burnout;
	long long		time_compile;
	long long		time_debug;
	long long		time_refactor;
	int				nb_compiles_req;
	long long		dongle_cooldown;
	char			*scheduler;

	long long		start_sim;
	bool			active_sim;
	pthread_t		monitoring_id;

	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_sim;
}					t_data;

typedef struct s_queue
{
	t_fifo			*front;
	t_fifo			*rear;

	pthread_mutex_t	mutex_queue;
	pthread_cond_t	cond_queue;
}					t_queue;

typedef struct s_heap
{
	t_edf			*node;
	int				size;

	pthread_mutex_t	mutex_heap;
	pthread_cond_t	cond_heap;
}					t_heap;

typedef struct s_fifo
{
	t_coder			*coder;
	t_fifo			*next;
}					t_fifo;

typedef struct s_edf
{
	t_coder			*coder;
	long long		deadline;
}					t_edf;

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
void		terminal_logs(t_data *data, t_coder *coder);

bool		take_dongle(t_data *data, t_coder *coder);
void		release_dongle(t_data *data, t_coder *coder);

void		create_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);
void		create_threads(t_data *data);
void		join_threads(t_data *data);

/* ---------| SCHEDULERS |-------- */
void		scheduler_fifo(t_queue *queue, t_coder *coder, int step);
void		scheduler_edf(t_heap *heap, t_coder *coder);

/* -----------| UTILS |----------- */
int			ft_atoi(const char *str);

long long	get_time(void);
long long	get_current_time(t_data *data);
bool		get_active_sim(t_data *data);
bool		get_finished(t_coder *coder);

void		free_structures(t_data *data);

void		debug_print_struct(t_data *data);
void		debug_print_queue(t_queue *manager);
void		debug_print_heap(t_heap *heap);

#endif
