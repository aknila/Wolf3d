/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/05/07 14:28:51 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		key_press(int k, t_ptr *ptr)
{
	if (k == 126)
		ptr->key->up = 1;
	if (k == 125)
		ptr->key->down = 1;
	if (k == 124)
		ptr->key->right = 1;
	if (k == 123)
		ptr->key->left = 1;
	if (k == 49)
		system("afplay ah.mp3 &");
	if (k == 6)
	{
		ptr->key->crouch = 1;
		wlf_aff_rendu(ptr);
	}
	if (k == 257 || k == 8 || k == 53 || (k >= 82 && k <= 89))
		key_press2(k, ptr);
	return (0);
}

int		key_press2(int k, t_ptr *ptr)
{
	if (k == 257)
		ptr->key->sprint = 1;
	if (k == 8)
	{
		ptr->key->c = (ptr->key->c == 0 ? 1 : 0);
		set_color(ptr);
	}
	if (k == 53)
		ptr->key->esc = 1;
	if (k >= 82 && k <= 89)
	{
		ptr->texture = k - 82;
		init_text(ptr->txt, ptr);
	}
	return (0);
}

int		key_release(int k, t_ptr *ptr)
{
	if (k == 126)
		ptr->key->up = 0;
	if (k == 125)
		ptr->key->down = 0;
	if (k == 124)
		ptr->key->right = 0;
	if (k == 123)
		ptr->key->left = 0;
	if (k == 6)
		ptr->key->crouch = 0;
	if (k == 257)
		ptr->key->sprint = 0;
	if (ptr->key->chg > 18)
		wlf_aff_rendu(ptr);
	return (0);
}

int		mouse_code(int button, int x, int y, t_ptr *ptr)
{
	if (button != 1)
		return (0);
	if (x >= 110 && y >= 284 && x <= 232 && y <= 400)
		ptr->menu->skb = 1;
	else if (x >= 232 && y >= 284 && x <= 348 && y <= 400)
		ptr->menu->skb = 0;
	else if (x >= 110 && y >= 400 && x <= 232 
		&& y <= 520 && ptr->menu->skbsel != 4)
		ptr->menu->skbmv = 1;
	else if (x >= 232 && y >= 400 && x <= 348 && y <= 520)
		ptr->menu->skbmv = 0;
	else if (x >= 310 && y >= 634 && x <= 432 && y <= 750)
	{
		ptr->menu->skbsel = 1;
		ptr->menu->skbmv = 1;
		init_skybox(ptr->sky, ptr);
	}
	else
		return (mouse_code2(x, y, ptr));
	aff_choice(ptr);
	return (0);
}

int		mouse_code2(int x, int y, t_ptr *ptr)
{
	if (x >= 432 && y >= 634 && x <= 548 && y <= 750)
	{
		ptr->menu->skbsel = 2;
		ptr->menu->skbmv = 1;
		init_skybox(ptr->sky, ptr);
	}
	else if (x >= 310 && y >= 750 && x <= 432 && y <= 870)
	{
		ptr->menu->skbsel = 3;
		ptr->menu->skbmv = 1;
		init_skybox(ptr->sky, ptr);
	}
	else if (x >= 432 && y >= 750 && x <= 548 && y <= 870)
	{
		ptr->menu->skbsel = 4;
		ptr->menu->skbmv = 0;
		init_skybox(ptr->sky, ptr);
	}
	else
		return (0);
	aff_choice(ptr);
	return (0);
}
