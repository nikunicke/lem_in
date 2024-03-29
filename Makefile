# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/06 14:31:52 by npimenof          #+#    #+#              #
#    Updated: 2020/11/19 17:26:58 by npimenof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Werror -Wextra

SRC = src/main.c src/lem_in.c\
		src/parser/parser.c src/parser/parser_helper.c\
		src/lexer/lexer.c src/lexer/lexer_helper.c\
		src/network_flow/edge.c src/network_flow/node.c\
		src/network_flow/path.c\
		src/network_flow/edmons_karp.c\
		src/network_flow/queue.c\
		src/output/cost.c src/output/output.c\
		src/output/write.c

INCL = ./includes

LIBFT = ./libft
FT_HASH = ./ft_hash
FT_GRAPH = ./ft_graph
LIBFT_INCL = $(LIBFT)/includes
FT_HASH_INCL = $(FT_HASH)/includes
FT_GRAPH_INCL = $(FT_GRAPH)/includes

all: $(NAME)

$(NAME): $(SRC) $(INCL)/lem_in.h
	@if git submodule status | egrep -q '^[-]' ; then \
		echo "INFO: Initializing git submodules"; \
		git submodule update --init; \
	fi
	make -C $(LIBFT)
	make -C $(FT_HASH)
	make -C $(FT_GRAPH)
	gcc -g $(FLAGS) -o $(NAME) $(SRC) -I$(INCL) \
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
