CC=gcc
CFLAGS=-Wall
LDFLAGS=-lpthread
EXE_PHASE1=detect
OBJ_PHASE1=deadLockFunc.o task12Func.o challengeTask.o

all: $(EXE_PHASE1)


$(EXE_PHASE1): detect.c $(OBJ_PHASE1)
	$(CC) $(CFLAGS) -o $(EXE_PHASE1) $< $(OBJ_PHASE1)

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o $(EXE_PHASE1)

format:
	clang-format -i *.c *.h

