/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_checks2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:12:52 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/04 20:19:35 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

typedef struct s_pxy
{
	int	x;
	int	y;
}	t_pxy;

typedef struct s_sprite
{
	int		w;
	int		h;
	void	*img;
}	t_sprite;

typedef struct s_map
{
	char	*path;
	size_t	h;
	size_t	w;
	size_t	ex;
	size_t	pos;
	size_t	coll;
	int		fd;
	char	**grid;
	char	**highlight_grid;
	size_t	exit_acc;
	size_t	coll_acc;
	size_t	player_on_exit;
	size_t	moves;
	t_pxy	sc_s;
}	t_map;

typedef struct s_main
{
	void		*mlx_p;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			b;
	int			ls;
	int			end;
	t_map		map;
	t_pxy		p_pos;
	t_pxy		e_pos;
	t_sprite	spr_wall;
	t_sprite	spr_floor;
	t_sprite	spr_coll;
	t_sprite	spr_door;
	t_sprite	spr_p;
}	t_main;

#endif