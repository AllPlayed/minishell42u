/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_cases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:07:27 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/04 10:24:25 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_case(char *str, int i, int *cmd, int *counter)
{
	if (str[i] != '>' && str[i] != '<')
		return (ft_case_1(str, i, cmd));
	else if (str[i] == '<')
		return (ft_case_2(str, i, counter));
	else if (str[i] == '>')
		return (ft_case_3(str, i, counter));
	return (i);
}

int	ft_case_1(char *str, int i, int *cmd)
{
	i += ft_pass_4(str + i);
	(*cmd)++;
	return (i);
}

int	ft_case_2(char *str, int i, int *counter)
{
	i++;
	if (str[i] == '<')
		i++;
	i += ft_pass(str + i);
	if (str[i] == '\"' || str[i] == '\'')
		i += ft_pass_2(str + i, str[i]);
	else
		i += ft_pass_3(str + i);
	(*counter)++;
	return (i);
}

int	ft_case_3(char *str, int i, int *counter)
{
	i++;
	if (str[i] == '>')
		i++;
	i += ft_pass(str + i);
	if (str[i] == '\"' || str[i] == '\'')
		i += ft_pass_2(str + i, str[i]);
	else
		i += ft_pass_3(str + i);
	i += ft_pass_3(str + i);
	(*counter)++;
	return (i);
}

int	ft_case_4(char *str, int i, int *cmd)
{
	i += ft_pass_3(str + i);
	(*cmd)++;
	return (i);
}
