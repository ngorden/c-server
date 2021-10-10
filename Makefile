CC			:=	gcc
CFLAGS	:=	-Wall -Wextra -Wpedantic -Wmissing-include-dirs

BIN	:=	bin
DEP	:=	dep
EXE	:=	server
INC	:=	src
SRC	:=	src
TST	:=	test

SRCS	:=	$(wildcard $(SRC)/*.c)
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

$(BIN)/$(DEP):
	@mkdir -p $@

$(BIN)/$(DEP)/%.d: $(SRC)/%.c $(BIN)/$(DEP)
	$(CC) $(CFLAGS) $< -I$(INC) -MM >$@

-include $(DEPS)
$(BIN):
	@mkdir -p $(dir $@)

$(BIN)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(TST)/$(BIN):
	@mkdir -p $@

$(TST)/$(BIN)/%: INC += -Ilibs/minunit/
$(TST)/$(BIN)/%: $(TST)/%.c $(TST)/$(BIN)
	$(CC) $(CFLAGS) -I$(INC) $(TOBJS) $< -o $@

clean:
	$(RM) $(DEPS)
	$(RM) $(OBJS)
	$(RM) $(TBINS)
	$(RM) -r $(TST)/$(BIN)

purge: clean
	$(RM) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -pthread $^ -o $@

test: $(TBINS)
	@for test in $(TBINS) ; do ./$$test ; done
