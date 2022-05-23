/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 07:53:33 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 10:23:43 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*new_chunck(char *chunck)
{
	size_t	i;
	char	*s_new_chunck;

	i = 0;
	while (*(chunck + i) && *(chunck + i) != '\n')
		i++;
	if (*(chunck + i) == '\0')
	{
		free(chunck);
		return (NULL);
	}
	s_new_chunck = (char *)malloc(sizeof(char) * (ft_strlen(chunck) - i + 1));
	if (!s_new_chunck)
		return (NULL);
	ft_strlcpy(s_new_chunck, (chunck + i + 1), (ft_strlen(chunck) - i + 1));
	free(chunck);
	return (s_new_chunck);
}

static char	*get_line(char *chunck)
{
	size_t	i;
	char	*s_line;

	i = 0;
	if (*(chunck + i) == '\0')
		return (NULL);
	while (*(chunck + i) && *(chunck + i) != '\n')
		i++;
	s_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!s_line)
		return (NULL);
	if (*(chunck + i) == '\n')
		ft_strlcpy(s_line, chunck, (i + 2));
	if (*(chunck + i) == '\0')
		ft_strlcpy(s_line, chunck, (i + 1));
	return (s_line);
}

static int	check_new_line(char *chunck)
{
	int		i;
	int		nl;

	i = 0;
	nl = 0;
	while (*(chunck + i))
		if (*(chunck + i++) == '\n')
			nl = 1;
	return (nl);
}

static char	*read_chunck(int fd, char *chunck)
{
	int		nl;
	int		bytes_read;
	char	*s_buff;

	s_buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!s_buff)
		return (NULL);
	nl = 0;
	bytes_read = 1;
	while (nl == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, s_buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(s_buff);
			return (NULL);
		}
		*(s_buff + bytes_read) = '\0';
		chunck = gnl_join(chunck, s_buff);
		nl = check_new_line(chunck);
	}
	free(s_buff);
	return (chunck);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*chunck;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	chunck = read_chunck(fd, chunck);
	if (!chunck)
		return (NULL);
	line = get_line(chunck);
	chunck = new_chunck(chunck);
	return (line);
}
