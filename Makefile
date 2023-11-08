FLAGS=-O2 -fopenmp

CC=gcc

RM=rm -f

EXEC=haar

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

run: clean all
	command time -v ./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
