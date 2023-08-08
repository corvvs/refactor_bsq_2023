/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 11:18:55 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_FUNCTIONS_H
#define BSQ_FUNCTIONS_H

#include "bsq_common.h"
#include "bsq_structure.h"

// bsq_run_session.c
bool		bsq_run_session(int fd);

// bsq_map.c
bool		bsq_generate_map(int fd, t_map *map_ptr);
void		bsq_destroy_map(t_map* map);

// bsq_read_file.c
char*		bsq_read_file(int fd);

// bsq_validators_content.c
bool		is_nl_ended_content(char *content);

// bsq_validators_lines.c
bool		are_valid_lines(char** const lines);

// bsq_validators_map.c
bool		is_valid_map(const t_map *map);

// bsq_get_maximum_square.c
t_square	bsq_get_maximum_square(size_t top, size_t left, const t_map* map);

// bsq_split.c
char**		bsq_split(char* str, char delimiter);

// utils_number.c
bool		str_to_u64(const char* str, size_t max_len, uint64_t* result);

// utils_put.c
void		ft_putstr_fd(int fd, const char* str);
void		ft_putnstr_fd(int fd, const char* str, size_t max_len);

// utils_misc.c
size_t 		ft_strlen(const char* str);
void*		ft_memcpy(void* dst, const void* src, size_t n);
bool		ft_is_printable(char c);

#endif
