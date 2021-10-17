CC			:=	gcc
CFLAGS	:=	-Wall -Wextra -Wpedantic -Wmissing-include-dirs

BIN	:=	bin
DEP	:=	dep
EXE	:=	server
INC	:=	src
SRC	:=	src
TST	:=	test

SRCS	:=	$(wildcard $(SRC)/*.c $(SRC)/net/*.c $(SRC)/structures/*.c)
OBJS	:=	$(patsubst $(SRC)/%.c,$(BIN)/%.o,$(SRCS))
DEPS	:=	$(patsubst $(SRC)/%.c,$(BIN)/$(DEP)/%.d,$(SRCS))

TSRCS	:=	$(wildcard $(TST)/*.c)
TOBJS	:=	$(filter-out $(BIN)/main.o,$(OBJS)) # subset of $(OBJS)
TBINS	:=	$(patsubst $(TST)/%.c,$(TST)/$(BIN)/%,$(TSRCS))

.PHONY: debug
debug: CFLAGS += -g -O0 -fdata-sections
debug: all

release: CFLAGS += -Os
release: clean
release: all

.PHONY: all
all: $(EXE)

$(TST)/$(BIN):
	@mkdir -p $@

$(BIN)/$(DEP)/%.d: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -I$(INC) -MM >$@

$(BIN)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(TST)/$(BIN)/%: INC += -Ilibs/minunit/
$(TST)/$(BIN)/%: $(TST)/%.c $(TST)/$(BIN) $(TOBJS)
	$(CC) $(CFLAGS) -I$(INC) $(TOBJS) $< -o $@

clean:
	$(RM) $(DEPS) $(OBJS) $(TBINS)
	$(RM) -r $(TST)/$(BIN)

purge: clean
	$(RM) $(EXE)

-include $(DEPS)
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -pthread $^ -o $@

test: $(TBINS) $(TST)/$(BIN)
	@for test in $(TBINS) ; do ./$$test ; done
