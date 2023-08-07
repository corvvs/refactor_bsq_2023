/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:47:47 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:59:58 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// 先頭行をパースして、t_info 構造体に格納する
t_map	parse_header_line(char **lines)
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
	return (t_map){
		.lines			= lines,
		.header_line	= header_line,
		.field_lines	= lines + 1,
		.num_rows		= num_rows,
		.empty			= header_line[len - 3],
		.obstacle		= header_line[len - 2],
		.full			= header_line[len - 1],
	};
}
