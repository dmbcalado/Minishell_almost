/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridges.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:20:36 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/18 20:58:54 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	bridge_infiles(t_data *data, int index)
{
	int	i;
	int	ret;
	int	count;

	i = -1;
	ret = 0;
	while (++count <= index)
	{
		while (data->par_line[++i])
		{
			if (count == index)
				ret = bridging_infiles(data, i);
			if (ret == -2)
				break ;
			else if (ret == -1)
				return (-1);
		}
	}
	return (1);
}

int	bridging_infiles(t_data *data, int i)
{
	int	ret;

	ret = redir_detector (data, data->par_line[i]);
	if (ret == 1)
		return (-2);
	if (ret > 1)
	{
		if (ret < 3 && i != data->redir.last)
		{
			if (open(data->par_line[i + 1], O_RDONLY) < 0)
			{
				printf("Error: the file %s does not exist.", data->par_line[i + 1]);
				return (-1);
			}
			printf("bridged : %s\n",data->par_line[i + 1]);
		}
	}
	return (1);
}

int	bridge_outfiles(t_data *data, int index)
{
	int	i;
	int	ret;
	int	count;

	i = -1;
	count = -1;
	while (++count <= index)
	{
		while (data->par_line[++i])
		{
			if (count == index)
				ret = bridging_outfiles(data, i);
			if (ret == 0)
				break ;
			else if (ret == -1)
				return (-1);
		}
	}
	return (1);
}

int	bridging_outfiles(t_data *data, int i)
{
	int	ret;

	while (data->par_line[i])
	{
		ret = redir_detector (data, data->par_line[i]);
		if (ret == 1)
			return (0);
		if (ret > 1)
		{
			if (ret > 3 && i != data->redir.last)
			{
				printf("%d entrou para dar bridge a %s\n", i, data->par_line[i + 1]);
				if (open(data->par_line[i + 1], O_CREAT | O_RDWR | O_TRUNC, 777) < 0)
					return (-1);
			}
		}
		i++;
	}
	return (i);
}

