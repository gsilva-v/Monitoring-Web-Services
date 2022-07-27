NAME = monitoring

CC = gcc
INCLUDE = -I ./include/
CFLAGS = -g $(INCLUDE) -pthread # -Wall -Werror -Wextra


RM = rm -rf

PATH_SRCS = ./src/
PATH_MAIN = $(PATH_SRCS)main/


PATH_OBJS = ./objs/

SRCS = 	$(PATH_MAIN)main.c 
		

OBJS = $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MYSQL_FLAGS) -lcurl -lbsd

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)main/
	$(CC) $(CFLAGS) -c $< -o $@ $(MYSQL_FLAGS) -lbsd

clean: 
	$(RM) $(PATH_OBJS)

fclean: clean
	$(RM) $(NAME)	

re: fclean all

.PHONY: all  clean fclean $(PATH_OBJS) re