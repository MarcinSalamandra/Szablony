CFLAGS=-Wall -pedantic -std=c++17
LFLAGS=-lm
OBJS=main.o complex.o compile_vector.o compile_matrix.o compile_equation.o
EXEC=open

all: $(EXEC)

$(EXEC): $(OBJS)
	g++ $(LFLAGS) $+ -o $@

%.o: %.cpp
	g++ -c $(CFLAGS) $<

main.o: equation.h
complex.o: complex.h
compile_vector.o: vector.h
compile_matrix.o: matrix.h
compile_equation.o: equation.h

clean:
	rm -f *~
	rm -f *.bak
	rm -f $(EXEC) $(OBJS)

.PHONY: clean










