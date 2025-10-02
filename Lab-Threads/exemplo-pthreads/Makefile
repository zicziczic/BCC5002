all:	compile

compile:	exemplo-thread.c exemplo-thread-pthread-self.c
	gcc -lpthread exemplo-thread.c -o exemplo-thread.exe
	gcc -lpthread exemplo-thread-pthread-self.c -o exemplo-thread-pthread-self.exe

clean:
	rm *.exe

