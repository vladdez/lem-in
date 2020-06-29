/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:14:18 by kysgramo          #+#    #+#             */
/*   Updated: 2019/12/15 14:37:53 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_color2(char *color)
{
	if (ft_strcmp(color, "magneta") == 0)
	{
		ft_putstr(RED);
		return (9);
	}
	if (ft_strcmp(color, "cyan") == 0)
	{
		ft_putstr(CYAN);
		return (6);
	}
	if (ft_strcmp(color, "eoc") == 0)
	{
		ft_putstr(RESET);
		return (5);
	}
	return (2);
}

static int	put_color(char *color)
{
	if (ft_strcmp(color, "red") == 0)
	{
		ft_putstr(RED);
		return (5);
	}
	if (ft_strcmp(color, "green") == 0)
	{
		ft_putstr(GREEN);
		return (7);
	}
	if (ft_strcmp(color, "yellow") == 0)
	{
		ft_putstr(YELLOW);
		return (8);
	}
	if (ft_strcmp(color, "blue") == 0)
	{
		ft_putstr(BLUE);
		return (6);
	}
	return (put_color2(color));
}

int			color(const char *str)
{
	char	color[8];
	int		i;

	i = 0;
	while (str[i + 1] != '}' && str[i + 1] != '\0' && i < 7)
	{
		color[i] = str[i + 1];
		i++;
	}
	if (str[i + 1] == '}')
	{
		color[i] = '\0';
		i = put_color(color);
	}
	return (i);
}
