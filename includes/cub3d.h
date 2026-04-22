/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:00:59 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/22 18:01:11 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define ERR_CHAR "invalid character in map"
# define ERR_MAP "map is not closed"
# define ERR_PLAYER "invalid player count"
# define ERR_COLOR "invalid color value"
# define ERR_PATH "missing texture path"
# define ERR_FILE "cannot open file"
# define ERR_MALLOC "malloc failed"
# define ERR_EXT "file must have .cub extension"
# define ERR_USAGE "usage: ./cub3D <map.cub>"
# define ERR_DUP "duplicate identifier"
# define ERR_NOMAP "no map found"
# define ERR_SYNTAX "syntax error"

# define WIN_W     1280
# define WIN_H     720

# define KEY_ESC   65307
# define KEY_W     119
# define KEY_A     97
# define KEY_S     115
# define KEY_D     100
# define KEY_LEFT  65361
# define KEY_RIGHT 65363

# define MOVE_SPEED 0.05
# define ROT_SPEED  0.03

# define TEX_NO 0
# define TEX_SO 1
# define TEX_EA 2
# define TEX_WE 3

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	spawn_dir;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_ray;

typedef struct s_path
{
	char	*north;
	char	*east;
	char	*south;
	char	*west;
}	t_path;

typedef struct s_textures
{
	int		floor[3];
	int		ceiling[3];
	int		floor_color;
	int		ceiling_color;
}	t_textures;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

typedef struct s_data
{
	char		**map;
	char		**raw_file;
	int			m_raw;
	int			m_col;
	t_player	player;
	t_textures	textures;
	t_path		path;
	t_mlx		mlx;
	t_keys		keys;
	t_tex		tex[4];
}	t_data;

int		init_mlx(t_data *data);
void	setup_hooks(t_data *data);
int		render(t_data *data);
void	clean_exit(t_data *data);
int		handle_destroy(t_data *data);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	move_player(t_data *data);

void	draw_wall_stripe(t_data *data, t_ray *ray, int x, t_tex *tex);
void	init_textures_mlx(t_data *data);
int		get_tex_pixel(t_tex *tex, int x, int y);

void	free_all(t_data *data);
void	free_map(char **map);
void	init_all(t_data *data);
void	init_player(t_data *data);
void	init_mlx_data(t_data *data);
char	**parser(char *file, t_data *map);
void	parse_config(char **raw, t_data *data);
void	fill_map(t_data *data, char **file);
void	check_all(t_data *data);
void	check_map(t_data *data);
void	check_color_line(char *line, t_data *data);
int		check_extension(char *file);
void	raycast(t_data *data);

void	init_ray_dir(t_ray *ray, t_player *p, int x);
void	init_ray_step(t_ray *ray, t_player *p);
void	perform_dda(t_ray *ray, t_data *data);
void	calc_wall_height(t_ray *ray);
void	draw_column(t_data *data, t_ray *ray, int x);

void	ft_error(t_data *data, char *msg);
int		ft_isspace(char c);

#endif
