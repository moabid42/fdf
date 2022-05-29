/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:50:27 by moabid            #+#    #+#             */
/*   Updated: 2022/05/29 19:44:29 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define HEIGHT				1080
# define WIDTH				1920
# define BACKGROUND			0x1E1E1E
# define TEXT_COLOR			0xFFFFFF
# define TEXT_COLOR_2		0xFF0000
# define TITLE_BACKGROUND	0x800000
# define MENU_HEIGHT			500

# define COLOR_DISCO		0xFF0000
# define COLOR_BRICK_RED	0xC2294E
# define COLOR_FLAMINGO		0xEC4B27
# define COLOR_JAFFA		0xEF8633
# define COLOR_SAFFRON		0xF3AF3D

# define RED				0xFF0000
# define GREEN				0x00FF00
# define BLUE				0x0000FF

typedef enum e_projections
{
	twoD,
	threeD
}			t_projection;

typedef enum e_help
{
	without,
	with
}			t_help;

///////////////////////
//	    Structs		 //
///////////////////////

typedef struct s_coord_val
{
	int					z;
	int					color;
	struct s_coord_val	*next;
}						t_coord_val;

typedef struct s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}						t_point;

typedef struct s_camera
{
	t_projection		projection;
	t_help				help;
	int					zoom;
	double				alpha;
	double				beta;
	double				gamma;
	float				z_divisor;
	int					x_offset;
	int					y_offset;
}						t_camera;

typedef struct s_map
{
	int					width;
	int					height;
	int					*coords_arr;
	int					*colors_arr;
	int					z_min;
	int					z_max;
	int					z_range;
}						t_map;

typedef struct s_fdf
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_camera			*camera;
	t_map				*map;
}						t_fdf;

///////////////////////
//	    COLORS		 //
///////////////////////

int				get_default_color(int z, t_map *map);
double			percent(int start, int end, int current);
int				get_light(int start, int end, double percentage);
int				get_color(t_point current, t_point start, \
				t_point end, t_point delta);

///////////////////////
//	    DRAWER		 //
///////////////////////

void			print_menu(t_fdf *fdf);
void			print_help(t_fdf *fdf);
void			drawer(t_map *map, t_fdf *fdf);

///////////////////////
//	    INIT		 //
///////////////////////

void			init_background(t_fdf *fdf);
t_map			*map_init(void);
t_camera		*camera_init(t_fdf *fdf);
t_fdf			*fdf_init(t_map *map);

///////////////////////
//	     KEYS		 //
///////////////////////

void			rotate(int key, t_fdf *fdf);
void			zoom(int key, t_fdf *fdf);
void			move(int key, t_fdf *fdf);
void			threedialization(int key, t_fdf *fdf);
void			help(int key, t_fdf *fdf);

int				key_press(int key, void *param);
void			setup_keys(t_fdf *fdf);

///////////////////////
//	     PARSER		 //
///////////////////////

t_coord_val		*new_coord(char *s);
void			push_line(char **coords_line, t_coord_val **stack, t_map *map);
void			read_map(const int fd, t_coord_val **stack, t_map *map);

///////////////////////
//	     PROJECT	 //
///////////////////////

void			iso(int *x, int *y, int z);
t_point			project(t_point p, t_fdf *fdf);

///////////////////////
//	      STACK		 //
///////////////////////

t_point			new_point(int x, int y, t_map *map);
void			push(t_coord_val **stack, t_coord_val *new);
t_coord_val		*pop(t_coord_val **stack);
void			save_to_map_array(t_coord_val **stack, t_map *map);	

///////////////////////
//	      UTILS		 //
///////////////////////

void			new_line_remove(char *line);
int				ft_isnumber(char *str, int base);
int				ft_atoi_base(const char *str, int base);
void			error(char *s);
void			*ft_malloc(size_t size);
void			ft_strdel(char **as);
void			free_split_arr(char **arr);
int				ft_close(void *param);
int				ft_min(int a, int b);
int				ft_max(int a, int b);
int				sign_of(int a, int b);
t_point			ft_delta(t_point *f, t_point *s);
t_point			ft_sign(t_point *f, t_point *s);

#endif
