/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:00:29 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/18 13:09:40 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->cmd[i] != NULL)
	{
		j = 0;
		while (data->cmd[i][j])
		{
			free(data->cmd[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (data->infile && data->infile[i] != NULL)
	{
		j = 0;
		while (data->infile[i][j])
		{
			free(data->infile[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (data->outfile && data->outfile[i] != NULL)
	{
		j = 0;
		while (data->outfile[i][j])
		{
			free(data->outfile[i][j]);
			j++;
		}
		i++;
	}
	data->pipes = 0;
}