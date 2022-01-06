CC = g++
ex_name = a.out
libs = -l:libcryptopp.so
files = Main.cpp Encryption.cpp
flags = -DNDEBUG -g3 -O2 -Wall -Wextra
all: compile


compile:
	${CC} ${flags} -o ${ex_name} ${files} ${libs}

no-flags:
	${CC} -o ${ex_name} ${files} ${libs}

clean:
	rm ${ex_name}
