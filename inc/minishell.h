/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:54:15 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/18 11:42:30 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_PATH 260 //As a convention

# include "libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

extern volatile sig_atomic_t	g_sigint_recived;

typedef enum t_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_SUBSHELL,
	AST_REDIRECT_IN,
	AST_REDIRECT_OUT,
	AST_APPEND,
	AST_HEREDOC,
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_ast_node
{
	t_type				type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_minishell
{
	char		**envp;
	int			fd_in;
	int			fd_out;
	int			input_redirect;
	int			output_redirect;
	char		*input_line;
	t_ast_node	*ast;
}	t_minishell;

///###   AST
t_ast_node	*create_ast_node(t_type type, char *value);
void		free_ast(t_ast_node *node);
t_ast_node	*build_ast(t_token *tokens);

///###   AST UTILS
void		add_token_back(t_token **head, t_token *new_token);
void		free_tokens(t_token *token);

///###	PARSER
t_token		*lexer(char *input);

///###   SPLIT_CMD
char		**split_cmd(const char *cmd, const char *delimiters);

////###   GET_PATH
char		*get_path(char *cmd, const char *env_path);

///###   EXECUTE
void		execute_ast_command(t_ast_node *node, t_minishell *shell);
void		execute_single_command(char *value, t_minishell *shell);

///###	MINISHELL
int			minishell(char **envp);

///###   SIGNAL
void		setup_signal_handlers(void);

///###   BUILTIN
int			handle_builtin(char **cmd_args, t_minishell *shell);
void		echo_command(char **cmd_args);
void		cd_command(char **cmd_args);
void		pwd_command(void);
int			export_command(char **cmd_args, t_minishell *shell);
int			unset_command(char **args, t_minishell *shell);
void		env_command(t_minishell *shell);
int			exit_command(char **cmd_args, t_minishell *shell);

///###	PIPE
void		execute_single_cmd(t_minishell *shell, t_ast_node *cmd_node,
				int input, int output);
void		execute_ast_pipe(t_ast_node *cmd_node, t_minishell *shell);
void		create_pipe(int pipes[2]);

///###	INPUT
int			handle_input(char *input, t_minishell *shell);
int			ft_tablen(char **tab);
void		handle_error(const char *msg, int use_perror, int error_code);

#endif
