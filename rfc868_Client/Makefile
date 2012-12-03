CC = /usr/bin/g++
CFLAGS = -Wall
OBJ = tcp_client.o udp_client.o client_.o main.o

client: $(OBJ)
		$(CC) $(CFLAGS) -o client $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
