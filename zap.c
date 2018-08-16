#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
char *command = "ps -ax"; // please make sure the 1st field is pid

int main(int argc, char* argv[])
{
	FILE *fin; 
	fin = popen(command, "r"); // set as the output of the ps command
	char buf[BUFSIZ]; // buffer to store current line of output
	int pid; // to store the pid of the program being iterated at
	int mypid = getpid(); // pid of this process
	int i; // iterating variable

	fgets(buf, sizeof buf, fin); // eliminate the first line
	fprintf(stderr, "%s", buf);
	while (fgets(buf, sizeof buf, fin) != NULL) // get a line
	{
		sscanf(buf, "%d", &pid); // get pid
		int match=0; // does not match by default
		if (argc == 1) // if no arguments, set as match
			match=1;
		else
		{
			for (i=1; i<argc; ++i)
				if (strstr(buf,argv[i]) != NULL && 
						pid != mypid)
					/* if any of the arguments matches the line, 
					 * and the line is not the current process, 
					 * set as match. */
				{
					match=1;
					break;
				}
		}
		if (match)
		{
			buf[strlen(buf)-1] = '\0'; // eliminate the final \n
			fprintf(stderr, "%s? (y/n/q)", buf); 
			char answer = fgetc(stdin);
			// clear keyboard buffer
			char ch; while ((ch = getc(stdin)) != '\n' && ch != EOF); 
			if (answer == 'y')
			{
				kill(pid, SIGKILL);
				fprintf(stderr, "%d killed\n", pid);
			}
			else if (answer == 'q')
				break;
			else
				continue;
		}
	}
	return 0;
}

