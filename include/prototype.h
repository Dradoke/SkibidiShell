/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:17:51 by mavander          #+#    #+#             */
/*   Updated: 2025/08/14 18:15:06 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H
# include "skibidi_shell.h"

/*████████████████████████████████████████████████████████████████████████████*/
/*---builtins---*/
// builtins_utils.c
unsigned long	hash_key(const char *s);
int				get_tabindex(unsigned long hash);
t_bool			is_builtins(char *cmd, t_builtins *builtins);
t_builtins		*builtins_init(void);
// builtins_utils2.c
int				check_args_exit(t_shell *sh, t_cmd *cmd);
// ft_builtins.c
int				ft_builtins(t_shell *sh, t_cmd *cmd);
// ft_cd.c
int				ft_cd(t_shell *sh, t_list **env, t_cmd *cmd);
// ft_echo.c
int				ft_echo(t_shell *sh, t_list **env, t_cmd *cmd);
// ft_env.c
int				ft_env(t_shell *sh, t_list **env, t_cmd *cmd);
// ft_exit.c
void			close_stdfd(t_shell *sh);
int				normalize_exit_code(int ret_nb);
int				ft_exit(t_shell *sh, t_list **env, t_cmd *cmd);
// ft_export.c
int				ft_export(t_shell *sh, t_list **env, t_cmd *cmd);
// ft_pwd.c
int				ft_pwd(t_shell *sh, t_list **env, t_cmd *cmd);
// ft_unset.c
int				ft_unset(t_shell *sh, t_list **env, t_cmd *cmd);

/*████████████████████████████████████████████████████████████████████████████*/

/*---debug---*/
// print_list.c
void			print_list(t_list *lst, t_lstype type);

/*████████████████████████████████████████████████████████████████████████████*/

/*---exec---*/
// ft_critical_exec.c
t_bool			single_critical_case(t_shell *sh, t_cmd *cmd);
// ft_exec.c
t_bool			ft_exec(t_shell *sh);
// ft_heredoc.c
t_bool			ft_heredoc(t_shell *sh, t_list *cmd);
// ft_path.c
char			*ft_path(t_shell *sh, t_cmd *cmd);
int				is_directory(const char *path);
// ft_pipe.c
t_bool			setup_redir(t_shell *sh, t_cmd *cmd);
void			setup_pipes_and_redir(t_shell *sh, t_cmd *cmd);
void			switch_pipes(int (*pipe_new)[2], int (*pipe_old)[2]);
void			init_pipes(t_shell *sh);
// is_critical.c
t_bool			is_critical(t_list *args);

/*████████████████████████████████████████████████████████████████████████████*/

/*---parser---*/
// ft_addarg.c
t_bool			ft_addarg(t_shell *sh, t_cmd *tcmd);
// ft_addredir.c
t_bool			ft_addredir(t_shell *sh, t_cmd *tcmd);
// ft_cpyword.c
char			*ft_cpyword(t_shell *sh);
// ft_env_to_lst.c
char			*get_env_key(char *line);
char			*get_env_value(char *line);
t_list			*ft_env_to_lst(t_shell *sh, char **envp);
// ft_parser.c
t_bool			ft_parser(t_shell *sh);

/*████████████████████████████████████████████████████████████████████████████*/

/*---utils---*/
// ft_env_utils.c
void			ft_setenv(t_list *env, char *key, char *value);
char			*ft_getenv_val(t_list *env, char *key);
t_env			*ft_getenv(t_list *env, char *key);
// ft_env_utils2.c
t_bool			is_valid_key(char *str);
// ft_error.c
int				ft_isinvalidchar(int c);
void			ft_seterror(t_shell *sh, char *msg, int code);
void			ft_clearerror(t_shell *sh);
int				ft_puterror(t_shell *sh);
// ft_exec_utils.c
void			handle_execve_error(char *path, char *cmd_name);
void			handle_no_path(char *cmd_name);
int				get_exit_code(char *path);
t_bool			close_all_fd(t_list *redir);
t_bool			close_pipes(t_shell *sh);
// ft_free.c
void			ft_free_targ(void *targ);
void			ft_free_tredir(void *tredir);
void			ft_free_tenv(void *tenv);
void			ft_free_tcmd(void *tcmd);
void			ft_free_all(t_shell **sh);
// ft_isdelim.c
t_bool			ft_isdelim(int c);
// ft_lsttoarray.c
char			**ft_argtoarray(t_list *list);
void			ft_free_array(char **array);
char			**ft_envtoarray(t_list *list);
// ft_signal.c
void			sigint_handler(int sig);
// ft_skipspace.c
t_bool			ft_skipspace(char *str, size_t *i);
// ft_var_expand.c
size_t			ft_get_env_size(t_shell *sh, char *src, size_t *i);
t_bool			ft_write_env(t_shell *sh, char *src, char *dst, size_t *i);

/*████████████████████████████████████████████████████████████████████████████*/

#endif
