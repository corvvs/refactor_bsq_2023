/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:32:57 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/07 19:33:25 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// ifd から全データを読み取り, 1つの文字列に結合して返す
static char	*ft_read_all(int ifd)
{
	char	*content;
	char	buf[FT_BUFSIZ + 1];
	int		n;

	content = NULL;
	while ((n = read(ifd, buf, FT_BUFSIZ)) > 0)
	{
		buf[n] = '\0';
		if (content == NULL)
			content = ft_strdup(buf);
		else
			content = ft_strjoin(content, buf);
	}
	return (content);
}

char*	read_content(int fd) {
	char*	content = ft_read_all(fd);
	if (content == NULL) {
		return (NULL);
	}
	if (validate_content_ends_with_nl(content) == FAIL) {
		free(content);
		return (NULL);
	}
	content[ft_strlen(content) - 1] = '\0'; // bsq_split で余計な空文字列を生成させないための措置
	return (content);
}
