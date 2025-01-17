/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:08:01 by jekim             #+#    #+#             */
/*   Updated: 2022/03/15 17:40:18 by gilee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	callback_exit(void *dt)
{
	t_data	*data;

	data = (t_data *)dt;
	mlx_destroy_window(data->window->mlx_ptr, data->window->win_ptr);
	exit(0);
}

int	subcallback_press_move(int code, t_data *data)
{
	if (code == KEY_W)
		move_front(data);
	if (code == KEY_RGT)
		turn_right(data);
	if (code == KEY_S)
		move_back(data);
	if (code == KEY_LFT)
		turn_left(data);
	if (code == KEY_A)
		move_left(data);
	if (code == KEY_D)
		move_right(data);
	render(data);
	return (0);
}

int	callback_key(int code, t_data *data)
{
	if (code == KEY_W || code == KEY_A
		|| code == KEY_RGT || code == KEY_LFT
		|| code == KEY_S || code == KEY_D)
		subcallback_press_move(code, data);
	if (code == KEY_ESC)
		callback_exit(data);
	return (0);
}

void	set_hooks(t_data *data)
{
	mlx_hook(data->window->win_ptr, 17, 0, &callback_exit, data);
	mlx_hook(data->window->win_ptr, EVENT_KEY_PRESS, 0,
		&callback_key, (void *)data);
}
