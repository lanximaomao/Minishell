/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:23:45 by lliu              #+#    #+#             */
/*   Updated: 2023/07/31 16:04:37 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** 386 = 255 + 1 + 130
** rl_on_new_line: 移动到新行，保留输入，否则会直接清空当前输入
** rl_replace_line: 替换为空字符，需要在display之前
** rl_redisplay: 重新显示当前命令行prompt + replace_line函数所替换的rl_line_buffer
*/
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exitcode == 256 || g_exitcode == 386)
			g_exitcode = 386;
		else
		{
			ft_printf("\n");
			g_exitcode = 1;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		(void)sig;
		return ;
	}
}

/* SIGQUIT: parent process ignore and quit in child process */
void	handle_cmd(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		(void)sig;
	}
	else if (sig == SIGQUIT)
		ft_printf("Quit: %d\n", sig);
	return ;
}

/*
** ioctl(0, TIOCSTI, "\x04"); heredoc结束，自动添加ctrl D EOF。
** 不能使用的原因是，如果EOF了之后行为会与heredoc的^D时一致，导致无法换行。
** heredoc中，ctrl+d新的prompt不换行，而ctrl+c新的prompt换行
** ioctl(0, TIOCSTI, "\n"): heredoc结束，自动添加"\n"
** printf("\033[1A"); 光标上移一行
*/
void	handle_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		ft_printf("\033[1A");
		g_exitcode = -2;
	}
	else
		g_exitcode = sig;
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}
