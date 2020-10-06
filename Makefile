NAME = lem-in

FLAGS = -Wall -Werror -Wextra

SRC = src/main.c

INCL = ./includes

LIBFT = ./libft
FT_HASH = ./ft_hash
FT_GRAPH = ./ft_graph
LIBFT_INCL = LIBFT/includes
FT_HASH_INCL = FT_HASH/includes
FT_GRAPH_INCL = FT_GRAPH/includes

all: $(NAME)

$(NAME): $(SRC)
	make -C $(LIBFT)
	make -C $(FT_HASH)
	make -C $(FT_GRAPH)
	gcc $(FlAGS) -o $(NAME) $(SRC) -L./libft -lft -I$(LIBFT_INCL)

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
