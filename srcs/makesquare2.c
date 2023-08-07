/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makesquare2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:58:55 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

extern	int g_max;
extern	int g_col;
extern	int g_row;

// カーソル位置で定義される正方形の右辺および下辺がすべて空白であることを確認する
int		square_edge_is_open(char **map, t_tempcrs *p_tempcrs, t_info *p_info)
{
	int i;

	i = 0;
	while (i <= p_tempcrs->size)
	{
		if (cell_is_open(map, p_tempcrs->col + i,
		p_tempcrs->row + p_tempcrs->size, p_info) == 0)
		{
			return (0);
		}
		i++;
	}
	i = 0;
	while (i <= p_tempcrs->size)
	{
		if (cell_is_open(map, p_tempcrs->col + p_tempcrs->size,
		p_tempcrs->row + i, p_info) == 0)
			return (0);
		i++;
	}
	return (1);
}

// カーソル位置で定義される正方形を可能な限り拡大する
void	extend_square_by_cursor(char **map, t_tempcrs *p_tempcrs, t_info *p_info)
{
	p_tempcrs->size = 0;
	while (square_edge_is_open(map, p_tempcrs, p_info) == 1)
	{
		p_tempcrs->size++;
	}
	if (g_max < p_tempcrs->size)
	{
		g_max = p_tempcrs->size;
		g_col = p_tempcrs->col;
		g_row = p_tempcrs->row;
	}
}

void	print_map(char **map, t_info *p_info)
{
	int i;
	int j;

	i = 1;
	while (i <= p_info->num_rows)
	{
		j = 0;
		while (j < get_map_width(map))
		{
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

// マップデータを求めた bsq に従って変更し, 出力する
void	print_answer(t_info *p_info) {
	char	**map = p_info->lines;
	int		i;
	int		j;
	t_bsq	*p_bsq;

	i = 0;
	p_bsq = malloc(sizeof(t_bsq));
	set_bsq(p_bsq);
	while (i < g_max)
	{
		j = 0;
		while (j < g_max)
		{
			map[g_row + i][g_col + j] = p_info->full;
			j++;
		}
		i++;
	}
	print_map(map, p_info);
	free(p_bsq);
	return ;
}

// bsq = best square を探索する
void	run_bsq(t_info *p_info)
{
	t_tempcrs *p_tempcrs;

	// カーソルを初期化する
	g_max = 0;
	g_col = 0;
	g_row = 0;
	p_tempcrs = malloc(sizeof(t_tempcrs));
	init_cursor(p_tempcrs);
	// すべてのセルについて, そのセルを左上隅とする正方形の最大サイズを調べる
	while (p_tempcrs->row <= p_info->num_rows)
	{
		p_tempcrs->col = 0;
		while (p_tempcrs->col < get_map_width(p_info->lines))
		{
			if (cell_is_open(p_info->lines, p_tempcrs->col, p_tempcrs->row, p_info) == 1)
			{
				extend_square_by_cursor(p_info->lines, p_tempcrs, p_info);
			}
			p_tempcrs->col++;
		}
		p_tempcrs->row++;
	}
	print_answer(p_info);
	free(p_tempcrs);
	return ;
}
