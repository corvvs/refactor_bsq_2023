/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 10:50:43 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdbool.h>
# include "common.h"

# define FT_ERR_MAP "map error\n"
# define N_LETTER_TYPES 3

typedef struct	s_capped_buffer {
	void*	buffer;
	size_t	capacity;
	size_t	used;
}				t_capped_buffer;

typedef struct	s_basedata {
	char*	content;
	char**	lines;
}				t_basedata;

typedef	struct	s_map {
	t_basedata	basedata;
	// フィールド行; 一番上の行(ヘッダー行)以降の行
	char**	field_lines;
	// ヘッダー行で定義されたフィールド行の行数
	size_t	num_rows;
	// フィールド行の列数
	size_t	num_cols;
	union {
		struct s_chars {
			// ヘッダー行で定義された empty 文字
			char	empty;
			// ヘッダー行で定義された obstacle 文字
			char	obstacle;
			// ヘッダー行で定義された full 文字
			char	full;
		}		letter;
		char	letter_array[N_LETTER_TYPES];
	};
}				t_map;

typedef	struct	s_square {
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

// bsq_validator_content.c
bool		is_nl_ended_content(char *content);

// bsq_validator_lines.c
bool		are_valid_lines(char** const lines);

// bsq_validator_map.c
bool		is_valid_map(const t_map *info);

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

// bsq_number.c
bool		bsq_str_to_u64(const char *str, size_t max_len, uint64_t *result);

#endif
