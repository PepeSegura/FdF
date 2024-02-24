#include <stdio.h>
#include <stdlib.h>

void	bresenham_line(int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	x;
	int	y;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	err = dx - dy;
	x = x0;
	y = y0;
	while (x != x1 || y != y1)
	{
		printf("(%d, %d)\n", x, y);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
	printf("(%d, %d)\n", x1, y1);
}

int	main(void)
{
	int	x0;
	int	x1;

	x0 = 128, y0 = 72;
	x1 = 231, y1 = 72;
	bresenham_line(x0, y0, x1, y1);
	return (0);
}
