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

t_list	*ft_env_to_lst(t_shell *sh, char **envp);

int		ft_isdelim(int c);
int		ft_isinvalidchar(int c);

void	print_list(t_list *lst, t_lstype type);

bool	ft_parser(t_shell *sh);

bool	ft_skipspace(char *str, size_t *i);

bool	ft_addredir(t_shell *sh, t_cmd *tcmd);
bool	ft_addarg(t_shell *sh, t_cmd *tcmd);

char	*ft_cpyword(t_shell *sh);

size_t	ft_get_env_size(t_shell *sh, char *src, size_t *i);
bool	ft_write_env(t_shell *sh, char *src, char *dst, size_t *i);

void	ft_free_targ(void *targ);
void	ft_free_tredir(void *tredir);
void	ft_free_tenv(void *tenv);
void	ft_free_tcmd(void *tcmd);

int		ft_isinvalidchar(int c);
void	ft_seterror(t_shell *sh, char *msg, int code);
void	ft_clearerror(t_shell *sh);
int		ft_puterror(t_shell *sh);

#endif