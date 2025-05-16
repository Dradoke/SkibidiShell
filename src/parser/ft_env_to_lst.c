/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidi_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/skibidi_shell.h"

typedef struct s_env
{
	struct s_env	*prev;
	int				index;
	char			*name;
	struct s_env	*next;
}	t_env;

t_env	*ft_env_to_lst(char **envp)
{
	t_env	*env_lst;
	t_env	*head;
	int i;

	env_lst = ft_calloc(sizeof(t_env) * 1);
	if (!env_lst)
		return (NULL);
	i = 0;
	head = env_lst;
	while (envp[i])
	{
		env_lst->index = i;
		env_lst->name = envp[i];
		if (envp[i + 1])
		{
			env_lst->next = ft_calloc(sizeof(t_env) * 1);
			if (!env_lst->next)
				return (NULL);
			env_lst->next->prev = env_lst;
			env_lst = env_lst->next;
		}
		i++;
	}
	env_lst = head;
	return(head);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env_lst;
// 	(void)argc;
// 	(void)argv;

// 	env_lst = ft_env_to_lst(envp);
// 	// if (!env_lst->next) //Ajouter la gestion d'erreur !!

// 	while (env_lst)
// 	{
// 		printf("%s\n", env_lst->name);
// 		env_lst = env_lst->next;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;
	t_env	*head;
	int i = 0;
	(void)argc;
	(void)argv;
	env_lst = ft_calloc(sizeof(t_env) * 1);
	
	head = env_lst;
	while (envp[i])
		printf("%s\n", envp[i++]);
	env_lst = head;
	return(0);
}
