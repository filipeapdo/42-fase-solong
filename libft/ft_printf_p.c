/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:11:31 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 11:47:26 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pf_p_default_handler(t_print *tab, unsigned long int n)
{
	tab->zero = 0;
	tab->sign = 0;
	tab->spce = 0;
	tab->hash = 1;
	if (n == 0)
		tab->hash = 0;
}

int	printf_p(t_print *tab, unsigned long int n)
{
	char	*str;

	pf_p_default_handler(tab, n);
	if (n == 0)
		str = ft_strdup("(nil)");
	else
		str = pf_itoa_base_ul(n, 16, 'x');
	if (tab->dash || (n != 0 && tab->zero && tab->prec == 1))
		str = pf_dash_or_zero_handler(tab, str, "0");
	else if (n == 0 && tab->zero && tab->prec == 1)
		str = pf_dash_or_zero_handler(tab, str, " ");
	if (tab->hash)
		str = pf_hash_handler(str, 'x');
	if (tab->sign || tab->spce)
		str = pf_sign_or_spce_handler(tab, str);
	str = pf_wdth_handler(tab, str);
	ft_putstr_fd(str, 1);
	tab->size += ft_strlen(str);
	free(str);
	return (tab->size);
}
