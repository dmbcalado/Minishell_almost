/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:30:44 by anfreire          #+#    #+#             */
/*   Updated: 2022/11/16 22:43:27 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	parse_double_quotes(char ***dbl_ptr, char *line, int args, t_data *data)
{
	int		i;
	char	*str;

	str = ft_substr(line, 1, (ft_strchr(&line[1], '\"') - line - 1));
	i = ft_strlen(str) + 2;
	str = is_string_expandable(str, data);
	*dbl_ptr = build_list(args, *dbl_ptr, str, data);
	free(str);
	return (i);
}

static int	parse_single_quotes(char ***dbl_ptr, char *line, int args, t_data *data)
{
	int		i;
	char	*str;

	str = ft_substr(line, 1, (ft_strchr(&line[1], '\'') - line - 1));
	i = ft_strlen(str) + 2;
	*dbl_ptr = build_list(args, *dbl_ptr, str, data);
	free(str);
	return (i);
}

static int	parse_chars(char ***dbl_ptr, char *line, int args, t_data *data)
{
	int		i;
	int		flag;
	char	append[2];
	char	*str;

	append[0] = 0;
	append[1] = 0;
	flag = 0;
	i = 0;
	while (line[i] != ' ' && line[i] != '|' && !is_str_in_quotes(&line[i], '\'') && !is_str_in_quotes(&line[i], '\"') && line[i] != 0)
	{
		append[0] = line[i];
		str = realloc_string(str, append, flag);
		flag = 1;
		i++;
	}
	flag = 0;
	str = is_string_expandable(str, data);
	*dbl_ptr = build_list(args, *dbl_ptr, str, data);
	free(str);
	return (i);
}

static int	parse_pipe(char ***dbl_ptr, char *line, int args, t_data *data)
{
	char	*str;

	str = ft_substr(line, 0, 1);
	*dbl_ptr = build_list(args, *dbl_ptr, str, data);
	free(str);
	return (1);
}

void	parse_line(t_data *data)
{
	int		i;
	int		args;
	char	*line;
	char	**dbl_ptr;

	dbl_ptr = malloc(sizeof(char *));
	dbl_ptr[0] = NULL;
	line = data->line;
	trim_spaces(line);
	i = 0;
	args = 1;
	while (line[i])
	{
		if (is_str_in_quotes(&line[i], '\"'))
			i += parse_double_quotes(&dbl_ptr, &line[i], args, data);
		else if (is_str_in_quotes(&line[i], '\''))
			i += parse_single_quotes(&dbl_ptr, &line[i], args, data);
		else if (line[i] == '|')
		{
			if(dbl_ptr[args - 1] != NULL)
				args++;
			i += parse_pipe(&dbl_ptr, &line[i], args, data);
			if(dbl_ptr[args - 1] != NULL)
				args++;
		}
		else if (line[i] == ' ')
		{
			if(dbl_ptr[args - 1] != NULL)
				args++;
			while (line[i] == ' ')
				i++;
		}
		else if (line[i] != ' ' && line[i] != '|')
			i += parse_chars(&dbl_ptr, &line[i], args, data);
	}
	data->par_line = dbl_ptr;
}
