/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_validator_lines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:32:57 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/08 02:26:57 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static bool	has_least_2_lines(char** const lines) {
	return (lines[0] != NULL && lines[1] != NULL);
}

static bool	is_enough_long_header_line(const char* line) {
	return (ft_strlen(line) >= 4);
}

static bool is_printable_str(const char* str) {
	for (size_t i = 0; str[i]; i += 1) {
		if (!ft_is_printable(str[i])) {
			return (false);
		}
	}
	return (true);
}

static bool	is_unique_str(const char* str) {
	unsigned char	mask[256] = {};
	for (size_t i = 0; str[i]; i += 1) {
		if (mask[(unsigned char)str[i]]) {
			return (false);
		}
		mask[(unsigned char)str[i]] = 1;
	}
	return (true);
}

// 先頭行について単体で完結するバリデーションを行う
bool		are_valid_lines(char** const lines) {
	// 少なくとも2行あることを確認する
	if (!has_least_2_lines(lines)) {
		return (false);
	}
	// 先頭行が4文字以上あることを確認する
	const char* header_line = lines[0];
	if (!is_enough_long_header_line(header_line)) {
		return (false);
	}
	const size_t header_len = ft_strlen(header_line);
	// 先頭行の末尾から3文字目までが uint64_t としてパースできることを確認する
	if (!bsq_str_to_u64(header_line, header_len - 3, NULL)) {
		return (false);
	}
	const char*	griphs = header_line + header_len - 3;
	// 先頭行の末尾3文字がすべて printable であることを確認する
	if (!is_printable_str(griphs)) {
		return (false);
	}
	// 先頭行の末尾3文字がすべて異なることを確認する
	if (!is_unique_str(griphs)) {
		return (false);
	}
	return (true);
}
