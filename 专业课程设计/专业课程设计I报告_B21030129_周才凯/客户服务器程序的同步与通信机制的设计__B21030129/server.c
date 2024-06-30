//server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>

// 定义消息队列名称
#define QUEUE_NAME "/stock_queue"
#define RESPONSE_QUEUE_NAME "/stock_response_queue"
#define MAX_SIZE 1024
#define STOCK_QUERY 1
#define STOCK_TRADE 2

// 定义股票消息结构体
struct StockMessage {
    long type; // 消息类型，用于区分查询和交易
    char stock_code[10]; // 股票代码
    int quantity; // 交易数量
};

// 定义股票响应结构体
struct StockResponse {
    long type; // 响应类型，与消息类型对应
    char response[MAX_SIZE]; // 响应内容
};

// 处理股票查询请求的函数
void handle_query(struct StockMessage* msg, struct StockResponse* res) {
    // 假设股票价格为100美元，实际应用中应从数据库或API获取
    sprintf(res->response, "Stock %s price is $100", msg->stock_code);
}

// 处理股票交易请求的函数
void handle_trade(struct StockMessage* msg, struct StockResponse* res) {
    // 假设交易成功，实际应用中应进行交易逻辑处理
    sprintf(res->response, "Traded %d shares of %s", msg->quantity, msg->stock_code);
}

int main() {
    mqd_t mq, mq_response; // 消息队列和响应队列的句柄
    struct mq_attr attr; // 消息队列属性
    struct StockMessage msg; // 用于接收消息的结构体
    struct StockResponse res; // 用于发送响应的结构体

    // 初始化消息队列属性
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // 最大消息数
    attr.mq_msgsize = sizeof(struct StockMessage); // 每个消息的最大字节数
    attr.mq_curmsgs = 0; // 当前消息数

    // 打开或创建消息队列
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    if (mq == -1) {
        perror("Server: mq_open (stock_queue)"); // 打开消息队列失败
        exit(1);
    }

    // 打开或创建响应队列
    mq_response = mq_open(RESPONSE_QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq_response == -1) {
        perror("Server: mq_open (stock_response_queue)"); // 打开响应队列失败
        exit(1);
    }

    // 服务器主循环，处理消息队列中的消息
    while (1) {
        // 从消息队列中接收消息
        if (mq_receive(mq, (char*)&msg, sizeof(msg), NULL) == -1) {
            perror("Server: mq_receive"); // 接收消息失败
            continue;
        }

        // 根据消息类型处理请求
        res.type = msg.type;
        if (msg.type == STOCK_QUERY) {
            handle_query(&msg, &res); // 处理查询请求
        } else if (msg.type == STOCK_TRADE) {
            handle_trade(&msg, &res); // 处理交易请求
        }

        // 将响应发送到响应队列
        if (mq_send(mq_response, (char*)&res, sizeof(res), 0) == -1) {
            perror("Server: mq_send"); // 发送响应失败
        }
    }

    // 关闭消息队列和响应队列
    mq_close(mq);
    mq_close(mq_response);

    // 删除消息队列和响应队列
    mq_unlink(QUEUE_NAME);
    mq_unlink(RESPONSE_QUEUE_NAME);

    return 0; // 程序正常退出
}