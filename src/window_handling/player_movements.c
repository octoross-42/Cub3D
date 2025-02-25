#include "cub3D.h"


// a == 97;
// w == 119;
// d == 100;
// s == 115;

void	move_player(t_map *game, t_player *player, int key)
{
	if ((game->map[(int)player->y][(int)(player->x + player->dx)] != '1')
		&& (game->map[(int)(player->y + player->dy)][(int)player->x] != '1'))
	{
		printf("player can be moved\n");
		if (key == 97)
			player->x -= 1; //à remove plus tard, juste atm pour tester la fonction
		if (key == 119)
			player->y += 1;// idem
		if (key == 100)
			player->x += 1;// idem
		if (key == 115)
			player->y -= 1;// idem
		ft_draw(game);
		// player->x += player->dx;
		// player->y += player->dy;
	}
	else
		printf("player can't be moved due to a wall or map boundary\n OR because it's close to a wall (we aren't changing dx nor dy yet so maths will always says it's clsoe to a wall)\n");
}