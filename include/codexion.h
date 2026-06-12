/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:51:08 by npillet           #+#    #+#             */
/*   Updated: 2026/06/12 17:08:46 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define MAX_CODER 300

/* ----------| LIBRARY |---------- */
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* ----------| PARSING |---------- */
int		parsing(int argc, char **argv);

int		args_parsing(int argc, char **argv);
int		time_parsing(char **argv);

int		check_number_of_arguments(int nb);
int		check_number_of_coder(char *coder);
int		check_given_time(char *given_time);
int		check_number_of_compiles(char *compiles);
int		check_scheduler(char *schedule);

/* -----------| CODERS |---------- */

/* -----------| UTILS |----------- */
int		ft_atoi(const char *str);

#endif
