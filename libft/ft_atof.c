/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:04:46 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/26 13:22:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_abs(long nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return (nbr);
}

double	ft_atof(const char *str)
{
	long	integ;
	double	fract;
	int		tens;
	int		sign;

	tens = 10;
	fract = 0;
	sign = 1;
	integ = ft_atoi(str);
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	str += nbr_length(integ);
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		fract = fract + (double)(*str - '0') / tens;
		tens *= 10;
		str++;
	}
	if (integ < 0)
		sign = -1;
	return (((double)ft_abs(integ) + fract) * sign);
}