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

t_dongle	*create_dongles(int n)
{
	t_dongle	*dongles;
	int			i;

	dongles = malloc(sizeof(t_dongle) * n);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < n){
		pthread_mutex_init(&(dongles[i].mutex), NULL);
		pthread_cond_init(&(dongles[i].cond), NULL);
		dongles[i].available_at = 0;
		i++;
	}
	return (dongles);
}

void	destroy_dongles(t_dongle *dongles, int n)
{
	int	i;
	if (!dongles)
		return ;

	i = 0;
	while (i < n){
		pthread_mutex_destroy(&(dongles[i].mutex));
		pthread_cond_destroy(&(dongles[i].cond));
		i++;
	}

	free(dongles);
} 
