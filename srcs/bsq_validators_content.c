/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_validators_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:32:57 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/08 11:21:19 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// content が改行で終了していることを確認
bool		is_nl_ended_content(char *content) {
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
