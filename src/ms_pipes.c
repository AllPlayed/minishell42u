/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:51:58 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/13 10:12:21 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtinpipe(t_data *data)
{
	if (data->inpipe != -1)
	{
		data->stdin = 1;
		dup2(data->inpipe, STDIN_FILENO);
	}
	if (data->outpipe != -1)
	{
		data->stdout = 1;
		dup2(data->outpipe, STDOUT_FILENO);
	}
}

void	ft_start_pipes(t_data *data)
{
	close(data->fd2[0]);
	if (data->inpipe != -1)
		dup2(data->inpipe, STDIN_FILENO);
	if (data->outpipe != -1)
		dup2(data->outpipe, STDOUT_FILENO);
	else
		dup2(data->fd2[1], STDOUT_FILENO);
	close(data->fd2[1]);
}

void	ft_mid_pipes(t_data *data)
{
	dup2(data->inpipe, STDIN_FILENO);
	if (data->outpipe != -1)
		dup2(data->outpipe, STDOUT_FILENO);
	else
		dup2(data->fd2[1], STDOUT_FILENO);
	close(data->fd2[1]);
	close(data->inpipe);
	close (data->fd2[0]);
}

void	ft_end_pipes(t_data *data)
{
	dup2(data->inpipe, STDIN_FILENO);
	if (data->outpipe != -1)
		dup2(data->outpipe, STDOUT_FILENO);
	close(data->fd2[1]);
	close(data->inpipe);
	close (data->fd2[0]);
}

void	ft_close_pipes(t_data *data)
{
	close(data->fd2[1]);
	close(data->inpipe);
	close (data->fd2[0]);
}
//poner _ en variables 