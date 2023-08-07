/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmakesquare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 22:42:55 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft.h"

// 位置 (row, col) に物が置けることを確認する
bool		is_empty_cell(size_t row, size_t col, const t_map *p_info)
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

