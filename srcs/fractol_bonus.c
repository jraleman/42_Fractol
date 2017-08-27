/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_fractals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 10:49:33 by jaleman           #+#    #+#             */
/*   Updated: 2017/03/22 10:49:34 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Looks like a bird... xD
*/

int			birdie(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	zr = (fractol->mouse.pos_x - WIN_WIDTH) / ((double)WIN_WIDTH * 2) + 0.25;
	zi = (fractol->mouse.pos_y - WIN_HEIGHT) / ((double)WIN_HEIGHT) + 0.50;
	ci = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	cr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	while (FT_SQUARE(zr) + FT_SQUARE(zi) < 4 \
			&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = zr;
		zr = FT_SQUARE(zr) - FT_SQUARE(zi) - cr - 0.69;
		zi = 1.15 * tmp_zr * fabs(zi) * -2.0 - ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}

/*
** Pikachu is one of the worst Pokemon! >:(
*/

int			pikachu(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	zr = (fractol->mouse.pos_x - WIN_WIDTH) / ((double)WIN_WIDTH * 2) + 0.25;
	zi = (fractol->mouse.pos_y - WIN_HEIGHT) / ((double)WIN_HEIGHT) + 0.50;
	ci = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	cr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	while (FT_SQUARE(zr) + FT_SQUARE(zi) < 5 \
			&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = zr;
		zr = FT_SQUARE(zr) * FT_SQUARE(zr) + FT_SQUARE(zi) * FT_SQUARE(zi) - 6 \
				* FT_SQUARE(zr) * FT_SQUARE(zi) - cr - 0.35;
		zi = -5 * fabs(tmp_zr) * zi * (FT_SQUARE(tmp_zr) - FT_SQUARE(zi)) - ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}

/*
** Just a simple star compass... you know, a four point star :)
*/

int			compass(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	zr = (fractol->mouse.pos_x - WIN_WIDTH) / ((double)WIN_WIDTH * 2) + 0.25;
	zi = (fractol->mouse.pos_y - WIN_HEIGHT) / ((double)WIN_HEIGHT) + 0.50;
	ci = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	cr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	while (FT_SQUARE(zr) + FT_SQUARE(zi) < 4 \
			&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = zr;
		zr = -1 * (FT_SQUARE(zr) - (FT_SQUARE(zi) * 3.0)) * zr + cr + 0.42;
		zi = ((FT_SQUARE(tmp_zr) * 3.0) - FT_SQUARE(zi)) * zi + ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}

/*
** If you don't knwo what a "pipi" is, click on the url below ;)
** http://www.urbandictionary.com/define.php?term=Pipi
*/

int			pipi(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	zr = (fractol->mouse.pos_x - WIN_WIDTH) / ((double)WIN_WIDTH) + 0.50;
	zi = (fractol->mouse.pos_y - WIN_HEIGHT) / ((double)WIN_HEIGHT) + 0.85;
	ci = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	cr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	while ((FT_SQUARE(zr) - FT_SQUARE(zi) < 32) \
			&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = zr;
		zr = FT_SQUARE(zr) - FT_SQUARE(zi) + ci;
		zi = (2.45 * zi) * fabs(tmp_zr) + cr;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}

/*
** A fractal sphere, heavily based from the Julia Set fractal.
** Found this by accident (by modifying some of the Julia's parameters),
** but it looks fucking awesome, and is shaped in 3D, so more bonus! :D
*/

int			sphere(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	cr = 0.139375;
	ci = -0.89250;
	zi = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	zr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	while (FT_SQUARE(zr) + FT_SQUARE(zi) < 1 \
			&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = zr;
		zr = FT_SQUARE(zr) - FT_SQUARE(zi) + cr;
		zi = fabs(zi) * fabs(tmp_zr) + ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}
