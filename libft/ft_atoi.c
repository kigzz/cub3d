/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:19:54 by bpouchep          #+#    #+#             */
/*   Updated: 2020/07/15 20:20:00 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long long unsigned	n;
	int					sign;
	long long unsigned	max;

	sign = 1;
	max = 9223372036854775807;
	n = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		sign = -sign;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = 10 * n + (*nptr - '0');
		if (n > max && sign == 1)
			return (-1);
		if (n > max + 1 && sign == -1)
			return (0);
		nptr++;
	}
	return (sign * n);
}
