/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 02:58:51 by jekim             #+#    #+#             */
/*   Updated: 2021/10/30 16:34:56 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*make_abspath(char *pwd, char *filepath, t_data *data)
{
	char	*ret;
	int		pwd_l;
	int		fp_l;

	pwd_l = ft_strlen(data->current_path);
	fp_l = ft_strlen(filepath);
	ret = (char *)ft_calloc(sizeof(char), pwd_l + fp_l);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, pwd, pwd_l + 1);
	while (*filepath == '.')
		filepath++;
	ft_strlcpy(ret + pwd_l, filepath, ft_strlen(filepath) + 1);
	ret[ft_strlen(ret)] = '\0';
	return (ret);
}

void free_splited(char **splited)
{
	int ix;

	ix = -1;
	if (splited)
	{
		while (splited[++ix])
			free(splited[ix]);
		free(splited);
		splited = NULL;
	}
}

int	run_mapfile(char *filepath, t_data *data)
{
	int		path_l;
	int		fd_check;
	char	*target_path;

	path_l = ft_strlen(filepath);
	if (!ft_strequel(filepath + path_l - 4, ".cub"))
		return (-1);
	target_path = filepath;
	if (!ft_strncmp(filepath, "./", 2) || !ft_strncmp(filepath, "../", 3))
		target_path = make_abspath(data->current_path, filepath, data);
	if (!target_path)
		return (-1);
	fd_check = open(target_path, O_RDONLY, NULL);
	if (fd_check == -1)
		return (-1);
	return (fd_check);
}

int	get_splited_len(char **splited)
{
	int	ix;

	ix = -1;
	while (splited[++ix])
		;
	return (ix);
}

char **get_and_check_splited(char *src, char c, int check_l, char *key)
{
	char **ret;

	ret = ft_split(src, c);
	if (ret == NULL
		|| get_splited_len(ret) != check_l
		|| !ft_strequel(ret[0], key))
	{
		free_splited(ret);
		return (NULL);
	}
	return (ret);
}

int	parse_imagepath(int fd, char **ptr, char *key)
{
	char	*line;
	char	**splited;
	int		line_check;

	line_check = ft_strgnl(fd, &line);
	if (line_check != 1)
		return (1);
	splited = get_and_check_splited(line, ' ', 2, key);
	if (splited == NULL)
		return (1);
	*ptr = ft_strdup(splited[1]);
	free_splited(splited);
	return (0);
}

int	parse_all_imagepaths(int map_fd, t_data *data)
{
	if (parse_imagepath(map_fd, &(data->map_data.NO_image_filename), "NO")
		|| parse_imagepath(map_fd, &(data->map_data.SO_image_filename), "SO")
		|| parse_imagepath(map_fd, &(data->map_data.WE_image_filename), "WE")
		|| parse_imagepath(map_fd, &(data->map_data.EA_image_filename), "EA"))
		return (1);
	trs(data->map_data.NO_image_filename);
	trs(data->map_data.SO_image_filename);
	trs(data->map_data.WE_image_filename);
	trs(data->map_data.EA_image_filename);
	return (0);
}

char	**get_RGBstr(int fd, char *key)
{
	char	*line;
	char	**splited;
	char	**rgb_arr;
	int		line_check;

	line_check = ft_strgnl(fd, &line);
	if (line_check != 1)
		return (NULL);
	splited = get_and_check_splited(line, ' ', 2, key);
	if (splited == NULL)
		return (NULL);
	rgb_arr = ft_split(splited[1], ',');
	if (rgb_arr == NULL
		|| get_splited_len(rgb_arr) != 3)
		return (NULL);
	return (rgb_arr);
}

int	get_RGBvalue(char **parsed, t_data *data, char key)
{
	int	ix;
	int	ovf_flag;
	int	value;

	ix = 0;
	ovf_flag = 0;
	while (ix != 3 && parsed[ix])
	{
		if (ft_isable_strtonbr(parsed[ix]))
			return (1);
		value = ft_atoi_covf(parsed[ix], &ovf_flag);
		if (ovf_flag == 1 || value < 0 || value > 255)
			return (1);
		if (key == 'F')
			data->map_data.F_RGB[ix] = value;
		if (key == 'C')
			data->map_data.C_RGB[ix] = value;
		ix++;
	}
	return (0);
}

// i thought "in a strict order" means
// a empty line must be there after the image paths
// so, i made this function to skip the empty line
// between RGB value line and that.
int	skip_line(int map_fd)
{
	int		check;
	char	*line;

	check = ft_strgnl(map_fd, &line);
	if (ft_strlen(line) > 1)
		return (1);
	return (0);
}

int	parse_all_RGBvalue(int map_fd, t_data *data)
{
	char	**rgb_parsed;

	data->map_data.F_RGB = (int *)malloc(sizeof(int) * 4);
	data->map_data.C_RGB = (int *)malloc(sizeof(int) * 4);
	if (!data->map_data.F_RGB || !data->map_data.C_RGB)
		return (1);
	data->map_data.F_RGB[3] = '\0';
	data->map_data.C_RGB[3] = '\0';
	if (skip_line(map_fd))
		return (1);
	rgb_parsed = get_RGBstr(map_fd, "F");
	if (rgb_parsed == NULL
		|| get_RGBvalue(rgb_parsed, data, 'F'))
		return (1);
	free_splited(rgb_parsed);
	rgb_parsed = get_RGBstr(map_fd, "C");
	if (rgb_parsed == NULL
		|| get_RGBvalue(rgb_parsed, data, 'C'))
		return (1);
	free_splited(rgb_parsed);
	return (0);
}

int	parse_mapdata(int map_fd, t_data *data)
{
	char **map_untouched;
	
	return (0);
}

int	parse_mapfile(char *filepath, t_data *data)
{
	int	map_fd;

	map_fd = run_mapfile(filepath, data);
	if (map_fd == -1)
		ft_strerr("Error : map file error\n");
	if (parse_all_imagepaths(map_fd, data)
		|| parse_all_RGBvalue(map_fd, data))
		return (close(map_fd) || ft_strerr("Error : invalid map data\n"));
	return (close(map_fd));
}