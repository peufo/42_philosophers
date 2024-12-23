NAME			=	philo
DIR_SRC			=	./
DIR_BUILD		=	./build
SOURCES			=	lib.c main.c 
SOURCES_NAME	=	$(basename $(SOURCES))
OBJECTS			=	$(addsuffix .o, $(addprefix $(DIR_BUILD)/, $(SOURCES_NAME)))
FLAGS			=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	@cc $(OBJECTS) $(FLAGS) -o $@

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c | $(DIR_BUILD)
	@cc $(FLAGS) -c $^ -o $@

$(DIR_BUILD):
	@mkdir -p $@

clean:
	rm -rf $(DIR_BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all
