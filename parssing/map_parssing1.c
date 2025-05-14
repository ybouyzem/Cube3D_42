/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parssing1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:43:13 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/21 01:29:27 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	*get_full_line(char *str, int highest_line)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = '1';
		i++;
	}
	while (i < highest_line)
	{
		str = ft_strjoin(str, "1");
		i++;
	}
	return (str);
}

int	read_map(char **files, int pos, t_data *data)
{
	int	i;
	int	len;

	data->map = (char **)ft_malloc(sizeof(char *) * (map_len(data) + 1), 1);
	if (!data->map)
	{
		ft_putstr_fd("Error\tMemory allocation failed to allocate memory\n", 2);
		return (-1);
	}
	i = 0;
	len = highest_line(files);
	while (files[pos])
	{
		if (!ft_strcmp(files[pos], "\n"))
			return (-1);
		files[pos] = ft_strtrim(files[pos], "\n");
		data->map[i] = ft_strdup(files[pos]);
		data->map[i] = get_full_line(data->map[i], len);
		i++;
		pos++;
	}
	data->map[i] = NULL;
	return (0);
}

int	check_around(t_data *data, int i, int j)
{
	if (i - 1 < 0 || i + 1 >= ft_strslen(data->map)
		|| j - 1 < 0 || j + 1 >= ft_strlen(data->map[i]))
		return (-1);
	if (data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' '
		|| data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')
		return (-1);
	return (0);
}

int	is_valid_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (in_set(data->map[i][j], "0NSEW"))
			{
				if (check_around(data, i, j) < 0)
				{
					return (-1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	map_parssing(char **file, int pos, t_data *data)
{
	int	ismap;

	pos++;
	while (file[pos] && !ft_strcmp(file[pos], "\n"))
		pos++;
	ismap = is_valid_chars(data, file, pos);
	if (ismap < 0)
		return (-1);
	ismap = read_map(file, pos, data);
	if (ismap < 0)
		return (-1);
	ismap = check_walls(data->map);
	if (ismap < 0)
	{
		return (-1);
	}
	ismap = is_valid_map(data);
	if (ismap < 0)
		return (-1);
	return (0);
}
