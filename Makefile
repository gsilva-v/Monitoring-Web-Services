NAME = monitoring

CC = gcc
INCLUDE = -I ./include/
CFLAGS = -g $(INCLUDE)  # -Wall -Werror -Wextra
CURLFLAGS = -lcurl -lbsd
RM = rm -rf

PATH_SRCS = ./src/
PATH_MAIN = $(PATH_SRCS)main/
PATH_HD = $(PATH_SRCS)handlers/
PATH_PC = $(PATH_SRCS)parse_conf/
PATH_TIME = $(PATH_SRCS)time/
PATH_UTIL = $(PATH_SRCS)util/


PATH_OBJS = ./objs/

SRCS = 	$(PATH_MAIN)main.c $(PATH_MAIN)run.c \
		$(PATH_HD)http_handler.c \
		$(PATH_PC)parse_http.c \
		$(PATH_TIME)time.c \
		$(PATH_UTIL)split.c $(PATH_UTIL)strjoin.c
		

OBJS = $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRCS))

build : all

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(CURLFLAGS)

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)main/
	@mkdir -p $(PATH_OBJS)handlers/
	@mkdir -p $(PATH_OBJS)parse_conf/
	@mkdir -p $(PATH_OBJS)time/
	@mkdir -p $(PATH_OBJS)util/
	$(CC) $(CFLAGS) -c $< -o $@ $(CURLFLAGS)

clean: 
	$(RM) $(PATH_OBJS)

fclean: clean
	$(RM) $(NAME)	

re: fclean all

.PHONY: all  clean fclean $(PATH_OBJS) re
