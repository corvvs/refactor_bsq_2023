/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:59:31 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 11:21:19 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// splitted にアドレス word_start を追加する
// (必要に応じて splitted を拡張する)
static bool	append_pointer(t_capped_buffer* splitted, char* word_start) {
	return (store_to_capped_buffer(splitted, &word_start, sizeof(char*), sizeof(char*) * 2));
}

// str を delimiterで区切った文字列の配列を返す.
// !! strを破壊的に変更する !!
// !! 返り値配列には空文字列が含まれうる !!
// !! 返り値配列の各要素は free-able ではない !!
char**	bsq_split(char* str, char delimiter) {
	t_capped_buffer	splitted = {};
	size_t			word_start = 0;
	for (size_t i = 0; ; i += 1) {
		if (str[i] != delimiter && str[i] != '\0') {
			continue;
		}
		if (!append_pointer(&splitted, &str[word_start])) {
			free(splitted.buffer);
			return (NULL);
		}
		if (str[i] == '\0') {
			break;
		}
		str[i] = '\0';
		word_start = i + 1;
	}
	if (!append_pointer(&splitted, NULL)) {
		free(splitted.buffer);
		return (NULL);
	}
	return (splitted.buffer);
}
