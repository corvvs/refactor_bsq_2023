/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_get_maximum_square.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 15:33:41 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// 位置 (row, col) に物が置けることを確認する
static bool		is_empty_cell(size_t row, size_t col, const t_map* map) {
	char** const	field = map->field_lines;

	// 横座標(col)がマップ横幅以内であることを確認
	if (col >= map->num_cols) {
		return (false);
	}
	// 縦座標(row)がマップ縦幅以内であることを確認
	if (row >= map->num_rows) {
		return (false);
	}
	// 座標 (top, left) に物が置けることを確認
	if (field[row][col] != map->letter.empty) {
		return (false);
	}
	return (true);
}

// 与えられた正方形 square について, 左上隅を固定したまま size を1増やせるかどうかを返す
static bool		is_extendible_square(const t_square* square, const t_map* map) {
	const size_t	i0 = square->top;
	const size_t	j0 = square->left;

	for (size_t k = 0; k <= square->size; k += 1) {
		// 右方向に1マス伸ばせるかどうか
		if (!is_empty_cell(i0 + k, j0 + square->size, map)) {
			return (false);
		}
		// 下方向に1マス伸ばせるかどうか
		if (!is_empty_cell(i0 + square->size, j0 + k, map)) {
			return (false);
		}
	}
	return (true);
}

// (top, left) を左上隅とする最大の正方形を返す
t_square	bsq_get_maximum_square(size_t top, size_t left, const t_map* map) {
	t_square	square = {
		.top	= top,
		.left	= left,
		.size	= 0,
	};

	if (!is_empty_cell(top, left, map)) {
		return (square);
	}
	for (square.size = 0; is_extendible_square(&square, map);) {
		square.size += 1;
	}
	return (square);
}
