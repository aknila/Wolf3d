/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/05/07 13:42:20 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void    wlf_aff_rendu(t_ptr *ptr)
{
    t_ptd   dir;
    int     x;
    int     w;
    double  camerax;
    t_ptd   raypos;
    t_ptd   raydir;
    t_pti   map;
    t_ptd   sidedist;
    t_ptd   deltadist;
    t_pti   step;
    t_ptd   wall;
    int     hit;
    int     side;
    double  perpwalldist;
    int     lineheight;
    int     drawstart;
    int     drawend;

    mlx_clr_img(ptr);
    dir.x = ptr->vec_x;
    dir.y = ptr->vec_y;
    x = 0;
    w = SIZE_X;
    while (x < w)
    {
        hit = 0;
        camerax = 2 * (double)x / (double)w - 1;
        raypos.x = ptr->x_player;
        raypos.y = ptr->y_player;
        raydir.x = dir.x + ptr->x_ecran * camerax;
        raydir.y = dir.y + ptr->y_ecran * camerax;
        map.x = (int)raypos.x;
        map.y = (int)raypos.y;
        deltadist.x = sqrt(1 + (raydir.y * raydir.y) / (raydir.x * raydir.x));
        deltadist.y = sqrt(1 + (raydir.x * raydir.x) / (raydir.y * raydir.y));
        step.x = (raydir.x < 0 ? -1 : 1);
        step.y = (raydir.y < 0 ? -1 : 1);
        if (raydir.x < 0)
            sidedist.x = (raypos.x - map.x) * deltadist.x;
        else
            sidedist.x = (map.x + 1 - raypos.x) * deltadist.x;
        if (raydir.y < 0)
            sidedist.y  = (raypos.y - map.y) * deltadist.y;
        else
            sidedist.y = (map.y + 1 - raypos.y) * deltadist.y;
        while (hit == 0)
        {
            if (sidedist.x < sidedist.y)
            {
                sidedist.x += deltadist.x;
                map.x += step.x;
                side = 0;
            }
            else
            {
                sidedist.y += deltadist.y;
                map.y += step.y;
                side = 1;
            }
            if (ptr->map->map[map.y][map.x] >= 1)
                hit = 1;
        }
        if (side == 0)
        {
            perpwalldist = (map.x - raypos.x + (1 - step.x) / 2) / raydir.x;
            wall.x = raypos.y + perpwalldist * raydir.y;
        }
        else
        {
            perpwalldist = (map.y - raypos.y + (1 - step.y) / 2) / raydir.y;
            wall.x = raypos.x + perpwalldist * raydir.x;
        }
        wall.x -= (int)(wall.x);
        lineheight = (int)(SIZE_Y / perpwalldist);
        drawstart = -lineheight / 2 + SIZE_Y / 2;
        if (drawstart + ptr->dec_y1 + (ptr->key->crouch * ptr->crouch) < 0 && ptr->texture == 0)
            drawstart = -(ptr->dec_y1 + (ptr->key->crouch * ptr->crouch));
        drawend = lineheight / 2 + SIZE_Y / 2;
        if (drawend + ptr->dec_y1 + (ptr->key->crouch * ptr->crouch) > SIZE_Y)
            drawend = SIZE_Y - (ptr->dec_y1 + (ptr->key->crouch * ptr->crouch));
        if (side == 0)
            ptr->colors = (step.x == -1 ? ptr->n : ptr->s);
        else
            ptr->colors = (step.y == -1 ? ptr->w : ptr->e);
        ptr->x0 = x;
        ptr->x1 = x;
        ptr->y0 = drawstart + ptr->dec_y1 + (ptr->key->crouch * ptr->crouch);
        ptr->y1 = drawend + ptr->dec_y1 + (ptr->key->crouch * ptr->crouch);
        wall.y = ptr->y0;
        while (ptr->y0 <= SIZE_Y)
        {
            if (ptr->y0 < ptr->y1 && ptr->y0 > 0)
            {
                if (ptr->texture != 0)
                    mlx_textur(ptr, x, wall, lineheight);
                else
                    mlx_pix_img(ptr, x, ptr->y0, ptr->colors);
            }
            else
                mlx_pix_img(ptr, x, ptr->y0, 0x00808080);
            ptr->y0 += 1;
        }
        x++;
    }
    mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img->ptr_img, 639, 200);
    draw_vis(ptr);
}

void    draw_vis(t_ptr *ptr)
{
    t_pti a;

    a.x = 639 + SIZE_X / 2 - ptr->vis1->x / 2;
    a.y = 200 + SIZE_Y - ptr->vis1->y;
    mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->vis1->ptr_img, a.x, a.y);
    mlx_put_image_to_window(ptr->mlx, ptr->win,
        ptr->vis3->ptr_img, 639 + 5, 200 - 40);
}
