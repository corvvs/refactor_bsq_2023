/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 18:51:43 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 19:10:33 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static bool	is_number(char c) {
	return ('0' <= c && c <= '9');
}

static bool will_overflow(uint64_t n, uint64_t digit) {
	return (n > UINT64_MAX / 10 || digit > UINT64_MAX - n * 10);
}

bool	str_to_u64(const char *str, size_t max_len, uint64_t *result) {
	uint64_t	n = 0;
	for (size_t i = 0; str[i] && i < max_len; i += 1) {
		if (!is_number(str[i])) {
			DEBUGERR("invalid character: %c", str[i]);
			return (false);
		}
		uint64_t	digit = str[i] - '0';
		// オーバーフローチェック
		if (will_overflow(n, digit)) {
			DEBUGERR("overflow: " U64T ", " U64T, n, digit);
			return (false);
		}
		n = n * 10 + digit;
	}
	if (result != NULL) {
		*result = n;
	}
	return (true);
}
