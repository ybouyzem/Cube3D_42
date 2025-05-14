/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:54:08 by ybouyzem          #+#    #+#             */
/*   Updated: 2025/03/20 23:58:19 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	ft_check(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (char) c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_content(int fd, char *content)
{
	char	*str;
	int		len;

	len = 1;
	str = (char *)ft_malloc((size_t)BUFFER_SIZE + 1, 1);
	if (!str)
		return (NULL);
	while (len != 0 && ft_check(content, '\n') == 0)
	{
		len = read(fd, str, BUFFER_SIZE);
		if (len == -1)
			return (NULL);
		str[len] = '\0';
		content = ft_strjoin(content, str);
	}
	return (content);
}

char	*get_reminder(char *buf)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\0')
		return (NULL);
	if (buf[i] == '\n')
		i++;
	new = (char *)ft_malloc(sizeof(char) * (ft_strlen(buf) - i + 1), 1);
	if (!new)
		return (NULL);
	j = 0;
	while (buf[i])
	{
		new[j] = buf[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*get_new_line(char *buf)
{
	int		i;
	char	*line;

	i = 0;
	if (buf[i] == '\0' || !buf)
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	line = (char *)ft_malloc((i + 1), 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_line(int fd)
{
	static char	*buf;
	char		*line;

	line = 0;
	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = get_content(fd, buf);
	if (!buf)
		return (NULL);
	line = get_new_line(buf);
	buf = get_reminder(buf);
	return (line);
}
