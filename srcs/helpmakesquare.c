/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmakesquare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 12:25:26 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft.h"

extern	int g_max;
extern	int g_col;
extern	int g_row;

// マップの横幅を返す
int		get_map_width(char **map)
{
	int count;

	count = 0;
	while (map[1][count])
	{
		count++;
	}
	return (count);
}

// カーソル構造体を初期化する
void	init_cursor(t_tempcrs *p_tempcrs)
{
	p_tempcrs->row = 1;
	p_tempcrs->col = 0;
	p_tempcrs->size = 0;
}

// 位置 (col, row) に物が置けることを確認する
int		cell_is_open(char **map, int col, int row, t_info *p_info)
{
	// 横座標(col)がマップ横幅以内であることを確認
	// NOTE: == ではなく >= が適切
	if (col == get_map_width(map))
	{
		return (0);
	}
	// 縦座標(row)がマップ縦幅以内であることを確認
	// NOTE: == ではなく >= が適切
	if (row == p_info->num_rows + 1)
	{
		return (0);
	}
	// 座標 (col, row) に物が置けることを確認
	// NOTE: 条件 == '\0 はいらなくない??
	if (map[row][col] == p_info->obstacle || map[row][col] == '\0')
	{
		return (0);
	}
	return (1);
}

void	set_bsq(t_bsq *p_bsq)
{
	p_bsq->x = g_col;
	p_bsq->y = g_row;
	p_bsq->size = g_max;
}
