/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 21:26:44 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static void	notice_error(const char* message) {
	ft_putstr_fd(STDERR_FILENO, message);
	ft_putstr_fd(STDERR_FILENO, "\n");
}

static void	run_for_stdin(void) {
	DEBUGINFO("start bsq session for %s", "STDIN");

	if (!bsq_run_session(STDIN_FILENO)) {
		notice_error(BSQ_ERR_MSG_MAP);
	}
}

static void	run_for_file(const char* filename) {
	DEBUGINFO("start bsq session for \"%s\"", filename);

	int	ifd = open(filename, O_RDONLY);
	if (ifd < 0) {
		DEBUGERR("failed to open file: \"%s\"", filename);
		notice_error(BSQ_ERR_MSG_FILEOPEN);
		return ;
	}

	if (!bsq_run_session(ifd)) {
		notice_error(BSQ_ERR_MSG_MAP);
	}

	close(ifd);
}

int		main(int argc, char *argv[]) {
	if (argc < 2) {
		run_for_stdin();
		return (0);
	}

	for (int i = 1; i < argc; i += 1) {
		if (1 < i) {
			ft_putstr_fd(STDOUT_FILENO, "\n");
		}
		run_for_file(argv[i]);
	}
	return (0);
}
