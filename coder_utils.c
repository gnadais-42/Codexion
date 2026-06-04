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

t_coder	*create_coders(t_dongle *dongles, int n){
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
		if (i == n - 1)
			coders[i].r_dongle = &dongles[0];
		else
			coders[i].r_dongle = &dongles[i + 1];
		coders[i].n_compiled = 0;
		coders[i].last_compiled = 0;
		coders[i].sim_data = NULL;
		i++;
	}
	return (coders);
}

void	destroy_coders(t_coder *coders){
	if (!coders)
		return ;
	free(coders);
}

void print_coder(t_coder coder)
{
	printf("Coder id: %d\n", coder.id);
	printf("Left dongle: %p\n", coder.l_dongle);
	printf("Right dongle: %p\n", coder.r_dongle);
	printf("Times compiled: %d\n", coder.n_compiled);
}
