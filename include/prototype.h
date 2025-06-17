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
# include "skibidi_shell.h"

t_list	*ft_env_to_lst(char **envp);

int		ft_isdelim(int c);

void	print_list(t_list *lst, t_lstype type);

t_list	*ft_parser(t_shell *shell);

void	ft_skipspace(char *str, size_t *i);

void	ft_addredir(t_shell *sh, t_cmd *tcmd);
void	ft_addarg(t_shell *sh, t_cmd *tcmd);

char	*ft_cpyword(t_shell *sh);

bool	quotes_usecase(char c, t_quotes_verif *quotes);
int	ft_strncmp_cstm(const char *s1, const char *s2, size_t n);
bool	ft_write_env(char *line, int *k, t_word *word, t_quotes_verif *quotes);
int	ft_get_env_size(t_shell *sh, char *line, t_quotes_verif quotes);

#endif