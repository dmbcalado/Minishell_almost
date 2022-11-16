/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 04:02:05 by anfreire          #+#    #+#             */
/*   Updated: 2022/11/12 16:06:20 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

void	b_cd(t_data *data)
{
	int	i;
	
	i = 0;
	while (data->par_line[i])
		i++;
	if (i > 2)
	{
		printf("Minishell: cd: too many arguments\n");
		g_exit = 1;
		return;
	}
	else if (i == 1 || (strncmp(data->par_line[1], "~", 2) == 0 && i == 2))
	{
		chdir(getenv("HOME"));
		g_exit = 0;
		return ;
	}
	else if (chdir(data->par_line[1]) != 0)
	{
		printf("Minishell: cd: %s: No such file or directory\n", data->par_line[1]);
		g_exit = 1;
		return ;
	}
	g_exit = 0;
}
