/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:59:31 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:04:29 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static int	is_delimiter(char ch, char delimiter) {
	return ch == delimiter || ch == '\0';
}

static size_t	count_words(const char* str, char delimiter) {
	size_t	n = 1;
	for (size_t i = 0; str[i]; ++i) {
		n += is_delimiter(str[i], delimiter);
	}
	return (n);
}

// str を delimiterで区切った文字列の配列を返す.
// !! strを破壊的に変更する !!
// !! 返り値配列には空文字列が含まれうる !!
// !! 返り値配列の各要素は free-able ではない !!
char**	bsq_split(char* str, char delimiter) {
	size_t	n_words = count_words(str, delimiter);
	char**	splitted = malloc(sizeof(char*) * (n_words + 1));
	if (!splitted) {
		return (NULL);
	}
	size_t	i_splitted = 0;
	size_t	begin_word = 0;
	size_t	end_word = 0;
	for (; i_splitted < n_words;) {
		while (!is_delimiter(str[end_word], delimiter)) {
			end_word += 1;
		}
		str[end_word] = '\0';
		splitted[i_splitted] = &str[begin_word];
		i_splitted += 1;
		end_word += 1;
		begin_word = end_word;
	}
	splitted[i_splitted] = NULL;
	return (splitted);
}

