CXX?= /usr/bin/g++
CFLAGS = -Wall
OBJ = tcp_client.o udp_client.o client_.o main.o

client: $(OBJ)
		$(CXX) $(CFLAGS) -o client $(OBJ)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<
