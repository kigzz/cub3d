/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 03:02:10 by bpouchep          #+#    #+#             */
/*   Updated: 2022/01/25 03:13:37 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	save_new_line_support(char *store, char *tmp, char *buf, int i)
{
	int	j;

	j = -1;
	while (buf[++j] && (ft_strlen(store) + j + 1) < (ft_strlen(store) + i + 1))
		tmp[ft_strlen(store) + j] = buf[j];
	tmp[ft_strlen(store) + j] = '\0';
	free(store);
}
