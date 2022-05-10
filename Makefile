DIROBJ := bin/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/
DIRLOG := log/

CFLAGS := -c -Wall -ansi
LDLIBS := -I$(DIRHEA) -pthread -std=c++17
CC := g++

all : dirs main


dirs:
	mkdir -p $(DIROBJ) $(DIREXE) $(DIRLOG)

main:$(DIROBJ)main.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

$(DIROBJ)%.o: $(DIRSRC)%.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

test:
	rm -rf $(DIRLOG)
	mkdir -p $(DIRLOG)
	./$(DIREXE)main

clean :
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRLOG)