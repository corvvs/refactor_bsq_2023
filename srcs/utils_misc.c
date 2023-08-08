/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:44:48 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 00:24:46 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

size_t	ft_strlen(const char *str) {
	size_t	n;

	for (n = 0; str[n];) {
		n += 1;
	}
	return (n);
}

void*	ft_memcpy(void* dst, const void* src, size_t n) {
	if (n == 0 || dst == src) {
		return (dst);
	}

	char*		dst_c = dst;
	const char*	src_c = src;
	for (size_t i = 0; i < n; ++i) {
		dst_c[i] = src_c[i];
	}
	return (dst);
}

bool	ft_is_printable(char c) {
	return !(c < 0x20 || c == 0x7f);
}
