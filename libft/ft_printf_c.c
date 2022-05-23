/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:35:17 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 11:36:21 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pf_c_default_handler(t_print *tab)
{
	tab->zero = 0;
	tab->sign = 0;
	tab->spce = 0;
	tab->hash = 0;
	if (tab->wdth > 0)
		tab->wdth--;
}

int	printf_c(t_print *tab, char c)
{
	char	*str;

	str = ft_strdup("");
	pf_c_default_handler(tab);
	if (tab->wdth > 0 && tab->dash)
	{
		str = pf_dash_or_zero_handler(tab, str, " ");
		ft_putchar_fd(c, 1);
		ft_putstr_fd(str, 1);
	}
	else if (tab->wdth > 0 && !tab->dash)
	{
		str = pf_wdth_handler(tab, str);
		ft_putstr_fd(str, 1);
		ft_putchar_fd(c, 1);
	}
	else
		ft_putchar_fd(c, 1);
	tab->size += ft_strlen(str) + 1;
	free(str);
	return (tab->size);
}
