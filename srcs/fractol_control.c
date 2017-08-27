/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 10:49:24 by jaleman           #+#    #+#             */
/*   Updated: 2017/03/22 10:49:25 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Increase the scale of the fractal, depending of the mouse position (x and y),
** and increase the iteration level.
** Saves the position to x_pos and y_pos, used later by zoom_out() function.
** If the fractal is a sphere or a pipi, the iterations won't increase. :/
** The zoom level is capped with the SCALE_LIMIT macro.
*/

static void		zoom_in(int x, int y, t_fractol *fractol)
{
	if (fractol->fractal.scale >= SCALE_LIMIT)
	{
		fractol->fractal.scale = SCALE_LIMIT;
		return ;
	}
	if (fractol->mouse.state == 1)
	{
		fractol->mouse.pos_x = x;
		fractol->mouse.pos_y = y;
	}
	fractol->fractal.xr = (x / fractol->fractal.scale + fractol->fractal.xr) - \
		((fractol->fractal.scale * SCALE_PRECISION) / 2);
	fractol->fractal.xr += ((fractol->fractal.scale * SCALE_PRECISION) / 2) - \
		(x / (fractol->fractal.scale * SCALE_PRECISION));
	fractol->fractal.yi = (y / fractol->fractal.scale + fractol->fractal.yi) - \
		((fractol->fractal.scale * SCALE_PRECISION) / 2);
	fractol->fractal.yi += ((fractol->fractal.scale * SCALE_PRECISION) / 2) - \
		(y / (fractol->fractal.scale * SCALE_PRECISION));
	fractol->fractal.scale *= SCALE_PRECISION;
	if (fractol->fractal.type != 3 && fractol->fractal.type != 5)
		fractol->fractal.iteration += 1;
}

/*
** Decrease the scale level and the iteration level.
** Uses the mouse position from zoom_in() function.
** If the fractal is a sphere or a pipi, the iterations won't decrease. :/
*/

static void		zoom_out(t_fractol *fractol)
{
	fractol->fractal.xr = (fractol->mouse.pos_x / fractol->fractal.scale + \
		fractol->fractal.xr) - ((fractol->fractal.scale / SCALE_PRECISION) / 2);
	fractol->fractal.xr += ((fractol->fractal.scale / SCALE_PRECISION) / 2) - \
		(fractol->mouse.pos_x / (fractol->fractal.scale / SCALE_PRECISION));
	fractol->fractal.yi = (fractol->mouse.pos_y / fractol->fractal.scale + \
		fractol->fractal.yi) - ((fractol->fractal.scale / SCALE_PRECISION) / 2);
	fractol->fractal.yi += ((fractol->fractal.scale / SCALE_PRECISION) / 2) - \
		(fractol->mouse.pos_y / (fractol->fractal.scale / SCALE_PRECISION));
	fractol->fractal.scale /= SCALE_PRECISION;
	if (fractol->fractal.type != 3 && fractol->fractal.type != 5)
		fractol->fractal.iteration -= 1;
}

/*
** Colorize the fractal with a random color.
** Colors go from 0x00 to 0x7F, because of technical issues (integer overflow).
*/

static void		random_colors(t_fractol *fractol)
{
	fractol->color.red = rand() % (0x4F + 0x01);
	fractol->color.green = rand() % (0x4F + 0x01);
	fractol->color.blue = rand() % (0x4F + 0x01);
}

/*
** Assign a mouse code (macros from "includes/mouse.h") to a specific task,
** like changing colors, zoom level, and modifying the parameter of the
** fractal (left click toggle that shit).
*/

int				fractol_mouse(int mousecode, int x, int y, t_fractol *fractol)
{
	if (x > 0 && y > 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		if (mousecode == MOUSE_UP_SCRLL)
			zoom_in(x, y, fractol);
		else if (mousecode == MOUSE_DOWN_SCRLL)
			zoom_out(fractol);
		else if (mousecode == MOUSE_MIDDLE_CLK)
			fractol_init(fractol);
		else if (mousecode == MOUSE_RIGHT_CLK)
			random_colors(fractol);
		else if (mousecode == MOUSE_LEFT_CLK)
			fractol->mouse.state = (fractol->mouse.state == 1) ? 0 : 1;
		fractol_update(fractol);
	}
	return (0);
}

/*
** Assign a key code (macros from "includes/keys.h") to a specific task,
** like changing colors, moving the fractal, zoom level, the number of
** iterations, etc...
*/

int				fractol_keys(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESCAPE)
		exit(0);
	else if (keycode == KEY_ANSI_W || keycode == KEY_UPARROW)
		fractol->fractal.yi -= 1 / fractol->fractal.scale;
	else if (keycode == KEY_ANSI_A || keycode == KEY_LEFTARROW)
		fractol->fractal.xr -= 1 / fractol->fractal.scale;
	else if (keycode == KEY_ANSI_S || keycode == KEY_DOWNARROW)
		fractol->fractal.yi += 1 / fractol->fractal.scale;
	else if (keycode == KEY_ANSI_D || keycode == KEY_RIGHTARROW)
		fractol->fractal.xr += 1 / fractol->fractal.scale;
	else if (keycode == KEY_ANSI_I)
		zoom_in((WIN_WIDTH / 2), (WIN_HEIGHT / 2), fractol);
	else if (keycode == KEY_ANSI_O)
		zoom_out(fractol);
	else if (keycode == KEY_ANSI_R)
		fractol_init(fractol);
	else if (keycode == KEY_SPACE)
		random_colors(fractol);
	else if (keycode == KEY_ANSI_J)
		fractol->fractal.iteration += 1;
	else if (keycode == KEY_ANSI_K)
		fractol->fractal.iteration -= 1;
	fractol_update(fractol);
	return (0);
}
