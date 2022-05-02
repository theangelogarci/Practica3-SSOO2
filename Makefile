DIROBJ := bin/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/

CFLAGS := -c -Wall -ansi
LDLIBS := -I$(DIRHEA) -pthread -std=c++11
CC := g++

all : dirs ssooiigle 

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

ssooiigle: $(DIROBJ)ssooiigle.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

palabra: $(DIROBJ)palabra.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

$(DIROBJ)%.o: $(DIRSRC)%.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

test:
	./$(DIREXE)ssooiigle "prueba.txt" david 3

test2:
	./$(DIREXE)ssooiigle "21-LEYES-DEL-LIDERAZGO.txt" del 1000

test3:
	./$(DIREXE)ssooiigle "17-LEYES-DEL-TRABAJO-EN-EQUIPO.txt" ley 15

clean :
	rm -rf *~ core $(DIROBJ) $(DIREXE)
