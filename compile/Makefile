CC = gcc

TARGET = main
OBJECTS = init.o grade.o
FLAG = -g

$(TARGET) : $(TARGET).o $(OBJECTS) remove.o
	$(CC) -o $(TARGET) $(TARGET).o $(OBJECTS)
	$(CC) -o remove remove.c

$(TARGET).o : $(TARGET).c
	$(CC) -c $(TARGET).c

init.o : init.c
	$(CC) -c $^

grade.o : grade.c
	$(CC) -c $^

remove.o : remove.c
	$(CC) -c $^

clean :
	rm $(TARGET) $(TARGET).o
	rm $(OBJECTS)
	rm remove remove.o

rm :
	./remove

# debug : $(OBJECTS)
# 	$(CC) -o $(TARGET) $(OBJECTS) $(FLAG)
# 	lldb ./$(TARGET)

# dlean :
# 	rm $(TARGET)
# 	rm -rf $(TARGET).dSYM