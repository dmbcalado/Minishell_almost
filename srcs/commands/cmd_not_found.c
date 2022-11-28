/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_not_found.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:26:55 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/23 18:26:23 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	command_not_found(t_data *data)
{
	int	i;
	int	len;

	i = -1;
	while (data->par_line[++i] != NULL)
	{
		if (redir_detector(data, data->par_line[i]) == 0)
		{
			len = ft_strlen(data->par_line[i]);
			write(2, data->par_line[i], len);
			write(2, ": command not found\n", 19);
			break ;
		}
		else if (data->par_line[i + 2])
			i++;
	}
}
