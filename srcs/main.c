/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:47:55 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static int	search_bsq_from_content(char* content) {
	char**	lines = bsq_split(content, '\n');
	if (lines == NULL) {
		return (FAIL);
	}

	// for (int i = 0; map[i]; ++i) {
	// 	printf("%s\n", map[i]);
	// }
	// printf("--\n");

	if (validate_header_line(lines) == FAIL) {
		free(lines);
		return (FAIL);
	}
	t_info	info = parse_header_line(lines);
	if (validate_map(lines, &info) == FAIL) {
		free(lines);
		return (FAIL);
	}
	print_bsq(lines, &info);
	free(info.lines);
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
