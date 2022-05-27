/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:28:36 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/23 10:24:56 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	get_digit(float nbr, int i)
{
	int	n;

	while (nbr - (float)((int)nbr) != 0)
		nbr *= 10;
	n = (int)nbr;
	while (i < (int)(nbr_length(n) - 1))
		n = n / 10;
	n = n % 10;
	if (n < 0)
		n = n * -1;
	n += 48;
	return ((char)n);
}

static void	edges(float *f, int *zero_c, char *str, int *i)
{
	if (*f < 0)
	{
		str[*i] = '-';
		(*i)++;
	}
	if ((int)*f == 0)
	{
		str[(*i)++] = '0';
		str[(*i)++] = '.';
		*zero_c += 2;
		*f *= 10;
	}
	while ((int)*f == 0)
	{
		str[(*i)++] = '0';
		*zero_c += 1;
		*f *= 10;
	}
}

char	*ft_ftoa(float f, int prec)
{
	char	*str;
	int		len;
	int		i;
	int		zero_c;

	len = ((int)nbr_length((int)f) + 1 + prec);
	str = ft_strnew((size_t)len);
	i = 0;
	zero_c = 0;
	if (f < 0 && (int)f == 0)
		len++;
	edges(&f, &zero_c, str, &i);
	while (i < len)
	{
		if ((int)nbr_length((int)f) == i)
		{
			zero_c += 1;
			str[i] = '.';
			i++;
		}
		str[i] = get_digit(f, i - zero_c);
		i++;
	}
	return (str);
}
