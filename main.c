// 头文件调用
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 结构体

typedef struct {
    int id;
    char name[20], pwd[20], phone[12]; // 名称 密码 电话号码
    int type; // 类型   
    int credit; // 积分
    double money; // 余额
} User;

typedef struct {
    int id; // 任务id
    int pubId; // 发布者
    int runId; // 接单者
    char title[50], content[100]; // 标题 内容
    double reward; // 酬金
    int status; // 状态（未接单 已接单）
} Task;

// 全局变量
User users[100], currentUser;
Task tasks[100];
int userCnt = 0; // 统计用户数量
int tackCnt = 0; // 统计任务数量
int userNextId = 1; // 用来分配用户Id
int taskNextId = 1; // 用来分配任务Id

void printLine() {
    printf("==========================================================");
}


// 用户注册与登录
void userRegister() {
    printLine();
}

int userLogin() {
    printLine();
}

// 发布任务
void publishTask() {
    printLine();
}

// 浏览与接单
void browseTask() {
    printLine();
}

// 查看与处理
void checkTask() {
    printLine();
}

// 充值
void Recharge() {
    printLine();
}

// 主函数

int main() {

}

