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
	t_sim *sim_data;

	if (!validator(argc, argv))
		return (1);
	sim_data = create_simulation(argv);
	if (!sim_data)
			return (2);
	
}

