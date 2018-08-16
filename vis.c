#include <stdio.h>
#include <ctype.h>

int main() {
	int c;
	while ((c = getchar()) != EOF)
	{
		if (isalpha(c) || isdigit(c))
			putchar(c);
		else 
			switch(c)
			{
				case '\n':
					printf("\\%c\n", 'n');
					break;
				case '\t':
					printf("\\%c", 't');
					break;
				case '\b':
					printf("\\%c", 'b');
					break;
				case '\\':
					printf("\\%c", '\\');
					break;
				default:
					printf("\\%03o", c);
			}
	}
	return 0;
}
