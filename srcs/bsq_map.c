/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:47:47 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 00:51:22 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// 入力行をパースして, t_map 構造体を生成する
static t_map	parse_lines_into_map(char* content, char** lines) {
	const char*		header_line = lines[0];
	const size_t	rows_len = ft_strlen(header_line) - N_LETTER_TYPES;
	// ASSUMPTION: header_line の長さが N_LETTER_TYPES より大きいこと
	uint64_t 		field_height;
	str_to_u64(header_line, rows_len, &field_height);
	// ASSUMPTION: この整数変換が成功すること
	const size_t	field_width = ft_strlen(lines[1]);
	const char*		letters = header_line + rows_len;

	t_map	map = {
		.basedata		= {
			.content	= content,
			.lines		= lines,
		},
		.field_lines	= lines + 1,
		.field_height	= field_height,
		.field_width	= field_width,
	};
	ft_memcpy(map.letter_array, letters, N_LETTER_TYPES);
	return (map);
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

// 与えられた fd からマップ構造体を作成し, map_ptr にセットする.
// 作成できなかった場合は false を返す.
bool	bsq_generate_map(int fd, t_map* map_ptr) {
	if (fd < 0) {
		DEBUGERR("invalid fd: %d", fd);
		return (false);
	}
	char*	content = bsq_read_file(fd);
	if (content == NULL) {
		return (false);
	}
	char**	lines = generate_lines(content);
	if (lines == NULL) {
		free(content);
		return (false);
	}
	t_map	map = parse_lines_into_map(content, lines);
	if (!is_valid_map(&map)) {
		bsq_destroy_map(&map);
		return (false);
	}
	*map_ptr = map;
	return (true);
}

// 与えられたマップ構造体を破壊する
void	bsq_destroy_map(t_map* map) {
	free(map->basedata.content);
	free(map->basedata.lines);
}
