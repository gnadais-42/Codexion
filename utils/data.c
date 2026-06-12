/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnadais- <gnadais-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:52:53 by gnadais-          #+#    #+#             */
/*   Updated: 2026/05/14 00:19:31 by gnadais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static t_schedule	get_schedule(char *sch);
static char			*get_str_schedule(t_schedule sch);

static t_schedule	get_schedule(char *sch)
{
	if (strcmp(sch, "fifo") == 0)
		return (FIFO);
	else
		return (EDF);
}

static char	*get_str_schedule(t_schedule sch)
{
	if (sch == FIFO)
		return ("fifo");
	else if (sch == EDF)
		return ("edf");
	else
		return (NULL);
}

t_data	create_data(char *argv[])
{
	t_data	data;

	data.n_coders = atoi(argv[1]);
	data.t_burnout = atoi(argv[2]);
	data.t_compile = atoi(argv[3]);
	data.t_debug = atoi(argv[4]);
	data.t_refactor = atoi(argv[5]);
	data.n_compiles = atoi(argv[6]);
	data.d_cooldown = atoi(argv[7]);
	data.schedule = get_schedule(argv[8]);

	return (data);
}


void print_data(t_data data)
{
	printf("Number of coders total: %d\n", data.n_coders);
	printf("Time to burnout: %d ms\n", data.t_burnout);
	printf("Time to compile: %d ms\n", data.t_compile);
	printf("Time to debug: %d ms\n", data.t_debug);
	printf("Time to refactor: %d ms\n", data.t_refactor);
	printf("Required compiles: %d\n", data.n_compiles);
	printf("Dongle cooldown: %d ms\n", data.d_cooldown);
	printf("Scheduling: %s\n", get_str_schedule(data.schedule));
}
