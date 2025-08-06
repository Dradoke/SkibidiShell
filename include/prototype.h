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
void			print_list(t_list *lst, t_lstype type);
/*████████████████████████████████████████████████████████████████████████████*/
/*---exec---*/
// ft_heredoc.c
t_bool			ft_heredoc(t_shell *sh, t_list *cmd);
/*████████████████████████████████████████████████████████████████████████████*/
/*---parser---*/
// ft_addarg.c
t_bool			ft_addarg(t_shell *sh, t_cmd *tcmd);
// ft_addredir.c
t_bool			ft_addredir(t_shell *sh, t_cmd *tcmd);
// ft_cpyword.c
char			*ft_cpyword(t_shell *sh);
// ft_env_to_lst.c
size_t			ft_get_env_size(t_shell *sh, char *src, size_t *i);
char			*get_env_key(char *line);
char			*get_env_value(char *line);
t_bool			ft_write_env(t_shell *sh, char *src, char *dst, size_t *i);
t_list			*ft_env_to_lst(t_shell *sh, char **envp);
// ft_parser.c
t_bool			ft_parser(t_shell *sh);
/*████████████████████████████████████████████████████████████████████████████*/
/*---utils---*/
// ft_error.c
void			ft_free_targ(void *targ);
void			ft_free_tredir(void *tredir);
void			ft_free_tenv(void *tenv);
void			ft_free_tcmd(void *tcmd);

int				ft_isinvalidchar(int c);
void			ft_seterror(t_shell *sh, char *msg, int code);
void			ft_clearerror(t_shell *sh);
int				ft_puterror(t_shell *sh);
// ft_free.c
void			ft_free_targ(void *targ);
void			ft_free_tredir(void *tredir);
void			ft_free_tenv(void *tenv);
void			ft_free_tcmd(void *tcmd);
// ft_isdelim.c
t_bool			ft_isdelim(int c);
// ft_lsttoarray.c
char			**ft_argtoarray(t_list *list);
char			**ft_envtoarray(t_list *list);
// ft_signal.c
void			sigint_handler(int sig);
// ft_skipspace.c
t_bool			ft_skipspace(char *str, size_t *i);
// ft_var_expand.c
size_t			ft_get_env_size(t_shell *sh, char *src, size_t *i);
t_bool			ft_write_env(t_shell *sh, char *src, char *dst, size_t *i);
void			ft_setenv(t_list *env, char *key, char *value);
char			*ft_getenv_val(t_list *env, char *key);
t_env			*ft_getenv(t_list *env, char *key);
t_bool			have_equal(char *str);
t_bool			is_valid_key(char *str);
t_bool			is_valid_env(char *str, char eu);

/* Builtins */
int				ft_builtins(t_shell *sh, t_cmd *cmd);
int				ft_echo(t_shell *sh, t_list **env);
int				ft_cd(t_shell *sh, t_list **env);
int				ft_pwd(t_shell *sh, t_list **env);
int				ft_export(t_shell *sh, t_list **env);
int				ft_unset(t_shell *sh, t_list **env);
int				ft_env(t_shell *sh, t_list **env);
int				ft_exit(t_shell *sh, t_list **env);

unsigned long	hash_key(const char *s);
int				get_tabindex(unsigned long hash);
t_builtins		*builtins_init(void);
t_bool			is_builtins(char *cmd, t_builtins *builtins);

char			*ft_path(t_shell *sh, t_cmd *cmd);
t_bool			is_critical(t_list *args);

char			*ft_path(t_shell *sh, t_cmd *cmd);
t_bool			is_critical(t_list *args);

t_bool			ft_exec(t_shell *sh);

#endif
