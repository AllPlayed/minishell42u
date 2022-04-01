/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:39:14 by ecamara           #+#    #+#             */
/*   Updated: 2022/04/01 12:49:03 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell"

void	ft_infile(t_data *data)
{
	char	*str;
	char	*temp;

	str = NULL;
	/*if (data->input[0].id != 1)
		return (1);*/
	if (data->infile.modes[i] == 1)
	{
		while (!ft_strnstr(str, data->infile.files[i], ft_strlen(str)))
		{
			temp = readline("> ");
			if (ft_strnstr(temp, data->infile.files[i], ft_strlen(temp)))
				break ;
			str = ft_strjoin_ms(str, temp, ft_strlen(str), ft_strlen(temp));
			str = ft_strjoin_ms(str, "\n", ft_strlen(str), 1);
			free (temp);
		}
		if (data->infile.files[i + 1] == NULL)
			write(fd0[1], str, ft_strlen(str));
	}
	else
		fd0[0] = open(data->infile.files[i], O_RDONLY);
	i++;
	if (data->infile.files[i] != NULL)
		ft_input_c(data, i, fd0, fd1);
	else
	{
		//ft_print_fd(fd0[0]);
		dup2(fd0[0], STDIN_FILENO);
	}
	close (fd0[1]);
	return (0);
}

int	ft_outfile(t_data *data, int i, int fd0[2], int fd1[2])
{
	int	fd;

	if (data->output[data->counter].id != 1)
		return (1);
	if (data->outfile.modes[i] && data->outfile.files[i + 1] != NULL)
		open(data->outfile.files[i], O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (!data->outfile.modes[i] && data->outfile.files[i + 1] != NULL)
		open(data->outfile.files[i], O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (!data->outfile.modes[i] && data->outfile.files[i + 1] == NULL)
	{
		open(data->outfile[data->counter].files[i], O_TRUNC);
		fd = open(data->outfile[data->counter].files[i], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, STDOUT_FILENO);
		close (fd);
		return(0);
	}
	else if (data->outfile[data->counter].modes[i] && data->outfile[data->counter].files[i + 1] == NULL)
	{
		fd = open(data->outfile[data->counter].files[i], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, STDOUT_FILENO);
		close (fd);
		return(0);
	}
	i++;
	if (data->outfile[data->counter].files[i] != NULL)
		ft_outfile(data, i, fd0, fd1);
	return (0);
}