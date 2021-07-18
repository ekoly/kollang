CC = g++
CFLAGS = -g -Wall

TARGET = kol

all: $(TARGET)

$(TARGET): main.o KolMain.o KolParse.o KolObj.o KolScopes.o KolOverhead.o KolInt.o KolFloat.o KolString.o KolTuple.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o KolMain.o KolParse.o KolObj.o KolScopes.o KolOverhead.o KolInt.o KolFloat.o KolString.o KolTuple.o

main.o: main.cpp KolMain.h KolParse.h
	$(CC) $(CFLAGS) -c main.cpp

KolMain.o: KolMain.cpp KolMain.h KolObj.h KolScopes.h KolOverhead.h KolInt.h KolFloat.h KolString.h KolTuple.h
	$(CC) $(CFLAGS) -c KolMain.cpp

KolParse.o: KolParse.cpp KolMain.h KolObj.h KolScopes.h KolOverhead.h KolInt.h KolFloat.h KolString.h KolParse.h KolTuple.h
	$(CC) $(CFLAGS) -c KolParse.cpp

KolObj.o: KolObj.cpp KolMain.h KolObj.h KolScopes.h
	$(CC) $(CFLAGS) -c KolObj.cpp

KolScopes.o: KolScopes.cpp KolMain.h KolScopes.h
	$(CC) $(CFLAGS) -c KolScopes.cpp

KolOverhead.o: KolOverhead.cpp KolMain.h KolObj.h KolTuple.h KolScopes.h KolOverhead.h
	$(CC) $(CFLAGS) -c KolOverhead.cpp

KolInt.o: KolInt.cpp KolMain.h KolInt.h KolFloat.h KolString.h KolObj.h KolScopes.h
	$(CC) $(CFLAGS) -c KolInt.cpp

KolFloat.o: KolFloat.cpp KolMain.h KolFloat.h KolInt.h KolString.h KolObj.h KolScopes.h
	$(CC) $(CFLAGS) -c KolFloat.cpp

KolString.o: KolString.cpp KolMain.h KolString.h KolObj.h KolScopes.h
	$(CC) $(CFLAGS) -c KolString.cpp

KolTuple.o: KolTuple.cpp KolMain.h KolTuple.h KolString.h KolObj.h KolScopes.h
	$(CC) $(CFLAGS) -c KolTuple.cpp

clean:
	$(RM) $(TARGET) *.o
