/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <mhdeeb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:11:48 by mhdeeb            #+#    #+#             */
/*   Updated: 2025/10/12 11:46:11 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

int	is_digit(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			i++;
			continue ;
		}
		return (0);
	}
	return (1);
}

int	valid(char *str)
{
	int	flag1;
	int	flag3;

	flag1 = is_digit(str);
	flag3 = (ft_atoi(str) <= 0);
	if (!flag1)
		return (0);
	if (flag3)
		return (0);
	return (1);
}
