/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_structure.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 11:32:34 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_STRUCTURE_H
#define BSQ_STRUCTURE_H

#include "bsq_common.h"

typedef struct	s_basedata {
	char*	content;
	char**	lines;
}				t_basedata;

typedef struct	s_map {
	t_basedata	basedata;
	// フィールド行; 一番上の行(ヘッダー行)以降の行
	char**		field_lines;
	// ヘッダー行で定義されたフィールド行の行数
	size_t		num_rows;
	// フィールド行の列数
	size_t		num_cols;
	union {
		struct	s_chars {
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

typedef struct	s_square {
	size_t	top;
	size_t	left;
	size_t	size;
}				t_square;

#endif
