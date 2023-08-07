/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 02:47:33 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int		main(int argc, char *argv[]) {
	if (argc < 2) {
		// [from stdin]
		run_bsq_session(STDIN_FILENO);
		return (0);
	}
	// [using arguments]
	for (int i = 1; i < argc; ++i) {
		if (1 < i) {
			ft_putstr_fd(STDIN_FILENO, "\n");
		}
		int ifd = open(argv[i], O_RDONLY);
		run_bsq_session(ifd);
		if (ifd < 0) {
			close(ifd);
		}
	}
	return (0);
}
