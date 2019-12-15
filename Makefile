NAME = Zashodaktor

CFILE = ./srcs/*.c

OBJECTS = *.o

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -c $(CFILE) -I./includes
	gcc -o $(NAME) $(OBJECTS) -I./includes

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
