#ifndef WLF_H
# define WLF_H

# include <math.h>

typedef struct  s_ptd
{
    double      x;
    double      y;
}               t_ptd;

typedef struct  s_pti
{
    int         x;
    int         y;
}               t_pti;

# define SIZE_X 1500;
# define SIZE_Y 1000;
#endif

int main (void)
{
    t_ptd   pos;
    t_ptd   dir;
    t_ptd   plane;
    int     x;
    int     w;
    double  camerax;
    t_ptd   raypos;
    t_ptd   raydir;
    t_pti   map;
    t_ptd   sidedist;
    t_ptd   deltadist;
    t_pti   step;
    int     hit;
    int     side;
    double  perpwalldist;
    int     lineheight;
    int     drawstart;
    int     drawend;

    hit = 0;
    pos.x = 22;
    pos.y = 12;
    dir.x = -1;
    dir.y = 0;
    plane.x = 0;
    plane.y = 0.66;
    x = 0;
    w = SIZE_X;
    while (x < w)
    {
        camerax = 2 * x / (double)w - 1;
        raypos.x = pos.x;
        raypos.y = pos.y;
        raydir.x = dir.x + plane.x * camerax;
        raydir.y = dir.y + plane.y * camerax;
        map.x = (int)raypos.x;
        map.y = (int)raypos.y;
        deltadist.x = sqrt(1 + (raydir.y * raydir.y) / (raydir.x * raydir.x));
        deltadist.y = sqrt(1 + (raydir.x * raydir.x) / (raydir.y * raydir.y));
        if (raydir.x < 0)
        {
            step.x = -1;
            sidedist.x = (raypos.x - map.x) * deltadist.x;
        }
        else
        {
            step.x = 1;
            sidedist.x = (map.x + 1 - raypos.x) * deltadist.x;
        }
        if (raydir.y < 0)
        {
            step.y = -1;
            sidedist.y  = (raypos.y - map.y) * delatdist.y;
        }
        else
        {
            step.y = 1;
            sidedist.y = (map.y + 1 - raypos.y) * deltadist.y;
        }
        while (hit == 0)
        {
            if (sidedist.x < sidedist.y)
            {
                sidedist.y += deltadist.x;
                map.x += step.x;
                side = 0;
            }
            else
            {
                sidedist.y += deltadist.y;
                map.y += step.y;
                side = 1;
            }
            if (worldmap[map.x][map.y] == 1)
                hit = 1;
        }
        if (side == 0)
        {
            perpwalldist = (map.x - raypos.x + (1 - step.x) / 2) / raydir.x;
        }
        else
        {
            perpwalldist = (map.y - raypos.y + (1 - step.y) / 2) / raydir.y;
        }
        lineheight = (int)(SIZE_Y / perpwalldist);
        drawstart = -lineheight / 2 + SIZE_Y / 2;
        if (drawstart < 0)
            drawstart = 0;
        drawend = lineheight / 2 + SIZE_Y / 2;
        if (drawend >= SIZE_Y)
            drawend >= SIZE_y - 1;
        
        // ajout de l adaptation pour mon code
        ptr->x0 = x;
        ptr->x1 = x;
        ptr->y0 = drawstart;
        ptr->y1 = drawend;
        mlx_put_line(ptr);
        mlx_put_image_to_window(...);
        // retour au tuto

        double  movespeed;
        double  rotspeed;
        double  olddirx;
        double  oldplanex;

        movespeed = 5.0;
        rotspeed = 3.0;
        if (KEY_UP)
        {
            if (worldmap[(int)(pos.x + dir.x * movespeed)][(int)pos.y] != 1)
                pos.x += dir.x * movespeed;
            if (worldmap[(int)pos.x][(int)(pos.y + dir.y * movespeed)] != 1)
                pos.y += dir.y * movespeed;
        }
        if (KEY_DOWN)
        {
            if (worldmap[(int)(pos.x - dir.x * movespeed)][(int)pos.y] != 1)
                pos.x -= dir.x * movespeed;
            if (worldmap[(int)pos.x][(int)(pos.y - dir.y * movespeed)] != 1)
                pos.y -= dir.y * movespeed;
        }
        if (KEY_RIGHT)
        {
            olddirx = dir.x;
            oldplanex = plane.x;
            dir.x = dir.x * cos(-rotspeed) - dir.y * sin(-rotspeed);
            dir.y = olddirx * sin(-rotspeed) + dir.y * cos(-rotspeed);
            plane.x = plane.x * cos(-rotspeed) - plane.y * sin(-rotspeed);
            plane.y = oldplanex * sin(-rotspeed) + plane.y * cos(-rotspeed);
        }
        if (KEY_LEFT)
        {
            olddirx = dir.x;
            oldplanex = plane.x;
            dir.x = dir.x * cos(rotspeed) - dir.y * sin(rotspeed);
            dir.y = olddirx * sin(rotspeed) + dir.y * cos(rotspeed);
            plane.x = plane.x * cos(rotspeed) - plane.y * sin(rotspeed);
            plane.y = oldplanex * sin(rotspeed) + plane.y * cos(rotspeed);
        }
        x++;
    }
}