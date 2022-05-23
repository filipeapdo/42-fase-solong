/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:03:29 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 11:51:27 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_length_base_ul(unsigned long int n, int base)
{
	int	len;

	if (n > 0)
		len = 0;
	else
		len = 1;
	while (n != 0)
	{
		len++;
		n /= base;
	}
	return (len);
}

char	*pf_itoa_base_ul(unsigned long int n, int base, char conv)
{
	int		len;
	char	*nptr;

	len = check_length_base_ul(n, base);
	nptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!nptr)
		return (NULL);
	if (n == 0 && ft_strlcpy(nptr, "0\0", 2))
		return (nptr);
	*(nptr + len) = '\0';
	while (n > 0)
	{
		len--;
		if (base == 10 || (base == 16 && (n % base) < 10))
			*(nptr + len) = n % base + '0';
		else if (base == 16)
		{
			if (conv == 'x' || conv == 'p')
				*(nptr + len) = n % base + 87;
			else if (conv == 'X')
				*(nptr + len) = n % base + 55;
		}
		n /= base;
	}
	return (nptr);
}

char	*pf_joinswap(char *s1, char *s2, int right)
{
	char	*s_join;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s_join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s_join)
		return (NULL);
	ft_strlcpy(s_join, s1, ft_strlen(s1) + 1);
	ft_strlcat(s_join, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!right)
		free(s1);
	else
		free(s2);
	return (s_join);
}

char	*pf_substrswap(char *s, int start, int len)
{
	char	*s_substr;

	s_substr = ft_substr(s, start, len);
	free(s);
	return (s_substr);
}

t_print	*pf_init_reset_tab(t_print *tab, int init)
{
	if (!tab)
	{
		tab = (t_print *)malloc(sizeof(t_print));
		if (!tab)
			return (NULL);
	}
	if (init)
		tab->size = 0;
	tab->dash = 0;
	tab->zero = 0;
	tab->sign = 0;
	tab->spce = 0;
	tab->hash = 0;
	tab->wdth = 0;
	tab->prec = -1;
	return (tab);
}
