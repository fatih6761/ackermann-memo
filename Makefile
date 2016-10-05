CSRC=src/main.c
CPPSRC=src/main.cpp
PREFLAGS=-Wall -O3
CPPPOSTFLAGS=-std=c++14 -march=native

all:	asm

	g++ $(PREFLAGS) -o bin/ack1 $(CPPSRC) $(CPPPOSTFLAGS)
	g++ $(PREFLAGS) -o bin/ack2 -DUSE_BRANCH_OPTIM $(CPPSRC) $(CPPPOSTFLAGS)
	g++ $(PREFLAGS) -o bin/ack3 -DUSE_MAP_INSTEAD_OF_VECTOR $(CPPSRC) $(CPPPOSTFLAGS)
	g++ $(PREFLAGS) -o bin/ack4 -DUSE_MAP_INSTEAD_OF_VECTOR -DUSE_BRANCH_OPTIM $(CPPSRC) $(CPPPOSTFLAGS)

	gcc -Wall -O3 -o bin/ack5 $(CSRC) -march=native

asm:
	g++ $(PREFLAGS) -o bin/asm/ack1.asm -S -fverbose-asm $(CPPSRC) $(CPPPOSTFLAGS)
	gcc $(PREFLAGS) -o bin/asm/ack5.asm -S -fverbose-asm $(CSRC) -march=native

clean:
	rm bin/ack*