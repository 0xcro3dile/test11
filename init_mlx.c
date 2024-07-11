/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohame2 <amohame2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:35:00 by amohame2          #+#    #+#             */
/*   Updated: 2024/07/10 20:53:28 by amohame2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	initialize_fractal_parameters(t_data *mlx_data, int argc, char **argv)
{
	mlx_data->min_real = -2.0;
	mlx_data->max_real = 2.0;
	mlx_data->min_imag = -2.0;
	mlx_data->max_imag = 2.0;
	if (mlx_data->fractal_type == 1)
	{
		if (argc == 4)
		{
			mlx_data->c_real = atof(argv[2]);
			mlx_data->c_imag = atof(argv[3]);
		}
		else
		{
			mlx_data->c_real = -0.7;
			mlx_data->c_imag = 0.27015;
		}
	}
}

int	initialize_window(t_data *mlx_data)
{
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, g_width, g_height,
			"Fractol");
	if (!mlx_data->win_ptr)
	{
		cleanup(mlx_data);
		printf("Failed to create window.\n");
		return (0);
	}
	mlx_data->img_ptr = mlx_new_image(mlx_data->mlx_ptr, g_width, g_height);
	if (!mlx_data->img_ptr)
	{
		cleanup(mlx_data);
		printf("Failed to create image.\n");
		return (0);
	}
	mlx_data->img_data = mlx_get_data_addr(mlx_data->img_ptr, &mlx_data->bpp,
			&mlx_data->size_line, &mlx_data->endian);
	if (!mlx_data->img_data)
	{
		cleanup(mlx_data);
		printf("Failed to get image data address.\n");
		return (0);
	}
	return (1);
}

int	initialize_mlx(t_data *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init();
	if (!mlx_data->mlx_ptr)
	{
		printf("Failed to initialize MiniLibX.\n");
		return (0);
	}
	return (initialize_window(mlx_data));
}
