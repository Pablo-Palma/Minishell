/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:54:15 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/29 13:02:10 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_PATH				260 //As a convention
# define SIGINT_NORMAL			0
# define SIGINT_RECIVED			1
# define SIGINT_COMMAND			2
# define SIGINT_HD				3
# define SIGINT_HD_RECIVED		4

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
	AST_AND,
	AST_OR,
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
	struct s_ast_node	*next;
}	t_ast_node;

typedef struct s_minishell
{
	char		**envp;
	char		**og_envp;
	char		*executable_path;
	int			pipes[2];
	int			special_cat;
	int			fd_read;
	int			fd_write;
	int			input_redirect;
	int			output_redirect;
	char		*input_line;
	t_ast_node	*ast;
	t_ast_node	*pipe_list;
	int			last_cmd;
	int			last_exit_status;
	int			shell_pid;
}	t_minishell;

///////////////////////////////////////////////////////////////////////////////
//																			 //
//									INPUT									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

//tokens
t_token		*create_token(t_type type, char *value);
t_token		*build_command_token(char **split_input, int *i);
t_token		*get_last_token(t_token *token);
t_type		token_type(char *value);
int			add_token_back(t_token **head, t_token *new_token);
void		free_tokens(t_token *token);

//ast
t_ast_node	*create_ast_node(t_type type, char *value);
t_ast_node	*build_ast(t_token *tokens);
void		add_cmd(t_ast_node **root, t_token *token);
void		add_pipe(t_ast_node **root, t_token *token);
void		add_red_out(t_ast_node **root, t_token *token, t_ast_node **file);
void		add_red_in(t_ast_node **root, t_token *token, t_ast_node **file);
void		free_ast(t_ast_node *node);
int			add_ast_back(t_ast_node **head, t_ast_node *new_node);

//parsing
t_token		*lexer(char **input);
int			handle_input(t_minishell *shell, char *input);
int			count_operators(char *input, char *operators);
char		*handle_operators(char *input, char *operators);
void		handle_envp(t_minishell *shell, t_token *node);
void		switch_envp(t_minishell *shell, t_token *token, int i);
int			open_quotes(char *str);
char		*strip_quotes(char *input);
int			is_valid(char *input, t_minishell *shell);

///////////////////////////////////////////////////////////////////////////////
//																			 //
//									EXECUTE									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

//execute
int			handle_redirect(t_minishell *shell, t_ast_node *cmd_node);
void		execute_ast_command(t_minishell *shell, t_ast_node *node);
void		execute_output_redirect(t_minishell *shell, t_ast_node *node);
void		execute_single_command(t_minishell *shell, char *value);
void		read_from_stdin(t_minishell *shell, const char *delim, int wr_fd);
void		proccess_heredoc(t_minishell *shell, char *delimiter);
void		execute_single_cmd(t_minishell *shell, t_ast_node *cmd_node);
void		execute_pipe_cmd(t_minishell *shell, t_ast_node *cmd_node);
int			execute_multiple_cmd(t_minishell *shell, t_ast_node *cmd_node);
int			handle_fd(t_minishell *shell);
void		select_exec(t_minishell *shell, char **command);
void		increment_shlvl(t_minishell *shell);
void		redirect_stdin(t_minishell *shell);
void		execute_single_cmd_process(t_minishell *shell, char **args,
				char *path);

///////////////////////////////////////////////////////////////////////////////
//																			 //
//									BUILTIN									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

//built-in
int			handle_builtin(t_minishell *shell, char **cmd_args);
int			special_builtin(t_minishell *shell, char **cmd_args);
void		echo_command(char **cmd_args);
void		env_command(t_minishell *shell);
void		pwd_command(void);
void		cd_command(t_minishell *shell, char **cmd_args);
int			export_command(t_minishell *shell, char **cmd_args);
int			unset_command(t_minishell *shell, char **args);
int			exit_command(t_minishell *shell, char **cmd_args);

///////////////////////////////////////////////////////////////////////////////
//																			 //
//									SIGNAL									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

//signal
void		setup_signal_handlers(void);
void		handle_sigint(int sig);
void		exit_status(t_minishell *shell, const char *msg, int status);

///////////////////////////////////////////////////////////////////////////////
//																			 //
//									ENVP									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

void		add_var_envp(char ***envp, const char *new_var);
void		update_env_var(char ***envp, const char *key, const char *value);
char		*doc_envp(t_minishell *shell, char *src);
void		increment_shlvl(t_minishell *shell);
void		free_env(char ***env);
char		*ft_double(t_minishell *shell, char *src, int i);
char		*empty_env_switch(t_minishell *shell, char *src, int i, int cnt);
char		*my_getenv(char **envp, const char *name);

///////////////////////////////////////////////////////////////////////////////
//																			 //
//									AUX_FT									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

//aux_ft
void		free_shell(t_minishell *shell);
char		**split_input(const char *cmd, const char *delimiters);
char		**split_cmd(const char *s, char *delim);
char		*get_path(char *cmd, const char *env_path);
void		handle_error(const char *msg, int use_perror, int error_code);
void		ft_strncpy(char *dst, const char *src, int n);
void		init_minishell(t_minishell *shell, char **env);
void		reset_minishell(t_minishell *shell);
char		*ft_strndup(const char *src, int n);

///////////////////////////////////////////////////////////////////////////////
//																			 //
//									MAIN									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

//minishell
int			minishell(char **envp);

///////////////////////////////////////////////////////////////////////////////
//																			 //
//									BONUS									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

char	**expand_wildcards(char **args);
char	**command(char **args, char **files);

#endif
