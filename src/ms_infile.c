/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:01:29 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/13 10:14:40 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_(t_data *data, int i)
{
	char	*str;
	char	*temp;
	char	*jump;
	int		fd[2];

	str = NULL;
	jump = "\n";
	while (!ft_strnstr(str, data->infile.files[i], ft_strlen(str)))
	{
		temp = readline("> ");
		if (temp == NULL || ft_strnstr(temp,
				data->infile.files[i], ft_strlen(temp)))
			break ;
		str = ft_ms_join(str, temp, ft_strlen(str), ft_strlen(temp));
		str = ft_ms_join(str, jump, ft_strlen(str), 1);
		free (temp);
	}
	if (data->infile.files[i + 1] == NULL)
	{
		pipe(fd);
		write(fd[1], str, ft_strlen(str));
		data->inpipe = fd[0];
		close (fd[1]);
	}
}

void	ft_infile(t_data *data, int i)
{
	int		fd;

	if (data->infile.files[i] == NULL)
		return ;
	if (data->infile.modes[i] == 1)
		ft_(data, i);
	else
	{
		fd = open(data->infile.files[i], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("bashie: ", 2);
			ft_putstr_fd(data->infile.files[i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			if (g_child == 1)
				exit (1);
			else
				return ;
		}
		else
			data->inpipe = fd;
	}
	i++;
	if (data->infile.files[i] != NULL)
		ft_infile(data, i);
}

void	ft_open_outfile(t_data *data, int i)
{
	data->outpipe = open(data->outfile.files[i],
			O_TRUNC | O_WRONLY | O_CREAT, 0644);
}

int	ft_outfile(t_data *data, int i)
{
	if (data->outfile.files[i] == NULL)
		return (0);
	if (data->outfile.modes[i] && data->outfile.files[i + 1] != NULL)
		open(data->outfile.files[i], O_CREAT, 0644);
	else if (!data->outfile.modes[i] && data->outfile.files[i + 1] != NULL)
		open(data->outfile.files[i], O_TRUNC | O_CREAT, 0644);
	else if (!data->outfile.modes[i] && data->outfile.files[i + 1] == NULL)
	{
		ft_open_outfile(data, i);
		return (0);
	}
	else if (data->outfile.modes[i] && data->outfile.files[i + 1] == NULL)
	{
		data->outpipe = open(data->outfile.files[i],
				O_WRONLY | O_APPEND | O_CREAT, 0644);
		return (0);
	}
	i++;
	if (data->outfile.files[i] != NULL)
		ft_outfile(data, i);
	return (0);
}
