/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:21:46 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/23 15:16:07 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_file
{
	int		*modes;
	char	**files;
}t_file;

typedef struct s_data
{
	char	**cmd;
	t_file	infile;
	t_file	outfile;
}t_data;

/* -------- INPUT -------- */

void	ft_input_in(char *str, t_data *data, int k);
void	ft_input_out(char *str, t_data *data, int k);
void	ft_input_cmd(char *str, t_data *data, int k);
void	ft_input(char *str, t_data *data);

/* --------- AUX ---------- */

int		ft_pass(char *str);
int		ft_pass_2(char *str, char c);
int		ft_pass_3(char *str);
void	ft_print_data(t_data *data);

/*-------- ALLOCATE -------*/

void	ft_allocate(t_data *data, int infile, int outfile, int cmd);

/* --------- FREE --------- */

void	ft_free_data(t_data *data);

/* ------- INPUT CASES -------*/

int		ft_case(char *str, int i, int *cmd, int *counter);
int		ft_case_1(char *str, int i, int *cmd);
int		ft_case_2(char *str, int i, int *cmd, int *counter);
int		ft_case_3(char *str, int i, int *cmd, int *counter);
int		ft_case_4(char *str, int i, int *cmd);

#endif