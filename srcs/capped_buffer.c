/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capped_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:32:57 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/08 02:49:31 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// 要求サイズ増分に対して必要なら capped_buffer を拡張する
static bool	extend_capped_buffer(
	t_capped_buffer* capped_buffer,
	size_t required_more,
	size_t minimum_size
) {
	if (capped_buffer->capacity >= capped_buffer->used + required_more) {
		return (true);
	}
	capped_buffer->capacity = capped_buffer->capacity > 0
		? capped_buffer->capacity * 2
		: minimum_size;
	char*	extended_buffer = malloc(capped_buffer->capacity);
	if (extended_buffer == NULL) {
		return (false);
	}
	ft_memcpy(extended_buffer, capped_buffer->buffer, capped_buffer->used);
	free(capped_buffer->buffer);
	capped_buffer->buffer = extended_buffer;
	return (true);
}

// capped_buffer にデータを保存する
// (必要に応じて capped_buffer を拡張する)
bool	store_to_capped_buffer(
	t_capped_buffer* capped_buffer,
	const void* data,
	size_t data_size,
	size_t minimum_size
) {
	if (!extend_capped_buffer(capped_buffer, data_size, minimum_size)) {
		DEBUGERR("failed to store: %p", capped_buffer);
		return (false);
	}
	ft_memcpy(capped_buffer->buffer + capped_buffer->used, data, data_size);
	capped_buffer->used += data_size;
	return true;
}
