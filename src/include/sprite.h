#ifndef SPRITE_H
# define SPRITE_H

typedef struct	s_sprite
{
	char	*name;
	int		x;
	int		y;
	int		width;
	int		height;

	int				frame_duration;
	struct s_sprite	*prev_anim;
	struct s_sprite	*next_anim;
}	t_sprite;


#endif