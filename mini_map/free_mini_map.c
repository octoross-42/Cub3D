#include "cub3D.h"

void    deal_with_minimap(t_map *game)
{
    if (game->minimap->dot_player)
        mlx_destroy_image(game->mlx->co, game->minimap->dot_player);
    if (game->minimap->wall_square)
        mlx_destroy_image(game->mlx->co, game->minimap->wall_square);
    if (game->minimap->empty_square)
        mlx_destroy_image(game->mlx->co, game->minimap->empty_square);
    if (game->minimap->void_square)
        mlx_destroy_image(game->mlx->co, game->minimap->void_square);
    free(game->minimap);
}