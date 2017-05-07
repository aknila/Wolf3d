/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wlf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/05/07 16:36:41 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		ft_error(int error)
{
	if (error == 0)
		ft_putstr(C_ROUGE "\terror : invalid file\n" FIN);
	if (error == 1)
		ft_putstr(C_ROUGE "\terror : bad extension\n" FIN);
	if (error == 2)
		ft_putstr(C_ROUGE "\tusage : ./wolf3d {filename}\n" FIN);
	if (error == 3)
		ft_putstr(C_ROUGE 
			"\tan error occured, please retry in few second\n" FIN);
	return (-1);
}

int		wlf_check_ext(char *str)
{
	int		i;
	int		j;
	char	ext[5];

	i = ft_strlen(str);
	i -= 4;
	j = 0;
	while (j < 4)
	{
		ext[j] = str[i];
		j++;
		i++;
	}
	ext[4] = '\0';
	if (ft_strcmp(ext, ".wlf") != 0)
		return (-1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_map	*m;
	int		fd;
	char	buf[1];

	system("afplay gamecube.mp3 &");
	if (argc != 2)
		return (ft_error(2));
	if (wlf_check_ext(argv[1]) == -1)
		return (ft_error(1));
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (read(fd, buf, 1) == -1)
			return (ft_error(0));
		close(fd);
		fd = open(argv[1], O_RDONLY);
		if (!(m = wlf_map_extract(fd, argv[1])))
			return (ft_error(0));
		wlf_aff_map(m);
	}
	return (0);
}
