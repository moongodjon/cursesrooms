all:
	cc main.c -lm -lncurses -o coordinate
clean:
	rm coordinate
run:
	cc main.c -lm -lncurses -o coordinate && ./coordinate
	
