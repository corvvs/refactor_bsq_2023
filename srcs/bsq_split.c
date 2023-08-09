/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:59:31 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 20:51:58 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// splitted にアドレス word_start を追加する
// (必要に応じて splitted を拡張する)
static bool	push_word_start(t_elastic_buffer* splitted, char* word_start) {
	return (push_to_elastic_buffer(splitted, &word_start, sizeof(char*), sizeof(char*) * 2));
}

// str を delimiterで区切った文字列の配列を返す.
// !! strを破壊的に変更する !!
// !! 返り値配列には空文字列が含まれうる !!
// !! 返り値配列の各要素は free-able ではない !!
char**	bsq_split(char* str, char delimiter) {
	// [動作イメージ]
	// 文字列 str を先頭から見ていく.
	// 途中で delimiter か NUL が見つかったら, そこまでを一つの単語として考え,
	// 単語の開始位置を配列に追加する.
	// ただし見つかったのが delimiter の場合そのままだと単語が終了しないため,
	// delimiter を NUL で上書きする.

	t_elastic_buffer	splitted = {};
	size_t				word_start = 0;

	for (size_t i = 0; ; i += 1) {
		// delimiter でも NUL でもない = 単語の途中である場合は次のループへ
		if (str[i] != delimiter && str[i] != '\0') {
			continue;
		}

		// 単語開始位置を spitted に追加する
		if (!push_word_start(&splitted, &str[word_start])) {
			free(splitted.buffer);
			return (NULL);
		}

		// NUL だった場合はループ脱出, そうでない場合は次の単語の準備をする
		if (str[i] == '\0') {
			break;
		}
		str[i] = '\0';
		word_start = i + 1;
	}

	if (!push_word_start(&splitted, NULL)) {
		free(splitted.buffer);
		return (NULL);
	}
	return (splitted.buffer);
}
