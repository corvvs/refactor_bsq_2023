/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_structure.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 19:33:15 by corvvs           ###   ########.fr       */
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
	// フィールド行の行数
	size_t		field_height;
	// フィールド行の列数
	size_t		field_width;

	// フィールド文字; フィールドの記述に使われる文字
	union {
		// 配列記述されたフィールド文字種
		char	letter_array[N_LETTER_TYPES];

		// 構造化されたフィールド文字種
		struct	s_chars {
			char	empty;
			char	obstacle;
			char	full;
		}		letter;
	};
}				t_map;

typedef struct	s_square {
	size_t	top;
	size_t	left;
	size_t	size;
}				t_square;

#endif
