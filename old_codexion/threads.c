/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnadais- <gnadais-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:22:16 by gnadais-          #+#    #+#             */
/*   Updated: 2026/05/17 19:16:27 by gnadais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

pthread_t	*create_threads(t_coder *coders, int n, void *(*routine)(void *), t_sim *sim)
{
	pthread_t	*threads;
	int			i;

	if (!coders)
		return (NULL);
	threads = malloc(sizeof(pthread_t) * n);
	if (!threads)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (pthread_create(&threads[i], NULL, routine, (void*) &coders[i]) != 0)
			return (threads);
		sim->thread_count++;
		i++;
	}
	return (threads);
}

void	destroy_threads(pthread_t *threads)
{
	free(threads);
}

void	join_threads(pthread_t *threads, int n)
{
	int	i;

	if (!threads)
		return ;

	i = 0;
	while (i < n)
		pthread_join(threads[i++], NULL);
}
