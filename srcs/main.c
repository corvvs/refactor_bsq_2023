/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 19:13:45 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static void	bsq_for_stdin(void) {
	DEBUGINFO("ping session for %s", "STDIN");
	bsq_run_session(STDIN_FILENO);
}

static void	bsq_for_file(const char* filename) {
	int ifd = open(filename, O_RDONLY);
	DEBUGINFO("ping session for \"%s\"", filename);
	bsq_run_session(ifd);
	if (ifd < 0) {
		return ;
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
			ft_putstr_fd(STDIN_FILENO, "\n");
		}
		bsq_for_file(argv[i]);
	}
	return (0);
}
