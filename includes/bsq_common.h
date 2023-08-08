/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_common.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 19:10:20 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_COMMON_H
#define BSQ_COMMON_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>

#define N_LETTER_TYPES		3
#define BSQ_ERROR_MESSAGE	"map error\n"

#ifdef __APPLE__
#define U64T "%llu"
#else
#define U64T "%lu"
#endif

#endif
