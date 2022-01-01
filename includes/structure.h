/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:23:08 by jekim             #+#    #+#             */
/*   Updated: 2022/01/01 21:58:42 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_pixel
{
	double			distance;
	unsigned int	*color;
}	t_pixel;

typedef struct s_ray
{
	t_vec	dir;
	double	distance;
}	t_ray;

typedef struct s_mapdata_lst
{
	char *row;
	struct s_mapdata_lst	*next;
}	t_mapdata_lst;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	int	health;
	int	speed;
	int armo;
}	t_player;

typedef struct s_static
{
	char					*NO_img_filepath;
	char					*SO_img_filepath;
	char					*WE_img_filepath;
	char					*EA_img_filepath;
	int						*F_RGB;
	int						F_RGB_value;
	int						*C_RGB;
	int						C_RGB_value;
	int						map_width;
	int						map_height;
	int						space_cnt;
	int						N_cnt;
	int						S_cnt;
	int						E_cnt;
	int						W_cnt;
	struct s_mapdata_lst	*rawdata;
}	t_static;

typedef struct s_img
{
	void	*main_image_ptr;
	int		*main_image_data;
	int		size_length;
	int		bpp;
	int		endian;
}	t_img;

typedef struct	s_window
{
	int 			resol_max_x;
	int 			resol_max_y;
	int				resol_basic_x;
	int				resol_basic_y;
	void			*win_ptr;
	void			*mlx_ptr;
	t_vec			origin;
	t_vec			dir;
	t_vec			plane;
	t_pixel			**pixel;
	t_ray			*ray;
	double			sin_unit;
	double			cos_unit;
	double			distance;
	struct s_img	*img;
}	t_window;

typedef struct s_data
{
	char			*current_path;
	int				**map_matrix;
	struct s_player *player;
	struct s_window	*window;
	struct s_static *parsed_data;
}	t_data;

#endif