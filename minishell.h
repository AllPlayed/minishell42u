/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:21:46 by ullorent          #+#    #+#             */
/*   Updated: 2022/05/17 19:24:01 by ullorent         ###   ########.fr       */
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
	char	**env;
	char	**path;
	t_file	infile;
	t_file	outfile;
	int		fd[2][2];
}t_data;

/* -------- INPUT -------- */

void	ft_bridge(char *str, t_data *data, int i, int j, char *env[]);
void	ft_input_type(char *str, t_data *data, int k, int boo);
void	ft_input_cmd(char *str, t_data *data, int k);
void	ft_input(char *str, t_data *data);

void	ft_expansion(t_data *data);
void	ft_split_expand(char *str, char **temp, int count);
char	*ft_split2(char *str, int *i);
int		ft_count(char *str);

/* --------- AUX ---------- */

int		ft_pass(char *str);
int		ft_pass_2(char *str, char c);
int		ft_pass_3(char *str);
void	ft_print_data(t_data *data);
int		ft_main_pass(char *str, int i, int comb);
void	ft_print_fd(int fd);

/*-------- ALLOCATE -------*/

void	ft_allocate(t_data *data, int infile, int outfile, int cmd);

/* --------- FREE --------- */

void	ft_free_data(t_data *data);
void	ft_freeo(char **list, int boo);

/* ------- INPUT CASES -------*/

int		ft_case(char *str, int i, int *cmd, int *counter);
int		ft_case_1(char *str, int i, int *cmd);
int		ft_case_2(char *str, int i, int *counter);
int		ft_case_3(char *str, int i, int *counter);
int		ft_case_4(char *str, int i, int *cmd);

/* -------- BUILTINS --------- */

int		ft_cmd_cases(t_data *data, char **env);

void	ft_echo(t_data *data, int boo);
void	ft_env(char *env[]);
void	ft_cd(t_data *data);
void	ft_pwd(void);

/* -------- UTILS ---------*/

char	**ft_dup_2d(char **str);
char	*ft_ms_join(char **str1, char **str2, int len1, int len2, int boo);
char	*ft_substr_ms(const char *s, unsigned int start, size_t len);
char	*ft_super_join(char **str);
int		ft_str_compare(char **str1, char *str2);

/* ------- PROCESS -------*/

void	ft_search_cmd(t_data *data);
void	ft_process(char *str, t_data *data, int index, int end, char **env);
int		ft_outfile(t_data *data, int i);
void	ft_infile(t_data *data, int i);

/* -------- PIPES --------*/

void	ft_init_pipes(t_data *data);
void	ft_close_pipes(t_data *data);
void	ft_start_pipes(t_data *data);
void	ft_mid_pipes(t_data *data);
void	ft_end_pipes(t_data *data);

/* -------- ERROR --------*/

void	ft_error_child(int w);

#endif