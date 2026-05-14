/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnadais- <gnadais-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:20:53 by gnadais-          #+#    #+#             */
/*   Updated: 2026/05/14 00:16:52 by gnadais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void destroy_everything(t_coder *coders, pthread_mutex_t *dongles, t_data *data, int n)
{
	destroy_coders(coders);
	destroy_dongles(dongles, n);
	destroy_data(data);
}

int main(int argc, char* argv[]){
	t_coder	*coders;
	pthread_mutex_t	*dongles;
	t_data *data;

	if (!validator(argc, argv))
		return (1);
	data = create_data(argv);
	if (!data)
		return (2);
	dongles = create_dongles(data->n_coders);
	coders = create_coders(dongles, data, data->n_coders);
	if (!dongles || !coders)
	{
		destroy_everything(coders, dongles, data, data->n_coders);
		return (3);
	}
	for (int i = 0; i < data->n_coders; i++){
		print_coder(coders[i]);
	}

	destroy_everything(coders, dongles, data, data->n_coders);
}

