/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:11:20 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/06 18:07:15 by psegura-         ###   ########.fr       */
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

/*__Keys_&_Events__*/
# ifdef OSX
#  define ESC			53
#  define W				13
#  define A				0
#  define S				1
#  define D				2

#  define SCROLL_UP     4
#  define SCROLL_DOWN   5

#  define UP			126
#  define DOWN			125
#  define LEFT			123
#  define RIGHT			124

#  define PLUS      30
#  define MINUS     44

#  define R	15

#  define DESTROY 		17

# else
#  ifndef LINUX
#   define LINUX
#  endif
#  define ESC			65307
#  define W				119
#  define A				97
#  define S				115
#  define D				100

#  define SCROLL_UP     4
#  define SCROLL_DOWN   5

#  define UP		65362
#  define DOWN		65364
#  define LEFT		65361
#  define RIGHT		65363

#  define PLUS      43 
#  define MINUS     45 

#  define R	114

#  define DESTROY 		17

# endif
#endif
