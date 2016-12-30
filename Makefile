CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c99

BINDIR := bin
SRCDIR := src
INCDIR := include
OBJDIR := obj

TARGET := $(BINDIR)/bf

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

release: CFLAGS += -O2
release: $(TARGET)

debug: CFLAGS += -O0 -g
debug: CFLAGS += -fsanitize=address -fno-omit-frame-pointer
debug: CFLAGS += -fsanitize=undefined
debug: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo linking $(TARGET)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo compiling $*.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<

clean:
	-@rm -f $(OBJECTS)
	-@rm -f $(TARGET)

.PHONY: clean debug release
