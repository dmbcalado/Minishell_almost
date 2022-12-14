/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:59:01 by anfreire          #+#    #+#             */
/*   Updated: 2022/11/15 13:13:03 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

static void	change_shlvl(t_data *data)
{
	int		i;
	int		value;
	char	*value_in_str;

	i = env_var_detector(data, "SHLVL");
	value_in_str = strchr(data->envp[i], '=') + 1;
	value = ft_atoi(value_in_str);
	value++;
	free(data->envp[i]);
	value_in_str = ft_itoa(value);
	data->envp[i] = ft_strjoin("SHLVL=", value_in_str);
	free(value_in_str);
}	

// https://www.geeksforgeeks.org/exit-status-child-process-linux/

void	run_minishell(t_data *data, int index)
{
	int		in_fd;
	int		out_fd;
	char	*av[] = {"/bin/bash", "./minishell", NULL};

	in_fd = 0;
	out_fd = 1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	data->ids.id[index] = fork();
	if (data->ids.id[index] == 0)
	{
		if (in_fd > 0)
			dup2 (in_fd, STDIN_FILENO);
		if (out_fd > 1)
			dup2 (out_fd, STDOUT_FILENO);
		change_shlvl(data);
		execve ("./minishell", av, data->envp);
	}
	else
	{
		waitpid(data->ids.id[index], &g_exit, 0);
		WEXITSTATUS(g_exit);
		g_exit /= 256;
		return ;
	}
}
