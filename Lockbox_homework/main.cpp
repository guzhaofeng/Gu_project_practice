#include <stdio.h>
#include "Lockbox.h"
#include "init.h"
#include <string>

void tips(){
    printf("thanks for using the lockbox.\n");
    printf("the bottons are following:\n\n");
    printf("init(You can use this button to initialize the entire lockbox)\n");
    printf("deposits(You can use this button to deposit your belongings)\n");
    printf("pickup(You can use this button to pickup your belongings)\n");
    printf("display(You can use this button to show the information of the lockbox)\n");

    printf("exit(you can use this botton to exit)\n");
}

int main(){

    tips();//打印提示

    struct Other_Data{
        int num = 0;//柜子数量
        int has_been_used_num = 0;//已经用的柜子数量
    };

    //打开文件

    int index = 1;
    while(index){
        printf("\nplease choose the botton:\n");

        char str[100];
        scanf("%s",str);

        if(strcmp(str,"init") == 0){
            if(access("./data.txt",F_OK) != -1){
                remove("./data.txt");
                printf("the old lockbox has been deleted.\n");
            }
            if(access("./other_data.txt",F_OK) != -1){
                remove("./other_data.txt");
                printf("the old other_data has been deleted.\n");
            }

            printf("Please enter the number of lockers you would like to create:\n");

            int num;
            scanf("%d",&num);
            //输入需要创建几个柜子

            Other_Data other_data = {num,0};


            FILE* file_write = fopen("./other_data.txt","wb");
            fwrite(&other_data,sizeof(Other_Data),1,file_write);
            fclose(file_write);

            init(num);
        }else if(strcmp(str,"exit") == 0){
            printf("you have exited.\n");
            index = 0;
        }else if(strcmp(str,"display") == 0){
            Other_Data other_data;

            FILE* file_read = fopen("./other_data.txt","rb");
            fread(&other_data,sizeof(Other_Data),1,file_read);
            fclose(file_read);

            display(other_data.num);
            printf("num = %d,has_been_used_num = %d.\n",other_data.num,other_data.has_been_used_num);
        }else if(strcmp(str,"deposits") == 0){//存件函数

            Other_Data other_data;

            FILE* file_read = fopen("./other_data.txt","rb");
            fread(&other_data,sizeof(Other_Data),1,file_read);
            fclose(file_read);

            if(other_data.num - other_data.has_been_used_num > 0){

                Deposits(other_data.num);
                other_data.has_been_used_num++;

                FILE* file_write = fopen("./other_data.txt","wb");
                fwrite(&other_data,sizeof(Other_Data),1,file_write);
                fclose(file_write);
            }else{
                printf("the lockbox is full.sorry\n");
            }

        }else if(strcmp(str,"pickup") == 0){//存件函数

            Other_Data other_data;

            FILE* file_read = fopen("./other_data.txt","rb");
            fread(&other_data,sizeof(Other_Data),1,file_read);
            fclose(file_read);

            if(other_data.has_been_used_num == 0){
                printf("the lockbox is empty\n");
            }else{
                if(Pickup(other_data.num) == 1){
                    other_data.has_been_used_num--;

                    FILE* file_write = fopen("./other_data.txt","wb");
                    fwrite(&other_data,sizeof(Other_Data),1,file_write);
                    fclose(file_write);
                }
            }

        }else{
            printf("your input is incorrect,please re-enter:\n");
        }
    }

    return 0;
}