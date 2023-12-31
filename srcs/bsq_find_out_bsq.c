/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_find_out_bsq.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/10 00:34:52 by corvvs           ###   ########.fr       */
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
	const size_t	top = square->top;
	const size_t	left = square->left;

	// 右方向に1マス伸ばせることを確認する
	for (size_t k = 0; k <= square->size; k += 1) {
		if (!is_empty_cell(top + k, left + square->size, map)) {
			return (false);
		}
	}

	// 下方向に1マス伸ばせることを確認する
	for (size_t k = 0; k <= square->size; k += 1) {
		if (!is_empty_cell(top + square->size, left + k, map)) {
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

// フィールド中に作成可能な最大の正方形(bsq; biggest square)を返す
t_square		bsq_find_out_bsq(const t_map* map) {
	t_square	biggest_square = {
		.size = 0,
	};

	for (size_t top = 0; top < map->field_height; top += 1) {
		for (size_t left = 0; left < map->field_width; left += 1) {
			const t_square maximum = get_maximum_square(top, left, map);
			if (biggest_square.size < maximum.size) {
				biggest_square = maximum;
			}
		}
	}

	DEBUGOUT(
		"biggest_square: (%zu, %zu), size: %zu", 
		biggest_square.top, biggest_square.left, biggest_square.size
	);
	return (biggest_square);
}
