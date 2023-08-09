/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 21:15:48 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "debugout.h"

// NOTE: mac と Linux では uint64_t に対応するフォーマット指定子が違う
#ifdef __APPLE__
#define U64T "%llu"
#else
#define U64T "%lu"
#endif

// utils_number.c
bool	str_to_u64(const char* str, size_t max_len, uint64_t* result);

// utils_put.c
void	ft_putstr_fd(int fd, const char* str);
void	ft_putnstr_fd(int fd, const char* str, size_t max_len);

// utils_misc.c
size_t	ft_strlen(const char* str);
void*	ft_memcpy(void* dst, const void* src, size_t n);
bool	ft_is_printable(char c);

#endif
