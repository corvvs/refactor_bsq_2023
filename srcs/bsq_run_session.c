/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_run_session.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/10 00:34:52 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static void	fill_out_bsq(t_map* map, const t_square* bsq) {
	char**	field = map->field_lines;

	for (size_t i = 0; i < bsq->size; i += 1) {
		for (size_t j = 0; j < bsq->size; j += 1) {
			field[bsq->top + i][bsq->left + j] = map->letter.full;
		}
	}
}

static void	print_map(const t_map* map) {
	char** const	field = map->field_lines;

	for (size_t i = 0; i < map->field_height; i += 1) {
		ft_putnstr_fd(STDOUT_FILENO, field[i], map->field_width);
		ft_putnstr_fd(STDOUT_FILENO, "\n", 1);
	}
}

// 与えられた fd に対してBSQセッションを実行する
bool	bsq_run_session(int ifd) {
	t_map	map;
	if (!bsq_generate_map(ifd, &map)) {
		return (false);
	}

	const t_square	biggest_square = bsq_find_out_bsq(&map);
	if (biggest_square.size == 0) {
		DEBUGERR("%s", "no square found");
		bsq_destroy_map(&map);
		return (false);
	}

	fill_out_bsq(&map, &biggest_square);
	print_map(&map);
	bsq_destroy_map(&map);
	return (true);
}
