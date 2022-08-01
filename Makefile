NAME = monitoring

CC = gcc
INCLUDE = -I ./include/
CFLAGS = -g $(INCLUDE) -Wall -Werror -Wextra
CURLFLAGS = -lcurl -lbsd
RM = rm -rf

PATH_SRCS = ./src/
PATH_MAIN = $(PATH_SRCS)main/
PATH_HD = $(PATH_SRCS)handlers/
PATH_LH = $(PATH_SRCS)log_handler/
PATH_PC = $(PATH_SRCS)parse_conf/
PATH_FL = $(PATH_SRCS)parse_flags/
PATH_TIME = $(PATH_SRCS)time/
PATH_UTIL = $(PATH_SRCS)util/

PATH_OBJS = ./objs/

SRC +=	$(addprefix $(PATH_MAIN), main run)
SRC +=	$(addprefix $(PATH_HD), http_handler ping_handler dns_handler)
SRC +=	$(addprefix $(PATH_LH), show_log_http show_log_ping show_log_dns)
SRC +=	$(addprefix $(PATH_PC), parse_http parse_ping parse_dns)
SRC +=	$(addprefix $(PATH_FL), parse_argv)
SRC +=	$(addprefix $(PATH_TIME), time get_time_stamp)
SRC +=	$(addprefix $(PATH_UTIL), split strjoin free_matrix matrix_len strtrim error_exit)
SRCS =	$(addsuffix .c, $(SRC))

OBJS = $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(CURLFLAGS)
	
$(PATH_OBJS)%.o: $(PATH_SRCS)%.c
	@mkdir -p ./logs
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)main/
	@mkdir -p $(PATH_OBJS)handlers/
	@mkdir -p $(PATH_OBJS)log_handler/
	@mkdir -p $(PATH_OBJS)parse_conf/
	@mkdir -p $(PATH_OBJS)parse_flags/
	@mkdir -p $(PATH_OBJS)time/
	@mkdir -p $(PATH_OBJS)util/
	@$(CC) $(CFLAGS) -c $< -o $@ $(CURLFLAGS)

clean: 
	@$(RM) $(PATH_OBJS)

fclean: clean
	@$(RM) $(NAME)

build: all

re: fclean all

.PHONY: all  clean fclean $(PATH_OBJS) re
