/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 19:26:50 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 10:20:28 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_length(int n)
{
	int	len;

	if (n > 0)
		len = 0;
	else
		len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*nptr;

	len = check_length(n);
	nptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!nptr)
		return (NULL);
	if (n == -2147483648 && ft_strlcpy(nptr, "-2147483648\0", 12))
		return (nptr);
	if (n == 0 && ft_strlcpy(nptr, "0\0", 2))
		return (nptr);
	if (n < 0)
	{
		*(nptr + 0) = '-';
		n = -n;
	}
	*(nptr + len) = '\0';
	while (n > 0)
	{
		len--;
		*(nptr + len) = n % 10 + '0';
		n /= 10;
	}
	return (nptr);
}
