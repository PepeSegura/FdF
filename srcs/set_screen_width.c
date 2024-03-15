/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen_width.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:08:10 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/13 21:06:13 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#ifdef OSX

void	set_screen_data(int *screen_width, int *screen_height)
{
	CGDirectDisplayID	display_id;
	CGRect				screen_bounds;
	int					width;
	int					height;

	display_id = kCGDirectMainDisplay;
	screen_bounds = CGDisplayBounds(display_id);
	width = CGRectGetWidth(screen_bounds);
	height = CGRectGetHeight(screen_bounds);
	(*screen_width) = SCREEN_WIDTH;
	(*screen_height) = SCREEN_HEIGHT;
	if (SCREEN_WIDTH > width)
		(*screen_width) = width;
	if (SCREEN_HEIGHT > height)
		(*screen_height) = height;
}

#else

void	set_screen_data(int *screen_width, int *screen_height)
{
	Display	*display;
	Screen	*screen;
	int		width;
	int		height;

	display = XOpenDisplay(NULL);
	if (!display)
		ft_print_error("Failed to open X display.");
	screen = XDefaultScreenOfDisplay(display);
	width = WidthOfScreen(screen);
	height = HeightOfScreen(screen);
	XCloseDisplay(display);
	(*screen_width) = SCREEN_WIDTH;
	(*screen_height) = SCREEN_HEIGHT;
	if (SCREEN_WIDTH > width)
		(*screen_width) = width;
	if (SCREEN_HEIGHT > height)
		(*screen_height) = height;
}

#endif
