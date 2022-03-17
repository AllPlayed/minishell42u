/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:42:55 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/17 14:36:18 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_input_2(char *str, t_data *data, int index)
{
	int	i;
	int	infile;
	int	outfile;
	int	cmd;

	i = 0;
	infile = 0;
	outfile = 0;
	cmd = 0;
	while (str[i] && str[i] != '|')
	{
		i += ft_pass(str + i);
		if (str[i] == '\"' || str[i] == '\'')
		{
			i += ft_pass_2(str + i, str[i]);
			cmd++;
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				i++;
			i++;
			infile++;
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				i++;
			i++;
			outfile++;
		}
		else
		{
			i += ft_pass_3(str + i);
			printf("me sumo\n");
			cmd++;
		}
		i++;
	}
	data->cmd[index] = malloc(cmd * sizeof(char *));
	data->infile[index] = malloc(infile * sizeof(char *));
	data->outfile[index] = malloc(outfile * sizeof(char *));
	printf("infile = %d\noutfile = %d\ncmd = %d\n", infile, outfile, cmd);
	return (i);
}

void	ft_input(char *str, t_data *data)
{
	int	i;
	int	index;
	int	pipes;

	i = 0;
	pipes = 0;
	while (str[i] != '\0')
	{
		i += ft_pass(str + i);
		if (str[i] == '\"' || str[i] == '\'')
			i += ft_pass_2(str + 1, str[i]);
		if (str[i] == '|')
			pipes++;
		i++;
	}
	data->pipes = pipes;
	data->cmd = malloc((pipes + 2) * sizeof(char **));
	data->cmd[pipes + 1] = NULL;
	data->infile = malloc((pipes + 2) * sizeof(char **));
	data->infile[pipes + 1] = NULL;
	data->outfile = malloc((pipes + 2) * sizeof(char **));
	data->outfile[pipes + 1] = NULL;
	printf("pipes= %d\n", pipes);
	i = 0;
	index = 0;
	while (i < data->pipes + 1)
	{
		index = ft_input_2(str + index, data, i);
		i++;
	}
}
