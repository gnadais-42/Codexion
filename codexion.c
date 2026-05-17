/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnadais- <gnadais-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:20:53 by gnadais-          #+#    #+#             */
/*   Updated: 2026/05/17 19:44:47 by gnadais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void destroy_everything(t_coder *coders, pthread_mutex_t *dongles, t_data *data, pthread_t *threads, int n)
{
	destroy_threads(threads);
	destroy_coders(coders);
	destroy_dongles(dongles, n);
	destroy_data(data);
}

int main(int argc, char* argv[])
{
	t_coder		*coders;
	pthread_mutex_t	*dongles;
	pthread_t	*threads;
	pthread_t	monitor;
	t_data		*data;

	if (!validator(argc, argv))
		return (1);
	data = create_data(argv);
	if (!data)
		return (2);
	dongles = create_dongles(data->n_coders);
	coders = create_coders(dongles, data, data->n_coders);
	threads = create_threads(coders, data->n_coders, coder_routine);
	pthread_create(&monitor, NULL, monitor_routine, (void *) coders); // Não esquecer de meter aqui a verificação de se actually criou a thread.
	if (!dongles || !coders || !threads)
	{
		destroy_everything(coders, dongles, data, threads, data->n_coders);
		return (3);
	}
	pthread_join(monitor, NULL);
	join_threads(threads, data->n);
	destroy_everything(coders, dongles, data, threads, data->n_coders);
} // Dados estão muito espalhados, Cria uma struct geral para centralizar tudo e mete cada coder a guardar essa struct.

