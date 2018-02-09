CODEFILES = main.c blocks.c transform.c debug.c

CODEHEADERS = ./*.h

CODEOBJECTS = $(CODEFILES:.c=.o)

FINAL = blokus

default: $(CODEHEADERS)
	@clear
	@/bin/echo -e "\x1b[31mStarting Compiler.\x1b[0m\n"
	@rm -rf $(FINAL)
	@/bin/echo -e "Compiling .o files"
	@gcc -c $(CODEFILES) -Wall
	@/bin/echo -e "Linking .o files"
	@gcc -o $(FINAL) $(CODEOBJECTS)
	@/bin/echo -e "Cleaning up .o files"
	@rm -rf *.o
	@/bin/echo -e "\n\x1b[32mDone!\x1b[0m\n"