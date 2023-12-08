#ifndef INPUT_H
# define INPUT_H

int	execute_non_pipe_command(t_minishell *shell);
int	execute_pipe_command(t_minishell *shell);
int	handle_input(char *input, t_minishell *shell);
int	ft_tablen(char **tab);

#endif