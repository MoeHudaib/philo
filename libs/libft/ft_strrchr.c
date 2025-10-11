/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:00:26 by mhdeeb            #+#    #+#             */
/*   Updated: 2025/08/10 13:00:41 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		last_occurrence;
	char	char_to_find;

	if (!str)
		return (NULL);
	char_to_find = (char)c;
	i = 0;
	last_occurrence = -1;
	while (str[i] != '\0')
	{
		if (str[i] == char_to_find)
			last_occurrence = i;
		i++;
	}
	if (char_to_find == '\0')
		return ((char *)&str[i]);
	if (last_occurrence == -1)
		return (NULL);
	return ((char *)&str[last_occurrence]);
}
