CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic `pkg-config --cflags gtk4`
LFLAGS = -lm `pkg-config --libs gtk4`

PROG = GTA_Suspender

# Directories (must exist)
SRCDIR = src
OBJDIR = bin
EXEDIR = bin

# All binaries are defined as EXEDIR/Name
all: $(EXEDIR)/$(PROG)

$(EXEDIR)/$(PROG): $(OBJDIR)/$(PROG).o
	$(CC) -o $@ $^ $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEDIR)/$(PROG) $(OBJDIR)/*.o

format:
	clang-format -i -style=file $(SRCDIR)/*[ch]

scan-build: clean
	scan-build make
