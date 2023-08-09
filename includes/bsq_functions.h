/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_functions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:16:03 by corvvs            #+#    #+#             */
/*   Updated: 2023/08/09 21:16:05 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_FUNCTIONS_H
#define BSQ_FUNCTIONS_H

#include "bsq_common.h"
#include "bsq_structures.h"

// bsq_run_session.c
bool		bsq_run_session(int fd);

// bsq_map.c
bool		bsq_generate_map(int fd, t_map *map_ptr);
void		bsq_destroy_map(t_map* map);

// bsq_read_file.c
char*		bsq_read_file(int fd);

// bsq_validate_content.c
bool		bsq_validate_content(const char *content);

// bsq_validate_lines.c
bool		bsq_validate_lines(char** const lines);

// bsq_validate_map.c
bool		bsq_validate_map(const t_map *map);

// bsq_find_out_bsq.c
t_square	bsq_find_out_bsq(const t_map* map);

// bsq_split.c
char**		bsq_split(char* str, char delimiter);

#endif
