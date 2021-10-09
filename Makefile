CC			:=	gcc
CFLAGS	:=	-Wall -Wextra -Wpedantic -Wmissing-include-dirs

BIN	:=	bin
INC	:=	src/
SRC	:=	src

SRCS	:=	$(wildcard $(SRC)/*.c)
OBJS	:=	$(patsubst $(SRC)/%.c,$(BIN)/%.o,$(SRCS))

debug: CFLAGS += -g -O0
debug: all

release: CFLAGS += -Os -fdata-sections
release: all

.PHONY: all
all: server

$(BIN)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

server: $(OBJS)
	$(CC) $(CFLAGS) -pthread $^ -o $@