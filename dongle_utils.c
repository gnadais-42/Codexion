/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnadais- <gnadais-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:26:43 by gnadais-          #+#    #+#             */
/*   Updated: 2026/05/13 22:15:40 by gnadais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

pthread_mutex_t *create_dongles(int n)
{
	pthread_mutex_t *dongles;

	dongles = malloc(sizeof(pthread_mutex_t) * n);
	if (!dongles)
		return (NULL);

	for (int i = 0; i < n; i++)
		pthread_mutex_init(&dongles[i], NULL);
	return (dongles);
}

void	destroy_dongles(pthread_mutex_t *dongles, int n)
{
	if (!dongles)
		return ;

	for (int i = 0; i < n; i++)
		pthread_mutex_destroy(&dongles[i]);

	free(dongles);
} 
