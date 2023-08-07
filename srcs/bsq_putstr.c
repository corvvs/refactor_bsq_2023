/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:46:13 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 01:36:27 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	ft_putstr_fd(int fd, const char *str) {
	ft_putnstr_fd(fd, str, SIZE_MAX);
}

void	ft_putnstr_fd(int fd, const char *str, size_t max_len) {
	size_t			len = ft_strlen(str);
	if (len > max_len) {
		len = max_len;
	}
	const size_t	batch_len = 1024;
	while (len >= batch_len) {
		write(fd, str, batch_len);
		str += batch_len;
		len -= batch_len;
	}
	if (len > 0) {
		write(fd, str, len);
	}
}
