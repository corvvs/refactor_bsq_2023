/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_validate_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:16:50 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/10 01:19:24 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static bool	has_least_2_lines(char** const lines) {
	if (lines[0] == NULL || lines[1] == NULL) {
		DEBUGERR("less than 2 lines: %p", lines);
		return (false);
	}
	return (true);
}

static bool	is_enough_long_header_line(const char* line, size_t minimum_len) {
	if (ft_strlen(line) < minimum_len) {
		DEBUGERR("too short: |%s| < %zu", line, minimum_len);
		return (false);
	}
	return (true);
}

static bool is_printable_str(const char* str) {
	for (size_t i = 0; str[i]; i += 1) {
		if (!ft_is_printable(str[i])) {
			DEBUGERR("encountered unprintable letter: %d", str[i]);
			return (false);
		}
	}
	return (true);
}

static bool	is_unique_str(const char* str) {
	// NOTE: ビットセットだとなお良し
	unsigned char	mask[256] = {};

	for (size_t i = 0; str[i]; i += 1) {
		if (mask[(unsigned char)str[i]]) {
			DEBUGERR("encountered duplicated letter: %c", str[i]);
			return (false);
		}
		mask[(unsigned char)str[i]] = 1;
	}
	return (true);
}

// 先頭行について単体で完結するバリデーションを行う
bool		bsq_validate_lines(char** const lines) {
	// 少なくとも2行あることを確認する
	if (!has_least_2_lines(lines)) {
		return (false);
	}

	const char*		header_line = lines[0];
	// 先頭行が
	// - フィールド行数
	// - フィールド文字種
	// を保持するために十分長いことを確認する
	if (!is_enough_long_header_line(header_line, N_LETTER_TYPES + 1)) {
		return (false);
	}

	const size_t	header_len = ft_strlen(header_line);
	const size_t	rows_len = header_len - N_LETTER_TYPES;
	// フィールド行数部分が uint64_t としてパースできることを確認する
	if (!str_to_u64(header_line, rows_len, NULL)) {
		return (false);
	}

	const char*		letters = header_line + rows_len;
	// フィールド文字がすべて printable であることを確認する
	if (!is_printable_str(letters)) {
		return (false);
	}
	// フィールド文字がすべて異なることを確認する
	if (!is_unique_str(letters)) {
		return (false);
	}
	return (true);
}
