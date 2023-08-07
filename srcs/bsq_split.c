/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:59:31 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 01:27:48 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

typedef struct s_splitted {
	char**	starts_list;
	size_t	capacity;
	size_t	used;
}	t_splitted;

// 必要なら splitted を拡張する
static bool	extend_splitted(t_splitted* splitted) {
	if (splitted->capacity >= splitted->used + 1) {
		return (true);
	}
	splitted->capacity = splitted->capacity > 0
		? splitted->capacity * 2
		: 2;
	char**	new_starts_list = malloc(sizeof(char*) * splitted->capacity);
	if (!new_starts_list) {
		return (false);
	}
	ft_memcpy(new_starts_list, splitted->starts_list, sizeof(char*) * splitted->used);
	free(splitted->starts_list);
	splitted->starts_list = new_starts_list;
	return (true);
}

// splitted にアドレス word_start を追加する
// (必要に応じて splitted を拡張する)
static bool	append_pointer(t_splitted* splitted, char* word_start) {
	if (!extend_splitted(splitted)) {
		return (false);
	}
	splitted->starts_list[splitted->used] = word_start;
	splitted->used += 1;
	return (true);
}

// str を delimiterで区切った文字列の配列を返す.
// !! strを破壊的に変更する !!
// !! 返り値配列には空文字列が含まれうる !!
// !! 返り値配列の各要素は free-able ではない !!
char**	bsq_split(char* str, char delimiter) {
	t_splitted	splitted = {};
	size_t	word_start = 0;
	for (size_t i = 0; ; i += 1) {
		if (str[i] != delimiter && str[i] != '\0') {
			continue;
		}
		if (!append_pointer(&splitted, &str[word_start])) {
			free(splitted.starts_list);
			return (NULL);
		}
		if (str[i] == '\0') {
			break;
		}
		str[i] = '\0';
		word_start = i + 1;
	}
	if (!append_pointer(&splitted, NULL)) {
		free(splitted.starts_list);
		return (NULL);
	}
	return (splitted.starts_list);
}
