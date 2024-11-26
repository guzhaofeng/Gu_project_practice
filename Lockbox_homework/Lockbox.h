#ifndef LOCKBOX_H
#define LOCKBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Locker{//柜子

    int numbering;//柜子的编号
    char name[100];//包中物品名称
    char password[6];//柜门密码

};

void generateRandomPassword(char* password){//密码生成
    for (int i = 0; i < 6; ++i) {
        //srand(time(NULL));(若需要更随机可以写这条代码)
        password[i] = '0' + rand() % 10;
    }
}

void Deposits(int num){//存件函数

    Locker list_lockbox[num];

    FILE* file_read = fopen("./data.txt","rb");
    fread(list_lockbox,sizeof(Locker),num,file_read);
    fclose(file_read);

    int index;
    for (int i = 0; i < num; ++i) {
        if(list_lockbox[i].name[0] == 0){
            index = i;
            break;
        }
    }

    printf("Please enter the name of your item:\n");
    char str[100];
    scanf("%s",str);

    for (int i = 0; i < 100; ++i) {
        list_lockbox[index].name[i] = str[i];
    }

    printf("your password is %s.\n",list_lockbox[index].password);
    printf("your numbering is %d.\n",list_lockbox[index].numbering);
    printf("dont forget to exit.\n");

    FILE* file;
    file = fopen("./data.txt","wb");
    fwrite(list_lockbox,sizeof(Locker),num,file);
    fclose(file);
}

int Pickup(int num){//取件函数
    int index = 0;

    begin:
    if(index == 3){
        printf("you dont have time to try.\n");
        exit(0);
    }

    printf("Please fill in your password:\n");
    char str[100];
    scanf("%s",str);

    Locker list_lockbox[num];

    FILE* file_read = fopen("./data.txt","rb");
    fread(list_lockbox,sizeof(Locker),num,file_read);
    fclose(file_read);


    for (int i = 0; i < num; ++i) {

        if(strcmp(str,list_lockbox[i].password) == 0  &&  list_lockbox[i].name[0] != 0){
            printf("your object has been finded.it is in the %d box.\n",list_lockbox[i].numbering);
            printf("yor object is %s.\n",list_lockbox[i].name);
            printf("please remember to take your object.\n");

            for (int j = 0; j < 100; ++j) {
                list_lockbox[i].name[j] = 0;
            }

            first:
            char new_password[6];
            generateRandomPassword(new_password);

            for (int j = 0; j < num; ++j) {
                if(strncmp(new_password,list_lockbox[j].password,6) == 0){
                    goto first;
                }
            }//检查是否出现重复密码

            for (int j = 0; j < 6; ++j) {
                list_lockbox[i].password[j] = new_password[j];
            }

            for (int j = 0; j < 100; ++j) {
                list_lockbox[i].name[j] = 0;
            }

            FILE* file;
            file = fopen("./data.txt","wb");
            fwrite(list_lockbox,sizeof(Locker),num,file);
            fclose(file);

            return 1;
        }
    }
    printf("your password may be wrong.please try again.\n");
    index++;
    goto begin;

}
#endif
