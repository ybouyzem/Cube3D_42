/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:25:11 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/21 01:29:13 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	**join_two_double_strs(char **s1, char **s2)
{
	int		i;
	int		j;
	int		len;
	char	**res;

	i = 0;
	j = 0;
	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	if (!s1 && !s2)
		return (NULL);
	len = ft_strslen(s1) + ft_strslen(s2);
	res = (char **)ft_malloc(sizeof(char *) * (len + 1), 1);
	if (!res)
		return (NULL);
	while (s1[i])
		(1) && (res[i] = ft_strdup(s1[i]), i++);
	while (s2[j])
		res[i++] = ft_strdup(s2[j++]);
	res[i] = 0;
	return (res);
}

char	**join_double_with_str(char **s1, char *s2)
{
	int		i;
	char	**res;

	i = 0;
	if (!s2)
		return (s1);
	if (!s1 || !*s1)
	{
		res = (char **)ft_malloc(sizeof(char *) * 2, 1);
		if (!res)
			return (NULL);
		res[0] = s2;
		res[1] = NULL;
		return (res);
	}
	res = (char **)ft_malloc(sizeof(char *) * (ft_strslen(s1) + 2), 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = ft_strdup(s1[i]);
		i++;
	}
	(1) && (res[i++] = ft_strdup(s2), res[i] = 0);
	return (res);
}

int	in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}
