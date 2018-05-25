/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 07:59:04 by slegros           #+#    #+#             */
/*   Updated: 2018/05/20 17:31:54 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_sigint(int signo)
{
	pid_t	pid;
	t_h		the;

	if (signo)
	{
		the = ft_history(0, NULL, 0);
		pid = ft_pid(0, 0);
		if (pid > 0)
		{
			kill(pid, 9);
			ft_putchar_fd('\n', 0);
			ft_exit_value(1, 130);
		}
		else
		{
			if (ft_button_select(0, 0) != 1 && ft_sigupk(0, 0) != 1)
			{
				ft_hist_return(the, 2);
				ft_history(13, NULL, 0);
				ft_control_c(1, 1);
				ft_putstr_col_fd(ft_where(0, NULL), BOLD, 0);
			}
		}
		pid = ft_pid(-1, 1);
	}
}

static void		ft_sigkill(int signo)
{
	t_blt	cmd;

	cmd.cmd = ft_strdup("exit");
	cmd.opt = NULL;
	cmd.args = ft_dbarrnew(1);
	cmd.args[0] = ft_strdup(ft_itoa(signo + 128));
	ft_exec_exit(cmd);
}

static void		ft_signal_resize(int signo)
{
	t_h		the;

	if (signo)
	{
		if (ft_button_select(0, 0) != 1)
		{
			the = ft_history(0, NULL, 0);
			ft_get_winsize(1);
			while (ft_strlen(ft_where(0, NULL)) + the.j > 0)
			{
				ft_hist_move_left(&the, 0);
				the.j--;
			}
			ft_putstr_fd(tgetstr("cd", NULL), 0);
			ft_putstr_col(ft_where(0, NULL), BOLD);
			ft_putstr(the.hist[the.i]);
		}
	}
}

static void		ft_signal_passif(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGIO, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGWINCH, ft_signal_resize);
}

void			ft_signal(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGHUP, ft_sigkill);
	signal(SIGILL, ft_sigkill);
	signal(SIGTRAP, ft_sigkill);
	signal(SIGABRT, ft_sigkill);
	signal(SIGEMT, ft_sigkill);
	signal(SIGFPE, ft_sigkill);
	signal(SIGKILL, ft_sigkill);
	signal(SIGBUS, ft_sigkill);
	signal(SIGSEGV, ft_sigkill);
	signal(SIGSYS, ft_sigkill);
	signal(SIGPIPE, ft_sigkill);
	signal(SIGALRM, ft_sigkill);
	signal(SIGSTOP, ft_sigkill);
	signal(SIGXCPU, ft_sigkill);
	signal(SIGXFSZ, ft_sigkill);
	signal(SIGVTALRM, ft_sigkill);
	signal(SIGPROF, ft_sigkill);
	signal(SIGUSR1, ft_sigkill);
	signal(SIGUSR2, ft_sigkill);
	ft_signal_passif();
}
