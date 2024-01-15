/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:54:15 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/10 00:20:12 by jbaeza-c         ###   ########.fr       */
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
	AST_FILE,
	AST_HEREDOC,
	AST_HEREDOC_DELIM,
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	int				envvar;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_ast_node
{
	t_type				type;
	char				*value;
	char				*delimiter;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_minishell
{
	char		**envp;
	char		**og_envp;
	char		*executable_path;
	int			pipes[2];
	int			fd_read;
	int			fd_write;
	int			input_redirect;
	int			output_redirect;
	char		*input_line;
	t_ast_node	*ast;
	int			last_cmd;
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
void		execute_ast_command(t_minishell *shell,t_ast_node *node);
void		execute_output_redirect(t_minishell *shell, t_ast_node *node);
void		execute_single_command(t_minishell *shell, char *value);
void		execute_subshell(t_minishell	*shell);
void    	read_from_stdin(const char *delimiter, int write_fd);
void		proccess_heredoc(t_minishell *shell, char *delimiter);

///###	MINISHELL
int			minishell(char **envp, char *executable_path);
void		execute_subshell(t_minishell *shell);

///###   SIGNAL
void		setup_signal_handlers(void);

///###   BUILTIN
int			handle_builtin(t_minishell *shell, char **cmd_args);
int			handle_special_builtin(t_minishell *shell, char **cmd_args);
void		echo_command(char **cmd_args);
void		cd_command(char **cmd_args);
void		pwd_command(void);
int			export_command(t_minishell *shell, char **cmd_args);
int			unset_command(t_minishell *shell, char **args);
void		env_command(t_minishell *shell);
int			exit_command(t_minishell *shell, char **cmd_args);

///###	PIPE
void		execute_single_cmd(t_minishell *shell, t_ast_node *cmd_node);
void		execute_ast_pipe(t_minishell *shell, t_ast_node *cmd_node);
void		create_pipe(int pipes[2]);
void		handle_fd(t_minishell *shell);

///###	INPUT
int			handle_input(t_minishell *shell, char *input);
int			handle_redirect(t_minishell *shell, t_ast_node *cmd_node);
int			ft_tablen(char **tab);
int			strip_quotes(char *quoted_str, char *unquoted_str);
void		handle_error(const char *msg, int use_perror, int error_code);
char		*ft_join(char *s1, char *s2);

#endif
