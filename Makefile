RM           = rm -f
CC           = gcc
LIBS         = 
CFLAGS       = 
EXTRA_CFLAGS = -O2 -Wall
SRCS         = anagram.c
OBJS         = $(SRCS:.c=.o)
EXE          = anagram

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(OBJS) $(LIBS) -o $(EXE)

$(OBJS): $(SRCS)
	$(CC) -c $(CFLAGS) $(EXTRA_CFLAGS) $(SRCS)

test: spotless all
	@ECHO "-~-~-~-~-~-~-~-~TEST~-~-~-~-~-~-~-~-~-~-"
	@$(EXE) testWords

clean:
	$(RM) $(OBJS)

spotless: clean
	$(RM) $(EXE)

