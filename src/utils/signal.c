/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunhole <hyunhole@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 00:36:48 by hyunhole          #+#    #+#             */
/*   Updated: 2022/09/23 00:36:48 by hyunhole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void set_signal(int sig_int, int sig_quit)
{
	if (sig_int == IGN)
		signal(SIGINT, SIG_IGN);
	if (sig_int == DFL)
		signal(SIGINT, SIG_DFL);
	if (sig_int == SHE)
		signal(SIGINT, signal_handler);
	if (sig_quit == IGN)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == DFL)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == SHE)
		signal(SIGQUIT, signal_handler);
}