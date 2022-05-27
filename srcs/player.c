/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:19:57 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/27 16:18:47 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisynth.h"
#include "miniaudio.h"

typedef struct s_player
{
	ma_audio_buffer_config	bufferConfig;
	ma_audio_buffer			buffer;
	ma_device				device;
	ma_device_config		deviceConfig;
}				t_player;

static void	print_wave(float *aud_buffer, int i)
{
	float	wave;

	wave = -1;
	while (wave < 1 && i > 0 && i < 200)
	{
		if ((int)(wave * 100) == (int)(aud_buffer[i] * 100))
			printf("X");
		else
			printf("-");
		wave += 0.01;
	}
	if (i > 0 && i < 200)
		printf("\n");
}

static void	play_sound(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
	ma_audio_buffer	*pBuffer;

	MA_ASSERT(pDevice->playback.channels == DEVICE_CHANNELS);
	pBuffer = (ma_audio_buffer *)pDevice->pUserData;
	MA_ASSERT(pBuffer != NULL);
	ma_audio_buffer_read_pcm_frames(pBuffer, pOutput, frameCount, 1);
//	ma_audio_buffer_seek_to_pcm_frame(pBuffer, 0);
	(void)pInput;
}

static void	init_device(ma_device_config *pDeviceConf, void *data)
{
	*pDeviceConf = ma_device_config_init(ma_device_type_playback);
	pDeviceConf->playback.format = DEVICE_FORMAT;
	pDeviceConf->playback.channels = DEVICE_CHANNELS;
	pDeviceConf->sampleRate = DEVICE_SAMPLE_RATE;
	pDeviceConf->dataCallback = play_sound;
	pDeviceConf->pUserData = data;
}

static void	sub_aud_buffer(float *aud_buffer, float freq, float amp, int wave)
{
	int	i;

	i = 0;
	while (i <= AUD_BUFF_SIZE)
	{
		if (wave == 2 || wave == 0)
			aud_buffer[i] -= amp * sin(freq * PI * (float)i / DEVICE_SAMPLE_RATE);
		if (wave == 2)
		{
			if (aud_buffer[i] < 0.75 * amp && aud_buffer[i] > -0.75 * amp)
				aud_buffer[i] = 0;
			else if (aud_buffer[i] >= 0.75 * amp)
				aud_buffer[i] = 1 * amp; 
			else if (aud_buffer[i] <= -0.75 * amp)
				aud_buffer[i] = -1 * amp; 
		}
		if (wave == 1)
			aud_buffer[i] -= amp * (1 / PI) * (freq * PI * fmod((float)i / DEVICE_SAMPLE_RATE, 1.0f / freq) - (PI / 2));
		if (wave == 3)
			aud_buffer[i] -= amp * asin(sin(freq * PI * (float)i / DEVICE_SAMPLE_RATE)) * 2 / PI;
		print_wave(aud_buffer, i);
		i++;
	}
}

void	add_aud_buffer(float *aud_buffer, float freq, float amp, int wave)
{
	int	i;

	i = 0;
	while (i <= AUD_BUFF_SIZE)
	{
		if (wave == 2 || wave == 0)
			aud_buffer[i] += amp * sin(freq * PI * (float)i / DEVICE_SAMPLE_RATE);
		if (wave == 2)
		{
			if (aud_buffer[i] < 0.75 * amp && aud_buffer[i] > -0.75 * amp)
				aud_buffer[i] = 0;
			else if (aud_buffer[i] >= 0.75 * amp)
				aud_buffer[i] = 1 * amp; 
			else if (aud_buffer[i] <= -0.75 * amp)
				aud_buffer[i] = -1 * amp; 
		}
		if (wave == 1)
			aud_buffer[i] += amp * (1 / PI) * (freq * PI * fmod((float)i / DEVICE_SAMPLE_RATE, 1.0f / freq) - (PI / 2));
		if (wave == 3)
			aud_buffer[i] += amp * asin(sin(freq * PI * (float)i / DEVICE_SAMPLE_RATE)) * 2 / PI;
		print_wave(aud_buffer, i);
		i++;
	}
}

void	fill_aud_buffer(float *aud_buffer, float freq, float amp, int wave)
{
	int	i;

	i = 0;
	ft_bzero(aud_buffer, AUD_BUFF_SIZE);
	while (i <= AUD_BUFF_SIZE)
	{
		if (wave == 2 || wave == 0)
			aud_buffer[i] = amp * sin(freq * PI * (float)i / DEVICE_SAMPLE_RATE);
		if (wave == 2)
		{
			if (aud_buffer[i] < 0.75 * amp && aud_buffer[i] > -0.75 * amp)
				aud_buffer[i] = 0;
			else if (aud_buffer[i] >= 0.75 * amp)
				aud_buffer[i] = 1 * amp; 
			else if (aud_buffer[i] <= -0.75 * amp)
				aud_buffer[i] = -1 * amp; 
		}
		if (wave == 1)
			aud_buffer[i] = amp * (2 / PI) * (freq * PI * fmod((float)i / DEVICE_SAMPLE_RATE, 1.0f / freq) - (PI / 2));
		if (wave == 3)
			aud_buffer[i] = amp * asin(sin(freq * PI * (float)i / DEVICE_SAMPLE_RATE)) * 2 / PI;
		print_wave(aud_buffer, i);
		i++;
	}
}

static void	init_aud_buffer_and_play(float *aud_buffer, float freq, float amp, t_player *player, int wave, int oper)
{
	ma_result	result;

	if (oper == 0)
		fill_aud_buffer(aud_buffer, freq, amp, wave);
	else if (oper == 1)
		add_aud_buffer(aud_buffer, freq, amp, wave);
	else if (oper == 2)
		sub_aud_buffer(aud_buffer, freq, amp, wave);
	player->bufferConfig = ma_audio_buffer_config_init(DEVICE_FORMAT, DEVICE_CHANNELS, AUD_BUFF_SIZE * 0.5, aud_buffer, NULL);
	result = ma_audio_buffer_init(&player->bufferConfig, &player->buffer);	
	if (result != MA_SUCCESS)
	{
		printf("Failed to init buffer.\n");
		exit (-1);
	}
	init_device(&player->deviceConfig, &player->buffer);
	if (ma_device_init(NULL, &player->deviceConfig, &player->device) != MA_SUCCESS)
	{
		printf("Failed to open playback device.\n");
		exit (-4);
	}
	printf("Device Name: %s\n", player->device.playback.name);
	if (ma_device_start(&player->device) != MA_SUCCESS)
	{
		printf("Failed to start playback device.\n");
		ma_device_uninit(&player->device);
		exit (-5);
	}
}

static void	play_tone(t_player *player, float *aud_buffer, float freq, float amp, float dur, int wave, int oper)
{
	if (ma_device_get_state(&player->device) == ma_device_state_started)
		ma_device_stop(&player->device);
	init_aud_buffer_and_play(aud_buffer, freq, amp, player, wave, oper);
	usleep (dur * 1000000);
}

static float	midi_note_to_freq(int note)
{
	float a = 440;

	if (note == -1)
		return (0);
	return ((a / 32) * pow(2, ((note - 9) / 12.0)));
}

static int char_to_semitone(char tone)
{
	int	semitone;

	if (tone == 'c')
		semitone = 0;
	if (tone == 'd')
		semitone = 2;
	if (tone == 'e')
		semitone = 4;
	if (tone == 'f')
		semitone = 5;
	if (tone == 'g')
		semitone = 7;
	if (tone == 'a')
		semitone = 9;
	if (tone == 'b')
		semitone = 11;
	if (tone == 'r')
		semitone = -1;
	return (semitone);
}

static int	note_to_midi_note(char tone, int sign, int octave)
{
	tone = char_to_semitone(tone);
	if (tone == -1)
		return (-1);
	return (octave * 12 + tone + sign);
}

static float	note_to_freq(char tone, int sign, int octave)
{
	return (midi_note_to_freq(note_to_midi_note(tone, sign, octave)));
}

void	player(t_utils *utils)
{
	t_player	player;
	float		*aud_buffer;
	int			i;
	float		tempo_rate;

	aud_buffer = (float *)malloc(sizeof(float) * AUD_BUFF_SIZE);
	i = 0;
	tempo_rate = (float)1 / utils->tempo * 60;
	while (1)
	{
		while (i <= utils->tracks[0].sounds_count)
		{
			utils->tracks[0].sounds[i].freq = note_to_freq(utils->tracks[0].sounds[i].note,
				utils->tracks[0].sounds[i].sign,
				utils->tracks[0].sounds[i].oct);
			if (utils->tracks[0].sounds[i].freq == 0)
			play_tone(&player, aud_buffer,
				utils->tracks[0].sounds[i].freq,
				0.0,
				utils->tracks[0].sounds[i].dur * tempo_rate,
				utils->tracks[0].wave,
				0);
			else
			play_tone(&player, aud_buffer,
				utils->tracks[0].sounds[i].freq,
				0.2,
				utils->tracks[0].sounds[i].dur * tempo_rate,
				utils->tracks[0].wave,
				0);
			i++;
		}
		exit (1);
	}
	ma_audio_buffer_uninit(&player.buffer);
	ma_device_uninit(&player.device);
	(void)utils;
}
