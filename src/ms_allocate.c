/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_allocate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:55:09 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/03 12:10:10 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_allocate(t_data *data, int infile, int outfile, int cmd)
{
	printf("infile[%d] outfile[%d] cmd[%d]", infile, outfile, cmd);
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
