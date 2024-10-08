HEADER = uart.h
NAME = uart
SRC = crc_calculations.c open_config.c ReceiveX.c TransmitX.c main.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

RM = rm -rf

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re