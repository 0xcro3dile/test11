/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohame2 <amohame2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:32:47 by amohame2          #+#    #+#             */
/*   Updated: 2024/07/11 15:51:27 by amohame2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
#include <stdlib.h>

int		g_width = 800;
int		g_height = 600;

int		validate_fractal_type(t_data *mlx_data, int argc, char **argv);
int		print_usage_and_exit(char *program_name);
void	initialize_fractal_parameters(t_data *mlx_data, int argc, char **argv);
int		initialize_mlx(t_data *mlx_data);
void	setup_hooks(t_data *mlx_data);
void	cleanup(t_data *mlx_data);
int		handle_resize(int g_width, int height, t_data *mlx_data);

void leaks(void)
{
	system("leaks fractol");
}
int	main(int argc, char **argv)
{


	atexit(leaks);
	t_data	mlx_data;

	
	if (argc < 2 || !validate_fractal_type(&mlx_data, argc, argv))
		return (print_usage_and_exit(argv[0]));
	initialize_fractal_parameters(&mlx_data, argc, argv);
	if (!initialize_mlx(&mlx_data))
		return (1);
	render(&mlx_data); 
	setup_hooks(&mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
	// system("leaks fractol");
	cleanup(&mlx_data);
	return (0);
}

int	validate_fractal_type(t_data *mlx_data, int argc, char **argv)
{
	mlx_data->fractal_type = atoi(argv[1]);
	if (mlx_data->fractal_type != 1 && mlx_data->fractal_type != 2)
	{
		printf("Use 1 for Julia set and 2 for Mandelbrot set.\n");
		return (0);
	}
	if (mlx_data->fractal_type == 1 && argc != 4 && argc != 2)
	{
		printf("For Julia set,provide 2 additional parameters for real and imaginary parts of the complex parameter.\n");
		return (0);
	}
	return (1);
}

int	print_usage_and_exit(char *program_name)
{
	printf("Usage: %s <fractal_type> [<c_real> <c_imag>]\n", program_name);
	printf("Use 1 for Julia set and 2 for Mandelbrot set.\n");
	printf("For Julia set,you can optionally provide 2 additional parameters for real and imaginary parts of the complex parameter.\n");
	return (1);
}



int	handle_destroy(t_data *mlx_data)
{
	cleanup(mlx_data);
	exit(0);
	return (0);
}

void	setup_hooks(t_data *mlx_data)
{
	mlx_hook(mlx_data->win_ptr, 2, 1L << 0, handle_key, mlx_data);
	mlx_mouse_hook(mlx_data->win_ptr, handle_mouse, mlx_data);
	mlx_hook(mlx_data->win_ptr, 17, 1L << 17, handle_destroy, mlx_data);
}

void cleanup(t_data *mlx_data)
{
	if (mlx_data->img_ptr)
	{
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img_ptr);
		printf("Image destroyed\n");
		mlx_data->img_ptr = NULL;
	}
	if (mlx_data->win_ptr)
	{
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
		printf("Window destroyed\n");
		mlx_data->win_ptr = NULL;
	}
	if (mlx_data->mlx_ptr)
	{
		free(mlx_data->mlx_ptr);
		printf("MLX pointer freed\n");
		mlx_data->mlx_ptr = NULL;
	}
}


int	handle_resize(int width, int height, t_data *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img_ptr);
	mlx_data->img_ptr = mlx_new_image(mlx_data->mlx_ptr, width, height);
	if (!mlx_data->img_ptr)
	{
		printf("Failed to create new image on resize.\n");
		return (1);
	}
	mlx_data->img_data = mlx_get_data_addr(mlx_data->img_ptr, &mlx_data->bpp,
			&mlx_data->size_line, &mlx_data->endian);
	g_width = width;
	g_height = height;
	render(mlx_data);
	return (0);
}
