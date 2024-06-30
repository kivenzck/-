#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// 定义服务器端口
const int PORT = 12345;

// 客户端主函数
void client_main() {
    // 创建一个socket文件描述符
    int sock = 0;
    // 定义服务器地址结构体
    struct sockaddr_in serv_addr;
    // 定义用于接收数据的缓冲区
    char buffer[1024] = {0};

    // 1、创建socket，返回文件描述符
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return;
    }

    // 2、设置服务器地址结构体的属性
    serv_addr.sin_family = AF_INET; // 使用IPv4地址
    serv_addr.sin_port = htons(PORT); // 将端口号转换为网络字节序

    // 将服务器地址转换为网络字节序
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return;
    }

    // 3、连接到服务器
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return;
    }

    // 4、数据传输
    // 从标准输入读取用户请求
    std::string request;
    std::cout << "Enter your request (e.g., QUERY:GOOGL or TRADE:GOOGL:10): ";
    std::getline(std::cin, request);

    // 发送请求到服务器
    send(sock, request.c_str(), request.length(), 0);
    // 从服务器接收响应
    int valread = read(sock, buffer, 1024);
    // 输出服务器的响应
    std::cout << "Server response: " << std::string(buffer, valread) << std::endl;

    // 5、关闭socket
    close(sock);
}

// 主函数，调用客户端主函数
int main() {
    client_main();
    return 0;
}