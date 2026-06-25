CC 		?= cc
CFLAGS	?= -Wall -Wextra -Werror -O2

BUILDDIR := build

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=$(BUILDDIR)/%.o)

PROGRAM := sudoku
TARGET := $(BUILDDIR)/$(PROGRAM)

.PHONY: all debug clean $(PROGRAM)

all: $(PROGRAM)

debug: $(BUILDDIR)/debug

$(PROGRAM): $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -s $^ -o $@

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/debug: $(SRCS) | $(BUILDDIR)
	$(CC) $(CFLAGS) -g $^ -o $@

$(BUILDDIR):
	@mkdir -p build

clean:
	$(RM) -r build
