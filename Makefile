CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic 

PROJ_NAME := ascii_im

all: uninstall $(PROJ_NAME)

$(PROJ_NAME):
	$(CC) $(CFLAGS) ./src/*.c -include ./inc/*.h -c
	mkdir -p obj
	mv ./*.o ./obj/
	$(CC) $(CFAGS) ./obj/* -o $(PROJ_NAME)
	rm -rf ./obj/

clean:
	rm -rf ./obj
	rm -rf *.o

uninstall: clean
	rm -rf $(PROJ_NAME)

reinstall:
	make uninstall
	make


	

