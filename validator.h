#ifndef VALIDATOR_H
# define VALIDATOR_H

int	validator(t_list *line_lst);
int	check_pipe(t_input *in1, t_input *in2, t_list *subsequent);
int	check_double(t_input *in1, t_input *in2, t_list *subsequent);
int	check_redir(t_input *in1, t_list *subsequent);

#endif
