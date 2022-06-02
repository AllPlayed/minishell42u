/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:51:58 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/02 12:51:21 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_pipes(t_data *data)
{
	pipe(data->fd[0]);
	pipe(data->fd[1]);
}

void	ft_start_pipes(t_data *data)
{
	dup2(data->fd[1][1], STDOUT_FILENO);
	close(data->fd[0][1]);
	close(data->fd[1][1]);
}

void	ft_mid_pipes(t_data *data)
{
	close(data->fd[1][1]);
	data->fd[0][0] = data->fd[1][0];
	pipe(data->fd[1]);
	dup2(data->fd[0][0], STDIN_FILENO);
	dup2(data->fd[1][1], STDOUT_FILENO);
}

void	ft_end_pipes(t_data *data)
{
	dup2(2, STDOUT_FILENO);
	close(data->fd[0][1]);
	close(data->fd[1][0]);
	close(data->fd[0][0]);
	close(data->fd[1][1]);
}

void	ft_close_pipes(t_data *data)
{
	close(data->fd[0][1]);
	close(data->fd[1][0]);
	close(data->fd[0][0]);
	close(data->fd[1][1]);
}
