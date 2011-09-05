/*  Printing convenience (print.c) */
void printv(va_list args, const char* format);
void print(const char* format, ...);
void printAt(int x, int y, const char* format, ...);
void errCheck(char* where);
