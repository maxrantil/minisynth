#include "minisynth.h"

int	main(int argc, char **argv)
{
	t_utils	utils;
	int		fd;
	int		fd2;
	char	*line = NULL;
	int		i;
	int		j;
	char	str_tempo[4];
	int		tempo;
	char	**waves;
	int		track_no;

	utils.tracks_count = 1;
	i = 0;
	j = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			perror("Error, need correct file for fd\n");
			exit(1);
		}
		fd2 = open(argv[1], O_RDONLY);
		if (fd2 == -1)
		{
			perror("Error, need correct file for fd2\n");
			exit(1);
		}

		while (get_next_line(fd, &line))
		{
			if (ft_strlen(line) > 3 && line[0] == 't' && line[1] == 'e' && line[2] == 'm' && line[3] == 'p' && line[4] == 'o')
			{
				while (line[i++])
				{
					if (ft_isdigit(line[i]))		// get tempo
						str_tempo[j++] = line[i];
				}
				str_tempo[j] = '\0';
			}
			if (ft_strlen(line) > 3 && line[0] == 't' && line[1] == 'r' && line[2] == 'a' && line[3] == 'c' && line[4] == 'k' && line[5] == 's') 
			{
				i = 0;
				while (line[i++])
				{
					if (line[i] == ',')				//get tracks no.
						utils.tracks_count++;
				}
				utils.tracks = (t_track *)malloc(sizeof(t_track) * utils.tracks_count); 		//mallocing tracks
				if (!utils.tracks)
				{
					perror("Error, malloc utils.tracks\n");
					exit(1);
				}
				i = 0;
				while (i < utils.tracks_count)
				{
					utils.tracks[i].sounds_count = 0;
					i++;
				}
				i = 0;
				while (line[i] != ' ')				//waves def
					i++;
				waves = ft_strsplit(&line[++i], ',');
				
			}
			if (ft_strlen(line) > 3 && ft_isdigit(line[0]) && (ft_isdigit(line[1]) || line[1] == ':' || (line[2] == ':'))) 		//99 tracks (maximum)
			{
				track_no = ft_atoi(line);
				i = 0;
				while (line[i])
				{
					if (ft_isalpha(line[i]))		//get sounds_count
					{
						if (line[i] == 'b' && line[i - 1] == 'b')
						{
							i++;
							continue;
						}
						utils.tracks[track_no - 1].sounds_count++;
					}
					i++;
				}
				//printf("track no:%d has sounds_count:%d\n", track_no, utils.tracks[track_no - 1].sounds_count);
			}
			free(line);
		}
		close(fd);
		i = 0;
		while (i < utils.tracks_count)
		{
			utils.tracks[i].sounds = (t_sound *)malloc(sizeof(t_sound) * utils.tracks[i].sounds_count);
			utils.tracks[i].sound_i = -1;
			i++;
		}
		while (get_next_line(fd2, &line))
		{
			if (ft_strlen(line) > 3 && ft_isdigit(line[0]) && (ft_isdigit(line[1]) || line[1] == ':' || (line[2] == ':'))) 		//separating tracks (maxmimum 99 tracks)
			{
				track_no = ft_atoi(line);
				i = 0; 
				while (line[i] != '\0' && utils.tracks[track_no - 1].sound_i < utils.tracks[track_no - 1].sounds_count)
				{
					if (ft_isalpha(line[i]))		//get first note
					{
						utils.tracks[track_no - 1].sound_i++;
						utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i].note = line[i];
						i++;
						if (line[i] == 'b' || line[i] == '#')		//get sign(flat or sharp)
						{
							if (line[i] == 'b')
								utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i].sign = -1;
							else
								utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i].sign = 1;
							i++;
						}
						else 
						{
							utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i].sign = 0;
						}
						if (ft_isdigit(line[i]))		//get octave
						{
							utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i].oct = ft_atoi(&line[i]);
							i++;
						}
						else if (utils.tracks[track_no - 1].sound_i > 0)
						{
							utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i].oct = utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i - 1].oct;
						}
						else
						{
							utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i].oct = 4;
						}
						if (line[i] == '/')				//get duration
						{
							i++;
							utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i].dur = ft_atof(&line[i]);
						}
						else if (utils.tracks[track_no - 1].sound_i > 0)
						{
							utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i].dur = utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i - 1].dur;
						}
						else
						{
							utils.tracks[track_no - 1].sounds[utils.tracks[track_no - 1].sound_i].dur = 1;
						}
					}
					i++;
				}
			}
			free(line);
		}
		close(fd2);
		tempo = ft_atoi(str_tempo);
		utils.tempo = tempo;
		/* printf("\n tempo is	= %d\n", tempo);
		printf(" tracks nr	= %d\n", utils.tracks_count);
		i = 0;
		while (i < utils.tracks_count)
		{
			printf(" track%d s_c	= %d\n", i, utils.tracks[i].sounds_count);
			i++;
		} */
		i = 0;
		while (i < utils.tracks_count)	
		{
			if (!ft_strcmp(waves[i], "sine"))
			{
				utils.tracks[i].wave = 0;
			}
			if (!ft_strcmp(waves[i], "saw"))
			{
				utils.tracks[i].wave = 1;
			}
			if (!ft_strcmp(waves[i], "square"))
			{
				utils.tracks[i].wave = 2;
			}
			if (!ft_strcmp(waves[i], "triangle"))
			{
				utils.tracks[i].wave = 3;
			}
			/* printf(" waves%d 	= %s(%d)\n", i, waves[i], utils.tracks[i].wave); */
			i++;
		}
		while (i >= 0)
		{
			free(waves[i]);
			i--;
		}
		i = 0;
/* 		while (i < utils.tracks[1].sounds_count)
		{
			printf("note%d	:%c", i, utils.tracks[1].sounds[i].note);
			printf("%d", utils.tracks[1].sounds[i].oct);
			printf("/%f\n", utils.tracks[1].sounds[i].dur);
			i++;
		} */
		player(&utils);
	}
	else
	{
		perror("Error, need 2 arguments\n");
		exit(1);
	}
	i = 0;
	while (i < utils.tracks_count)
	{
		free(utils.tracks[i].sounds);
		i++;
	}
	free(utils.tracks);
	return (0);
}

//use index check [0] != '\n' || '\0' or somthing to optimize strlen in if statements
