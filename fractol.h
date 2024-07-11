/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohame2 <amohame2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:50:28 by amohame2          #+#    #+#             */
/*   Updated: 2024/07/10 17:50:55 by amohame2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define ESC_KEY 53

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

# define ESC_KEY 53
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

extern int	g_width;
extern int	g_height;

typedef struct s_complex
{
	double	real;
	double	imag;
}			t_complex;

typedef struct s_draw_params
{
	double	min_real;
	double	max_real;
	double	min_imag;
	double	max_imag;
	int		max_iter;
}			t_draw_params;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		fractal_type;
	double	min_real;
	double	max_real;
	double	min_imag;
	double	max_imag;
	double	c_real;
	double	c_imag;
	int		max_iter;
}			t_data;

void		draw_julia_set(t_data *mlx_data);
void		draw_mandelbrot_set(t_data *mlx_data);
void		render(t_data *mlx_data);
int			handle_key(int key, t_data *mlx_data);
int			handle_mouse(int button, int x, int y, t_data *mlx_data);
void		zoom_in(t_data *mlx_data);
void		zoom_out(t_data *mlx_data);
int			handle_resize(int g_g_width, int height, t_data *mlx_data);
void		cleanup(t_data *mlx_data);
void		initialize_fractal_parameters(t_data *mlx_data, int argc,
				char **argv);

#endif
