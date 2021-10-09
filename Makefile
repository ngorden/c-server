CC			:=	gcc
CFLAGS	:=	-Wall -Wextra -Wpedantic -Wmissing-include-dirs

BIN	:=	bin
INC	:=	src
SRC	:=	src
TST	:=	test

SRCS	:=	$(wildcard $(SRC)/*.c)
OBJS	:=	$(patsubst $(SRC)/%.c,$(BIN)/%.o,$(SRCS))

TSRCS	:=	$(wildcard $(TST)/*.c)
TOBJS	:=	$(filter-out $(BIN)/main.o,$(OBJS))
TBINS	:=	$(patsubst $(TST)/%.c,$(TST)/$(BIN)/%,$(TSRCS))

.PHONY: debug
debug: CFLAGS += -g -O0
debug: all

release: CFLAGS += -Os -fdata-sections
release: clean
release: all

.PHONY: all
all: server

$(BIN)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(TST)/$(BIN)/%: $(TST)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Ilibs/minunit -I$(INC) $(TOBJS) $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(TBINS)

server: $(OBJS)
	$(CC) $(CFLAGS) -pthread $^ -o $@

test: $(TBINS)
	for test in $(TBINS) ; do ./$$test ; done
