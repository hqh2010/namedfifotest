#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    const char *fifoName = "/tmp/repohelper_fifo";
    // 以只读阻塞方式打开管道文件
    int pipeFd = open(fifoName, O_RDONLY);
    printf("process %d open fifo O_WRONLY ret:%d\n", getpid(), pipeFd);
    if (pipeFd != -1)
    {
        char buf[128];
        memset(buf, '\0', sizeof(buf));
        while (1)
        {
            int ret = read(pipeFd, buf, sizeof(buf));
            // error or end of file
            if (ret <= 0)
            {
                printf("read end or error!\n");
                break;
            }
            printf("%s\n", buf);
            if (strncmp(buf, "quit", 4) == 0)
            {
                break;
            }
        }
        close(pipeFd);
    }
    else
    {
        printf("process %d open %s err:%d\n", getpid(), fifoName, pipeFd);
    }
    return 0;
}