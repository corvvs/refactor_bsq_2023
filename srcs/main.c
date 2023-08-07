/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 12:33:36 by corvvs           ###   ########.fr       */
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

int		ft_main_1(void)
{
	char	*content;	// STDIN のすべての文字列
	char	**map;		// content を改行で区切ったもの
	t_info	*info;

	content = ft_read_all(0);
	if (validate_content_ends_with_nl(content) == FAIL)
		return (FAIL);
	map = ft_split(content, "\n");
	free(content);
	if (validate_header_line(map) == FAIL)
		return (FAIL);
	if (!(info = parse_header_line(map)))
		return (FAIL);
	if (validate_map(map, info) == FAIL)
		return (FAIL);
	print_bsq(map, info);
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

int		ft_main_2(int argc, char *argv[], int i)
{
	int		ifd;
	char	*content;
	char	**map;
	t_info	*info;

	if ((ifd = open(argv[i], O_RDONLY)) == -1)
		return (FAIL);
	content = ft_read_all(ifd);
	if (validate_content_ends_with_nl(content) == FAIL)
		return (FAIL);
	close(ifd);
	map = ft_split(content, "\n");
	free(content);
	if (validate_header_line(map) == FAIL)
		return (FAIL);
	if (!(info = parse_header_line(map)))
		return (FAIL);
	if (validate_map(map, info) == FAIL)
		return (FAIL);
	print_bsq(map, info);
	if (!(i + 1 == argc))
		ft_putstr("\n");
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

int		main(int argc, char *argv[])
{
	int i;

	if (argc < 2)
	{
		if (ft_main_1() == FAIL)
			ft_puterror(FT_ERR_MAP);
	}
	else
	{
		i = 0;
		while (++i < argc)
		{
			if (ft_main_2(argc, argv, i) == FAIL)
				ft_puterror(FT_ERR_MAP);
		}
	}
	return (0);
}
