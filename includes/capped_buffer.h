/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capped_buffer.h                                    :+:      :+:    :+:   */
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

typedef struct	s_capped_buffer {
	void*	buffer;
	size_t	capacity;
	size_t	used;
}				t_capped_buffer;

// capped_buffer.c
bool		store_to_capped_buffer(t_capped_buffer* capped_buffer, const void *data, size_t data_size, size_t minimum_size);

#endif
