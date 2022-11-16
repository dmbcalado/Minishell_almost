/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 22:17:20 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/15 13:02:44 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;
//safety numeros

static int	starts_with_wrong_char(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)\
	|| c == 95)
		return (0);
	else
		return (1);
}

void	unset(t_data *data, char *str)
{
	int		i;
	int		j;
	int		flag;
	char	**new_envp;

	j = 0;
	flag = 0;
	i = env_var_detector(data, str);
	if (starts_with_wrong_char(str[0]))
	{
		printf("minishell: unset: \'%s\': not a valid identifier\n", str);
		g_exit = 1;
		return ;
	}
	printf("i %d\n", i);
	g_exit = 0;
	if (i >= 0)
	{
		while (data->envp[j])
			j++;
		new_envp = (char **)malloc(j * sizeof(char *));
		new_envp[j - 1] = NULL;
		j = -1;
		while(data->envp[++j])
		{
			if (j != i)
				new_envp[j - flag] = selection(data, j);
			else
				flag = 1;
			free(data->envp[j]);
		}
		free(data->envp);
		data->envp = new_envp;
	}
}

char	*selection(t_data *data, int j)
{
	int		len;
	char	*str;


	len = len_str(data->envp[j]);
	str = (char *)malloc((len + 1) * sizeof(char));
	str[len] = 0;
	len = -1;
	while (data->envp[j][++len])
		str[len] = data->envp[j][len];
	return (str);
}


int	env_var_detector(t_data *data, char *str)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (data->envp[++i])
	{
			j = -1;
			len = len_str(data->envp[i]);
			while (str[++j] && j < len)
			{
				if (str[j] != data->envp[i][j])
					break ;
			}
			len = len_str(str);
			if (j == len)
				return (i);
	}
	return (-1);
}
