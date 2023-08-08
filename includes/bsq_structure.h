/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_structure.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 11:20:48 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_STRUCTURE_H
#define BSQ_STRUCTURE_H

#include "bsq_common.h"

typedef struct s_capped_buffer
{
	void *buffer;
	size_t capacity;
	size_t used;
} t_capped_buffer;

typedef struct s_basedata
{
	char *content;
	char **lines;
} t_basedata;

typedef struct s_map
{
	t_basedata basedata;
	// フィールド行; 一番上の行(ヘッダー行)以降の行
	char **field_lines;
	// ヘッダー行で定義されたフィールド行の行数
	size_t num_rows;
	// フィールド行の列数
	size_t num_cols;
	union
	{
		struct s_chars
		{
			// ヘッダー行で定義された empty 文字
			char empty;
			// ヘッダー行で定義された obstacle 文字
			char obstacle;
			// ヘッダー行で定義された full 文字
			char full;
		} letter;
		char letter_array[N_LETTER_TYPES];
	};
} t_map;

typedef struct s_square
{
	size_t top;
	size_t left;
	size_t size;
} t_square;

// bsq_run_session.c
void bsq_run_session(int fd);

// bsq_map.c
bool bsq_generate_map(int fd, t_map *map_ptr);
void bsq_destroy_map(t_map *map);

// bsq_read_file.c
char *bsq_read_file(int fd);

// bsq_validators_content.c
bool is_nl_ended_content(char *content);

// bsq_validators_lines.c
bool are_valid_lines(char **const lines);

// bsq_validators_map.c
bool is_valid_map(const t_map *info);

// bsq_get_maximum_square.c
t_square bsq_get_maximum_square(size_t top, size_t left, const t_map *p_info);

// bsq_split.c
char **bsq_split(char *str, char delimiter);

// capped_buffer.c
bool store_to_capped_buffer(t_capped_buffer *capped_buffer, const void *data, size_t data_size, size_t minimum_size);

// utils_put.c
void ft_putstr_fd(int fd, const char *str);
void ft_putnstr_fd(int fd, const char *str, size_t max_len);

// utils_number.c
bool str_to_u64(const char *str, size_t max_len, uint64_t *result);

// utils_misc.c
size_t ft_strlen(const char *str);
void *ft_memcpy(void *dst, const void *src, size_t n);
int ft_is_printable(char c);

#endif
