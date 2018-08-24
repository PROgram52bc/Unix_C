// This is a simplified version of cat, with nicer output for multiple arguments
#include <stdio.h>
#include <fcntl.h> // open(), creat()
#include <unistd.h> // read(), write(), close(), unlink()

int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("Usage: %s [filename1] [filename2]\n", argv[0]);
		return 1;
	}
	int i, fd, count;
	char buf[BUFSIZ+1];
	for (i=1; i<argc; i++)
	{
		buf[BUFSIZ] = '\0';
		if ((fd = open(argv[i], 0)) == -1)
		{
			printf("failed to read %s\n", argv[i]);
			continue;
		}
		printf("File %d, %s: \n", i, argv[i]);
		while ((count = read(fd, buf, BUFSIZ)) > 0) // sth read
		{
			write(1, buf, count);
		}
		printf("\n");
	}
	return 0;
}
