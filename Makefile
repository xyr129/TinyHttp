all:server client
.PHONY:all
server:server.c comm.c
	gcc -o $@ $^
client:client.c comm.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf server client
	
