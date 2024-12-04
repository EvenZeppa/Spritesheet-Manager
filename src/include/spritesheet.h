#ifndef SPRITESHEET_H
# define SPRITESHEET_H

# include "sprite.h"

typedef struct s_spritesheet
{
	char	*name;
	char	*file_path;
	int		width;
	int		height;

	int		cols;
	int		rows;
	int		grid_enabled;

	t_sprite	*first_sprite;
}	t_spritesheet;

t_spritesheet	*create_spritesheet();


#endif