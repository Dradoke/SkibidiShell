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

size_t	ft_get_env_size(char *word, size_t *i, t_list *env);
bool	ft_write_env(char *src, char *dst, size_t *i, t_list *env);


/* Builtins */
int	ft_echo(t_list *args, t_env **env);
int	ft_cd(t_list *args, t_env **env);
int	ft_pwd(t_list *args, t_env **env);
int	ft_export(t_list *args, t_env **env);
int	ft_unset(t_list *args, t_env **env);
int	ft_env(t_list *args, t_env **env);
int	ft_exit(t_list *args, t_env **env);

unsigned long hash_key(const char *s);
int get_tabindex(unsigned long hash);

#endif