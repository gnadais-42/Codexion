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

pthread_t	*create_threads(t_coder *coders, int n, void *(*routine)(void *))
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * n);
	if (!threads)
		return (NULL);

	for (int i = 0; i < n; i++)
	{
		if (pthread_create(&threads[i], NULL, routine, (void*) &coders[i]) != 0)
		{
			destroy_threads(threads);
			return (NULL);
		}
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

	i = 0;
	while (i < n)
		pthread_join(threads[i++], NULL);
}
