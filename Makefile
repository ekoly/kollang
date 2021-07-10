CC = g++
CFLAGS = -g -ansi -Wall

TARGET = kol

all: $(TARGET)

$(TARGET): main.o KolMain.o KolParse.o KolObj.o KolScopes.o KolOverhead.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o KolMain.o KolParse.o KolObj.o KolScopes.o KolOverhead.o

main.o: main.cpp KolMain.h KolParse.h KolObj.h KolScopes.h KolOverhead.h
	$(CC) $(CFLAGS) -c main.cpp

KolMain.o: KolMain.cpp KolMain.h KolObj.h KolScopes.h KolOverhead.h
	$(CC) $(CFLAGS) -c KolMain.cpp

KolParse.o: KolParse.cpp KolObj.h KolScopes.h KolOverhead.h KolParse.h
	$(CC) $(CFLAGS) -c KolParse.cpp

KolObj.o: KolObj.cpp KolMain.h KolObj.h KolScopes.h
	$(CC) $(CFLAGS) -c KolObj.cpp

KolScopes.o: KolScopes.cpp KolMain.h KolScopes.h
	$(CC) $(CFLAGS) -c KolScopes.cpp

KolScopes.o: KolScopes.cpp KolMain.h KolScopes.h
	$(CC) $(CFLAGS) -c KolScopes.cpp

KolOverhead.o: KolOverhead.cpp KolMain.h KolObj.h KolScopes.h KolOverhead.h
	$(CC) $(CFLAGS) -c KolOverhead.cpp

clean:
	$(RM) $(TARGET)
