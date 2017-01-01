CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c99

BINDIR := bin
SRCDIR := src
INCDIR := include
OBJDIR := obj

TARGET := $(BINDIR)/bf

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

debug: CFLAGS += -O0 -g
debug: CFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
debug: LDFLAGS := -fsanitize=address,undefined
debug: $(TARGET)

release: CFLAGS += -O2
release: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<

clean:
	-@rm -f $(OBJECTS)
	-@rm -f $(TARGET)

.PHONY: clean debug release
