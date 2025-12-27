// 头文件调用
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 用户结构体
typedef struct {
    int id;
    char name[20], pwd[20], phone[12]; // 名称 密码 电话号码 
    int credit; // 积分
    double money; // 余额
} User;

// 任务结构体
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
int taskCnt = 0; // 统计任务数量
int userNextId = 1; // 用来分配用户Id
int taskNextId = 1; // 用来分配任务Id
bool login = false; // 是否登录
int adminMod = 0; // 后台

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

//管理员密码
static char adminPwd[10] = "admin";

//控制面板
void adminCommands() {
    while (1) {
        char input[20];
        head("命令");
        printf("/back\n");
        printf("/list\n");
        printf("/listTask\n");
        printLine();
        scanf("%s", input);
        if (strcmp(input, "/back") == 0) return;
        else if (strcmp(input, "/list") == 0) {
            if (userCnt == 0) {
                printf("EMPTY\n");
                system("pause");
                continue;
            }
            for (int i = 0; i < userCnt; i++) {
                printf(
                    "id: %d name: %s pwd: %s phone: %s credit: %d money: $%.2f\n",
                    users[i].id,
                    users[i].name,
                    users[i].pwd,
                    users[i].phone,
                    users[i].credit,
                    users[i].money
                );
            }
            system("pause");
        }
        else if (strcmp(input, "/listTask") == 0) {
            if (taskCnt == 0) {
                printf("EMPTY\n");
                system("pause");
                continue;
            }
            for (int i = 0; i < taskCnt; i++) {
                printf(
                    "id: %d\n发布者: %d 接单者: %d\n标题:\n%s\n内容:\n%s\n酬金: $%.2f 状态: %s\n",
                    tasks[i].id,
                    tasks[i].pubId,
                    tasks[i].runId,
                    tasks[i].title,
                    tasks[i].content,
                    tasks[i].reward,
                    tasks[i].status == 1 ? "已接单" : "未接单"
                );
                printLine();
            }
            system("pause");
        }
        else {
            error();
        }
    }
    
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

        //重复性验证
        bool exist = false;
        for (int i = 0; i < userCnt; i++) {
            if (strcmp(users[i].name, input) == 0) {
                exist = true;
                printf("用户名已经存在，请更换\n");
                system("pause");
            }
        }
        if (exist) {
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
    printf("我要注册:(2)\n返回:(-1)        管理员? (0)\n");
    printLine();
    scanf("%d", &input);
    switch (input)
    {
    case -1:
        break;
    case 0:
        char pwdx[50];
        printf("请输入密码:");
        scanf("%s", &pwdx);
        if (strcmp(pwdx, adminPwd) == 0) {
            adminMod = 1 - adminMod;
        }
        break;
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

// 充值
void Recharge() {
    head("充值");
    printLine();
    
    if (currentUser.id==0) {
        printf("需要您的登录！\n");
        return;
    }

    double amount;
    printf("请输入充值金额：");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("充值金额不能为负！\n");
        return;
    }

    currentUser.money += amount;

    for (int i = 0; i < userCnt; i++) {
        if (users[i].id == currentUser.id) {
            users[i].money = currentUser.money;
            break;
        }
    }

    printf("您已充值成功！\n");
    printf("充值金额：%.2f 元\n", amount);
    printf("当前余额：%.2f 元\n", currentUser.money);
    system("pause");
}

// 发布任务
void publishTask(){
    head("发布任务");
    printLine();
	double reward;
	char currentTitle[50],currentCotent[100];

	printf("请输入报酬：\n");
	scanf("%lf",&reward);


    if (reward >= currentUser.money) {
        printf("没钱啦！\n您当前剩余金额: $%.2f\n", currentUser.money);
        system("pause");
        return;
    }

	while(reward<=0){
		printf("任务报酬须大于0,请重新输入:\n");
		scanf("%lf",&reward);
	}

	tasks[taskCnt].id=taskNextId++;
	tasks[taskCnt].runId=0;
	tasks[taskCnt].pubId=currentUser.id;

	printf("请输入任务标题：\n");
	scanf("%s",currentTitle);
	strcpy(tasks[taskCnt].title,currentTitle);

	printf("请输入任务内容：\n");
	scanf("%s",currentCotent);
	strcpy(tasks[taskCnt].content,currentCotent);

	tasks[taskCnt].reward=reward;
	tasks[taskCnt].status=0;
	taskCnt++;

    for(int j=0;j<userCnt;j++){
        if(users[j].id==currentUser.id){
            users[j].money-=reward;
            currentUser.money-=reward;
            printLine();
            printf("发布成功!任务编号: %d , 剩余金额: %.2f\n", taskCnt, currentUser.money);
        }
    }
    system("pause");
}

// 查看与处理
void checkTask(){
    int choice;
    do{
        head("任务管理");
        printf("\n请选择操作: \n");
        printf("1.查看我发布的任务\n");
        printf("2.查看可接任务\n");
        printf("3.查看我所接的任务\n");
        printf("4.标记任务为完成\n");
        printf("5.返回上一级\n");
        printf("请输入编号：");
        scanf("%d",&choice);

        switch(choice){
            case 1:{
                head("我发布的任务");
                printf("ID\t标题\t费用\t\t接单者ID\t状态\t发布者积分\n");
                printf("--------------------------------------------------------------\n");
                int hasTask=0;
                for(int i=0;i<taskCnt;i++){
                    if(tasks[i].pubId==currentUser.id){
                        hasTask=1;

                        char status[20];
                        switch(tasks[i].status){
                            case 0:strcpy(status,"未接单"); break;
                            case 1:strcpy(status,"已接单"); break;
                            case 2:strcpy(status,"已完成"); break;

                        }
                        int pubCredit=0;
                        for(int j=0;j<userCnt;j++){
                            if(users[j].id==tasks[i].pubId){
                                pubCredit=users[j].credit;
                                break;
                            }
                        }
                        printf("%d\t%s\t\t%.1lf\t\t%d\t\t%s\t%d\n",
                        tasks[i].id,tasks[i].title,tasks[i].reward,tasks[i].runId,status,pubCredit);
                    }
                }
                if(!hasTask) {
                    printf("您未发布任何任务！\n");
                    system("pause");
                    break;
                }
                }
                case 2:{
                    head("可接的任务");
                    Task availableTasks[100];
                    int availCnt=0;
                    for(int i=0;i<taskCnt;i++){
                        if(tasks[i].status==0){
                            availableTasks[availCnt++]=tasks[i];
                        }
                    }

                    if(availCnt==0){
                        printf("暂无可接单任务！\n");
                        system("pause");
                        break;
                    }

                    for(int i=0;i<availCnt-1;i++){
                        for(int j=0;j<availCnt-i-1;j++){
                            int creditJ=0,creditJ1=0;

                            for(int k=0;k<userCnt;k++){
                                if(users[k].id==availableTasks[j].pubId) creditJ=users[k].credit;
                                if(users[k].id==availableTasks[j+1].pubId) creditJ1=users[k].credit;
                            }

                            if(creditJ<creditJ1){
                                Task temp=availableTasks[j];
                                availableTasks[j]=availableTasks[j+1];
                                availableTasks[j+1]=temp;
                            }
                        }
                    }

                    printf("\n可接任务(按发布者积分优先): \n");
                    printf("优先级\t任务\t标题\t\t费用\t发布者ID\t发布者积分\n");
                    printf("-------------------------------------------------------------\n");
                    for(int i=0;i<availCnt;i++){
                        int pubCredit=0;
                        for(int j=0;j<userCnt;j++){
                            if(users[j].id==availableTasks[i].pubId){
                                pubCredit=users[j].credit;
                                break;
                            }
                        }

                        printf("%d\t%d\t%s\t\t%.1lf\t%d\t\t%d\n",
                        i+1,availableTasks[i].id,availableTasks[i].title,
                        availableTasks[i].reward,availableTasks[i].pubId,pubCredit);
                    }

                int taskId;
                printf("\n请输入要接取的任务ID(输入0取消):");
                scanf("%d",&taskId);
                if(taskId==0) break;

                for(int i=0;i<taskCnt;i++){
                    if(tasks[i].id==taskId&&tasks[i].status==0){
                        tasks[i].status=1;
                        tasks[i].runId=currentUser.id;
                        printf("接单成功! 任务ID: %d,费用：%.1lf\n",taskId,tasks[i].reward);
                        system("pause");
                        return;
                    }
                }
                printf("任务不存在或已被接单！\n");
                system("pause");
                break;

            }

            case 3:{
                head("我可接的任务");
                printf("任务ID\t发布者ID\t标题\t\t费用\t\t状态\n");
                printf("---------------------------------------------------------------\n");
                int hasTask=0;
                for(int i=0;i<taskCnt;i++){
                    if(tasks[i].runId==currentUser.id){
                        hasTask=1;
                        char status[20];
                        switch(tasks[i].status){
                            case 1:strcpy(status,"已接单"); break;
                            case 2:strcpy(status,"已完成"); break;
                    
                    }
                    printf("%d\t%d\t\t%s\t\t%.1lf\t\t%s\n",
                    tasks[i].id,tasks[i].pubId,tasks[i].title,
                    tasks[i].reward,status);
                }
            }

            if(!hasTask) printf("您未接任何任务！\n");
            system("pause");
            break;
        }

        case 4:{
            head("标记任务");
            int taskId;
            printf("\n请输入要标记完成的任务ID:  ");
            scanf("%d",&taskId);

            for(int i=0;i<taskCnt;i++){
                if(tasks[i].id==taskId&&tasks[i].runId==currentUser.id&&tasks[i].status==1){
                    tasks[i].status=2;
                    printf("任务【%d】已标记为完成! \n", taskId);

                    for(int j=0;j<userCnt;j++){
                        if(users[j].id==currentUser.id){
                            users[j].money+=tasks[i].reward;
                            users[j].credit+=10;
                            printf("您已获得酬金：%.1lf,积分+10,当前积分:%d\n",tasks[i].reward,users[i].credit);
                        }

                        if(users[j].id==tasks[i].pubId){
                            users[j].credit+=5;
                            printf("发布者积分+5,当前积分:%d\n",users[j].credit);

                        }
                    }
                    system("pause");
                    return;
                }
            }

            printf("任务不存在,非您接取或已完成！\n");
            system("pause");
            break;
        }
        case 5:
            break;
        default:
        error();
      }
    }while(choice!=5);
}

// 主函数
int main() {
    while (1) {
        head("欢迎");
        printf("欢迎来到本跑腿管理系统!\n退出:(-1)\n前进:(1)\n");
        if (adminMod == 1) {
            printf("管理员界面(0)\n");
        }
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
                head("主页");
                printf("账号: %s (余额: $%.2f)\n", currentUser.name, currentUser.money);
                printLine();
                printf("发布任务:(1)\n");
                printf("任务管理:(2)\n");
                printf("充值:(3)\n");
                printf("退出本账号:(-1)\n");
                printLine();
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    publishTask();
                    break;
                
                case 2:
                    checkTask();
                    break;

                case 3:
                    Recharge();
                    break;

                case -1:
                    login = false;
                    break;
                default:
                    error();
                }
            }
        }
        else if (adminMod == 1 && choice == 0) {
            adminCommands();
        }
        else {
            error();
        }
    }
    return 0;
}

