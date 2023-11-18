#include <stdio.h>

void printFrames(int frames[], int frameSize) {
    for (int i = 0; i < frameSize; ++i) {
        if (frames[i] == -1) {
            printf("X ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

void FCFS(int pages[], int frameSize, int n) {
    int frames[frameSize];
    int pageFaults = 0;

    for (int i = 0; i < frameSize; ++i) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; ++i) {
        int pageExists = 0;

        for (int j = 0; j < frameSize; ++j) {
            if (frames[j] == pages[i]) {
                pageExists = 1;
                break;
            }
        }

        if (pageExists == 0) {
            frames[pageFaults % frameSize] = pages[i];
            ++pageFaults;
        }

        printf("Frames (FCFS): ");
        printFrames(frames, frameSize);
    }

    printf("Number of page faults using FCFS: %d\n\n", pageFaults);
}

void LRU(int pages[], int frameSize, int n) {
    int frames[frameSize];
    int pageFaults = 0;
    int recent[frameSize];

    for (int i = 0; i < frameSize; ++i) {
        frames[i] = -1;
        recent[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        int pageExists = 0;

        for (int j = 0; j < frameSize; ++j) {
            if (frames[j] == pages[i]) {
                pageExists = 1;
                recent[j] = i;
                break;
            }
        }

        if (pageExists == 0) {
            int leastRecentIndex = 0;

            for (int j = 1; j < frameSize; j++) {
                if (recent[j] < recent[leastRecentIndex]) {
                    leastRecentIndex = j;
                }
            }

            frames[leastRecentIndex] = pages[i];
            recent[leastRecentIndex] = i;
            ++pageFaults;
        }

        printf("Frames (LRU): ");
        printFrames(frames, frameSize);
    }

    printf("Number of page faults using LRU: %d\n\n", pageFaults);
}

void Optimal(int pages[], int frameSize, int n) {
    int frames[frameSize];
    int pageFaults = 0;

    for (int i = 0; i < frameSize; ++i) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; ++i) {
        int pageExists = 0;

        for (int j = 0; j < frameSize; ++j) {
            if (frames[j] == pages[i]) {
                pageExists = 1;
                break;
            }
        }

        if (pageExists == 0) {
            int maxDistance = -1;
            int replaceIndex = -1;

            for (int j = 0; j < frameSize; ++j) {
                int futureIndex = n; // Initialize to a value greater than the reference string size.

                for (int k = i + 1; k < n; ++k) {
                    if (frames[j] == pages[k]) {
                        futureIndex = k;
                        break;
                    }
                }

                if (futureIndex == n) {
                    replaceIndex = j;
                    break;
                } else {
                    if (futureIndex > maxDistance) {
                        maxDistance = futureIndex;
                        replaceIndex = j;
                    }
                }
            }

            frames[replaceIndex] = pages[i];
            ++pageFaults;
        }

        printf("Frames (Optimal): ");
        printFrames(frames, frameSize);
    }

    printf("Number of page faults using Optimal: %d\n\n", pageFaults);
}

int main() {
    int pages[20];
    int n;

    printf("Enter the size of the reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (int i = 0; i < n; ++i) {
        printf("string:");
        scanf("%d", &pages[i]);
    }

    int frameSize = 3;
    FCFS(pages, frameSize, n);
    LRU(pages, frameSize, n);
    Optimal(pages, frameSize, n);

    return 0;
}

/*
/tmp/HBocYIHcF7.o
entre the size of the string :7
enter the string:
strin=g:1
strin=g:3
strin=g:0
strin=g:3
strin=g:5
strin=g:6
strin=g:3
Frame:	1	X	X	
Frame:	1	3	X	
Frame:	1	3	0	
Frame:	1	3	0	
Frame:	5	3	0	
Frame:	5	6	0	
Frame:	5	6	3	

pagefault:6

LRU frames:
Frame:	1	X	X	

LRU frames:
Frame:	3	X	X	

LRU frames:
Frame:	3	0	X	

LRU frames:
Frame:	3	0	X	

LRU frames:
Frame:	3	0	5	

LRU frames:
Frame:	3	6	5	

LRU frames:
Frame:	3	6	5	

pagefault: 5
Optimal:Frame:	1	X	X	
Optimal:Frame:	3	X	X	
Optimal:Frame:	3	0	X	
Optimal:Frame:	3	0	X	
Optimal:Frame:	3	5	X	
Optimal:Frame:	3	6	X	
Optimal:Frame:	3	6	X	

pagefault: 5
*/
