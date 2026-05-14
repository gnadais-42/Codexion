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

t_coder	*create_coders(pthread_mutex_t *dongles, t_data *data, int n){
	t_coder	*coders;

	if (!dongles || !data)
		return (NULL);

	coders = malloc(sizeof(t_coder) * n);
	if (!coders)
		return (NULL);

	for (int i = 0; i < n; i++){
		coders[i].id = i + 1;
		coders[i].l_dongle = &dongles[i];
		if (i == n - 1)
			coders[i].r_dongle = &dongles[0];
		else
			coders[i].r_dongle = &dongles[i + 1];
		coders[i].n_compiled = 0;
		coders[i].data = data;
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
	print_data(*(coder.data));
}
