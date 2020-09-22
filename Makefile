all: qttestdriver
  
qttestdriver: qttest.cpp qttest.h qt.cpp
	g++ -std=c++11 -o qtdriver qttest.cpp qt.cpp

clean:
	rm -f qttestdriver
