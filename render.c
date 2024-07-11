/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohame2 <amohame2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:46:17 by amohame2          #+#    #+#             */
/*   Updated: 2024/07/10 13:35:00 by amohame2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void	put_pixel_to_img(t_data *mlx_data, int x, int y, int color)
{
	int	pixel;

	pixel = (y * mlx_data->size_line) + (x * (mlx_data->bpp / 8));
	if (x >= 0 && x < g_width && y >= 0 && y < g_height && pixel >= 0
		&& pixel < (g_width * g_height * (mlx_data->bpp / 8)))
	{
		mlx_data->img_data[pixel] = color;
		mlx_data->img_data[pixel + 1] = color >> 8;
		mlx_data->img_data[pixel + 2] = color >> 16;
	}
}

void	draw_julia_set(t_data *mlx_data)
{
	double	min_real;
	double	max_real;
	double	min_imag;
	double	max_imag;
	int		max_iter;
	int		iter;
	double	temp;
	int		color;

	int x, y;
	double real, imag;
	min_real = mlx_data->min_real;
	max_real = mlx_data->max_real;
	min_imag = mlx_data->min_imag;
	max_imag = mlx_data->max_imag;
	max_iter = 1000;
	y = 0;
	while (y < g_height)
	{
		x = 0;
		while (x < g_width)
		{
			real = min_real + (x / (double)g_width) * (max_real - min_real);
			imag = min_imag + (y / (double)g_height) * (max_imag - min_imag);
			iter = 0;
			while (real * real + imag * imag <= 4 && iter < max_iter)
			{
				temp = real * real - imag * imag + mlx_data->c_real;
				imag = 2 * real * imag + mlx_data->c_imag;
				real = temp;
				iter++;
			}
			color = iter == max_iter ? 0x000000 : iter * 0x00FF00 / max_iter;
			put_pixel_to_img(mlx_data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_mandelbrot_set(t_data *mlx_data)
{
	double	min_real;
	double	max_real;
	double	min_imag;
	double	max_imag;
	int		max_iter;
	double	c_real;
	double	c_imag;
	double	z_real = 0, z_imag;
	int		iter;
	double	temp;
			int color;

	int x, y;
	min_real = mlx_data->min_real;
	max_real = mlx_data->max_real;
	min_imag = mlx_data->min_imag;
	max_imag = mlx_data->max_imag;
	max_iter = 1000;
	y = 0;
	while (y++ < g_height)
	{
		x = 0;
		while (x++ < g_width)
		{
			c_real = min_real + (x / (double)g_width) * (max_real - min_real);
			c_imag = min_imag + (y / (double)g_height) * (max_imag - min_imag);
			z_real = 0, z_imag = 0;
			iter = 0;
			while (iter < max_iter && z_real * z_real + z_imag * z_imag <= 4.0)
			{
				temp = z_real * z_real - z_imag * z_imag + c_real;
				z_imag = 2.0 * z_real * z_imag + c_imag;
				z_real = temp;
				iter++;
			}
			if (iter < max_iter)
			{
				color = (iter * 128) | ((iter % 48) << 8) | ((iter
							% 180) << 16);
			}
			else
			{
				color = 0;
			}
			put_pixel_to_img(mlx_data, x, y, color);
		}
	}
}

void	render(t_data *mlx_data)
{
	if (mlx_data->fractal_type == 1)
	{
		draw_julia_set(mlx_data);
	}
	else if (mlx_data->fractal_type == 2)
	{
		draw_mandelbrot_set(mlx_data);
	}
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
		mlx_data->img_ptr, 0, 0);
}
