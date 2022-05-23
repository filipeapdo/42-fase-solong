/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:13:29 by fiaparec          #+#    #+#             */
/*   Updated: 2022/02/26 06:36:38 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (f)(unsigned int, char))
{
	char			*s_fnc;
	unsigned int	i;

	if (!s)
		return (NULL);
	s_fnc = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s_fnc)
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		*(s_fnc + i) = f(i, *(s + i));
		i++;
	}
	*(s_fnc + i) = '\0';
	return (s_fnc);
}
