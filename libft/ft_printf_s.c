/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:50:15 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 11:50:39 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pf_s_default_handler(t_print *tab)
{
	tab->zero = 0;
	tab->sign = 0;
	tab->spce = 0;
	tab->hash = 0;
}

int	printf_s(t_print *tab, char *s)
{
	char	*str;

	str = ft_strdup(s);
	if (!str && tab->prec >= 0 && tab->prec <= 5)
		str = ft_strdup("");
	else if (!str)
		str = ft_strdup("(null)");
	pf_s_default_handler(tab);
	if (tab->prec >= 0 && (size_t)tab->prec <= ft_strlen(str))
		str = pf_substrswap(str, 0, tab->prec);
	if (tab->wdth > 0 && tab->dash)
		str = pf_dash_or_zero_handler(tab, str, " ");
	else if (tab->wdth > 0 && !tab->dash)
		str = pf_wdth_handler(tab, str);
	ft_putstr_fd(str, 1);
	tab->size += ft_strlen(str);
	free(str);
	return (tab->size);
}
