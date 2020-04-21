//
// @author m9rco
// @date 2020/4/21
//

#ifndef ALGORITHM_IOBLOCK_H
#define ALGORITHM_IOBLOCK_H

#include <algorithm>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

class IOBlock {
protected:
    int BufSize;

public:
    explicit IOBlock(int bufferSize) {
        BufSize = bufferSize;
    }

    void sendFile(const char *filename, int socket) {
        int fd, nRead, nWrite, i;
        char buf[BufSize];

        /* 打开文件 */
        fd = open(filename, O_RDONLY);
        if (fd < 0) {
            perror("打开文件失败");
        }

        /* 一部分一部分地读取并传输文件 */
        while (true) {
            /* 从硬盘读取一部分文件内容 */
            nRead = read(fd, buf, BufSize);
            if (nRead == 0) {
                /* 全部完成, 关闭文件, 关闭socket. */
                close(fd);
                close(socket);
                break;
            }

            /* 传输部分文件内容 */
            for (i = 0; i < nRead; i += nWrite) {
                /* 写入操作不一定能一次性完成,
                 * 所以我们要一点一点写入, 直到所有内容都写完
                 */
                nWrite = write(socket, buf + i, nRead - i);
                if (nWrite < 0) {
                    perror("写入失败");
                }
            }
        }
    }


    int terminal() {
        int n;
        char buf[BufSize];

        // read函数返回读取的字节数，此值用作要写的字节数。当达到输入文件的尾端时，read返回0，程序停止执行。
        while ((n = read(STDIN_FILENO, buf, BufSize)) > 0) {
            if (write(STDOUT_FILENO, buf, n) != n) {
                perror("write error :");
            }
        }

        if (n < 0) {
            perror("read error :");
        }

        return 0;
    }
};


#endif //ALGORITHM_IOBLOCK_H
