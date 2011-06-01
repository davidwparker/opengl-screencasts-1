GCC_OPTIONS=-Wall -pedantic
GL_OPTIONS=-framework OpenGL -framework GLUT 
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)

.c: 
	gcc $@.c $(OPTIONS) -o ./executables/$@