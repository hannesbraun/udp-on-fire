all: receiver sender

receiver: receiver.c
	gcc -Wall -Wextra -Wpedantic -O3 -o receiver receiver.c

sender: sender.c
	gcc -Wall -Wextra -Wpedantic -O3 -o sender sender.c

clean:
	rm receiver sender

.PHONY: all clean
