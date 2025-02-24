
#ifndef CUB3D_H

# define CUB3D_H

# include <stdio.h>
# include <string.h>

# include <time.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <mlx.h>
# include <math.h>

#include "constantes.h"

typedef struct	s_mlx
{
	void	*co;
	void	*win;
}			t_mlx;

typedef struct	s_rules
{
	int	north;
	int	south;
	int	east;
	int	west;
	int	floor;
	int	ceiling;
}		t_rules;

typedef struct	s_paths
{
	char	*n_path;
	char	*n_text;
	char	*s_path;
	char	*s_text;
	char	*e_path;
	char	*e_text;
	char	*w_path;
	char	*w_text;
	char	*floor;
	char	*ceiling;
	int		f_col[3];
	int		c_col[3];
}			t_paths;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	camera_plane_dx;
	float	camera_plane_dy;
}	t_player;

typedef struct	s_map
{
	char	**map;
	char	**map_copy;
	int		player_nbr;
	int		num_lines;
	int		max_width;
	t_player	*player;
	char	direction;
	t_paths	*textures;
	t_mlx	*mlx;
	t_img	*img;
}			t_map;

typedef	struct	s_search
{
	int	wall;
	int	zero;
}		t_search;

char	*get_next_line(int fd);
char	*process_buff(int fd, char *hold);
char	*holdtrim(char *hold);
char	*shortstr(char *src);
char	*ft_join(char *hold, char *buff);
char	*ft_strdup(char *s);
int		is_nl(char *s);
int		ft_len(char *s);

char	*ft_strncpy(const char *src, int size);
int		ft_atoi(char *s);
int		f_and_c_cmp(t_paths *textures);
int		change_map_get_player(t_map *game);

void	print_map(char **map);
void	free_map(char **map);
void	final_free(t_map *game);
void	print_int_array(int *colors);
void	empty_buffer(int fd);

int 	end_game(t_map *game);

int		check_north(char *s, t_rules *ways, t_paths *paths);
int		check_south(char *s, t_rules *ways, t_paths *paths);
int		check_west(char *s, t_rules *ways, t_paths *paths);
int		check_east(char *s, t_rules *ways, t_paths *paths);

int		check_floor(char *s, t_rules *ways, t_paths *paths);
int		check_ceiling(char *s, t_rules *ways, t_paths *paths);
int		map_textures(int fd, t_rules *w, t_paths *p);
int		map_content(int fd, t_map *game);
void	cringe_free(char *line, int fd, t_rules *w, t_paths *paths);

char	**copy_map(t_map *game);
void    free_copy_map(t_map *game, char **map);
void	noob_free(void  *ptr);
void    exit_bad_map(t_map *game);
void	release_textures(t_map *game);

int		is_map_closed(t_map *game);

int		go_to_mlx_functions(t_map *game);
void	get_images(t_map *game);
void	free_images(t_map *game);
int		check_images(t_map *game);
void	free_mlx(t_map *game);



void	ft_draw_pixel(t_img *img, int x, int y, int color);

int 	ft_draw_walls(t_map *map);
int		ft_draw(t_map *game);
t_img	*ft_init_image(t_mlx *mlx);

#endif
