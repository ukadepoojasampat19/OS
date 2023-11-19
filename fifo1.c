#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
// #include <unistd.h>

int main()
{

    int fd;
    char *myfifo = "myfifo";
    mkfifo(myfifo, 0666);

    char arr1[80], arr2[80], buffer[100];

    while (1)
    {
        int i = 0, wordCount = 0, lineCount = 0, charCount = 0;

        fd = open(myfifo, O_WRONLY);
        printf("Enter data : ");
        fgets(arr2, 80, stdin);
        write(fd, arr2, strlen(arr2) + 1);
        close(fd);

        // Open "count.txt" for reading
        FILE *countFileRead = fopen("count.txt", "r");
        if (countFileRead != NULL)
        {
            fread(buffer, sizeof(buffer), 1, countFileRead);
            fclose(countFileRead);

            // Now, buffer contains the contents of "count.txt"
            printf("Contents of count.txt:\n%s\n", buffer);
        }
        else
        {
            perror("Unable to open count.txt for reading");
        }
    }

    return 0;
}
