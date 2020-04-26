CFLAGS=-Wall -pedantic
LFLAGS=-lm
OBJS=main.o Lzespolona.o mym.o
EXEC=open

all: $(EXEC)

$(EXEC): $(OBJS)
	g++ $(LFLAGS) $+ -o $@

%.o: %.cpp
	g++ -c $(CFLAGS) $<

main.o: wektor.h
Lzespolona.o: Lzespolona.h
mym.o: wektor.h

clean:
	rm -f *~
	rm -f *.bak
	rm -f $(EXEC) $(OBJS)

.PHONY: clean










