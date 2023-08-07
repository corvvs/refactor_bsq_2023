/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_session.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 22:58:12 by corvvs           ###   ########.fr       */
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

static bool	search_out_bsq(char* content) {
	char**	lines = bsq_split(content, '\n');
	if (lines == NULL) {
		return (false);
	}

	if (!are_valid_lines(lines)) {
		free(lines);
		return (false);
	}
	t_map	map = parse_map(lines);
	if (!is_valid_map(&map)) {
		free(lines);
		return (false);
	}
	solve_bsq(&map);
	free(lines);
	return (true);
}

void	run_bsq_session(int fd) {
	if (fd < 0) {
		// fd is invalid
		ft_puterror(FT_ERR_MAP);
		return ;
	}
	char*	content = read_content(fd);
	if (content == NULL) {
		ft_puterror(FT_ERR_MAP);
		return ;
	}
	if (!search_out_bsq(content)) {
		ft_puterror(FT_ERR_MAP);
	}
	free(content);
}
