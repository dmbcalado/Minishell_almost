/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:54:26 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/15 13:15:16 by anfreire         ###   ########.fr       */
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
}
