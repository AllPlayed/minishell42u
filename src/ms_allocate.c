/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_allocate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:55:09 by ecamara           #+#    #+#             */
/*   Updated: 2022/03/18 14:04:30 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_allocate(t_data *data, int pipes)
{
	data->pipes = pipes;
	data->cmd = malloc((pipes + 2) * sizeof(char **));
	data->cmd[pipes + 1] = NULL;
	data->infile = malloc((pipes + 2) * sizeof(char **));
	data->infile[pipes + 1] = NULL;
	data->in_modes = malloc((pipes + 2) * sizeof(int *));
	data->outfile = malloc((pipes + 2) * sizeof(char **));
	data->out_modes = malloc((pipes + 2) * sizeof(int *));
	data->outfile[pipes + 1] = NULL;
}

void	ft_allocate_2(t_data *data, int index, int infile, int outfile)
{
	data->infile[index] = malloc((infile + 1) * sizeof(char *));
	data->in_modes[index] = malloc((infile) * sizeof(int));
	data->infile[index][infile] = NULL;
	data->outfile[index] = malloc((outfile + 1) * sizeof(char *));
	data->out_modes[index] = malloc((outfile) * sizeof(int));
	data->outfile[index][outfile] = NULL;
}

void	ft_allocate_3(t_data *data, int index, int cmd)
{
	data->cmd[index] = malloc((cmd + 1) * sizeof(char *));
	data->cmd[index][cmd] = NULL;
}
