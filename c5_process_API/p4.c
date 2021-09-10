#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int rc = fork();

    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child: redirect standard output to a file
        close(STDOUT_FILENO);

        open("./p4.output", 0_CREAT|0_WRONLY|0_TURNC, S_IRWXU);

        // now exec "wc"...
        char* myargs[3];
        myargs[0] = strdup("wc"); // program: "wc" (word count)
        myargs[1] = strdup("p3.c") // argument: file to count
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); // run words count

        printf("this shouldn't print out");
    } else { // parent goes down this path (main)
        int wc = wait(NULL);
    }

    return 0;
}

