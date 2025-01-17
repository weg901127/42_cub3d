/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:00:33 by jekim             #+#    #+#             */
/*   Updated: 2022/03/15 17:34:20 by gilee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../lib/libft/libft.h"
# include "../lib/minilibx_mms_20210621/mlx.h"
# include "./structure.h"
# include "./debug.h"

# define ERROR_OCCURED 1
# define TRUE 1
# define FALSE 0
# define RGB_RED 16777215
# define EVENT_KEY_PRESS 2
# define MOVE_SPEED 0.3
# define ROT_SPEED 0.25

/*
**  key binding
*/
# define BUTTON_REDCROSS 0x6d357408
# define KEY_ESC 0x35
# define KEY_W 13
# define KEY_S 1
# define KEY_LFT 123
# define KEY_RGT 124
# define KEY_A 0
# define KEY_D 2

/*
**  key binding
*/
# define MAPTILE_OUTSPACE 0
# define MAPTILE_INNERSPACE 1
# define MAPTILE_WALL 2
# define MAPTILE_SPWAN 3

/*
**  anlge_value
*/
# define ANGLE_MIN 5
# define FOV 66
# define PLANE_INIT 0.66


/*
**  texture_index & spwan_direction binding
*/
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define SPWAN_NO 1
# define SPWAN_SO 2
# define SPWAN_WE 4
# define SPWAN_EA 8

/*
**	initiation_part
*/
int init_game(int argc, char **argv, char **env, t_data **data);

/*
**	parser_part
*/
int parse_mapfile(char *filepath, char** env, t_data *data);
int	parse_all_RGBvalue(int map_fd, t_data *data);
int	parse_all_imagepaths(int map_fd, t_data *data);
int	parse_mapfile_rawdata(int map_fd, t_data *data);
int	load_imgs(void *mlxptr, t_map *map, t_static *parsed);
int convert_mapdata_matrix(t_data *data);
int validate_mapdata_space(int **map, t_data *data);
int validate_mapdata_object(t_data *data);
int validate_mapdata_border(int **map, t_data *data);

int skip_line(int fd, char **map_line, int *line_checker);
void free_splited(char **splited);
int	get_splited_len(char **splited);
char **get_and_check_splited(char *src, char c, int check_l, char *key);

int	img_loadchecker(t_texture *txtr);
int	img_path_validator(const char *path);
/*
**	hooks_part
*/
void set_hooks(t_data *data);

/*
**	engine_part
*/
int		render(t_data *data);
int     render_wall(t_data *data);
int     render_background(t_window *win, t_static *parsed);
void	draw_wall(t_data *data, int ray_index, t_ray *casted);
int     is_hit_on_wall(int **map_mtrx, int y, int x);
int     put_image_to_window(t_data *data);

/*
**	engine_utils
*/
void	init_ray_direction(t_ray *ray, t_camera *cam);
double	define_ray_distance(t_camera *cam, t_ray *ray, int side);
void	init_camera_struct(t_camera *cam, int window_w, int ray_index);

/*
**	engine - functions for vector calculation 
*/
t_vec	vec_create(double x, double y);
t_vec	vec_add(t_vec vec1, t_vec vec2);
t_vec	vec_minus(t_vec vec1, t_vec vec2);
t_vec	vec_scala_mul(t_vec vec, double n);
t_vec	vec_equation(t_vec *coeff0, t_vec *coeff1, t_vec *constant);
t_vec	vec_rot_ccw(t_vec a, double angle);
t_vec	vec_rot_min_ccw(t_vec a);
/*
**	event
*/
void	move_front(t_data *data);
void	move_back(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	turn_left(t_data *data);
void	turn_right(t_data *data);

int print_mapmatrix(t_map *map);

#endif
