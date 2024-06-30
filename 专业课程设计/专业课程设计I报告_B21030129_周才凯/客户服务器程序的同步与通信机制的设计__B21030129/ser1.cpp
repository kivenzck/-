#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// 定义服务器监听的端口号
const int PORT = 12345;

// 处理客户端请求的函数
std::string handle_request(const std::string& request) {
    // 如果请求以"QUERY:"开头
    if (request.find("QUERY:") == 0) {
        // 提取股票代码
        std::string stock_symbol = request.substr(6); // 6 表示从 request 字符串的第7个字符开始提取子串（因为字符串索引从0开始）
        // 返回模拟的股票价格查询响应
        if(stock_symbol=="GOOGL"){
            return "RESPONSE:Price of " + stock_symbol + " is $200";
        }
        return "RESPONSE:Price of " + stock_symbol + " is $100";
    } 
    // 如果请求以"TRADE:"开头
    else if (request.find("TRADE:") == 0) {
        // 查找第一个冒号的位置
        size_t first_colon = request.find(":", 6); // find 函数的第二个参数 6 是一个起始搜索位置。这意味着 find 函数将从 request 字符串的第7个字符开始搜索（因为字符串索引从0开始），直到字符串的末尾
        // 提取股票代码
        std::string stock_symbol = request.substr(6, first_colon - 6);
        // 提取交易数量
        std::string quantity = request.substr(first_colon + 1);
        // 返回模拟的交易响应
        return "RESPONSE:Traded " + quantity + " of " + stock_symbol;
    } 
    // 如果请求不符合预期格式
    else {
        // 返回无效请求的响应
        return "RESPONSE:Invalid request";
    }
}

// 服务器主函数
void server_main() {
    // 创建socket文件描述符
    int server_fd, new_socket;
    // 定义服务器地址结构体
    struct sockaddr_in address;

// struct sockaddr_in {
//     sa_family_t    sin_family; // 地址族，对于 IPv4 应该设置为 AF_INET
//     uint16_t       sin_port;   // 端口号，使用 htons() 函数转换为网络字节序
//     struct in_addr sin_addr;   // IPv4 地址，使用 inet_addr() 或 inet_aton() 函数填充
//     char           sin_zero[8]; // 保留空间，通常填充为 0
// };

    // 设置socket选项
    int opt = 1;
    // 设置地址长度变量
    int addrlen = sizeof(address);
    // 定义用于接收数据的缓冲区
    char buffer[1024] = {0};

    // 1、创建socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2、设置socket选项，允许重用地址和端口
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构体的属性
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // 允许任何IP地址连接
    address.sin_port = htons(PORT); // 将端口号转换为网络字节序

    // 3、绑定socket到指定的地址和端口
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4、开始监听连接
    if (listen(server_fd, 3) < 0) { // 3表示允许的最大连接数
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 打印服务器监听端口信息
    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    // 5、无限循环，等待客户端连接
    while (true) {
        // 接受客户端连接
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // 6、数据传输
        // 从客户端读取数据
        int valread = read(new_socket, buffer, 1024);
        // 将接收到的数据转换为字符串
        std::string request(buffer, valread);
        // 处理请求并获取响应
        std::string response = handle_request(request);
        // 发送响应给客户端
        send(new_socket, response.c_str(), response.length(), 0);
        // 7、关闭与客户端的连接
        close(new_socket);
        // close(server_fd); // 关闭监听socket
    }
}

// 主函数，启动服务器
int main() {
    server_main();
    return 0;
}