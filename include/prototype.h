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

// skibidi_shell.c
/*████████████████████████████████████████████████████████████████████████████*/
/*---builtins---*/
//
/*████████████████████████████████████████████████████████████████████████████*/
/*---debug---*/
// print_list.c
void				print_list(t_list *lst, t_lstype type);
/*████████████████████████████████████████████████████████████████████████████*/
/*---exec---*/
// ft_heredoc.c
t_bool				ft_heredoc(t_list *cmd);
/*████████████████████████████████████████████████████████████████████████████*/
/*---parser---*/
// ft_addarg.c
t_bool				ft_addarg(t_shell *sh, t_cmd *tcmd);
// ft_addredir.c
t_bool				ft_addredir(t_shell *sh, t_cmd *tcmd);
// ft_cpyword.c
char				*ft_cpyword(t_shell *sh);
// ft_env_to_lst.c
t_list				*ft_env_to_lst(t_shell *sh, char **envp);
// ft_parser.c
t_bool				ft_parser(t_shell *sh);
/*████████████████████████████████████████████████████████████████████████████*/
/*---utils---*/
// ft_error.c
int					ft_isinvalidchar(int c);
void				ft_seterror(t_shell *sh, char *msg, int code);
void				ft_clearerror(t_shell *sh);
int					ft_puterror(t_shell *sh);
// ft_free.c
void				ft_free_targ(void *targ);
void				ft_free_tredir(void *tredir);
void				ft_free_tenv(void *tenv);
void				ft_free_tcmd(void *tcmd);
// ft_isdelim.c
t_bool				ft_isdelim(int c);
// ft_lsttoarray.c
char				**ft_argtoarray(t_list *list);
char				**ft_envtoarray(t_list *list);
// ft_signal.c
void				sigint_handler(int sig);
// ft_skipspace.c
t_bool				ft_skipspace(char *str, size_t *i);
// ft_var_expand.c
size_t				ft_get_env_size(t_shell *sh, char *src, size_t *i);
t_bool				ft_write_env(t_shell *sh, char *src, char *dst, size_t *i);
/*████████████████████████████████████████████████████████████████████████████*/
#endif