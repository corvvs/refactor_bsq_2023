/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makesquare2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 22:17:54 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// カーソル位置で定義される正方形の右辺および下辺がすべて空白であることを確認する
static int		square_is_extendible(const t_square* square, const t_map *p_info) {
	const size_t	i0 = square->top;
	const size_t	j0 = square->left;
	for (size_t k = 0; k < square->size; k += 1) {
		if (cell_is_open(i0 + k, j0 + square->size, p_info) == 0) {
			return (0);
		}
		if (cell_is_open(i0 + square->size, j0 + k, p_info) == 0) {
			return (0);
		}
	}
	return (1);
}

// カーソル位置で定義される正方形を可能な限り拡大する
static t_square get_maximum_square(size_t top, size_t left, const t_map *p_info) {
	t_square	square = { .top = top, .left = left, .size = 0 };
	for (square.size = 0; square_is_extendible(&square, p_info); square.size += 1);
	return (square);
}

static t_square	find_bsq(t_map *map) {
	t_square	bsq = { .size = 0 };
	const size_t	map_width = get_map_width(map->field_lines);
	// すべてのセルについて, そのセルを左上隅とする正方形の最大サイズを調べる
	for (size_t top = 0; top < map->num_rows; top += 1) {
		for (size_t left = 0; left < map_width; left += 1) {
			if (cell_is_open(top, left, map)) {
				const t_square maximum_square = get_maximum_square(top, left, map);
				if (bsq.size < maximum_square.size) {
					bsq = maximum_square;
				}
			}
		}
	}
	return (bsq);
}
// マップデータを求めた bsq に従って変更する
static void	paint_bsq(t_map *p_info, const t_square* bsq) {
	char	**map = p_info->field_lines;
	for (size_t i = 0; i < bsq->size; i += 1) {
		for (size_t j = 0; j < bsq->size; j += 1) {
			map[bsq->top + i][bsq->left + j] = p_info->full;
		}
	}
}

static void	print_map(const t_map *p_info) {
	char** const	map = p_info->field_lines;
	const size_t	map_width = get_map_width(map);

	for (size_t i = 0; i < p_info->num_rows; i += 1) {
		for (size_t j = 0; j < map_width; j += 1) {
			write(1, &map[i][j], 1);
		}
		write(1, "\n", 1);
	}
}

// bsq = best square を探索する
void	run_bsq(t_map *map) {
	const t_square	bsq = find_bsq(map);
	paint_bsq(map, &bsq);
	print_map(map);
}
