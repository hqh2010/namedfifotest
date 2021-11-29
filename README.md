# 说明

This is a demo for named fifo.

命名管道以非阻塞方式写入时，必须先运行read管道，否则write端报错

# 使用方式

`g++ fifowrite.cpp -g -o `fifowrite

`g++ fiforead.cpp -g -o `fiforead

# 运行

进入终端

./fifowrite

再开一个终端

./fiforead

在fifowrite终端输入

123

456

789

quit

可以在fiforead终端看到fifowrite终端写入的值

# 参考文档

命名管道阻塞与非阻塞说明

[https://blog.csdn.net/zuozi123456/article/details/51440144]()
