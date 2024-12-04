CC = gcc
C_FLAGS = -Wall -Werror -Wextra
INCLUDE_REPOS = -Isrc/include -IC:\Libraries\SDL2\include -IC:\Libraries\BOX\include
LIB_REPOS = -LC:\Libraries\SDL2\lib -LC:\Libraries\BOX\lib
LIB_FLAGS = -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_image -lSDL2 -lBOX
SRCS =	src/main.c
NAME = sm.exe

all : ${NAME}

${NAME} :
	${CC} ${C_FLAGS} ${LIB_REPOS} ${SRCS} ${LIB_FLAGS} ${INCLUDE_REPOS} -o ${NAME}

clean :
	rm ${NAME}

fclean : clean
	rm -f ${NAME}

re : clean fclean all

exe : re
	./${NAME}
