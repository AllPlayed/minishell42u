/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_allocate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:55:09 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/11 12:27:30 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_allocate(t_data *data, int infile, int outfile, int cmd)
{
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

int	ft_findequal(char *str)
{
	int	i;

	i = 0;
	if (!str || str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_super_join(char **str)
{
	int		i;
	int		k;
	int		size;
	char	*final;
	int		index;

	k = -1;
	size = 0;
	while (str[++k] != NULL)
		size += ft_strlen(str[k]);
	final = malloc (size + 1);
	final[size] = '\0';
	k = -1;
	index = 0;
	while (str[++k] != NULL)
	{
		i = -1;
		while (str[k][++i] != '\0')
		{
			final[index] = str[k][i];
			index++;
		}
	}
	return (final);
}
