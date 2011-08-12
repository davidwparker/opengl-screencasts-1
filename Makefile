# Target to build
#TARGET = 001 002 003 004
TARGET = 004
#EXECS = ./executables/001 ./executables/002 ./executables/003 ./executables/004
EXECS = ./executables/004

# Libraries - LINUX
#LIBS=-lglut -lGLU
# Libraries - OSX
LIBS=-framework OpenGL -framework GLUT

all: $(TARGET)

# Generic compile rules
.c.o: 
	gcc -c -O -Wall $<

# Generic compile and link
%: %.c screencasts.a
	gcc -Wall -O3 -o ./executables/$@ $^ $(LIBS)

clean:
	rm -f $(EXECS) *.o *.a

screencasts.a:print.o
	ar -rcs screencasts.a $^