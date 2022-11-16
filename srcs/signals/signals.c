/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:22:28 by anfreire          #+#    #+#             */
/*   Updated: 2022/11/15 13:31:16 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;
/* *************************************************************************** */
/*							 Ctrl-C - SIGINT								   */
/*							 Ctrl-\ - SIGQUIT								   */
/*				 source: https://www.computerhope.com/unix/signals.htm         */
/* *************************************************************************** */
void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
		g_exit = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");//injetar input no terminal
		rl_replace_line("", 0);
		rl_on_new_line();
    }
}

void    sig_handler_one(int signum)
{
    if (signum == SIGINT)
    {
		g_exit = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
    }
}

void	back_slash(int sig)
{
	if (sig == SIGQUIT)
	{
		g_exit = 131;
		printf("Quit (core dumped)\n");	
	}
}
