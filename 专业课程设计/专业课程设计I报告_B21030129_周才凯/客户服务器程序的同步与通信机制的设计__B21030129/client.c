#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include <microhttpd.h>

#define PORT 8888
#define QUEUE_NAME "/stock_queue"
#define RESPONSE_QUEUE_NAME "/stock_response_queue"
#define MAX_SIZE 1024

// �����Ʊ��Ϣ�ṹ��
struct StockMessage {
    long type; // ��Ϣ����
    char stock_code[10]; // ��Ʊ����
    int quantity; // ��Ʊ����
};

// �����Ʊ��Ӧ�ṹ��
struct StockResponse {
    long type; // ��Ӧ����
    char response[MAX_SIZE]; // ��Ӧ����
};

// ������Ϣ����Ϣ���еĺ���
void sendMessage(long type, const char* stockCode, int quantity, char* result) {
    mqd_t mq, mq_response; // ��Ϣ���е�������
    struct StockMessage msg; // Ҫ���͵���Ϣ
    struct StockResponse res; // ���ڽ�����Ӧ����Ϣ

    // ����Ϣ����
    mq = mq_open(QUEUE_NAME, O_WRONLY);
    if (mq == -1) {
        perror("Client: mq_open (stock_queue)");
        strcpy(result, "Error opening stock queue");
        return;
    }

    // ������Ϣ����
    msg.type = type;
    strncpy(msg.stock_code, stockCode, sizeof(msg.stock_code) - 1);
    msg.stock_code[sizeof(msg.stock_code) - 1] = '\0';
    msg.quantity = quantity;

    // ������Ϣ������
    if (mq_send(mq, (char*)&msg, sizeof(msg), 0) == -1) {
        perror("Client: mq_send");
        strcpy(result, "Error sending message");
        return;
    }

    // �ر���Ϣ����
    mq_close(mq);

    // ����Ӧ��Ϣ����
    mq_response = mq_open(RESPONSE_QUEUE_NAME, O_RDONLY);
    if (mq_response == -1) {
        perror("Client: mq_open (stock_response_queue)");
        strcpy(result, "Error opening response queue");
        return;
    }

    // �Ӷ����н�����Ӧ
    if (mq_receive(mq_response, (char*)&res, sizeof(res), NULL) == -1) {
        perror("Client: mq_receive");
        strcpy(result, "Error receiving response");
        return;
    }

    // �ر���Ӧ��Ϣ����
    mq_close(mq_response);

    // ����Ӧ���ݸ��Ƶ�����ַ���
    strcpy(result, res.response);
}

// ����HTTP���ӵĻص�����
int answer_to_connection(void* cls, struct MHD_Connection* connection,
    const char* url, const char* method, const char* version,
    const char* upload_data, size_t* upload_data_size, void** con_cls) {
    const char* page = "<html><body>Request not supported</body></html>"; // Ĭ��ҳ��
    struct MHD_Response* response; // HTTP��Ӧ����
    int ret; // ��������ֵ

    char result[MAX_SIZE] = { 0 }; // ���ڴ洢��Ӧ����Ļ�����

    // ������󷽷�����GET���򷵻ش���
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    // ������ͬ��URL·��
    if (strncmp(url, "/query", 6) == 0) {
        const char* stockCode = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
        if (stockCode) {
            sendMessage(1, stockCode, 0, result); // ���Ͳ�ѯ����
        }
    }
    else if (strncmp(url, "/trade", 6) == 0) {
        const char* stockCode = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
        const char* quantityStr = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");
        if (stockCode && quantityStr) {
            int quantity = atoi(quantityStr);
            sendMessage(2, stockCode, quantity, result); // ���ͽ�������
        }
    }

    // ������Ӧ����
    response = MHD_create_response_from_buffer(strlen(result), (void*)result, MHD_RESPMEM_PERSISTENT);
    // ����HTTP��Ӧ
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    // ������Ӧ����
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon* daemon; // HTTP�������ػ�����

    // ����HTTP�������ػ�����
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
        &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    // ��ӡ������������Ϣ
    printf("Server running on port %d\n", PORT);

    // �ȴ��û����룬��ֹ���������˳�
    getchar();

    // ֹͣHTTP�������ػ�����
    MHD_stop_daemon(daemon);
    return 0;
}