// 头文件调用
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 结构体

typedef struct {
    int id;
    char name[20], pwd[20], phone[12]; // 名称 密码 电话号码 
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
bool login = false; // 是否登录

void printLine() {
    printf("==========================================================\n");
    
}


// 报错格式
void error() {
    printf("请检查输入是否正确!\n");
    system("pause");
}

// 页面头格式
void head(char * str) {
    system("cls");
    printf("您现在处于 %s 界面!\n", str);
    printLine();
    return;
}


// 用户注册
void userRegister() {
    char input[50];
    int len; // 输入值长度
    int flag = 0; // 注册进度

    /*输入部分开头*/
    while (flag == 0) {
        head("注册");
        printf("请输入您的用户名(长度1 ~ 19, 不含空格):");
        scanf("%s", input);
        len = strlen(input);
        if (len > 20) {
            error();
            continue;
        }
        strcpy(users[userCnt].name, input);
        flag++;
        break;
    }
    while (flag == 1) {
        head("注册");
        printf("请输入您的密码(长度1 ~ 19), 不含空格:");
        scanf("%s", input);
        len = strlen(input);
        if (len > 20) {
            error();
            continue;
        }
        strcpy(users[userCnt].pwd, input);
        flag++;
        break;
    }
    while (flag == 2) {
        head("注册");
        printf("请输入您的电话号码(长度11):");
        scanf("%s", input);
        len = strlen(input);
        if (len != 11) {
            error();
            continue;
        }
        strcpy(users[userCnt].phone, input);
        flag++;
        break;
    }
    // 以下为非输入数据初始化
    {
        users[userCnt].credit = 0;
        users[userCnt].id = userNextId;
        users[userCnt].money = 0;
    }
    // 以下为全局变量自增
    {
        userNextId++;
        userCnt++;
    }
    /*输入部分结尾*/
    
}

// 用户登录
int userLogin() {
    char namex[20], pwdx[20];
    int len; // 输入值长度
    int flag = 0; // 登录进度

    /*输入部分开头*/
    while (flag == 0) {
        head("登录");
        printf("请输入您的用户名:");
        scanf("%s", namex);
        flag++;
        break;
    }
    while (flag == 1) {
        head("登录");
        printf("请输入您的密码:");
        scanf("%s", pwdx);
        flag++;
        break;
    }
    
    //验证是否存在
    bool exist = false;
    int p;
    for (int i = 0; i < userCnt; i++) {
        if (strcmp(users[i].name, namex) == 0) {
            if (strcmp(users[i].pwd, pwdx) == 0) {
                p = i;
                exist = true;
                break;
            }
        }
    }
    if (exist) {
        currentUser = users[p];
        login = true;
        printLine();
        printf("您已成功登录!\n");
        system("pause");
    }
    else {
        printLine();
        printf("用户名或密码错误，请重试!");
        system("pause");
    }
}

//登录注册选择界面
void start() {
    int input;
    system("cls");
    printf("请登录或注册!\n");
    printLine();
    printf("我要登录:(1)\n");
    printf("我要注册:(2)\n");
    printLine();
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        if (userCnt == 0) {
            printLine();
            printf("系统中还没有用户！\n");
            system("pause");
            break;
        }
        userLogin();
        break;

    case 2:
        userRegister();
        break;
    
    default:
        error();
        break;
    }
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
    while (1) {
        head("欢迎");
        printf("欢迎来到本系统!\n退出:(-1)\n前进:(1)\n");
        printLine();
        int choice;
        scanf("%d", &choice);
        if (choice == -1) {
            break;
        }
        else if (choice == 1) {
            if (!login) {
                start();
            }
            else {
                system("cls");
                printf("您现在处于 %s 的主页!\n", currentUser.name);
                printLine();
                system("pause");
                /*剩下代码直接塞进来*/
            }
        }
        else {
            error();
        }
    }
    return 0;
}

