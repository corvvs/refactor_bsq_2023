/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:48:35 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 12:19:03 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// マップ1行目の1文字目のバリデーション
// NOTE: 必要??
int		validate_map_top(char **map, t_info *info)
{
	// 入力文字列が少なくとも2行あることを確認する
	if (!(map[0] && map[1]))
		return (FAIL);
	// マップ1行目が empty, obstacle, full のいずれかであることを確認する
	// NOTE: full だとダメなのでは??
	if (!(map[1][0] == info->empty ||
			map[1][0] == info->obstacle ||
			map[1][0] == info->full))
		return (FAIL);
	return (SUCCESS);
}

// マップの各セルが empty, obstacle のいずれかであることを確認する
int		validate_map_cell_griphs(char **map, t_info *info)
{
	int i;
	int j;

	i = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!(map[i][j] == info->empty || map[i][j] == info->obstacle))
				return (FAIL);
		}
	}
	return (SUCCESS);
}

// マップの形状のバリデーション
int		validate_map_shape(char **map, t_info *info)
{
	int i;
	int len;

	i = 1;
	// マップの各行の長さが等しいことを確認する
	len = ft_strlen(map[i]);
	while (map[i])
	{
		if (len != ft_strlen(map[i]))
			return (FAIL);
		i++;
	}
	// マップの長さがヘッダ行の記述と一致することを確認する
	if (i - 1 != info->num_rows)
		return (FAIL);
	return (SUCCESS);
}

// content が改行で終了していることを確認
int		validate_content_ends_with_nl(char *content)
{
	int		i;

	i = 0;
	while (content[i] != '\0')
		i++;
	if (content[i - 1] != '\n')
		return (FAIL);
	return (SUCCESS);
}

// マップ = 入力ファイルの先頭行より後の部分についてのバリデーション
int		validate_map(char **map, t_info *info)
{
	if (validate_map_top(map, info) == FAIL)
		return (FAIL);
	if (validate_map_cell_griphs(map, info) == FAIL)
		return (FAIL);
	if (validate_map_shape(map, info) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
