FINAL = NO

CODEFILES = main.c blocks.c transform.c check.c str_ar.c

PROG = blokus

#######################################

CODEHEADERS = ./*.h

CODEOBJECTS = $(CODEFILES:.c=.o)

ifeq ($(FINAL), YES)
	DEBUGFILES = debug_empty.c
else
	DEBUGFILES = debug.c
endif

DEBUGOBJECTS = $(DEBUGFILES:.c=.o)

default: $(CODEHEADERS)
	@clear
	@/bin/echo -e "\x1b[31mStarting Compiler.\x1b[0m\n"
	@rm -rf $(PROG)
	@/bin/echo -e "Compiling .o files"
	@gcc -c $(CODEFILES) $(DEBUGFILES) -Wall
	@/bin/echo -e "Linking .o files"
	@gcc -o $(PROG) $(CODEOBJECTS) $(DEBUGOBJECTS)
	@/bin/echo -e "Cleaning up .o files"
	@rm -rf *.o
	@/bin/echo -e "\n\x1b[32mDone!\x1b[0m\n"