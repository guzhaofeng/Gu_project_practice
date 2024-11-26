#ifndef LOCKBOX_INIT_H
#define LOCKBOX_INIT_H

#include <stdio.h>
#include "Lockbox.h"
#include <string.h>
#include <unistd.h>


void init(int num){//初始化密码柜

    char list_password[num][6];//创建一个密码列表
    for (int i = 0; i < num; ++i) {
        begin:

        char new_password[6];
        generateRandomPassword(new_password);

        for (int j = 0; j < i-1; ++j) {
            if(strncmp(new_password,list_password[j],6) == 0){
                goto begin;
            }
        }//检查是否出现重复密码

        for (int j = 0; j < 6; ++j) {
            list_password[i][j] = new_password[j];
        }//将密码载入
    }

    Locker list_lockbox[num];
    for (int i = 0; i < num; ++i) {
        list_lockbox[i].numbering = i;
        for (int j = 0; j < 6; ++j) {
            list_lockbox[i].password[j] = list_password[i][j];
        }
        for (int j = 0; j < 100; ++j) {
            list_lockbox[i].name[j] = 0;
        }
    }
    FILE* file;
    file = fopen("./data.txt","wb");
    fwrite(list_lockbox,sizeof(Locker),num,file);
    fclose(file);
    //储存到data

    printf("your lockbox has been done.\n");

    ;
}

void display(int num){//检查柜子

    FILE* file = fopen("./data.txt","rb");

    Locker list_lockbox[num];
    fread(list_lockbox,sizeof(Locker),num,file);

    for (int i = 0; i < num; ++i) {
        printf("%d %s %s\n",list_lockbox[i].numbering,list_lockbox[i].name,list_lockbox[i].password);
    }

    printf("the data has been printed.\n");
    fclose(file);
}
#endif
