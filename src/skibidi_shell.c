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

#include "skibidi_shell.h"

static void	free_shell(t_shell *sh)
{
    if (sh->line)
    {
        free(sh->line);
        sh->line = NULL;
    }
    if (sh->cmd)
    {
        ft_lstclear(&sh->cmd, free); // Adapter selon votre fonction de free
        sh->cmd = NULL;
    }
    if (sh->env)
    {
        ft_lstclear(&sh->env, free); // Adapter selon votre fonction de free
        sh->env = NULL;
    }
}

static int	process_line(t_shell *sh)
{
    if (!sh->line || ft_strlen(sh->line) == 0)
        return (1);
    
    // Ajouter à l'historique si la ligne n'est pas vide
    add_history(sh->line);
    
    // Reset l'index pour le parsing
    sh->i = 0;
    
    // Parser la ligne
    if (!ft_parser(sh))
    {
        printf("SkibidiShell: parsing error\n");
        return (1);
    }
    
    // Debug: afficher le résultat du parsing
    print_list(sh->cmd, CMD);
    
    // Ici vous pourrez ajouter l'exécution des commandes
    // execute_commands(sh);
    
    return (1);
}

int	main(int ac, char **av, char **env)
{
    t_shell	*sh;
    
    (void)ac;
    (void)av;
    
    sh = ft_calloc(sizeof(t_shell));
    if (!sh)
        return (1);
        
    sh->env = ft_env_to_lst(env);
    
    while (1)
    {
        // Libérer la ligne précédente et les commandes
        free_shell(sh);
        
        // Lire une nouvelle ligne avec le prompt
        sh->line = readline("SkibidiShell ➜ ");
        
        // Ctrl+D (EOF) pour quitter
        if (!sh->line)
        {
            printf("exit\n");
            break;
        }
        
        // Traiter la ligne
        process_line(sh);
    }
    
    // Nettoyage final
    free_shell(sh);
    free(sh);
    
    // Nettoyer l'historique de readline
    clear_history();
    
    return (0);
}
