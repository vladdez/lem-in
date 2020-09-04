/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:58:04 by kysgramo          #+#    #+#             */
/*   Updated: 2019/10/06 12:16:13 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFF_SIZE 9999
#define MAXINT 2147483648

static int	gnl_shortline(int fd, char **stock, char **line, int pkg)
{
	size_t		len;
	char		*temp;

	len = 0;
	while (stock[fd][len] != '\n' && stock[fd][len] != '\0')
		len++;
	if (stock[fd][len] == '\n')
	{
		*line = ft_strsub(stock[fd], 0, len);
		temp = ft_strdup(ft_strchr(stock[fd], '\n') + 1);
		free(stock[fd]);
		stock[fd] = temp;
		if (stock[fd][0] == '\0')
			ft_strdel(&stock[fd]);
	}
	else
	{
		if (pkg == BUFF_SIZE)
			get_next_line(fd, line);
		*line = ft_strdup(stock[fd]);
		ft_strdel(&stock[fd]);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*stock[256];
	int			pkg;
	char		balance[BUFF_SIZE + 1];
	char		*wagon;

	if (fd < 0 || fd > 256 || !line || !BUFF_SIZE)
		return (-1);
	while ((pkg = read(fd, balance, BUFF_SIZE)) > 0)
	{
		balance[pkg] = '\0';
		if (!stock[fd])
			stock[fd] = ft_strnew(1);
		wagon = ft_strjoin(stock[fd], balance);
		free(stock[fd]);
		stock[fd] = ft_strdup(wagon);
		free(wagon);
		if (ft_strchr(balance, '\n'))
			break ;
	}
	if (pkg < 0)
		return (-1);
	if (pkg == 0 && !stock[fd])
		return (0);
	return (gnl_shortline(fd, stock, line, pkg));
}
