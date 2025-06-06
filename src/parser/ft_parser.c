/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static void	new_redir(char *line, char **env, int *i, t_cmd *redir)
{
	
}

static void	set_last_redir(t_cmd *content)
{
	t_list	*redir;

	redir = content->redir;
	while (redir->next)
	{
		if (((t_redir *)redir->content)->type == INFILE
			|| ((t_redir *)redir->content)->type == HEREDOC)
			content->last_redir[INPUT] = redir->content;
		else if (((t_redir *)redir->content)->type == OUTFILE
			|| ((t_redir *)redir->content)->type == APPEND)
			content->last_redir[OUTPUT] = redir->content;
		redir = redir->next;
	}
}

static void	new_command(char *line, char **env, int *i, t_list *cmd)
{
	ft_lstadd_back(&cmd, ft_lstnew(ft_calloc(sizeof(t_cmd))));
	while (line[*i] != '|')
	{
		while (isspace(line[*i]))
			(*i)++;
		if (ft_isdelim(line[*i]))
			new_redir(line, env, i, (t_cmd *)cmd->content);
		(*i)++;
	}
	set_last_redir(cmd->content);
	
}

int	ft_skipspace(char *str, int *i)
{
	while (ft_isspace(str[*i]))
		(*i)++;
	return (1);
}

t_list	*ft_parser(char *line, char **env)
{
	size_t			i;
	t_list			*cmd;
	
	cmd = ft_lstnew(ft_calloc(sizeof(t_cmd)));
	if (!ft_lstlast(cmd)->index)
		manage_first_cmd();
	while (line[i])
	{
		ft_skipspace(line, &i);
		if (line[i] == '|')
		{
			i++;
			if (!ft_lstlast(cmd)->prev || !cmd->index)
				perror("SkibidiShell: syntax error near unexpected token '|'");
			else
				new_command(line, env, &i, cmd);
		}
	}
	return (cmd);
}



// TEST FT_PARSER

static void	process_pipe(char *line, char **env, size_t *i, t_list *cmd)
{
    if (!ft_lstlast(cmd)->index)
    {
        perror("SkibidiShell: syntax error near unexpected token '|'");
        return ;
    }
    (*i)++;
    new_command(line, env, (int *)i, cmd);
}

static void	process_current_command(char *line, char **env, size_t *i, t_list *cmd)
{
    while (line[*i] && line[*i] != '|')
    {
        while (ft_isspace(line[*i]))
            (*i)++;
        if (line[*i] && line[*i] != '|')
        {
            if (ft_isdelim(line[*i]))
                new_redir(line, env, (int *)i, (t_cmd *)ft_lstlast(cmd)->content);
            else
            {
                // Passer les arguments (à implémenter)
                while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && !ft_isdelim(line[*i]))
                    (*i)++;
            }
        }
    }
    set_last_redir(ft_lstlast(cmd)->content);
}

t_list	*ft_parser(t_shell *shell)
{
    size_t	i;
    t_list	*cmd;
    
    i = 0;
    cmd = ft_lstnew(ft_calloc(sizeof(t_cmd)));
    
    while (line[i])
    {
        ft_skipspace(line, (int *)&i);
        if (!line[i])
            break;
            
        if (line[i] == '|')
            process_pipe(line, env, &i, cmd);
        else
            process_current_command(line, env, &i, cmd);
    }
    return (cmd);
}
