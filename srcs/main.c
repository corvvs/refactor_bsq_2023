/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 23:41:26 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static void	bsq_for_stdin(void) {
	DEBUGINFO("start bsq session for %s", "STDIN");
	if (!bsq_run_session(STDIN_FILENO)) {
		ft_putstr_fd(STDERR_FILENO, BSQ_ERROR_MESSAGE);
	}
}

static void	bsq_for_file(const char* filename) {
	DEBUGINFO("start bsq session for \"%s\"", filename);
	int ifd = open(filename, O_RDONLY);
	if (ifd < 0) {
		ft_putstr_fd(STDERR_FILENO, BSQ_ERROR_MESSAGE);
		return ;
	}
	if (!bsq_run_session(ifd)) {
		ft_putstr_fd(STDERR_FILENO, BSQ_ERROR_MESSAGE);
	}
	close(ifd);
}

int		main(int argc, char *argv[]) {
	if (argc < 2) {
		bsq_for_stdin();
		return (0);
	}
	for (int i = 1; i < argc; ++i) {
		if (1 < i) {
			ft_putstr_fd(STDERR_FILENO, "\n");
		}
		bsq_for_file(argv[i]);
	}
	return (0);
}
