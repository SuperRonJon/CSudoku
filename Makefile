CC 			?= cc
CFLAGS		?= -Wall -Wextra -Werror -O2

BUILDDIR	:= build
SRCDIR		:= src

SRCS 		:= $(wildcard $(SRCDIR)/*.c)
OBJS 		:= $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

ifeq ($(OS),Windows_NT)
        EXE_EXT := .exe
else
        EXE_EXT :=
endif

PROGRAM 	:= sudoku$(EXE_EXT)
TARGET 		:= $(BUILDDIR)/$(PROGRAM)
DEBUGTARGET	:= $(BUILDDIR)/debug$(EXE_EXT)

.PHONY: all debug clean $(PROGRAM)

all: $(PROGRAM)

debug: $(DEBUGTARGET)

$(PROGRAM): $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -s $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEBUGTARGET): $(SRCS) | $(BUILDDIR)
	$(CC) $(CFLAGS) -g $^ -o $@

$(BUILDDIR):
	@mkdir -p build

clean:
	$(RM) -r build
