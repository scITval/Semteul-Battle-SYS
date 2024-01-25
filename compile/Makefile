CC = gcc

TARGET = main
OBJECTS = init.o grade.o
FLAG = -g

$(TARGET) : $(TARGET).o $(OBJECTS)
	$(CC) -o $(TARGET) $(TARGET).o $(OBJECTS)
#	./$(TARGET)

$(TARGET).o : $(TARGET).c
	$(CC) -c $(TARGET).c

init.o : init.c
	$(CC) -c $^

grade.o : grade.c
	$(CC) -c $^

clean :
	rm $(TARGET) $(TARGET).o
	rm $(OBJECTS)
	# rm ./code/prog

# debug : $(OBJECTS)
# 	$(CC) -o $(TARGET) $(OBJECTS) $(FLAG)
# 	lldb ./$(TARGET)

# dlean :
# 	rm $(TARGET)
# 	rm -rf $(TARGET).dSYM