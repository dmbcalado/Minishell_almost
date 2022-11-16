/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:35:12 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/12 18:25:53 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

// else if(data->built.args == 2)
// 		export_var (data, data->built.builtin[index][1]);

static int	starts_with_wrong_char(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)\
	|| c == 95)
		return (0);
	else
		return (1);
}

static int	is_in_char_set(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)\
	 || (c >= 97 && c <= 122) || c == 95 || c == 61)
		return (1);
	else
		return (0);
}

static int	is_not_valid(t_data *data, int arg)
{
	int	i;

	if (starts_with_wrong_char(data->par_line[arg][0]))
		return (1);
	i = -1;
	while (data->par_line[arg][++i])
	{
		if (!is_in_char_set(data->par_line[arg][i]))
			return (1);
	}
	return (0);
}

static void	has_equal_sign(t_data *data, int arg)
{
	int	i;

	i = -1;
	while (data->par_line[arg][++i])
	{
		if (data->par_line[arg][i] == 61)
		{
			export_var(data, data->par_line[arg]);
			return ;
		}
	}
}

void	parse_export(t_data *data)
{
	int	i;

	i = 0;
	g_exit = 0;
	while (data->par_line[++i])
	{
		if (is_not_valid(data, i))
		{
			printf("minishell: export: \'%s\': not a valid identifier\n", data->par_line[i]);
			g_exit = 1;
		}
		else
			has_equal_sign(data, i);
	}
}