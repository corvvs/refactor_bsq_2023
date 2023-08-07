/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:47:47 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:53:47 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// 先頭行について単体で完結するバリデーションを行う
int		validate_header_line(char **map)
{
	int		len;
	char	*line;
	int		i;

	if (!map[0])
		return (FAIL);
	// 先頭行が4文字以上あることを確認する
	line = map[0];
	len = ft_strlen(line);
	if (len < 4)
		return (FAIL);
	// 先頭行の末尾3文字が以外がすべて数字であることを確認する
	i = -1;
	while (++i < len - 3)
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (FAIL);
	// 先頭行の末尾3文字がすべて printable であることを確認する
	if (!(ft_is_printable(line[len - 1]) &&
				ft_is_printable(line[len - 2]) &&
				ft_is_printable(line[len - 3])))
		return (FAIL);
	// 先頭行の末尾3文字がすべて異なることを確認する
	if (line[len - 1] == line[len - 2] ||
			line[len - 2] == line[len - 3] ||
			line[len - 3] == line[len - 1])
		return (FAIL);
	return (SUCCESS);
}

// 先頭行をパースして、t_info 構造体に格納する
t_info	parse_header_line(char **lines)
{
	int		len;
	int		i;
	char	*num;

	char*	header_line = lines[0];
	len = ft_strlen(header_line);
	// TODO: この malloc をやめる
	num = malloc(sizeof(char) * (len - 3) + 1);
	i = -1;
	while (++i < len - 3)
		num[i] = header_line[i];
	num[i] = '\0';
	int num_rows = ft_atoi(num);
	free(num);
	return (t_info){
		.lines			= lines,
		.header_line	= header_line,
		.field_lines	= lines + 1,
		.num_rows		= num_rows,
		.empty			= header_line[len - 3],
		.obstacle		= header_line[len - 2],
		.full			= header_line[len - 1],
	};
}
