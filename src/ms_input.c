/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:42:55 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/18 13:26:31 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_input_3(char *str, t_data *data, int index)
{
	int	i;
	int	j;
	int	in;
	int	out;

	i = 0;
	in = 0;
	out = 0;
	//printf("string = %s\n", str);
	while (str[i] && str[i] != '|')
	{
		i += ft_pass(str + i);
		if (str[i] == '\"' || str[i] == '\'')
		{
			j = i;
			i += ft_pass_2(str + i, str[i]);
			ft_substr(str, j, i - j);
		}
		else if (str[i] == '<')
		{
			j = i;
			if (str[i + 1] == '<')
			{
				data->in_modes[index][in] = 1;
				i++;
			}
			else
				data->in_modes[index][in] = 0;
			i++;
			in++;
			j = i;
			i += ft_pass_3(str + i);
			ft_substr(str, j, i - j);
		}
		else if (str[i] == '>')
		{
			j = i;
			if (str[i + 1] == '>')
			{
				data->out_modes[index][out] = 1;
				i++;
			}
			else
				data->out_modes[index][out] = 0;
			i++;
			out++;
			j = i;
			i += ft_pass_3(str + i);
			ft_substr(str, j, i - j);
		}
		else
		{
			i += ft_pass_3(str + i);
		}
		i++;
	}
}

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
	//printf("string = %s\n", str);
	while (str[i] && str[i] != '|')
	{
		printf("i1 = %d\n",  i);
		i += ft_pass(str + i);
		printf("i2 = %d\n",  i);
		if (str[i] == '\"' || str[i] == '\'')
		{
			//printf("esto es -> %c\n", str[i]);
			i += ft_pass_2(str + i, str[i]);
			cmd++;
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				i++;
			i++;
			infile++;
			cmd--;
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				i++;
			i++;
			outfile++;
			cmd--;
		}
		else
		{
			//printf("cmd state: [%s]\n", str + i);
			i += ft_pass_3(str + i);
			printf("me sumo %d\n", i);
			cmd++;
		}
		printf("i3 = %d\n",  i);
		i++;
	}
	data->cmd[index] = malloc((cmd + 1)* sizeof(char *));
	data->cmd[index][cmd] = NULL; 
	data->infile[index] = malloc((infile + 1) * sizeof(char *));
	data->in_modes[index] =  malloc((infile) * sizeof(int));
	data->infile[index][infile] = NULL; 
	data->outfile[index] = malloc((outfile + 1) * sizeof(char *));
	data->out_modes[index] =  malloc((outfile) * sizeof(int));
	data->outfile[index][outfile] = NULL; 
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
	data->in_modes =  malloc((pipes + 2) * sizeof(int *));
	data->outfile = malloc((pipes + 2) * sizeof(char **));
	data->out_modes =  malloc((pipes + 2) * sizeof(int *));
	data->outfile[pipes + 1] = NULL;
	printf("pipes= %d\n", pipes);
	i = 0;
	index = 0;
	while (i < data->pipes + 1)
	{
		index = ft_input_2(str + index, data, i);
		ft_input3(str, data, i);
		index++;
		i++;
	}
	
}
