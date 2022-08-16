/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:05:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/16 16:31:30 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void get_token(char *in, t_general *gen, t_token **head)
{
    int j;
    int flag;
    t_token    *buffer;

    gen->i = 0;
    j = 0;
    flag = 0;
    if (strchr(WHITESPACE, in[0]))
        flag = 1;
    while (in[gen->i] != '\0')
    {
        if (strchr(TOKENS, in[gen->i]))
        {
            if (in[gen->i + 1] == in[gen->i])
            {
                if (in[gen->i] == '<')
                {
                    token_add_front(head, token_new('-', NULL));
                                buffer = *head;
                    printf("buffer; type: %c, contents: %s\n", buffer->type, buffer->content);
                }
                if (in[gen->i] == '>')
                {
                    token_add_front(head, token_new('+', NULL));
                                buffer = *head;
                    printf("buffer; type: %c, contents: %s\n", buffer->type, buffer->content);
                }
                gen->i += 2;
                j = gen->i;
            }
            else
            {
                token_add_front(head, token_new(in[gen->i], NULL));
                            buffer = *head;
                printf("buffer; type: %c, contents: %s\n", buffer->type, buffer->content);
            }
        }
        if ((strchr(WHITESPACE, in[gen->i]) || strchr(TOKENS, in[gen->i])) && flag)
        {
            gen->i++;
            j++;
            if (!strchr(WHITESPACE, in[gen->i]) && !strchr(TOKENS, in[gen->i]))
                flag = 0;
            continue ;
        }
        else if (strchr(WHITESPACE, in[gen->i]) || strchr(TOKENS, in[gen->i]))
        {
            token_add_front(head, token_new('a', ft_substr(in, j, gen->i - j)));
            buffer = *head;
            printf("buffer; type: %c, contents: %s\n", buffer->type, buffer->content);
            flag = 1;
            j = gen->i;
        }
        gen->i++;
    }
    if (gen->i != j)
    {
        while (strchr(WHITESPACE, in[j]))
            j++;
        token_add_front(head, token_new('a', ft_substr(in, j, gen->i - j)));
        buffer = *head;
        printf("buffer; type: %c, contents: %s\n", buffer->type, buffer->content);
    }
}

void	init(t_general *gen)
{
	gen->buff = malloc(sizeof(char *) * MAX_WORDS);
	gen->token_buff = malloc(sizeof(char) * MAX_WORDS);
}

void	reset(t_general *gen, t_token **head)
{
    token_clear(head, free);
	gen->i = 0;
}

void	parse_token(t_general *gen, t_token **head, char *inpt)
{
	while (strchr(WHITESPACE, inpt[gen->i]))
		gen->i++;
	inpt += gen->i;
	while (gen->i < strlen(inpt))
	{
        get_token(inpt, gen, head);
		inpt += gen->i;
	}
	reset(gen, head);
}