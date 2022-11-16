/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:51:01 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/15 12:58:11 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	cont;

	cont = 0;
	while (str[cont] != '\0')
	{
		cont++;
	}
	return (cont);
}

/*int	main(void)
{
	char	a[] = "aasadaswwdwdwdqwa";
	char	*ptr;
	int		contador;

	ptr = a;
	contador = ft_strlen(ptr);
	printf("%d\n", contador);
}*/