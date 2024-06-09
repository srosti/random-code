# Define the compiler
CC = clang

# Define flags for C++ compilation (modify for C if needed)
CFLAGS = -g -fsanitize=address

# Define the output file name
OUT = use-after-free

# Define all object files (depends on your source files)
OBJS = use-after-free.o

# Main rule - builds the final executable
all: $(OUT)

# Compile each source file into an object file
%.o: %.cpp
	$(CC) $(CFLAGS)-c $< -o $@

# Link object files into the final executable
$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -O1 -fsanitize=address $(OBJS) -o $@

# Define linker flags for ASan (adjust paths based on your system)
LDFLAGS = -L/usr/lib/x86_64-linux-gnu


# Clean rule - removes object files and the final executable
clean:
	rm -f $(OBJS) $(OUT)

test:
	./use-after-free