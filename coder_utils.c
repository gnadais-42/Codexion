/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnadais- <gnadais-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:09:51 by gnadais-          #+#    #+#             */
/*   Updated: 2026/05/14 00:10:44 by gnadais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*create_coders(t_dongle *dongles, int n, t_sim *sim)
{
	t_coder	*coders;
	int		i;

	if (!dongles)
		return (NULL);

	coders = malloc(sizeof(t_coder) * n);
	if (!coders)
		return (NULL);

	i = 0;
	while (i < n){
		coders[i].id = i + 1;
		coders[i].l_dongle = &dongles[i];
		coders[i].r_dongle = &dongles[(i + 1) % n];
		pthread_mutex_init(&(coders[i].state_mutex), NULL);
		coders[i].sim_data = sim;
		coders[i].last_compiled = sim->start_time;
		coders[i].n_compiled = 0;
		i++;
	}
	return (coders);
}

void	destroy_coders(t_coder *coders, int n){
	int	i;

	if (!coders)
		return ;
	i = 0;
	while (i < n)
		pthread_mutex_destroy(&(coders[i++].state_mutex));
	free(coders);
}

void print_coder(t_coder coder)
{
	printf("Coder id: %d\n", coder.id);
	printf("Left dongle: %p\n", coder.l_dongle);
	printf("Right dongle: %p\n", coder.r_dongle);
	printf("Times compiled: %d\n", coder.n_compiled);
}
