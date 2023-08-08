/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 16:11:21 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static void	bsq_for_stdin(void) {
	DEBUGINFO("ping session for %s", "STDIN");
	bsq_run_session(STDIN_FILENO);
}

static void	bsq_for_arguments(int argc, char **argv) {
	for (int i = 0; i < argc; ++i) {
		if (0 < i) {
			ft_putstr_fd(STDIN_FILENO, "\n");
		}

		int ifd = open(argv[i], O_RDONLY);
		DEBUGINFO("ping session for \"%s\"", argv[i]);
		bsq_run_session(ifd);
		if (ifd < 0) {
			continue;
		}
		close(ifd);
	}
}

int		main(int argc, char *argv[]) {
	if (argc < 2) {
		bsq_for_stdin();
	} else {
		bsq_for_arguments(argc - 1, argv + 1);
	}
	return (0);
}
