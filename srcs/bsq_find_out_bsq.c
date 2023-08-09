/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_find_out_bsq.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 12:16:41 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// 位置 (row, col) に物が置けることを確認する
static bool		is_empty_cell(size_t row, size_t col, const t_map* map) {
	char** const	field = map->field_lines;

	// 横座標(col)がマップ横幅以内であることを確認
	if (col >= map->field_width) {
		return (false);
	}
	// 縦座標(row)がマップ縦幅以内であることを確認
	if (row >= map->field_height) {
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
static t_square	get_maximum_square(size_t top, size_t left, const t_map* map) {
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

// フィールド中に作成可能な最大の正方形(bsq; best square)を返す
t_square	bsq_find_out_bsq(const t_map* map) {
	t_square	best_square = {
		.size = 0,
	};

	for (size_t top = 0; top < map->field_height; top += 1) {
		for (size_t left = 0; left < map->field_width; left += 1) {
			const t_square maximum = get_maximum_square(top, left, map);
			if (best_square.size < maximum.size) {
				best_square = maximum;
			}
		}
	}

	DEBUGOUT(
		"best_square: (%zu, %zu), size: %zu", 
		best_square.top, best_square.left, best_square.size
	);
	return (best_square);
}
