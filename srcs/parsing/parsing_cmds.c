/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinhosujo <ratinhosujo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 01:04:26 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/17 05:22:53 by ratinhosujo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

// -----------------------------------------------------------------------------
// Function allocates all data gpaths.iven for the commands, and stores cmdx.
// matrix that has the format exemplified below:
// cmdx[cmd n-1]+...  [0] = "ls"	;	[1] = "-a"
// cmdx[cmd n]  +... [0] = "grep"	;	[1] = "hello"
// -----------------------------------------------------------------------------

int	count_cmd_args(t_data *data, int i)
{
	int	count;

	count = 0;
	while (data->par_line[++i])
	{
		if (builtin_detector (data, data->par_line[i]) >= 0)
			break ;
		if (redir_detector (data, data->par_line[i]) > 0)
			break ;
		if (cmd_detector (data, data->par_line[i]) == 1)
			break ;
		count++;
	}
	return (count);
}

int	get_cmd_i(t_data *data, int index)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (data->par_line[++i])
	{
		if (cmd_detector (data, data->par_line[i]) == 1)
		{
			if (builtin_detector(data, data->par_line[i]) == -1)
				count++;
		}
		else if (cmd_detector (data, data->par_line[i]) == 2)
			count++;
		if (count == index + 1)
			break ;
	}
	return (i);
}

void	parse_cmd(t_data *data, int index)
{
	int	i;
	int	j;
	int	k;
	int	count;

	j = -1;
	i = get_cmd_i(data, index);
	count = count_cmd_args(data, i);
	if (cmd_detector(data, data->par_line[i]) == 2)
	{
		printf("entra no true path\n");
		true_path(data, index, i, count);
		return ;
	}
	data->cmd.cmdx[index] = (char **)malloc((count + 2) * sizeof(char *));
	data->cmd.cmdx[index][count + 1] = NULL;
	while (++j <= count)
	{
		k = 0;
		while (data->par_line[i][k])
			k++;
		data->cmd.cmdx[index][j] = (char *)malloc((k + 1) * sizeof(char));
		data->cmd.cmdx[index][j][k] = '\0';
		k = -1;
		while (data->par_line[i][++k])
			data->cmd.cmdx[index][j][k] = data->par_line[i][k];
		i++;
	}
}

void	true_path(t_data *data, int index, int i, int count)
{
	int	j;
	int	start;
	int	len;

	j = 0;
	while (data->par_line[i][j])
	{
		if(data->par_line[i][j] == '/')
		{
			start = j + 1;
			len = 0;
		}
		j++;
		len++;
	}
	data->cmd.cmdx[index] = (char **)malloc((count + 2) * sizeof(char *));
	data->cmd.cmdx[index][count + 1] = NULL;
	data->cmd.cmdx[index][0] = (char *)malloc((len) * sizeof(char));
	data->cmd.cmdx[index][0][len - 1] = 0;
	len = 0;
	while (data->par_line[i][start])
	{
		data->cmd.cmdx[index][0][len] = data->par_line[i][start];
		start++;
		len++;
	}
	printf("%s\n", data->cmd.cmdx[index][0]);
	j = 0;
	while (++j < count)
	{
		i++;
		len = 0;
		while (data->par_line[i] && data->par_line[i][len])
			len++;
		data->cmd.cmdx[index][j] = (char *)malloc((len + 1) * sizeof(char));
		data->cmd.cmdx[index][j][len] = '\0';
		len = -1;
		while (data->par_line[i] && data->par_line[i][++len])
			data->cmd.cmdx[index][j][len] = data->par_line[i][len];
	}
}

void	parse_cmds(t_data *data)
{
	int	i;
	int	cmds;

	i = 0;
	cmds = data->cmd.cmd_nbr + 1;
	if (cmds > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	while (--cmds > 0)
	{
		parse_cmd (data, i);
		i++;
	}
}

// -----------------------------------------------------------------------------
// Function tests if theres the command executable file in the paths of my env.
// -----------------------------------------------------------------------------

int	acessing_cmd(t_data *data, int index, int i)
{
	int	j;
	int	c;

	j = -1;
	c = 0;
	while (data->paths.paths[c])
		c++;
	while (++j < c)
	{
		path_join (data, index, j);
		if (access(data->paths.path_cmd[index], X_OK) == 0 && \
		!is_dot_cmd(data->paths.path_cmd[index]))
			return (1);
		else
			free (data->paths.path_cmd[index]);
	}
	if (true_path_join(data, index, i) == 1)
		return (1);
	return (0);
}

int	true_path_join(t_data *data, int index, int i)
{
	int	j;

	j = 1;
	while(data->par_line[i][j])
		j++;
	data->paths.path_cmd[index] = (char *)malloc(j * sizeof(char));
	j = -1;
	while (data->par_line[i][++j])
		data->paths.path_cmd[index][j] = data->par_line[i][j];
	data->paths.path_cmd[index][i] = '\0';
	if (access(data->paths.path_cmd[index], X_OK) == 0 && \
		!is_dot_cmd(data->paths.path_cmd[index]))
		return (1);
	return (0);
}