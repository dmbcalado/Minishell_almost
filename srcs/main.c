/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 06:49:28 by anfreire          #+#    #+#             */
/*   Updated: 2022/11/28 16:32:05 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	g_exit;

int	walk_till_executable(t_data *data, int i)
{
	int	len;
	int	flag;

	len = 0;
	flag = 0;
	while (data->par_line[len])
		len++;
	if (len <= i + 1)
		return (-1);
	else
	{
		while (data->par_line[++i])
		{
			if (builtin_detector(data, data->par_line[i]) >= 0)
				break ;
			else if (cmd_detector(data, data->par_line[i]) == 1 && \
			data->paths.p_str != NULL)
				break ;
			else if (redir_detector(data, data->par_line[i]) == 1)
				flag++;
		}
	}
	if (flag > 1)
		command_not_found(data);
	if (i == len)
		return (-1);
	return (i - 1);
}

void	brain(t_data *data)
{
	int	i;

	i = -1;
	if (data->line == NULL || data->line[0] == '\0')
		return ;
	while (data->par_line[++i])
	{
		if (builtin_detector (data, data->par_line[i]) >= 0)
		{
			parse_builtin(data, i, data->built.b_counter);
			exec_builtin(data, data->redir.r_counter, i);
			data->built.b_counter++;
		}
		else if (cmd_detector(data, data->par_line[i]) > 0 && \
		data->paths.p_str != NULL)
		{
			run_command(data, data->redir.r_counter, data->cmd.c_counter, i);
			data->cmd.c_counter++;
			data->redir.r_counter++;
		}
		i = walk_till_executable(data, i);
		if (i < 0)
			break ;
	}
	close_files(data);
}

void	close_files(t_data *data)
{
	int	i;
	int	size;

 	i = -1;
	size = data->cmd.cmd_nbr + data->built.builtin_n;
	while (++i < size)
		close(data->ids.pfd[i][1]);
	i = -1;
	while (++i < size)
		close(data->ids.pfd[i][0]);
	i = -1;
	while (++i < size)
		waitpid(data->ids.id[i], &g_exit, 0);
	WEXITSTATUS(g_exit);
	if (g_exit == 2)
		g_exit = 130;
	else if (g_exit == 131)
		g_exit = 131;
	else
		g_exit /= 256;
}

void	starting_vars(t_data *data)
{
	data->andre.args = 0;
	data->cmd.c_counter = 0;
	data->built.b_counter = 0;
	data->redir.r_counter = 0;
	data->redir.father_flag = 0;
	data->redir.hdoc_id = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc < 1 || *argv == NULL)
		return (0);
	starting(&data, envp);
	while (1)
	{
		get_line(&data);
		starting_vars(&data);
		parse_line(&data);
		get_paths(&data);
		if (data.paths.p_str != NULL)
		{
			parse_alloc(&data);
			if (redirect(&data) < 0)
				continue ;
			parse_cmds(&data);
			brain(&data);
			free_line_info(&data);
		}
	}
	return (0);
}
