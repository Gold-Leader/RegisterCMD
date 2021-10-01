all: Register
CC = g++ -std=c++11
	
Register: driver.o regUtil.o procInputUtil.o getInputUtil.o
	$(CC) -g driver.o regUtil.o procInputUtil.o getInputUtil.o -o Register
driver.o: driver.cpp
	$(CC) -g -c driver.cpp
regUtil.o: regUtil.cpp
	$(CC) -g -c regUtil.cpp
procInputUtil.o: procInputUtil.cpp
	$(CC) -g -c procInputUtil.cpp
getInputUtil.o: getInputUtil.cpp
	$(CC) -g -c getInputUtil.cpp

Register_test: test.o
	$(CC) -g test.o -o Register_test
test.o: test.cpp
	$(CC) -g -c test.cpp