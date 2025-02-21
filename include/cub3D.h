
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

# define BUFFER_SIZE 4096


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
	char	*s_path;
	char	*e_path;
	char	*w_path;
	char	*floor;
	char	*ceiling;
	int		f_col[3];
	int		c_col[3];
}			t_paths;

typedef struct	s_map
{
	char	**map;
	char	**map_copy;
	int		player;
	int		num_lines;
	int		max_width;
	float	play_x_start;
	float	play_y_start;
	char	direction;
	t_paths	*textures;
	t_mlx	*mlx;
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
void	change_map_get_player(t_map *game);

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
void	free_mlx(t_map *game);

#endif
