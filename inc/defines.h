/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:11:20 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/15 18:02:46 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*__Constants__*/
# define TRUE 			1
# define FALSE 			0

/*__Game_Settings__*/
# define MS				0.6
# define ROT_MS			0.1

// # define MAP_WIDTH		24
// # define MAP_HEIGHT		24
#ifndef SCREEN_WIDTH
# define SCREEN_WIDTH	1280
#endif

#ifndef SCREEN_HEIGHT
# define SCREEN_HEIGHT	720
#endif

# define MINIMAP_SIZE	200
# define CELL_SIZE	5

/*__Map_Chars__*/
# define VALID_CHARS		" 01NSEW"
# define EMPTY_CHAR			'0'
# define WALL_CHAR			'1'
# define NORTH_CHAR			'N'
# define SOUTH_CHAR			'S'
# define EAST_CHAR			'E'
# define WEST_CHAR			'W'

enum e_sides
{
	EW,
	NS
};

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
