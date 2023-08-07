/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:55:14 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <libgen.h>

# define FT_BUFSIZ 320000
# define IN 1
# define OUT 0
# define SUCCESS 1
# define FAIL 0
# define FT_ERR_MAP "map error\n"

typedef	struct	s_bsq
{
	int			x;
	int			y;
	int			size;
}				t_bsq;

typedef	struct	s_info
{
	char**	lines;
	// ヘッダー行; フィールド行の行数と各種文字を定義する行
	char*	header_line;
	// フィールド行
	char**	field_lines;
	// ヘッダー行で定義されたフィールド行の行数
	int		num_rows;
	// ヘッダー行で定義された empty 文字
	char	empty;
	// ヘッダー行で定義された obstacle 文字
	char	obstacle;
	// ヘッダー行で定義された full 文字
	char	full;
}				t_info;

typedef	struct	s_tempcrs
{
	int	col;
	int	row;
	int	size;
}				t_tempcrs;

// read.c
char*	read_content(int fd);

// ft_validate_map
int				validate_map(const t_info *info);
int				validate_content_ends_with_nl(char *content);


int				g_max;
int				g_col;
int				g_row;
void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_puterror(char *str);
size_t			ft_strlen(const char *str);
int				ft_is_printable(char c);
char			*ft_strdup(char *src);
char			*ft_strjoin(char *s1, char *s2);
char**			bsq_split(char* str, char delimiter);
int				ft_atoi(char *str);
t_info			parse_header_line(char **map);
void			init_cursor(t_tempcrs *p_tempcrs);
int				cell_is_open(char **map, int col, int row, t_info *p_info);
void			print_bsq(char **map, t_info *p_info);
void			set_bsq(t_bsq *p_bsq);
int				get_map_width(char **map);

#endif
