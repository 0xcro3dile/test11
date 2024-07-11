/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohame2 <amohame2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:30:10 by amohame2          #+#    #+#             */
/*   Updated: 2024/07/10 20:56:29 by amohame2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_key(int key, t_data *mlx_data)
{
	if (key == ESC_KEY)
	{
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img_ptr);
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
		if (mlx_data->mlx_ptr)
			free(mlx_data->mlx_ptr);
		exit(0);
	}
	return (0);
}

int	handle_mouse(int button, int x, int y, t_data *mlx_data)
{
	if (button == MOUSE_SCROLL_UP)
	{
		printf("Zooming in at (%d, %d)\n", x, y);
		zoom_in(mlx_data);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		printf("Zooming out at (%d, %d)\n", x, y);
		zoom_out(mlx_data);
	}
	return (0);
}

void	zoom_in(t_data *mlx_data)
{
	double	real_range;
	double	imag_range;
	double	zoom_factor;
	double	real_center;
	double	imag_center;

	real_range = mlx_data->max_real - mlx_data->min_real;
	imag_range = mlx_data->max_imag - mlx_data->min_imag;
	zoom_factor = 1.1;
	real_center = mlx_data->min_real + (g_width / 2.0) / (double)g_width
		* real_range;
	imag_center = mlx_data->min_imag + (g_height / 2.0) / (double)g_height
		* imag_range;
	mlx_data->min_real = real_center - (real_range / zoom_factor) / 2;
	mlx_data->max_real = real_center + (real_range / zoom_factor) / 2;
	mlx_data->min_imag = imag_center - (imag_range / zoom_factor) / 2;
	mlx_data->max_imag = imag_center + (imag_range / zoom_factor) / 2;
	printf("Zoom In - min_real: %f, max_real: %f, min_imag: %f, max_imag: %f\n",
		mlx_data->min_real, mlx_data->max_real, mlx_data->min_imag,
		mlx_data->max_imag);
	render(mlx_data);
}

void	zoom_out(t_data *mlx_data)
{
	double	real_range;
	double	imag_range;
	double	zoom_factor;
	double	real_center;
	double	imag_center;

	real_range = mlx_data->max_real - mlx_data->min_real;
	imag_range = mlx_data->max_imag - mlx_data->min_imag;
	zoom_factor = 1.1;
	real_center = mlx_data->min_real + (g_width / 2.0) / (double)g_width
		* real_range;
	imag_center = mlx_data->min_imag + (g_height / 2.0) / (double)g_height
		* imag_range;
	mlx_data->min_real = real_center - (real_range * zoom_factor) / 2;
	mlx_data->max_real = real_center + (real_range * zoom_factor) / 2;
	mlx_data->min_imag = imag_center - (imag_range * zoom_factor) / 2;
	mlx_data->max_imag = imag_center + (imag_range * zoom_factor) / 2;
	render(mlx_data);
}
