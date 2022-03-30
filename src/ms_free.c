/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:00:29 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/30 13:19:47 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_data_2(t_data *data)
{
	int	i;

	i = 0;
	while (data->outfile.files[i] != NULL)
	{
		free(data->outfile.files[i]);
		i++;
	}
	free(data->outfile.files);
	data->outfile.files = NULL;
	free(data->outfile.modes);
	data->outfile.modes = NULL;
}

void	ft_free_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd[i] != NULL)
	{
		free(data->cmd[i]);
		i++;
	}
	free(data->cmd);
	data->cmd = NULL;
	i = 0;
	while (data->infile.files[i] != NULL)
	{
		free(data->infile.files[i]);
		i++;
	}
	free(data->infile.files);
	data->infile.files = NULL;
	free(data->infile.modes);
	data->infile.modes = NULL;
	ft_free_data_2(data);
}

void	ft_freeo(char **list, int boo)
{
	while (*list)
	{
		free (*list);
		(*list)++;
	}
	if (boo)
		free (list);
}
