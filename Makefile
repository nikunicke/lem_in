# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/06 14:31:52 by npimenof          #+#    #+#              #
#    Updated: 2020/11/03 14:44:35 by npimenof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Werror -Wextra

SRC = src/main.c src/lem_in.c\
		src/parser/parser.c src/parser/parser_helper.c\
		src/lexer/lexer.c src/lexer/lexer_helper.c\
		src/network_flow/bfs.c\
		src/network_flow/costs.c

INCL = ./includes

LIBFT = ./libft
FT_HASH = ./ft_hash
FT_GRAPH = ./ft_graph
LIBFT_INCL = $(LIBFT)/includes
FT_HASH_INCL = $(FT_HASH)/includes
FT_GRAPH_INCL = $(FT_GRAPH)/includes

all: $(NAME)

$(NAME): $(SRC) $(INCL)/lem_in.h
	make -C $(LIBFT)
	make -C $(FT_HASH)
	make -C $(FT_GRAPH)
	gcc $(FlAGS) -o $(NAME) $(SRC) -I$(INCL) \
	-L$(LIBFT) -lft -I$(LIBFT_INCL) \
	-L$(FT_HASH) -lhashft -I$(FT_HASH_INCL) \
	-L$(FT_GRAPH) -lgraph -I$(FT_GRAPH_INCL) \

clean:
	make clean -C $(LIBFT)
	make clean -C $(FT_HASH)
	make clean -C $(FT_GRAPH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)
	make fclean -C $(FT_HASH)
	make fclean -C $(FT_GRAPH)

re: fclean all

test:
	gcc main.c -L. -lgraph -I./includes -I./libft/includes -I./ft_hash/includes
