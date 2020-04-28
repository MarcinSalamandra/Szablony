CFLAGS=-Wall -pedantic -std=c++17
LFLAGS=-lm
OBJS=main.o complex.o vector_templates.o matrix_templates.o equation_templates.o
EXEC=open

all: $(EXEC)

$(EXEC): $(OBJS)
	g++ $(LFLAGS) $+ -o $@

%.o: %.cpp
	g++ -c $(CFLAGS) $<

main.o: equation.h
complex.o: complex.h
vector_templates.o: vector.h
matrix_templates.o: matrix.h
equation_templates.o: equation.h



clean:
	rm -f *~
	rm -f *.bak
	rm -f $(EXEC) $(OBJS)

.PHONY: clean










