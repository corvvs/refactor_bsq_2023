/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmakesquare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 22:15:12 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft.h"

// マップの横幅を返す
size_t		get_map_width(char** const map) {
	return (ft_strlen(map[0]));
}

// 位置 (row, col) に物が置けることを確認する
int		cell_is_open(size_t row, size_t col, const t_map *p_info)
{
	char**	map = p_info->field_lines;
	// 横座標(col)がマップ横幅以内であることを確認
	if (col >= get_map_width(map)) {
		return (0);
	}
	// 縦座標(row)がマップ縦幅以内であることを確認
	if (row >= p_info->num_rows) {
		return (0);
	}
	// 座標 (top, left) に物が置けることを確認
	// NOTE: 条件 == '\0 はいらなくない??
	if (map[row][col] == p_info->obstacle) {
		return (0);
	}
	return (1);
}

