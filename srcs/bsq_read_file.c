/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:32:57 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/09 00:53:00 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#define READ_BUFFER_SIZE (1u << 16)

// ifd から全データを読み取り, 1つの文字列に結合して返す
static char*	read_all_text(int ifd) {
	t_elastic_buffer	joined = {};
	char				read_buffer[READ_BUFFER_SIZE];

	while (true) {
		ssize_t	read_size = read(ifd, read_buffer, sizeof(read_buffer));
		if (read_size < 0) {
			DEBUGERR("read error: %zd", read_size);
			free(joined.buffer);
			return (NULL);
		} else if (read_size == 0) {
			break ;
		}
		// 読み取ったデータを elastic_buffer に保存する
		if (!store_to_elastic_buffer(&joined, read_buffer, read_size, sizeof(read_buffer))) {
			free(joined.buffer);
			return (NULL);
		}
	}
	// 最後に NUL を入れる
	if (!store_to_elastic_buffer(&joined, "", 1, sizeof(read_buffer))) {
		free(joined.buffer);
		return (NULL);
	}
	return (joined.buffer);
}

// 与えられた fd からデータを読み取り, 1つの文字列として返す.
char*	bsq_read_file(int ifd) {
	char*	content = read_all_text(ifd);
	if (content == NULL) {
		return (NULL);
	}
	// content は改行(nl)で終わっている必要があるので, それを確認する
	if (!is_nl_ended_content(content)) {
		free(content);
		return (NULL);
	}
	content[ft_strlen(content) - 1] = '\0';
	// NOTE: bsq_split で余計な空文字列を生成させないための措置
	// NOTE: content が改行で終わっているので, ft_strlen(content) >= 1 が保証される
	return (content);
}
