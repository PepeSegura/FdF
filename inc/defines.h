/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:11:20 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/16 22:39:49 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*__Constants__*/
# define TRUE 			1
# define FALSE 			0

/*__Game_Settings__*/
# define SCREEN_WIDTH	1280
# define SCREEN_HEIGHT	720

# define SCALE			1.25
/*__Keys_&_Events__*/
# ifdef OSX
#  define ESC	53
#  define W		13
#  define A		0
#  define S		1
#  define D		2

#  define UP			126
#  define LEFT		123
#  define DOWN		125
#  define RIGHT		124
#  define DESTROY 	17

# else
#  ifndef LINUX
#   define LINUX
#  endif
#  define ESC		65307
#  define W		119
#  define A		97
#  define S		115
#  define D		100

#  define UP		65362
#  define LEFT		65361
#  define DOWN		65364
#  define RIGHT		65363

# endif
#endif
