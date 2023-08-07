/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 22:58:12 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// 位置 (row, col) に物が置けることを確認する
static bool		is_empty_cell(size_t row, size_t col, const t_map *p_info)
{
	char**	map = p_info->field_lines;
	// 横座標(col)がマップ横幅以内であることを確認
	if (col >= p_info->num_cols) {
		return (false);
	}
	// 縦座標(row)がマップ縦幅以内であることを確認
	if (row >= p_info->num_rows) {
		return (false);
	}
	// 座標 (top, left) に物が置けることを確認
	// NOTE: 条件 == '\0 はいらなくない??
	if (map[row][col] == p_info->obstacle) {
		return (false);
	}
	return (true);
}

// カーソル位置で定義される正方形の右辺および下辺がすべて空白であることを確認する
static bool		is_extendible_square(const t_square* square, const t_map *p_info) {
	const size_t	i0 = square->top;
	const size_t	j0 = square->left;
	for (size_t k = 0; k < square->size; k += 1) {
		if (is_empty_cell(i0 + k, j0 + square->size, p_info) == 0) {
			return (false);
		}
		if (is_empty_cell(i0 + square->size, j0 + k, p_info) == 0) {
			return (false);
		}
	}
	return (true);
}

// カーソル位置で定義される正方形を可能な限り拡大する
static t_square	get_maximum_square(size_t top, size_t left, const t_map *p_info) {
	t_square	square = { .top = top, .left = left };
	for (square.size = 0; is_extendible_square(&square, p_info); square.size += 1);
	return (square);
}

static t_square	find_bsq(t_map *map) {
	t_square	bsq = { .size = 0 };
	// すべてのセルについて, そのセルを左上隅とする正方形の最大サイズを調べる
	for (size_t top = 0; top < map->num_rows; top += 1) {
		for (size_t left = 0; left < map->num_cols; left += 1) {
			if (is_empty_cell(top, left, map)) {
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
static void	paint_bsq(t_map *map, const t_square* bsq) {
	char**	field = map->field_lines;

	for (size_t i = 0; i < bsq->size; i += 1) {
		for (size_t j = 0; j < bsq->size; j += 1) {
			field[bsq->top + i][bsq->left + j] = map->full;
		}
	}
}

static void	print_map(const t_map* map) {
	char** const	field = map->field_lines;

	for (size_t i = 0; i < map->num_rows; i += 1) {
		write(STDOUT_FILENO, field[i], map->num_cols);
		write(STDOUT_FILENO, "\n", 1);
	}
}

// bsq = best square を探索する
void	solve_bsq(t_map *map) {
	const t_square	bsq = find_bsq(map);
	paint_bsq(map, &bsq);
	print_map(map);
}
