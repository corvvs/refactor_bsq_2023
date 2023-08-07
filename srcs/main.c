/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:55:08 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// 先頭行について単体で完結するバリデーションを行う
static int		validate_header_line(char **map) {
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

static int	search_bsq_from_content(char* content) {
	char**	lines = bsq_split(content, '\n');
	if (lines == NULL) {
		return (FAIL);
	}

	// for (int i = 0; lines[i]; ++i) {
	// 	printf("%s\n", lines[i]);
	// }
	// printf("--\n");

	if (validate_header_line(lines) == FAIL) {
		free(lines);
		return (FAIL);
	}
	t_info	map = parse_header_line(lines);
	if (validate_map(&map) == FAIL) {
		free(lines);
		return (FAIL);
	}
	print_bsq(lines, &map);
	free(map.lines);
	return (SUCCESS);
}

static void	search_out_bsq(int fd) {
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
	if (search_bsq_from_content(content) == FAIL) {
		ft_puterror(FT_ERR_MAP);
	}
	free(content);
}

int		main(int argc, char *argv[]) {
	if (argc < 2) {
		// [from stdin]
		search_out_bsq(STDIN_FILENO);
		return (0);
	}
	// [using arguments]
	for (int i = 1; i < argc; ++i) {
		if (1 < i) {
			printf("\n");
		}
		int ifd = open(argv[i], O_RDONLY);
		search_out_bsq(ifd);
		if (ifd < 0) {
			close(ifd);
		}
	}
	return (0);
}
