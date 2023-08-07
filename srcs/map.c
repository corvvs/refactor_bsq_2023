/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:47:47 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 00:14:07 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// 先頭行について単体で完結するバリデーションを行う
static bool		are_valid_lines(char** const lines) {
	int		len;
	char	*line;
	int		i;

	// 少なくとも2行あることを確認する
	if (lines[0] == NULL || lines[1] == NULL)
		return (false);
	// 先頭行が4文字以上あることを確認する
	line = lines[0];
	len = ft_strlen(line);
	if (len < 4)
		return (false);
	// 先頭行の末尾3文字が以外がすべて数字であることを確認する
	i = -1;
	while (++i < len - 3)
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (false);
	// 先頭行の末尾3文字がすべて printable であることを確認する
	if (!(ft_is_printable(line[len - 1]) &&
				ft_is_printable(line[len - 2]) &&
				ft_is_printable(line[len - 3])))
		return (false);
	// 先頭行の末尾3文字がすべて異なることを確認する
	if (line[len - 1] == line[len - 2] ||
			line[len - 2] == line[len - 3] ||
			line[len - 3] == line[len - 1])
		return (false);
	return (true);
}

// 先頭行をパースして、t_info 構造体に格納する
static t_map	parse_map(char* content, char** lines) {
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
		.basedata		= { .content = content, .lines = lines },
		.header_line	= header_line,
		.field_lines	= lines + 1,
		.num_rows		= num_rows,
		.num_cols		= ft_strlen(lines[1]),
		.empty			= header_line[len - 3],
		.obstacle		= header_line[len - 2],
		.full			= header_line[len - 1],
	};
}

static char**	generate_lines(char* content) {
	char**	lines = bsq_split(content, '\n');
	if (lines == NULL) {
		return (NULL);
	}
	if (!are_valid_lines(lines)) {
		free(lines);
		return (NULL);
	}
	return (lines);
}

bool	generate_map(int fd, t_map* map_ptr) {
	if (fd < 0) {
		return (false);
	}
	char*	content = read_content(fd);
	if (content == NULL) {
		return (false);
	}
	char**	lines = generate_lines(content);
	if (lines == NULL) {
		free(lines);
		return (false);
	}
	t_map	map = parse_map(content, lines);
	if (!is_valid_map(&map)) {
		destroy_map(&map);
		return (false);
	}
	*map_ptr = map;
	return (true);
}

void	destroy_map(t_map* map) {
	free(map->basedata.content);
	free(map->basedata.lines);
}
