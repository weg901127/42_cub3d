/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 01:04:55 by jekim             #+#    #+#             */
/*   Updated: 2021/12/28 18:32:59 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int init_struct_player(t_player *player)
{
	player->health = 100;
	player->armo = 15;
	player->speed = 10;
	return (0);
}

int get_basic_screen_size(t_window *win, int *x_ptr, int *y_ptr)
{
	int max_x;
	int max_y;

	max_x = win->resol_max_x;
	max_y = win->resol_max_y;
	if ((max_x / 16) == (max_y / 9))
	{
		*x_ptr = 960;
		*y_ptr = 540;
	}
	else
	{
		*x_ptr = 800;
		*y_ptr = 600;
	}
	return (0);
}

int init_window(t_window *win)
{
	win->mlx_ptr = mlx_init();
	mlx_get_screen_size(win->mlx_ptr,
		&win->resol_max_x, &win->resol_max_y);
	get_basic_screen_size(win,
		&win->resol_basic_x, &win->resol_basic_y);
	win->win_ptr = mlx_new_window(win->mlx_ptr,
		win->resol_basic_x, win->resol_basic_x, "cub3.d");
	win->img->main_image_ptr = mlx_new_image(win->mlx_ptr, 
		win->resol_basic_x, win->resol_basic_y);
	return (0);
}

int init_struct(t_data **data)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		ft_strerr("data error\n");
	(*data)->parsed_data = (t_static *)malloc(sizeof(t_static));
	(*data)->player = (t_player *)malloc(sizeof(t_player));
	(*data)->window = (t_window *)malloc(sizeof(t_window));
	(*data)->window->img = (t_img *)malloc(sizeof(t_img));
	if ((*data)->parsed_data == NULL
		|| (*data)->player == NULL
		|| (*data)->window == NULL
		|| (*data)->window->img == NULL)
		ft_strerr("data error\n");
	return (0);
}

int init_game(int argc, char **argv, char **env, t_data **data)
{
	if (argc != 2)
		ft_strerr("Error : no parameter\n");
	if (init_struct(data)
		|| init_struct_player((*data)->player)
		|| init_window((*data)->window)
		|| parse_mapfile(argv[1], env, *data))
		ft_strerr("Error : the game can't be loaded");
	return (0);
}