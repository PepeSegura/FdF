/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:18:22 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/06 20:47:36 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_H
# define LIBS_H

/*______UNISTD_______
Write, Read, Close
*/
# include <unistd.h>

/*______FCNTL________
Open
*/
# include <fcntl.h>

/*______STDIO________
Printf, Strerror, Perror
*/
# include <stdio.h>

/*______STDLIB_______
Malloc, Free, Exit
*/
# include <stdlib.h>

# define _USE_MATH_DEFINES
# include <math.h>
# include <mlx.h>
# include <limits.h>

/* ______BONUS_______
*/
# ifdef OSX
#  include <CoreGraphics/CoreGraphics.h>
# else
#  include <X11/Xlib.h>
# endif

#endif
