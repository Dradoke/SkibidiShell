/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H
# include <stdbool.h>

t_list	*ft_env_to_lst(char **envp);

int	ft_isdelim(int c);
// UTILS
bool	ft_cpyword(char *line, int *i, t_list *env);
int	ft_get_env_size(t_word *word, char *line, t_quotes_verif quotes, int *j);
bool	ft_write_env(char *line, int *k, t_word *word, t_quotes_verif *quotes);

#endif