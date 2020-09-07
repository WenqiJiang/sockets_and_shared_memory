# gcc for C compilation and g++ for C++ compilation
# CC = gcc 
CXX = g++

# Additional include directories
INCDIR :=
# INCDIR += -I../inc

# Compilation options:

# -g for debugging info and -Wall enables all warnings
# C_FLAGS = -g -Wall $(INCLUDES) 
CXX_FLAGS = -g -Wall $(INCLUDES)

# Linking options:
# linking flags: -g for debugging info
LD_FLAGS := 
LD_FLAGS += -g

# List the libraries we need to link with in LDLIBS 
# For example, use "-lm" for the math library
LD_LIBS :=
# LD_LIBS += -lm

# The 1st target gets built when you type "make".
# It’s usually your executable. ("main" in this case.)

# # Note that we did not specify the linking rule.

# Instead, we rely on one of make’s implicit rules:

# # $(CC) $(LDFLAGS) <all-dependent-.o-files> $(LDLIBS) # # Also note that make assumes that main depends on main.o, # so we can omit it if we want to.

shm: shm.o
# main: #main.o myadd.o

shm.o: shm.cpp

# main.o: main.c myadd.h
# myadd.o: myadd.c myadd.h

.PHONY: clean 
	clean:
	rm -f *.o a.out # core main