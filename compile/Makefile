CC = gcc

TARGET = prog
OBJECTS = main.c
FLAG = -g

$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)
	./$(TARGET)
	rm ./$(TARGET)

# debug : $(OBJECTS)
# 	$(CC) -o $(TARGET) $(OBJECTS) $(FLAG)
# 	lldb ./$(TARGET)

clean :
	rm $(TARGET)

dlean :
	rm $(TARGET)
	rm -rf $(TARGET).dSYM
