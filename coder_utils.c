/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnadais- <gnadais-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:09:51 by gnadais-          #+#    #+#             */
/*   Updated: 2026/05/12 20:11:36 by gnadais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*create_coders(pthread_mutex_t *dongles, int n){
	t_coder	*coders;

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
	}
}

void	destroy_coders(t_coder *coders){
	free(coders);
}
