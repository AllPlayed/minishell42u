/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_allocate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:55:09 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/01 14:45:52 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_allocate(t_data *data, int infile, int outfile, int cmd)
{
	//printf("CMD = %d INFILE = %d OUTFILE = %d\n", cmd, infile, outfile);
	data->infile.files = malloc((infile + 1) * sizeof(char *));
	data->infile.modes = malloc((infile) * sizeof(int));
	data->infile.files[infile] = NULL;
	data->outfile.files = malloc((outfile + 1) * sizeof(char *));
	data->outfile.modes = malloc((outfile) * sizeof(int));
	data->outfile.files[outfile] = NULL;
	data->cmd = malloc((cmd + 1) * sizeof(char *));
	data->cmd[cmd] = NULL;
	data->cmd_n = cmd;
	data->outfile_n = outfile;
	data->infile_n = infile;
}
