/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 18:52:27 by jaleman           #+#    #+#             */
/*   Updated: 2017/03/15 18:52:27 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Display a usage message on how to run and use fractol.
*/

static void		fractol_usage(char *argv0)
{
	ft_putstr("Usage: ");
	ft_putstr(ft_program_name(argv0));
	ft_putstr(" [ mandelbrot | julia | rorscharch | sphere | pipi | compass ");
	ft_putendl("| pikachu | birdie ]");
	ft_putendl("Keys:");
	ft_putendl("\t[I]               -> Zoom in");
	ft_putendl("\t[O]               -> Zoom out");
	ft_putendl("\t[J]               -> Iterations++");
	ft_putendl("\t[K]               -> Iterations--");
	ft_putendl("\t[R]               -> Reset values");
	ft_putendl("\t[SPACE]           -> Colorize");
	ft_putendl("\t[W][A][S][D]      -> Move");
	ft_putendl("\t[ESC]             -> Exit");
	ft_putendl("Mouse:");
	ft_putendl("\t[SCROLL]          -> Zoom");
	ft_putendl("\t[RIGHT CLK]       -> Colorize");
	ft_putendl("\t[MIDDLE CLK]      -> Reset values");
	ft_putendl("\t[LEFT CLK]        -> Manipulate fractal");
}

/*
** List of fractal available.
** If the fractal is invalid, exit program with error code two (2).
*/

static int		fractol_selection(char *argument, t_fractol *fractol)
{
	fractol->fractal.type = 0;
	if (ft_strequ(ft_str_to_lowcase(argument), "mandelbrot"))
		fractol->fractal.type = 1;
	else if (ft_strequ(ft_str_to_lowcase(argument), "julia"))
		fractol->fractal.type = 2;
	else if (ft_strequ(ft_str_to_lowcase(argument), "rorscharch"))
		fractol->fractal.type = 3;
	else if (ft_strequ(ft_str_to_lowcase(argument), "sphere"))
		fractol->fractal.type = 4;
	else if (ft_strequ(ft_str_to_lowcase(argument), "pipi"))
		fractol->fractal.type = 5;
	else if (ft_strequ(ft_str_to_lowcase(argument), "compass"))
		fractol->fractal.type = 6;
	else if (ft_strequ(ft_str_to_lowcase(argument), "pikachu"))
		fractol->fractal.type = 7;
	else if (ft_strequ(ft_str_to_lowcase(argument), "birdie"))
		fractol->fractal.type = 8;
	else
	{
		ft_putstr(argument);
		ft_putendl(" is not a valid parameter! :(");
		ft_putendl("See usage for a list of valid parameters. ;)");
	}
	return (fractol->fractal.type);
}

/*
** Gives the current fractal some initial values.
** @1 : Mandelbrot Set
** @2 : Julia Set
** @4 : Rorscharch Test
** @5 : Sphere (bonus)
** @6 : Pipi (bonus)
** @7 : Compass (bonus)
** @8 : Pikachu (bonus)
** @9 : Birdie (bonus)
*/

void			fractol_init(t_fractol *fractol)
{
	fractol->fractal.xr = -2.60;
	fractol->fractal.yi = -1.20;
	fractol->fractal.scale = 300.00;
	fractol->fractal.iteration = 42;
	fractol->color.red = 0x42;
	fractol->color.green = 0x32;
	fractol->color.blue = 0x22;
	fractol->mouse.pos_x = WIN_WIDTH / 2;
	fractol->mouse.pos_y = WIN_HEIGHT / 2;
	if (fractol->fractal.type == 2 || fractol->fractal.type == 4 \
			|| fractol->fractal.type == 3)
	{
		fractol->fractal.xr = -2.10;
		fractol->mouse.state = 1;
		if (fractol->fractal.type == 2 || fractol->fractal.type == 4)
			fractol->fractal.iteration = 100;
		if (fractol->fractal.type == 3)
			fractol->fractal.iteration = 10;
	}
	if (fractol->fractal.type == 5)
	{
		fractol->fractal.xr = -2.20;
		fractol->fractal.yi = -1.60;
		fractol->fractal.iteration = 14;
	}
}

/*
** Refresh the image. Updates its values and prints the number of iterations
** and the zoom level (scale) of the fractal.
*/

void			fractol_update(t_fractol *fractol)
{
	if (fractol->fractal.iteration <= 0)
		fractol->fractal.iteration = 0;
	fractol_pthread(fractol);
	mlx_string_put(fractol->mlx.init, fractol->mlx.win, 10, 5, 0xFFFFFF, \
						ft_strjoin("Number of iterations : ", \
						ft_itoa(fractol->fractal.iteration)));
	mlx_string_put(fractol->mlx.init, fractol->mlx.win, 10, 35, 0xFFFFFF, \
						ft_strjoin("Zoom level: ", \
						ft_itoa((int)fractol->fractal.scale)));
}

/*
** Main function, creates the fractol structure and a network connection between
** the program and the x-server, making it possible to draw on the screen,
** getting the keyboard and mouse inputs.
*/

int				main(int argc, char *argv[])
{
	t_fractol	*fractol;

	if (argc == 2)
	{
		if (!(fractol = (t_fractol *)malloc(sizeof(t_fractol))))
			ft_puterror("Memory Allocation failed! :O", 1);
		if (!fractol_selection(argv[1], fractol))
			ft_puterror("Please, try again! :D", 2);
		fractol->mlx.init = mlx_init();
		fractol->mlx.win = mlx_new_window(fractol->mlx.init, WIN_WIDTH, \
			WIN_HEIGHT, TITLE(argv[1]));
		fractol->mlx.img = mlx_new_image(fractol->mlx.init, WIN_WIDTH, \
			WIN_HEIGHT);
		fractol->image.data = mlx_get_data_addr(fractol->mlx.img, \
			&fractol->image.bpp, &fractol->image.size, &fractol->image.endian);
		fractol_init(fractol);
		fractol_update(fractol);
		mlx_hook(fractol->mlx.win, 2, 3, fractol_keys, fractol);
		mlx_hook(fractol->mlx.win, 4, 3, fractol_mouse, fractol);
		mlx_hook(fractol->mlx.win, 6, 3, fractol_manipulate, fractol);
		mlx_loop(fractol->mlx.init);
	}
	else
		fractol_usage(argv[0]);
	return (0);
}
