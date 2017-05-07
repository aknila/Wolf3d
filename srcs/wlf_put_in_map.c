/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wlf_put_in_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/05/03 04:48:17 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

char	*wlf_extracting(int fd)
{
	char	*tmp;
	char	*str;
	char	*buf;

	tmp = NULL;
	if (!(str = (char *)malloc(sizeof(char) * 11)))
		return (NULL);
	if (!(buf = (char *)malloc(sizeof(char) * 10001)))
		return (NULL);
	ft_memset(buf, '\0', 10001);
	ft_memset(str, '\0', 11);
	while (read(fd, buf, 10000) > 0)
	{
		tmp = str;
		if (!(str = ft_strjoin(str, buf)))
		{
			ft_strdel(&tmp);
			return (NULL);
		}
		ft_strdel(&tmp);
		ft_memset(buf, '\0', 10000);
	}
	return (str);
}

int		**wlf_put_in_map(int **map, int fd)
{
	int		n;
	int		s;
	int		i;
	char	*str;

	n = 0;
	i = 0;
	s = 0;
	if (!(str = wlf_extracting(fd)))
		return (NULL);
	while (str[i])
	{
		if (str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
		{
			map[n][s++] = ft_atoi(&str[i]);
			while (str[i] && (str[i] == '-'
				|| (str[i] >= '0' && str[i] <= '9')))
				i++;
		}
		n += (str[i] && str[i] == '\n' ? 1 : 0);
		s = (str[i] && str[i++] == '\n' ? 0 : s);
		i += (str[i] && str[i] == ' ' ? 1 : 0);
	}
	free(str);
	return (map);
}

void	mlx_put_line(t_ptr *ptr)
{
	t_line	l;

	l.dx = ABS(ptr->x1 - ptr->x0);
	l.sx = (ptr->x0 < ptr->x1 ? 1 : -1);
	l.dy = ABS(ptr->y1 - ptr->y0);
	l.sy = (ptr->y0 < ptr->y1 ? 1 : -1);
	l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (1)
	{
		mlx_pix_img(ptr, ptr->x0, ptr->y0, ptr->colors);
		if (ptr->x0 == ptr->x1 && ptr->y0 == ptr->y1)
			break ;
		l.e2 = l.err;
		if (l.e2 > -l.dx)
		{
			l.err -= l.dy;
			ptr->x0 += l.sx;
		}
		if (l.e2 < l.dy)
		{
			l.err += l.dx;
			ptr->y0 += l.sy;
		}
	}
}
