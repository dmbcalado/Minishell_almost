/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinhosujo <ratinhosujo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:29:28 by anfreire          #+#    #+#             */
/*   Updated: 2022/11/15 15:37:51 by ratinhosujo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../header.h"

extern int	g_exit;
// colects environment intrinsic to the computer and allocates
// to our own environment.

void	get_envp(t_data *data, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	data->envp = (char **)malloc((i + 1) * sizeof(char *));
	data->envp[i] = NULL;
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while(envp[i][j])
			j++;
		data->envp[i] = (char *)malloc((j + 1) * sizeof(char));
		data->envp[i][j] = '\0';
		j = -1;
		while(envp[i][++j] != 0)
			data->envp[i][j] = envp[i][j];
	}
}

// built-in that performs the function of env in our own
// environment.

void	env(t_data *data)
{
	int	i;

	i = -1;
	if (data->par_line[1])
	{
		printf("env: \'%s\': No such file or directory\n", data->par_line[1]);
		g_exit = 127;
		return ;
	}
	while (data->envp[++i])
		printf("%s\n",data->envp[i]);
	g_exit = 0;
}