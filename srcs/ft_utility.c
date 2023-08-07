/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:44:48 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:46:16 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

size_t		ft_strlen(const char *str) {
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_is_printable(char c)
{
	if (c < 0x20 || c == 0x7f)
		return (0);
	return (1);
}
