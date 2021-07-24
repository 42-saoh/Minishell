#include <sys/stat.h>

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int fd;
    // 표준입력은 터미널에 연결되어 있으므로 1을 출력한다.  
    printf("isatty(0) : %d\n", isatty(0));
   
    // 파일은 터미널에 연결되어 있지 않으므로 0을 출력한다.
    fd = open("test100", O_RDWR);
    printf("test100 : %d\n", isatty(fd));
    close(fd);

    fd = open("/dev/ttyS0", O_RDONLY);
    if (fd < -1)
    {
        printf("open error\n");
        exit(0);
    }
    printf("/dev/ttyS0 : %d\n", isatty(fd));

    printf("ttyname(0) : %s\n", ttyname(0));
    printf("ttyname(1) : %s\n", ttyname(1));
    printf("ttyslot() : %d\n", ttyslot());


    close(fd);
    exit(0);
}