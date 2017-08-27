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
** Fractal simulating the Rorschach test, a psychological test in which
** subjects' perceptions of inkblots are recorded and then analyzed
** using psychological interpretation, complex algorithms, or both.
** A striking characteristic of the Rorschach inkblots is their symmetry,
** making this a very fun fractal. :)
*/

int			rorscharch(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	cr = (fractol->mouse.pos_x - WIN_WIDTH) / ((double)WIN_WIDTH * 2) + 0.25;
	ci = (fractol->mouse.pos_y - WIN_HEIGHT) / ((double)WIN_HEIGHT) + 0.50;
	zi = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	zr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	while (FT_SQUARE(zr) + FT_SQUARE(zi) < 4 \
			&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = fabs(zr);
		zr = FT_SQUARE(zr) - FT_SQUARE(zi) - cr;
		zi = (2 * zi) * tmp_zr - ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}

/*
** Set consisting of values generated by a mathematical function such that an
** arbitrarily small perturbation can cause drastic changes in the sequence of
** iterated function values.
*/

int			julia(t_fractol *fractol)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	fractol->fractal.depth = 0;
	cr = (fractol->mouse.pos_x - (210.0 / 2.0) - WIN_WIDTH) \
			/ ((double)WIN_WIDTH * 2) + 0.15;
	ci = (fractol->mouse.pos_y - (320.0 / 2.0) - WIN_HEIGHT) \
			/ (double)WIN_HEIGHT - 0.15;
	zi = fractol->fractal.width / fractol->fractal.scale + fractol->fractal.yi;
	zr = fractol->fractal.height / fractol->fractal.scale + fractol->fractal.xr;
	while (FT_SQUARE(zr) + FT_SQUARE(zi) < 4 \
			&& fractol->fractal.depth < fractol->fractal.iteration)
	{
		tmp_zr = zr;
		zr = FT_SQUARE(zr) - FT_SQUARE(zi) + cr;
		zi = (2 * zi) * tmp_zr + ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}

/*
** Sampling complex numbers and determining, for each sample point (ci and cr),
** whether the result of iterating the above function goes to infinity.
** Treating the real and imaginary parts of c as image coordinates (xr + yi) on
** the complex plane, pixels may then be colored according to how rapidly
** the sequence diverges (depth), with the color 0 (black) used for points
** where the sequence does not diverge (iteration == depth).
*/

int			mandelbrot(t_fractol *fractol)
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
		zr = FT_SQUARE(zr) - FT_SQUARE(zi) + cr;
		zi = (2 * zi) * tmp_zr + ci;
		fractol->fractal.depth += 1;
	}
	return (fractol->fractal.depth);
}
