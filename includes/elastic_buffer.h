/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elastic_buffer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 13:28:22 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAPPED_BUFFER_H
#define CAPPED_BUFFER_H
#include <stdlib.h>

// [elastic_buffer]
// 必要に応じてサイズが伸長するバッファ
typedef struct	s_elastic_buffer {
	void*	buffer;
	size_t	capacity;
	size_t	used;
}				t_elastic_buffer;

// elastic_buffer.c
bool		store_to_elastic_buffer(t_elastic_buffer* elastic_buffer, const void *data, size_t data_size, size_t minimum_size);

#endif
