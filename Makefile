CC := gcc-10
CFLAGS := -Wall -Wextra -Wpedantic -std=c17

BINDIR := bin
SRCDIR := src
INCDIR := include
OBJDIR := obj

TARGET := $(BINDIR)/bf

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

debug: CFLAGS += -Og -g
debug: CFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
debug: LDFLAGS := -fsanitize=address,undefined
debug: $(TARGET)

release: CFLAGS += -O2
release: $(TARGET)

$(TARGET): $(OBJECTS) | $(BINDIR)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<

$(BINDIR) $(OBJDIR):
	@mkdir $@

clean:
	-@rm -rf $(TARGET) $(OBJECTS)

.PHONY: clean debug release
