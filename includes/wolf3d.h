/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/05/07 14:56:06 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../minilibx_macos/mlx.h"
# include "color.h"
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define ABS(x) ((x) < 0 ? -(x) : (x))
# define SIZE_X 1350
# define SIZE_Y 900
# define MENU_X 2048
# define MENU_Y 1152
# define CASE_X 25
# define CASE_Y 25
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define RAD(x) PI * x / 180
# define PI M_PI
# define MAX_FPS 60
# define SPEED_DEF 0.3

typedef struct	s_line
{
	int		dx;
	int		dy;
	int		err;
	int		sx;
	int		sy;
	int		e2;
}				t_line;

typedef struct	s_img
{
	void		*ptr_img;
	char		*bts;
	int			size_line;
	int			bpp;
	int			end;
}				t_img;

typedef struct	s_file
{
	void		*ptr_img;
	char		*bts;
	int			size_line;
	int			bpp;
	int			end;
	int			x;
	int			y;
}				t_file;

typedef struct	s_map
{
	int			l;
	int			c;
	int			**map;
}				t_map;

typedef struct	s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef	struct	s_ptd
{
	double		x;
	double		y;
}				t_ptd;

typedef	struct	s_pti
{
	int			x;
	int			y;
}				t_pti;

typedef struct	s_key
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			sprint;
	int			crouch;
	int			esc;
	int			c;
	int			menu;
	int			chg;
	int			plus;
}				t_key;

typedef struct	s_menu
{
	int			skb;
	int			skbsel;
	int			skbmv;
	t_file		*menu;
}				t_menu;

typedef struct	s_ptr
{
	t_map		*map;
	t_img		*img;
	t_img		*menul;
	t_img		*menud;
	t_menu		*menu;
	t_vec		*vec;
	t_file		*sky;
	t_key		*key;
	t_file		*vis1;
	t_file		*vis2;
	t_file		*vis3;
	t_file		*txt;
	int			texture;
	double		cam;
	double		x_ecran;
	double		y_ecran;
	double		x_player;
	double		y_player;
	double		dis;
	double		a;
	void		*mlx;
	void		*win;
	int			size_x;
	int			size_y;
	int			colors;
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			n;
	int			s;
	int			w;
	int			e;
	double		vec_x;
	double		vec_y;
	int			dec_x;
	int			dec_y;
	int			dec_x1;
	int			dec_y1;
	int			crouch;
	double		movespeed;
	double		rotspeed;
}				t_ptr;

int				main(int argc, char **argv);
int				wlf_check_ext(char *str);
int				ft_error(int error);
t_map			*wlf_map_extract(int fd, char *filename);
int				wlf_check_file2(char **str1, int *l, int *a);
int				wlf_check_file(int *l, int *a, int fd);
int				ft_isfullnum(char *str);
int				ft_count_s(char *str);
int				**wlf_put_in_map(int **map, int fd);
char			*wlf_extracting(int fd);
void			wlf_aff_map(t_map *m);
void			wlf_aff_rendu(t_ptr *ptr);
int				wlf_close(void);
void			wlf_draw_img(t_ptr *ptr);
void			mlx_pix_img(t_ptr *ptr, int x, int y, int color);
void			mlx_clr_img(t_ptr *ptr);
void			mlx_put_line(t_ptr *ptr);
void			mlx_img_copy(t_ptr *ptr, int x, int y, t_pti dec);
void   			draw_vis(t_ptr *ptr);
int				scnd_main(char *argv);
char			*name(int x);
char			*name2(int x);
void			aff_charge(int i, t_ptr *ptr);
void			set_menu(char id, t_img *img);
void			mlx_pix_put(t_img *img, int x, int y, int color);
void			aff_menu(t_ptr *ptr);
void			aff_choice(t_ptr *ptr);
void			init_menu(t_menu *menu);
void			mlx_textur(t_ptr *ptr, int x, t_ptd wall, int line);
void			init_text(t_file *txt, t_ptr *ptr);
int				wlf_move(char k, t_ptr *ptr);
int				wlf_rot(char k, t_ptr *ptr);
void			init_skybox(t_file *sky, t_ptr *ptr);
void			wlf_initialis(t_ptr *ptr);
void			init_key(t_key	*key);
void	 		init_map(t_map *map, t_ptr *ptr);
int				key_press2(int k, t_ptr *ptr);
void			set_color(t_ptr *ptr);
int				key_press(int k, t_ptr *ptr);
int				key_press2(int k, t_ptr *ptr);
int				key_release(int k, t_ptr *ptr);
int				mouse_code(int button, int x, int y, t_ptr *ptr);
int				mouse_code2(int x, int y, t_ptr *ptr);
void			loading_file(t_ptr *ptr);

#endif
