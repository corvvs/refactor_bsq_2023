/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:29:51 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	ft_free(char ***map)
{
	long int i;

	i = 0;
	while ((*map)[i])
	{
		free((*map)[i]);
		i++;
	}
	free(*map);
	*map = NULL;
}

// ifd から全データを読み取り, 1つの文字列に結合して返す
char	*ft_read_all(int ifd)
{
	char	*content;
	char	buf[FT_BUFSIZ + 1];
	int		n;

	content = NULL;
	while ((n = read(ifd, buf, FT_BUFSIZ)) > 0)
	{
		buf[n] = '\0';
		if (content == NULL)
			content = ft_strdup(buf);
		else
			content = ft_strjoin(content, buf);
	}
	return (content);
}

char*	read_content(int fd) {
	char*	content = ft_read_all(fd);
	if (content == NULL) {
		return (NULL);
	}
	if (validate_content_ends_with_nl(content) == FAIL) {
		free(content);
		return (NULL);
	}
	content[ft_strlen(content) - 1] = '\0'; // bsq_split で余計な空文字列を生成させないための措置
	return (content);
}

int	search_bsq_from_content(char* content) {
	char**	map = bsq_split(content, '\n');
	if (map == NULL) {
		return (FAIL);
	}

	// for (int i = 0; map[i]; ++i) {
	// 	printf("%s\n", map[i]);
	// }
	// printf("--\n");

	if (validate_header_line(map) == FAIL) {
		free(map);
		return (FAIL);
	}
	t_info	info = parse_header_line(map);
	if (validate_map(map, &info) == FAIL) {
		free(map);
		return (FAIL);
	}
	print_bsq(map, &info);
	free(map);
	return (SUCCESS);
}

void	search_out_bsq(int fd)
{
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

int		main(int argc, char *argv[])
{
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
		if (ifd < 0) {
			ft_puterror(FT_ERR_MAP);
			continue;
		}
		search_out_bsq(ifd);
		close(ifd);
	}
	return (0);
}
