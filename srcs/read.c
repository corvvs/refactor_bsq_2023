/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:32:57 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/08 01:56:33 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#define FT_BUFSIZ (1u << 16)

// ifd から全データを読み取り, 1つの文字列に結合して返す
static char*	read_all_text(int ifd) {
	t_capped_buffer	joined = {};
	char			read_buffer[FT_BUFSIZ];

	while (true) {
		ssize_t	read_size = read(ifd, read_buffer, sizeof(read_buffer));
		if (read_size < 0) {
			free(joined.buffer);
			return (NULL);
		} else if (read_size == 0) {
			break ;
		}
		// 読み取ったデータを capped_buffer に保存する
		if (!store_to_capped_buffer(&joined, read_buffer, read_size, sizeof(read_buffer))) {
			free(joined.buffer);
			return (NULL);
		}
	}
	// 最後に NUL を入れる
	if (!store_to_capped_buffer(&joined, "", ft_strlen("") + 1, sizeof(read_buffer))) {
		free(joined.buffer);
		return (NULL);
	}
	return (joined.buffer);
}

char*	read_content(int ifd) {
	char*	content = read_all_text(ifd);
	if (content == NULL) {
		return (NULL);
	}
	// content は改行(nl)で終わっていて欲しい
	if (!is_nul_terminated_content(content)) {
		free(content);
		return (NULL);
	}
	content[ft_strlen(content) - 1] = '\0'; // bsq_split で余計な空文字列を生成させないための措置
	return (content);
}
