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

all_seq: exe_seq

exe_seq:
	$(CC) $(FLAGS) haar_seq.c -c -o exe_seq.o
	$(CC) $(FLAGS) exe_seq.o -o exe_seq

run_seq: clean_seq all_seq
	command time -v ./exe_seq

clean_seq:
	$(RM) $(EXEC).o $(EXEC)
