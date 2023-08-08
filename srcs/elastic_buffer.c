/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elastic_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:32:57 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/08 11:21:19 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// 要求サイズ増分に対して必要なら elastic_buffer を拡張する
static bool	extend_elastic_buffer(
	t_elastic_buffer* elastic_buffer,
	size_t required_more,
	size_t minimum_size
) {
	if (elastic_buffer->capacity >= elastic_buffer->used + required_more) {
		return (true);
	}
	elastic_buffer->capacity = elastic_buffer->capacity > 0
		? elastic_buffer->capacity * 2
		: minimum_size;
	char*	extended_buffer = malloc(elastic_buffer->capacity);
	if (extended_buffer == NULL) {
		DEBUGERR("failed to extend: %zu", elastic_buffer->capacity);
		return (false);
	}
	ft_memcpy(extended_buffer, elastic_buffer->buffer, elastic_buffer->used);
	free(elastic_buffer->buffer);
	elastic_buffer->buffer = extended_buffer;
	return (true);
}

// elastic_buffer にデータを保存する
// (必要に応じて elastic_buffer を拡張する)
bool	store_to_elastic_buffer(
	t_elastic_buffer* elastic_buffer,
	const void* data,
	size_t data_size,
	size_t minimum_size
) {
	if (!extend_elastic_buffer(elastic_buffer, data_size, minimum_size)) {
		return (false);
	}
	ft_memcpy(elastic_buffer->buffer + elastic_buffer->used, data, data_size);
	elastic_buffer->used += data_size;
	return true;
}
