/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 18:54:36 by jaleman           #+#    #+#             */
/*   Updated: 2017/03/15 18:54:36 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*
** Required header files.
*/

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <math.h>
# include <time.h>

/*
** User defined header files.
*/

# include "mlx.h"
# include "keys.h"
# include "mouse.h"
# include "libft.h"

/*
** Macros of the window size (width and height), and the title of the window.
*/

# define WIN_WIDTH			(1280)
# define WIN_HEIGHT			(720)
# define TITLE(fractal)		(ft_strjoin("Fractol - ", ft_strcap(fractal)))
# define THREADS			(8)
# define SCALE_LIMIT		(500000000)
# define SCALE_PRECISION	(1.042)

/*
** Fract'ol Structures
**
** @t_mlx     : required minilibx arguments.
** @t_image   : variables to be used for creation of the image.
**              data -> information about the image, allowing to be modified.
**              size -> move from one line to another in the image.
**              endian -> how the pixel color in the image needs to be stored.
**              bpp -> filled with number of bits to represent a pixel color.
** @t_type    : store the fractal values, such as the iteration level, scale,
**              type, limit, width and height, etc...
** @t_mouse   : get the mouse state (toggle by left click), and the x and y
**              coordinates of the cursor.
** @t_color   : define the color, rgb value (24-bits).
** @t_fractol : nested structure that calls all the other structures.
*/

typedef struct	s_mlx
{
	void	*init;
	void	*win;
	void	*img;
}				t_mlx;

typedef struct	s_image
{
	char	*data;
	int		size;
	int		endian;
	int		bpp;
}				t_image;

typedef struct	s_color
{
	int		red;
	int		green;
	int		blue;
}				t_color;

typedef struct	s_type
{
	int		type;
	int		depth;
	int		iteration;
	double	width;
	double	height;
	double	scale;
	double	limit;
	double	xr;
	double	yi;
}				t_type;

typedef struct	s_mouse
{
	int		state;
	int		pos_x;
	int		pos_y;
}				t_mouse;

typedef struct	s_fractol
{
	t_mlx	mlx;
	t_image	image;
	t_color	color;
	t_type	fractal;
	t_mouse	mouse;
}				t_fractol;

/*
** main.c
** Prototypes of the function to initialize the fractal values, and to update
** the fractal drawing on the window image.
*/

void			fractol_init(t_fractol *fractol);
void			fractol_update(t_fractol *fractol);

/*
** fractol_controls.c
** Prototypes of the functions to control the fractals, and to modify some of
** the properties, such as the color, iteration leve, scaling, etc...
*/

int				fractol_keys(int keycode, t_fractol *fractol);
int				fractol_mouse(int mousecode, int x, int y, t_fractol *fractol);

/*
** fractol_draw.c
** Prototypes of the functions to draw the fractals on the window image, and to
** manipulate the fractal's parameters.
*/

void			fractol_pthread(t_fractol *fractol);
int				fractol_manipulate(int x, int y, t_fractol *fractol);

/*
** fractol_fractals.c
** Prototypes of the functions of the available fractals that can be drawn
** on the window image.
*/

int				mandelbrot(t_fractol *fractol);
int				julia(t_fractol *fractol);
int				rorscharch(t_fractol *fractol);

/*
** fractol_bonus.c
** Prototypes of the bonus fractals ;)
*/

int				sphere(t_fractol *fractol);
int				pipi(t_fractol *fractol);
int				compass(t_fractol *fractol);
int				pikachu(t_fractol *fractol);
int				birdie(t_fractol *fractol);

#endif
