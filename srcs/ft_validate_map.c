/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:48:35 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 20:35:36 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// マップ1行目の1文字目のバリデーション
// NOTE: 必要??
static int		validate_map_top(const t_map *info) {
	char** const	map = info->lines;
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
static int		validate_map_cell_griphs(const t_map *info) {
	char** const	map = info->field_lines;
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
static int		validate_map_shape(const t_map *info) {
	char** const	map = info->field_lines;
	size_t			i;

	i = 0;
	// マップの各行の長さが等しいことを確認する
	size_t	len = ft_strlen(map[i]);
	while (map[i])
	{
		if (len != ft_strlen(map[i]))
			return (FAIL);
		i++;
	}
	// マップの長さがヘッダ行の記述と一致することを確認する
	if (i != info->num_rows)
		return (FAIL);
	return (SUCCESS);
}

// マップ = 入力ファイルの先頭行より後の部分についてのバリデーション
int		validate_map(const t_map *info) {
	if (validate_map_top(info) == FAIL)
		return (FAIL);
	if (validate_map_cell_griphs(info) == FAIL)
		return (FAIL);
	if (validate_map_shape(info) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

// content が改行で終了していることを確認
int		validate_content_ends_with_nl(char *content) {
	size_t	n = ft_strlen(content);
	return (n > 0 && content[n - 1] == '\n')
		? SUCCESS
		: FAIL;
}
