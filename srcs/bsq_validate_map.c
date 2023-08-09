/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_validate_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:16:55 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/09 21:16:56 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static bool		is_expected_field_height(const t_map *map) {
	char** const	field = map->field_lines;
	size_t			actual_height;
	for (actual_height = 0; field[actual_height] != NULL;) {
		actual_height += 1;
	}
	if (actual_height != map->field_height) {
		DEBUGERR(
			"unexpected row number: expected: %zu actual: %zu",
			map->field_height, actual_height
		);
		return (false);
	}
	return (true);
}

static bool		is_valid_map_shape(const t_map *map) {
	char** const	field = map->field_lines;

	if (map->field_width == 0) {
		DEBUGERR("width is zero: %zu", map->field_width);
		return (false);
	}

	for (size_t row = 0; row < map->field_height; row += 1) {
		const size_t	row_size = ft_strlen(field[row]);
		if (row_size != map->field_width) {
			DEBUGERR("invalid row size: %zu at line %zu", row_size, row);
			return (false);
		}
	}
	return (true);
}

static bool		are_valid_cell_letters(const t_map *map) {
	char** const	field = map->field_lines;

	for (size_t row = 0; row < map->field_height; row += 1) {
		for (size_t col = 0; col < map->field_width; col += 1) {
			const char	letter = field[row][col];
			if (letter != map->letter.empty && letter != map->letter.obstacle) {
				DEBUGERR("invalid cell letter: %c at (%zu, %zu)", letter, row, col);
				return (false);
			}
		}
	}
	return (true);
}

// マップ構造体の内容が正しいかどうかを確認する
bool		bsq_validate_map(const t_map *map) {
	// フィールドの行数がヘッダの定義と一致することを確認する
	if (!is_expected_field_height(map)) {
		return (false);
	}

	// フィールドの形状が想定通りの長方形であることを確認する
	if (!is_valid_map_shape(map)) {
		return (false);
	}

	// フィールドの各セルの文字が obstacle か empty であることを確認する
	if (!are_valid_cell_letters(map)) {
		return (false);
	}
	return (true);
}
