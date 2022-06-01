/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:00:29 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/01 12:50:11 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_data_2(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->outfile_n)
	{
		free(data->outfile.files[i]);
		i++;
	}
	if (data->outfile.files != NULL)
	{
		free(data->outfile.files);
		free(data->outfile.modes);
	}
	data->outfile.files = NULL;
	data->outfile.modes = NULL;
}

void	ft_free_data(t_data *data)
{
	int	i;

	i = 0;
	ft_freeo(data->cmd, 1);
	while (i < data->infile_n)
	{
		free(data->infile.files[i]);
		i++;
	}
	if (data->infile.files != NULL)
	{
		free(data->infile.files);
		free(data->infile.modes);
	}
	data->infile.files = NULL;
	data->infile.modes = NULL;
	ft_free_data_2(data);
}

void	ft_freeo(char **list, int boo)
{
	int	i;

	if (!list || list == NULL || !list[0])
		return ;
	i = 0;
	while (list[i] != NULL && list[i])
	{
		free(list[i]);
		i++;
	}
	if (boo)
		free (list);
}
