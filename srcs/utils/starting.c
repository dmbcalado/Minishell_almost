/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:54:26 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/21 19:28:56 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

void	starting(t_data *data, char *envp[])
{
	signal (SIGQUIT, SIG_IGN);
	signal (SIGINT, sig_handler);
	get_envp (data, envp);
	data->line = NULL;
	g_exit = 0;
	data->redir.hdoc_key = NULL;
}
