/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapparser_img_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gilee <gilee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:33:04 by gilee             #+#    #+#             */
/*   Updated: 2022/03/15 17:34:35 by gilee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	img_loadchecker(t_texture *txtr)
{
	return (!txtr->img.img_ptr || !txtr->rowdata);
}

int	img_path_validator(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	return (close(fd));
}
