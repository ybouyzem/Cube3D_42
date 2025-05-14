/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:25:03 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/21 01:05:13 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	word_count(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static char	*get_word(const char *s1, int *index, char c)
{
	char	*copy;
	size_t	word_len;
	int		i;

	word_len = 0;
	while (s1[*index] == c)
		(*index)++;
	i = *index;
	while (s1[i] && s1[i] != c)
	{
		word_len++;
		i++;
	}
	copy = ft_malloc(sizeof(char) * (word_len + 1), 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[*index] && s1[*index] != c)
		copy[i++] = s1[(*index)++];
	copy[i] = '\0';
	return (copy);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		index;
	int		wc;
	int		i;

	index = 0;
	i = 0;
	if (!s)
		return (NULL);
	wc = word_count(s, c);
	arr = ft_malloc(sizeof(char *) * (wc + 1), 1);
	if (!arr)
		return (NULL);
	while (i < wc)
	{
		arr[i] = get_word(s, &index, c);
		if (!arr[i])
			return (ft_malloc(0, 0));
		i++;
	}
	arr[i] = 0;
	return (arr);
}
