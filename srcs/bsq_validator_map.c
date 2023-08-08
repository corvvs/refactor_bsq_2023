/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_validator_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:48:35 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 10:45:05 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// マップの各セルが empty, obstacle のいずれかであることを確認する
static bool		are_valid_cell_letters(const t_map *info) {
	char** const	field = info->field_lines;

	for (size_t row = 0; row < info->num_rows; row += 1) {
		for (size_t col = 0; col < info->num_cols; col += 1) {
			char	letter = field[row][col];
			if (letter != info->letter.empty && letter != info->letter.obstacle) {
				DEBUGERR("invalid cell letter: %c at (%zu, %zu)", letter, row, col);
				return (false);
			}
		}
	}
	return (true);
}

// マップの形状のバリデーション
static bool		is_valid_map_shape(const t_map *info) {
	char** const	field = info->field_lines;

	if (info->num_cols == 0) {
		DEBUGERR("width is zero: %zu", info->num_cols);
		return (false);
	}

	for (size_t row = 0; row < info->num_rows; row += 1) {
		if (ft_strlen(field[row]) != info->num_cols) {
			DEBUGERR("invalid row size: %zu at line %zu", ft_strlen(field[row]), row);
			return (false);
		}
	}
	return (true);
}

// マップ = 入力ファイルの先頭行より後の部分についてのバリデーション
bool		is_valid_map(const t_map *info) {
	if (!are_valid_cell_letters(info)) {
		return (false);
	}
	if (!is_valid_map_shape(info)) {
		return (false);
	}
	return (true);
}
