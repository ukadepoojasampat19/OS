#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
// #include<unistd.h>


int main() {

    int fd1 ;
    char * myfifo = "myfifo" ;
    mkfifo(myfifo,0666) ;

    char arr1[80] , arr2[80] ,buff[80];

    while(1) {

        int i = 0 , wordCount = 0 , lineCount = 0 , charCount = 0 ;

        fd1 = open(myfifo,O_RDONLY);
        read(fd1,arr1,80);
        printf("User 1: %s \n",arr1);
        close(fd1);

        while(i < strlen(arr1)) {
              if(arr1[i] == ' ')
              {
              wordCount++ ;
              charCount++ ;
              }
              else if(arr1[i] == '\n')
              {
              wordCount++ ;
              lineCount++ ;
              }
              else
              {
              charCount++ ;
              }
              i++;
        }
    
      FILE *countFile = fopen("count.txt", "w");
              if (countFile != NULL) {
                  fprintf(countFile, "Word Count: %d\n", wordCount);
                  fprintf(countFile, "Line Count: %d\n", lineCount);
                  fprintf(countFile, "Character Count: %d\n", charCount);
                  fclose(countFile);
              } else {
                  perror("Unable to open count.txt for writing");
              }
      fd1 = open(myfifo,O_WRONLY) ;

      write(fd1,arr1,strlen(arr1)+1);
      
    }
return 0 ;
}
Os/fifo/fifo2.c at main · sahiltambe18/Os
