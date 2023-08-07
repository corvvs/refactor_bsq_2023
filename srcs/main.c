/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 12:51:54 by corvvs           ###   ########.fr       */
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

int		search_out_bsq(int fd)
{
	char	*content;	// STDIN のすべての文字列
	char	**map;		// content を改行で区切ったもの
	t_info	info;

	content = ft_read_all(fd);
	if (validate_content_ends_with_nl(content) == FAIL) {
		return (FAIL);
	}
	map = bsq_split(content, '\n');
	if (map == NULL) {
		return (FAIL);
	}
	for (int i = 0; map[i]; ++i) {
		printf("%s\n", map[i]);
	}
	if (validate_header_line(map) == FAIL) {
		return (FAIL);
	}
	info = parse_header_line(map);
	if (validate_map(map, &info) == FAIL) {
		return (FAIL);
	}
	print_bsq(map, &info);
	// TODO: return (FAIL); 時のメモリリークを直す
	free(map);
	free(content);
	return (SUCCESS);
}

int		main(int argc, char *argv[])
{
	int i;

	if (argc < 2) {
		if (search_out_bsq(STDIN_FILENO) == FAIL) {
			ft_puterror(FT_ERR_MAP);
		}
	} else {
		i = 0;
		while (++i < argc) {
			if (1 < i) {
				printf("\n");
			}
			int ifd = open(argv[i], O_RDONLY);
			if (0 <= ifd) {
				if (search_out_bsq(ifd) == FAIL) {
					ft_puterror(FT_ERR_MAP);
				}
				close(ifd);
			}
		}
	}
	return (0);
}
