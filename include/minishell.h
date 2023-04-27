/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:41:46 by aessakhi          #+#    #+#             */
/*   Updated: 2022/06/24 16:09:08 by aessakhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>

extern int	g_ret;

typedef enum e_tokentype
{
	WORD,
	COMMAND,
	ARG,
	S_QUOTES,
	D_QUOTES,
	PIPE,
	REDIR,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	FILENAME,
	BLANK,
	ERROR,
	NONE,
}	t_tokentype;

typedef enum e_cmdtype
{
	CMD,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	EXEC,
	NO_CMD,
}	t_cmdtype;

typedef struct s_token
{
	char			*content;
	t_tokentype		type;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_tokentype		redir_type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_fd
{
	int	fd_in;
	int	fd_out;
}	t_fd;

typedef struct s_aux
{
	char	*path;
	char	*tmp;
	char	**folders;
}	t_aux;

typedef struct s_cmd
{
	char			*cmd;
	char			**cmd_array;
	t_cmdtype		type;
	t_redir			*redir;
	char			*filename;
	pid_t			pid;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_expand
{
	char	*result;
	int		i;
}	t_expand;

typedef struct s_shell
{
	char	*line;
	char	**env;
	int		fd_in;
	int		fd_out;
	int		std_in;
	int		std_out;
	t_token	*token;
	t_cmd	*cmd;
}	t_shell;

void	launch_shell(t_shell *shell);

//Init
void	init_shell(t_shell *shell, char **envp);

//Tokens
void	tokenize(t_shell *shell);
char	*get_token(t_token **token, char *str);
char	*get_word(t_token **token, char *str);
char	*get_pipe(t_token **token, char *str);
char	*get_redirect(t_token **token, char *str);
char	*get_space(t_token **token, char *str);
char	*get_s_quotes(t_token **token, char *str);
char	*get_d_quotes(t_token **token, char *str);
int		find_end_quote(char *str, char c, int start);
t_token	*create_token(char *content);
t_token	*create_token_space(char *content);
void	add_token(t_token **token, t_token *new_token);
void	delete_token(t_token **token);
void	delete_space(t_token *token);
void	delete_blank(t_shell *shell);

//Check tokens
int		check_tokens(t_shell *shell, t_token *token);
int		check_word(t_token **token, char **envp);
int		check_squotes(t_token **token);
int		check_dquotes(t_token **token, char **envp);
int		add_type(t_token **token, char **envp);
int		check_redir(t_token **token);
int		check_left_redir(t_token **token);
int		check_right_redir(t_token **token);
void	assign_filename_to_redir(t_token *token);
int		check_pipe(t_token **token);

//Check tokens: Expand
char	*expand_dollar(char *str, char **envp);
void	expand_check(t_expand *exp, char *str, char **envp);
void	expand_env(char *str, t_expand *exp, int j, char **envp);
char	*expand_signal(char *result);
char	*join_character(char *str, char c);
char	*replace_by_variable(char *src, int start, int end, char **envp);
char	*cpy_var(char	*src, int start, int end);

//Cmd struct
void	create_cmd_list(t_shell *shell, t_token *token);
t_cmd	*create_new_cmd(int n_of_args);
void	add_cmd(t_cmd **cmd, t_cmd *new_cmd);
void	add_cmd_type(t_cmd *cmd);
int		ft_strncmp_both(char *s1, char *s2);
int		count_n_args(t_token **token, int n_args);
void	create_cmd(t_cmd **cmd, t_token **token, int n_of_args);
int		get_cmd(t_token **token, t_cmd *new_cmd);
int		is_redir(t_token **token);
void	get_cmd_2(t_token **token, t_cmd *new_cmd, int i);

//Cmd struct: Redir
void	create_redir(t_cmd *cmd, t_token **token);
void	add_redir(t_redir **redir, t_redir *new_redir);

//Check cmd
void	check_cmd_list(t_cmd *cmd);
void	check_cmd(t_cmd *cmd);
char	**replace_cmd(char **old_array, char **new_array, int start);

//Exec
void	exec(t_shell *shell, t_cmd *cmd);

//Exec: Single cmd
void	exec_single_cmd(t_shell *shell, t_cmd *cmd);
void	exec_builtins(t_shell *shell, t_cmd *cmd);
void	exec_cmd(t_shell *shell, t_cmd *cmd);
void	exec_bin(t_shell *shell, t_cmd *cmd);
void	redir(t_shell *shell, t_redir *redir);
void	redir_in(t_shell *shell, t_redir *redir);
void	heredoc(t_shell *shell, t_redir *redir);
void	redir_out(t_shell *shell, t_redir *redir);
void	read_until_delimitor(int fd, char	*delimitor);
int		redir_builtins(t_shell *shell, t_redir *redir);
int		redir_in_builtins(t_shell *shell, t_redir *redir);
int		heredoc_builtins(t_shell *shell, t_redir *redir);
int		redir_out_builtins(t_shell *shell, t_redir *redir);

//Exec: Pipe
void	exec_pipe(t_shell *shell, t_cmd *cmd);
void	create_pipe(t_cmd *cmd, int *old_p, int *new_p);
void	exec_cmd_pipe(t_shell *shell, t_cmd *cmd, int *p);
void	exec_cmd_pipe_2(t_shell *shell, t_cmd *cmd, int *p, t_fd *fd);
void	exec_bin_pipe(t_shell *shell, t_cmd *cmd, t_fd *fd, int *p);
void	close_and_free_builtins(t_shell *shell,
			int *old_p, t_fd *fd);
void	exec_builtins_pipe(t_shell *shell, t_cmd *cmd);
void	exec_builtins_and_free(t_shell *shell, t_cmd *cmd, int *p, t_fd *fd);
void	prepare_for_next_cmd(t_cmd *cmd, int *old_p, int *new_p);
void	wait_for_exec(t_cmd *cmd);
void	redir_pipe(t_shell *shell, t_fd *fds, t_redir *redir);
void	redir_in_pipe(t_shell *shell, t_fd *fds, t_redir *redir);
void	heredoc_pipe(t_shell *shell, t_fd *fds, t_redir *redir);
void	redir_out_pipe(t_shell *shell, t_fd *fds, t_redir *redir);
void	read_until_delimitor_pipe(t_shell *shell, int fd, char	*delimitor);
void	check_valid_fd(t_shell *shell, t_fd *fd, int *p);
int		create_line_2(char **str, char **line, char *delimitor);
int		get_next_line_2(int fd, char **line, char *delimitor);

//Exec: Utils
int		check_dbl_array_size(char **arg);
void	get_cmd_path(t_cmd *cmd, char **envp);
void	init_aux(t_aux *aux, char **envp, t_cmd *cmd);
int		find_char(char *str, char c);
char	*ft_strjoin_2(char *s1, char *s2);

//Builtins
int		str_is_num(char *str);
int		ft_atol(const char *str);
void	ft_exit_single_cmd(t_shell *shell, t_cmd *cmd);
void	ft_exit_pipe(t_cmd *cmd);
void	ft_cd(char **path, t_shell *shell);
void	ft_cd_oldpwd(char **path, t_shell *shell, char *env_path, char *tmp);
void	ft_cd_home(char **path, t_shell *shell, char *env_path, char *tmp);
void	ft_cd_exp(char *oldpwd, char *pwd, t_shell *shell);
char	*get_env_path(char *search, int delim, char **env);
void	ft_echo(char **str);
int		match(char *str, char *cmd);
void	ft_env(char **env);
void	ft_export(char **export, t_shell *shell);
void	ft_sort_env(char **env);
void	ft_putstr_decl(char *str);
int		check_export(char *export, int i);
int		ft_isalnum_uscore(char c);
char	**ft_export_arg(char *export, char **envp);
int		env_size(char **envp);
int		check_env_name(char *name, char **env);
char	*get_env_name(char *env);
int		ft_pwd(void);
void	ft_unset(char **unset, t_shell *shell);
char	**ft_del_env(char **env, int id);
int		check_unset(char *export, int i, int cpt, int forb);
void	replace_env(t_shell *shell, char **cpy);
void	ft_putstr_uns(char *str);
void	ft_putstr_exp(char *str);

//Free
void	free_everything(t_shell *shell);
void	free_shell(t_shell *shell);
void	free_tokens(t_shell *shell);
void	free_cmd(t_shell *shell);
void	free_redir(t_redir *redir);
void	free_dbl_array(char **str);
void	free_aux(t_aux *aux);
void	free_and_close(t_shell *shell);

//Utils
char	*ft_strtrim2(char *s1, char const *set);
int		ft_isset(char c, char const *set);
char	*cpy_portion(char	*str, int start, int end);
int		is_special_char(char c);
char	*extract_str(char *str, int start);
char	**cpy_env(char	**envp);
char	*cpy_env_line(char *to_find, char **envp);
int		right_line(char *to_find, char *line);
char	*remove_char(char	*src, int to_remove);

//Signals
void	catch_signals(void);
void	catch_signals_exec(void);
void	catch_sigquit(int sig);
void	catch_sigint(int sig);;
void	catch_sigint_exec(int sig);
void	catch_sigquit_exec(int sig);

char	*expand(char *str, char **envp);
void	expand_base(t_expand *exp, char *str, char **envp);

#endif
