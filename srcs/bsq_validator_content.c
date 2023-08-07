/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_validator_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:32:57 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/08 01:57:20 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// content が改行で終了していることを確認
bool		is_nul_terminated_content(char *content) {
	size_t	n = ft_strlen(content);
	return (n > 0 && content[n - 1] == '\n');
}
