/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:00:29 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/23 15:01:09 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	i = 0;
	while (data->infile.files[i] != NULL)
	{
		free(data->infile.files[i]);
		i++;
	}
	free(data->infile.files);
	free(data->infile.modes);
	i = 0;
	while (data->outfile.files[i] != NULL)
	{
		free(data->outfile.files[i]);
		i++;
	}
	free(data->outfile.files);
	free(data->outfile.modes);
}
