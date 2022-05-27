/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisynth.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:13:02 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/27 15:34:21 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISYNTH_H
# define MINISYNTH_H
#define MINIAUDIO_IMPLEMENTATION

#define DEVICE_FORMAT       ma_format_f32
#define DEVICE_CHANNELS     2
#define DEVICE_SAMPLE_RATE  48000
# define PI 3.141592
# define AUD_BUFF_SIZE 100000

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct s_sound
{
	float	freq;
	float	dur;
	char	note;
	int		sign;
	int		oct;
}				t_sound;

typedef struct s_track
{
	t_sound	*sounds;
	int		sounds_count;
	int		sound_i;
	int		wave;
}				t_track;

typedef struct s_utils
{
	t_track	*tracks;
	int		tracks_count;
	int		tempo;
}				t_utils;

void	player(t_utils *utils);

#endif
