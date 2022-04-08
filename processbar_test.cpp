

#include <stdio.h>
#include <unistd.h>
#include<string.h>
#include <iostream>

using namespace std;

void showProgressBar()
{
    // https://www.cnblogs.com/3me-linux/p/4270295.html
    // 隐藏光标
    printf("\033[?25l");
    int i = 0;
    char bar[102] = {'\0'};
    const char *lab = "-\\|/";
    while (i <= 100) {
        // 左对齐 右边补空格 \r表示将光标移动到行首
        printf("[%-101s][%d%%][%c]\r", bar, i, lab[i % 4]);
        fflush(stdout);
        sleep(1);
        bar[i++] = '#';
        bar[i] = '\0';
    }
    printf("\n");
}

void getProgress(char *bar, int n)
{
    const char *percentblock = "█";
    int len = strlen(percentblock);
    int pos = 0;
    int i = 0;
    while (i < n) {
        strncpy(bar + pos, percentblock, len);
        i++;
        pos = pos + len;
    }
    // "█" printf 算 3 个字符，终端只算一个占位符，导致显示有问题。
    int j = 1;
    while (j <= 100 - n) {
        bar[pos++] = ' ';
        j++;
    }
}

void showProgressBar1()
{
    // https://www.cnblogs.com/3me-linux/p/4270295.html
    // 隐藏光标
    printf("\033[?25l");
    int i = 1;
    char bar[301] = {'\0'};
    const char *lab = "-\\|/";
    while (i <= 100) {
        getProgress(bar, i);
        // 左对齐 右边补空格 \r表示将光标移动到行首
        printf("[%s][%d%%][%c]\r", bar, i, lab[i % 4]);
        fflush(stdout);
        sleep(1);
        i++;
    }
    printf("\n");
}

std::string getProgress2(int n)
{
    string ret;
    for (int i = 1; i <= n; i++) {
        ret += "█";
    }
    ret += string(100 - n, ' ');
    return ret;
}

void showProgressBar2()
{
    // https://www.cnblogs.com/3me-linux/p/4270295.html
    // 隐藏光标
    printf("\033[?25l");
    int i = 1;
    char bar[301] = {'\0'};
    const char *lab = "-\\|/";
    while (i <= 100) {
        // 左对齐 右边补空格 \r表示将光标移动到行首
        printf("[%s][%d%%][%c]\r", getProgress2(i).c_str(), i, lab[i % 4]);
        fflush(stdout);
        sleep(1);
        i++;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    showProgressBar1();
    return 0;
}