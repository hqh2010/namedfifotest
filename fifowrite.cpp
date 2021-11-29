#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    const char *fifoName = "/tmp/repohelper_fifo";
    if (access(fifoName, F_OK) == -1)
    {
        // 管道文件不存在 创建命名管道
        int ret = mkfifo(fifoName, S_IFIFO | 0666);
        if (ret != 0)
        {
            fprintf(stdout, "could not create fifo %s\n", fifoName);
            return -1;
        }
    }
    // 以只写阻塞方式打开FIFO文件, 非阻塞方式O_NONBLOCK必须先打开fifo读,否则报错
    // int pipeFd = open(fifoName, O_WRONLY | O_NONBLOCK);
    int pipeFd = open(fifoName, O_WRONLY);
    printf("process %d open fifo O_WRONLY ret:%d\n", getpid(), pipeFd);
    if (pipeFd != -1)
    {
        char buf[128];
        memset(buf, '\0', sizeof(buf));
        while (1)
        {
            scanf("%s", buf);
            int ret = write(pipeFd, buf, strlen(buf) + 1);
            if (ret < 0)
            {
                printf("write fifo error\n");
                break;
            }
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
    printf("process %d write finished\n", getpid());
    return 0;
}