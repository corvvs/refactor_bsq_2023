/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_validate_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:16:44 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/09 21:16:45 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// content が改行で終了していることを確認する
bool		bsq_validate_content(const char *content) {
	size_t	n = ft_strlen(content);
	if (n == 0) {
		DEBUGERR("%s", "empty content");
		return (false);
	}

	if (content[n - 1] != '\n') {
		DEBUGERR("does not end with nl: %c", content[n - 1]);
		return (false);
	}
	return (true);
}
