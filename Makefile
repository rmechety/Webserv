# --   VARIABLE   -- #
NAME = webserv

EXT = .cpp
PARAM = ./config

ADDED =
ADDEDT =

EXTRAFILE =


CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
CFLAGS += $(ADDED)
CFLAGS += $(ADDEDT)

# --   INCLUDES   -- #

INC_DIR		=	includes

# --   SOURCES   -- #
SRC_DIR = srcs

SRCSS =	srcs/main.cpp\

SRCS = $(SRCSS:$(SRC_DIR)/%$(EXT)=%$(EXT))

# --   OBJECT   -- #
OBJ_DIR     =	objs

OBJ_SUB_DIR =	exec\
				parsing\

OBJ_TO_CREATE = $(addprefix $(OBJ_DIR)/, $(OBJ_SUB_DIR))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%$(EXT)=%.o))

#Mandatory rules

all :
	mkdir -p $(OBJ_TO_CREATE)
	make $(NAME) --no-print-directory

off : clean
	mkdir -p $(OBJ_TO_CREATE)
	make ADDED=-DNAMESPACE=std $(NAME) --no-print-directory

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%$(EXT)
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -rf $(EXTRAFILE)

re: fclean all



#My personal rules


git :
	git add --all
	git commit
	git push

get_src:
		@find $(SRC_DIR) -type f -name "*$(EXT)" | tr "\n" "|" | sed -r 's/["|"]+/\\ \n/g'

run: all
	./$(NAME) $(PARAM)

test:
	make re
	./$(NAME) > ft
	make off
	./$(NAME) > std
	diff ft std > diff.log

leaks: all
	 valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --leak-resolution=high --show-reachable=yes --trace-children=yes --verbose --log-file=valgrind.log ./$(NAME) $(PARAM)

get_dir:
		@find $(SRC_DIR) -type d | tr "\n" "|" | sed -r 's/["|"]+/\\ \n/g' | sed -e 's/$(SRC_DIR)\///g'

header :
	@Headermaker $(SRC_DIR) $(INC_DIR)/prototypes.h -inc structs define


.PHONY: all clean fclean re git get_src get_dir run leaks header