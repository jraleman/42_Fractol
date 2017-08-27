/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:51:39 by jaleman           #+#    #+#             */
/*   Updated: 2017/03/22 12:51:40 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Put a pixel in a specific position defined by the draw_fractal() function.
** Change colors depending on the iteration level.
** If the iteration level is equal to the fractal depth, paint it black ;)
*/

static void		put_pixel(t_fractol *fractol, int depth)
{
	int			pos;

	pos = (fractol->fractal.height + (fractol->fractal.width * WIN_WIDTH)) * 4;
	if (fractol->fractal.height < WIN_WIDTH \
			&& fractol->fractal.width < WIN_HEIGHT \
				&& depth == fractol->fractal.iteration)
	{
		fractol->image.data[pos] = 0x00;
		fractol->image.data[pos + 1] = 0x00;
		fractol->image.data[pos + 2] = 0x00;
	}
	else if (fractol->fractal.height < WIN_WIDTH \
				&& fractol->fractal.width < WIN_HEIGHT)
	{
		fractol->image.data[pos] = fractol->color.red + (depth * 2.42);
		fractol->image.data[pos + 1] = fractol->color.green + (depth * 2.42);
		fractol->image.data[pos + 2] = fractol->color.blue + (depth * 2.42);
	}
}

/*
** Draw the fractal from the fractal.type (selection), and put it on the
** window image.
** Colors will depend on the "depth level", each fractal function will return
** this level.
*/

static void		*draw_fractal(void *tab)
{
	t_fractol	*fractol;
	int			depth;
	double		tmp_width;

	fractol = (t_fractol *)tab;
	tmp_width = fractol->fractal.width;
	while (fractol->fractal.height < WIN_WIDTH)
	{
		fractol->fractal.width = tmp_width;
		while (fractol->fractal.width < fractol->fractal.limit)
		{
			depth = (fractol->fractal.type == 1) ? mandelbrot(fractol) : depth;
			depth = (fractol->fractal.type == 2) ? julia(fractol) : depth;
			depth = (fractol->fractal.type == 3) ? rorscharch(fractol) : depth;
			depth = (fractol->fractal.type == 4) ? sphere(fractol) : depth;
			depth = (fractol->fractal.type == 5) ? pipi(fractol) : depth;
			depth = (fractol->fractal.type == 6) ? compass(fractol) : depth;
			depth = (fractol->fractal.type == 7) ? pikachu(fractol) : depth;
			depth = (fractol->fractal.type == 8) ? birdie(fractol) : depth;
			put_pixel(fractol, depth);
			fractol->fractal.width += 1;
		}
		fractol->fractal.height += 1;
	}
	return (tab);
}

/*
** The image is passed to this function, cutting it cut it into smaller section
** for the multithreading. Once all the image have been generated, the resulting
** image is put to the window and then destroyed.
*/

void			fractol_pthread(t_fractol *fractol)
{
	t_fractol	tab[THREADS];
	pthread_t	t[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void *)&tab[i], (void *)fractol, sizeof(t_fractol));
		tab[i].fractal.width = ((double)(1.00 / THREADS) * WIN_WIDTH) * i;
		tab[i].fractal.limit = ((double)(1.00 / THREADS) * WIN_WIDTH) * (i + 1);
		i += 1;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_create(&t[i], NULL, draw_fractal, &tab[i]);
		i += 1;
	}
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(fractol->mlx.init, fractol->mlx.win, \
								fractol->mlx.img, 0, 0);
}

/*
** If mouse.state is on (1), get the x and y coordinates of the mouse cursor,
** and keep updating it to the fractol structure. This is used to manipulate
** the parameters of the fractals (ci, and cr).
*/

int				fractol_manipulate(int x, int y, t_fractol *fractol)
{
	if (fractol->mouse.state == 1 && (x > 0 && y > 0) \
			&& (x < WIN_WIDTH && y < WIN_HEIGHT))
	{
		fractol->mouse.pos_x = x;
		fractol->mouse.pos_y = y;
		fractol_update(fractol);
	}
	return (0);
}
