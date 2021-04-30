#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"

#include "libft.h"
#include "get_next_line.h"

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;		// bpp (3 RGB + 1 Opacity = 4bits/pixel)
	int			line_length;		// (y * line_length + x * (bits_per_pixel / 8))
	int			endian;				// 1 or 0 (depends on archi, order or sequence of bytes)
}				t_data;