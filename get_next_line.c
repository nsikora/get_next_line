/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:49:20 by nsikora           #+#    #+#             */
/*   Updated: 2018/02/08 10:41:03 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

static ssize_t	get_read_file(const int fd, char **str)
{
	ssize_t		ret;
	char		*copy;
	char		buf[BUFF_SIZE + 1];

	if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		return (-1);
	buf[ret] = '\0';
	copy = *str;
	*str = ft_strjoin(*str, buf);
	if (*copy != 0)
		free(copy);
	return (ret);
}

static int		get_line(char **str, char *s, char **line)
{
	int			i;
	char		*copy;

	i = 0;
	if (*s == '\n')
		i = 1;
	*s = 0;
	*line = ft_strjoin("", *str);
	if (i == 0 && ft_strlen(*str))
	{
		*str = ft_strnew(1);
		return (1);
	}
	if (i == 0 && !(ft_strlen(*str)))
		return (0);
	copy = *str;
	*str = ft_strjoin(s + 1, "");
	free(copy);
	return (i);
}

int				get_next_line(const int fd, char **line)
{
	int			ret;
	char		*s;
	static char	*str;

	if (!str)
		str = "";
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	ret = BUFF_SIZE;
	while (line)
	{
		s = str;
		while (*s || ret < BUFF_SIZE)
		{
			if (*s == '\n' || *s == 0)
				return (get_line(&str, s, line));
			s++;
		}
		ret = get_read_file(fd, &str);
		if (ret == -1)
			return (-1);
	}
	return (0);
}
