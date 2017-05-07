/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wlf_start_aff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/05/07 16:36:59 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		wlf_close(void)
{
	system("killall afplay");
	exit(0);
	return (0);
}

void	set_color(t_ptr *ptr)
{
	if (ptr->key->c == 0)
	{
		ptr->n = 0x00FFFF00;
   		ptr->s = 0x00FF0000;
    	ptr->e = 0x0000FF00;
    	ptr->w = 0x000000FF;
	}
	else
	{
		ptr->n = 0x00FF9933;
		ptr->s = 0x00CF5048;
		ptr->e = 0x00339933;
		ptr->w = 0x000066FF;
	}
}

int		game_loop(t_ptr *ptr)
{
	if (ptr->key->chg <= 17)
	{
		aff_charge(ptr->key->chg, ptr);
		if (ptr->key->chg == 17)
			usleep(650000);
		else if (ptr->key->chg < 9)
			usleep(100000);
		else
			usleep(300000);
		ptr->key->chg += 1;
		return (0);
	}
	if (ptr->key->chg == 18)
	{
		system("afplay file/castle.mp3 &");
		aff_choice(ptr);
		ptr->key->chg += 1;
	}
	if (ptr->key->chg > 18)
	{
		ptr->movespeed = (ptr->key->sprint ? SPEED_DEF * 2 : SPEED_DEF);
		ptr->movespeed = (ptr->key->crouch ? SPEED_DEF / 2 : ptr->movespeed);
		if (ptr->key->up)
			wlf_move('N', ptr);
		if (ptr->key->down)
			wlf_move('S', ptr);
		if (ptr->key->left)
			wlf_rot('W', ptr);
		if (ptr->key->right)
			wlf_rot('E', ptr);
		if (ptr->key->esc)
			wlf_close();
		ptr->dec_x += -1 * ptr->menu->skbmv;
		wlf_aff_rendu(ptr);
	}
	return (0);
}

char	*name(int x)
{
	if (x == 0)
		return ("file/portal750xpm/750as.xpm");
	if (x == 1)
		return ("file/portal750xpm/750as1.xpm");
	if (x == 2)
		return ("file/portal750xpm/750as2.xpm");
	if (x == 3)
		return ("file/portal750xpm/750as3.xpm");
	if (x == 4)
		return ("file/portal750xpm/750as4.xpm");
	if (x == 5)
		return ("file/portal750xpm/750as5.xpm");
	if (x == 6)
		return ("file/portal750xpm/750as6.xpm");
	if (x == 7)
		return ("file/portal750xpm/750as7.xpm");
	if (x == 8)
		return ("file/portal750xpm/750as8.xpm");
	if (x >= 9 && x <= 17)
		return (name2(x));
	return (NULL);
}

char	*name2(int x)
{
	if (x == 9)
		return ("file/portal750xpm/750as9.xpm");
	if (x == 10)
		return ("file/portal750xpm/750as10.xpm");
	if (x == 11)
		return ("file/portal750xpm/750as11.xpm");
	if (x == 12)
		return ("file/portal750xpm/750as12.xpm");
	if (x == 13)
		return ("file/portal750xpm/750as13.xpm");
	if (x == 14)
		return ("file/portal750xpm/750as14.xpm");
	if (x == 15)
		return ("file/portal750xpm/750as15.xpm");
	if (x == 16)
		return ("file/portal750xpm/750as16.xpm");
	if (x == 17)
		return ("file/portal750xpm/750as16.xpm");
	return (NULL);
}

void	aff_choice(t_ptr *ptr)
{
	t_menu *choice;
	t_file *aff;
	char *filename;

	aff = (t_file *)malloc(sizeof(t_file));
	choice = ptr->menu;
	mlx_put_image_to_window(ptr->mlx, ptr->win, choice->menu->ptr_img, 0, 0);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->vis2->ptr_img,
		MENU_X - ptr->vis2->x, 0);
	if (choice->skbsel == 1)
		filename = "file/menudesignxpm/sky1.xpm";
	else if (choice->skbsel == 2)
		filename = "file/menudesignxpm/sky2.xpm";
	else if (choice->skbsel == 3)
		filename = "file/menudesignxpm/sky3.xpm";
	else
		filename = "file/menudesignxpm/sky4.xpm";
	ptr->dec_y = (choice->skbsel == 4 ? 100 : 50);
	aff->ptr_img = mlx_xpm_file_to_image(ptr->mlx, filename, &aff->x, &aff->y);
	aff->bts = mlx_get_data_addr(aff->ptr_img, &(aff->bpp),
		&(aff->size_line), &(aff->end));
	mlx_put_image_to_window(ptr->mlx, ptr->win, aff->ptr_img, 180, 500);
	if (choice->skb == 1)
		filename = "file/menudesignxpm/up-on.xpm";
	else
		filename = "file/menudesignxpm/up-off.xpm";
	aff->ptr_img = mlx_xpm_file_to_image(ptr->mlx, filename, &aff->x, &aff->y);
	aff->bts = mlx_get_data_addr(aff->ptr_img, &(aff->bpp),
		&(aff->size_line), &(aff->end));
	mlx_put_image_to_window(ptr->mlx, ptr->win, aff->ptr_img, -20, 150);
	if (choice->skbmv == 1)
		filename = "file/menudesignxpm/down-on.xpm";
	else
		filename = "file/menudesignxpm/down-off.xpm";
	aff->ptr_img = mlx_xpm_file_to_image(ptr->mlx, filename, &aff->x, &aff->y);
	aff->bts = mlx_get_data_addr(aff->ptr_img, &(aff->bpp),
		&(aff->size_line), &(aff->end));
	mlx_put_image_to_window(ptr->mlx, ptr->win, aff->ptr_img, -20, 150);
	free(aff);
}

void	aff_charge(int i, t_ptr *ptr)
{
	char	*filename;
	t_file	*charg;
	
	charg = (t_file *)malloc(sizeof(t_file));
	filename = name(i);
	charg->ptr_img = mlx_xpm_file_to_image(ptr->mlx, filename,
		&charg->x, &charg->y);
	charg->bts = mlx_get_data_addr(charg->ptr_img,
		&(charg->bpp), &(charg->size_line), &(charg->end));
	mlx_put_image_to_window(ptr->mlx, ptr->win,
		charg->ptr_img, MENU_X / 2 - charg->x / 2, MENU_Y / 2 - charg->y / 2);
	free(charg);
}

void	loading_file(t_ptr *ptr)
{
	t_file	vis1;
	t_file	vis2;
	t_file	vis3;

	vis1.ptr_img = mlx_xpm_file_to_image(ptr->mlx, "file/arme2.xpm",
		&vis1.x, &vis1.y);
	vis1.bts = mlx_get_data_addr(vis1.ptr_img, &(vis1.bpp),
		&(vis1.size_line), &(vis1.end));
	ptr->vis1 = &vis1;
	vis2.ptr_img = mlx_xpm_file_to_image(ptr->mlx, "file/aknila3.xpm",
		&vis2.x, &vis2.y);
	vis2.bts = mlx_get_data_addr(vis2.ptr_img, &(vis2.bpp),
		&(vis2.size_line), &(vis2.end));
	ptr->vis2 = &vis2;
	vis3.ptr_img = mlx_xpm_file_to_image(ptr->mlx, "file/lifebar.xpm",
		&vis3.x, &vis3.y);
	vis3.bts = mlx_get_data_addr(vis3.ptr_img, &(vis3.bpp),
		&(vis2.size_line), &(vis3.end));
	ptr->vis3 = &vis3;
}

void	wlf_aff_map(t_map *m)
{
	t_ptr	ptr;
	t_img	img;
	t_file	sky;
	t_key	key;
	t_file	menu;
	t_menu	menu1;
	t_file	txt;

	ptr.map = m;
	ptr.mlx = mlx_init();
	ptr.win = mlx_new_window(ptr.mlx, MENU_X, MENU_Y, "Wolf3D");
	img.ptr_img = mlx_new_image(ptr.mlx, SIZE_X, SIZE_Y);
	img.bts = mlx_get_data_addr(img.ptr_img, &(img.bpp),
		&(img.size_line), &(img.end));
	ptr.img = &img;
	menu.ptr_img = mlx_xpm_file_to_image(ptr.mlx,
		"file/menudesignxpm/menu-aancel.xpm", &menu.x, &menu.y);
	menu.bts = mlx_get_data_addr(menu.ptr_img, &(menu.bpp),
		&(menu.size_line), &(menu.end));
	menu1.menu = &menu;
	init_menu(&menu1);
	ptr.menu = &menu1;
	init_skybox(&sky, &ptr);
	ptr.sky = &sky;
	loading_file(&ptr);
	init_text(&txt, &ptr);
	ptr.txt = &txt;
	wlf_initialis(&ptr);
	init_key(&key);
	ptr.key = &key;
	mlx_mouse_hook(ptr.win, mouse_code, &ptr);
	mlx_hook(ptr.win, 17, (1L << 17), wlf_close, NULL);
	mlx_hook(ptr.win, 2, (1L << 0), key_press, &ptr);
	mlx_hook(ptr.win, 3, (1L << 1), key_release, &ptr);
	mlx_loop_hook(ptr.mlx, game_loop, &ptr);
	mlx_loop(ptr.mlx);
}

int		wlf_move(char k, t_ptr *ptr)
{
	int dir;

	if (k == 'N' || k == 'S')
	{
		dir = (k == 'N' ? 1 : -1);
		if (ptr->map->map[(int)ptr->y_player][(int)(ptr->x_player +
			(dir * ptr->vec_x * ptr->movespeed) + 0.2 * ptr->vec_x)] == 0)
			ptr->x_player += (ptr->vec_x * ptr->movespeed) * dir;
		if (ptr->map->map[(int)(ptr->y_player + (dir * ptr->vec_y *
			ptr->movespeed) + 0.2 * ptr->vec_y)][(int)ptr->x_player] == 0)
			ptr->y_player += (ptr->vec_y * ptr->movespeed) * dir;
		if (ptr->dec_x1 == 1)
			ptr->dec_x1 = (ptr->dec_y1 >= 10 ? -1 : 1);
		else
		 	ptr->dec_x1 = (ptr->dec_y1 <= -10 ? 1 : -1);
		ptr->dec_y -= (ptr->key->sprint + 1) * ptr->dec_x1;
		ptr->dec_y1 += (ptr->key->sprint + 1) * 2 * ptr->dec_x1;
	}
	return (0);
}

int		wlf_rot(char k, t_ptr *ptr)
{
	double	olddirx;
	double	oldplanex;
	int		dir;

	if (k == 'W' || k == 'E')
	{
		dir = (k == 'W' ? 1 : -1);
		olddirx = ptr->vec_x;
		oldplanex = ptr->x_ecran;
		ptr->vec_x = ptr->vec_x * cos(ptr->rotspeed * dir) - ptr->vec_y
		* sin(ptr->rotspeed * dir);
		ptr->vec_y = olddirx * sin(ptr->rotspeed * dir)
		+ ptr->vec_y * cos(ptr->rotspeed * dir);
		ptr->x_ecran = ptr->x_ecran * cos(ptr->rotspeed * dir)
		- ptr->y_ecran * sin(ptr->rotspeed * dir);
		ptr->y_ecran = oldplanex * sin(ptr->rotspeed * dir)
		+ ptr->y_ecran * cos(ptr->rotspeed * dir);
		ptr->dec_x -= (dir * 50);
	}
	return (0);
}
