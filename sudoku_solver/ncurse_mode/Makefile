MAINSOURCE = sudoku_solve_backtrace_recursive.c
MAINOBJ = sudoku_solve_backtrace_recursive.o
CFLAGS = -lncurses
OBJECTS = $(MAINOBJ) boxing.o

sudoku_solver : $(OBJECTS)
	gcc $(CFLAGS) -o sudoku_solver $(OBJECTS)

$(MAINOBJ) : $(MAINSOURCE) boxing.h
	gcc -c $(MAINSOURCE)

boxing.o : boxing.c boxing.h
	gcc -c boxing.c

clean :
	rm -rf $(OBJECTS)
