/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 01:43:26 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

# define FT_ERR_MAP "map error\n"

typedef struct s_capped_buffer {
	void*	buffer;
	size_t	capacity;
	size_t	used;
}	t_capped_buffer;

typedef struct s_basedata
{
	char*	content;
	char**	lines;
}	t_basedata;

typedef	struct	s_map
{
	t_basedata	basedata;
	// ヘッダー行; フィールド行の行数と各種文字を定義する行
	char*	header_line;
	// フィールド行
	char**	field_lines;
	// ヘッダー行で定義されたフィールド行の行数
	size_t	num_rows;
	// フィールド行の列数
	size_t	num_cols;
	// ヘッダー行で定義された empty 文字
	char	empty;
	// ヘッダー行で定義された obstacle 文字
	char	obstacle;
	// ヘッダー行で定義された full 文字
	char	full;
}				t_map;

typedef	struct	s_square
{
	size_t	top;
	size_t	left;
	size_t	size;
}				t_square;


// bsq_session.c
void		run_bsq_session(int fd);

// maximum_square.c
t_square	get_maximum_square(size_t top, size_t left, const t_map *p_info);

// read.c
char*		read_content(int fd);

// map.c
bool		generate_map(int fd, t_map* map_ptr);
void		destroy_map(t_map* map);

// ft_validate_map
bool		is_valid_map(const t_map *info);
bool		does_content_end_with_nl(char *content);

// capped_buffer.c
bool		store_to_capped_buffer(t_capped_buffer* capped_buffer, const void* data, size_t data_size, size_t minimum_size);

// ft_utility.c
size_t		ft_strlen(const char *str);
void*		ft_memcpy(void* dst, const void* src, size_t n);
int			ft_is_printable(char c);

// bsq_split.c
char**		bsq_split(char* str, char delimiter);

// ft_puts.c
void		ft_putstr_fd(int fd, const char *str);
void		ft_putnstr_fd(int fd, const char *str, size_t max_len);

int				ft_atoi(char *str);

#endif
