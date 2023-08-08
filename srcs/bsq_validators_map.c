/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_validators_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:48:35 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 15:11:46 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static bool		is_expected_row_number(const t_map *map) {
	char** const	field = map->field_lines;
	size_t			actual_num_rows;
	for (actual_num_rows = 0; field[actual_num_rows] != NULL;) {
		actual_num_rows += 1;
	}
	if (actual_num_rows != map->num_rows) {
		DEBUGERR(
			"unexpected row number: expected: %zu actual: %zu",
			map->num_rows, actual_num_rows
		);
		return (false);
	}
	return (true);
}

static bool		is_valid_map_shape(const t_map *map) {
	char** const	field = map->field_lines;

	if (map->num_cols == 0) {
		DEBUGERR("width is zero: %zu", map->num_cols);
		return (false);
	}

	for (size_t row = 0; row < map->num_rows; row += 1) {
		const size_t	row_size = ft_strlen(field[row]);
		if (row_size != map->num_cols) {
			DEBUGERR("invalid row size: %zu at line %zu", row_size, row);
			return (false);
		}
	}
	return (true);
}

static bool		are_valid_cell_letters(const t_map *map) {
	char** const	field = map->field_lines;

	for (size_t row = 0; row < map->num_rows; row += 1) {
		for (size_t col = 0; col < map->num_cols; col += 1) {
			const char	letter = field[row][col];
			if (letter != map->letter.empty && letter != map->letter.obstacle) {
				DEBUGERR("invalid cell letter: %c at (%zu, %zu)", letter, row, col);
				return (false);
			}
		}
	}
	return (true);
}

bool		is_valid_map(const t_map *map) {
	if (!is_expected_row_number(map)) {
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
