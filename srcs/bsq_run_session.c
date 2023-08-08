/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_run_session.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 19:24:50 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static t_square	find_out_bsq(const t_map* map) {
	t_square	bsq = { .size = 0 };

	for (size_t top = 0; top < map->field_height; top += 1) {
		for (size_t left = 0; left < map->field_width; left += 1) {
			const t_square maximum_square = bsq_get_maximum_square(top, left, map);
			if (bsq.size < maximum_square.size) {
				bsq = maximum_square;
			}
		}
	}

	DEBUGOUT("best_square: (%zu, %zu), size: %zu", bsq.top, bsq.left, bsq.size);
	return (bsq);
}

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

void	bsq_run_session(int ifd) {
	t_map	map;

	if (!bsq_generate_map(ifd, &map)) {
		ft_putstr_fd(STDERR_FILENO, BSQ_ERROR_MESSAGE);
		return ;
	}
	const t_square	best_square = find_out_bsq(&map);
	fill_out_bsq(&map, &best_square);
	print_map(&map);
	bsq_destroy_map(&map);
}
