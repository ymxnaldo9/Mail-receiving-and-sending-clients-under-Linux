#ifndef _SENDMAIL_H_ 
#define _SENDMAIL_H_
#include "tools.h"

char *recv_data;
char server1[56]="smtp.163.com"; 
char Subject[512];
char Content[6000]={0};
char From[128];
char To[128];

int sendmail(char* name,char* passwd,char* from,char* to,char* subject,char* content){
	//1.连接主机服务器
	//2.登录
	//3.发送邮件
	if(connectHost(server1,IPSTR_SMTP,25)<0){
           printf("1");
           return -1;
    }
 
    if(login(name, passwd) < 0){
        fprintf(stderr,"Can Not LOGIN !\n");
        printf("2");
        return -1;
    }

    if(from =="" ||to == ""||subject == ""||content == ""){
        printf("arguments error!\n");
        return -1;
    }
    
    sprintf(From, "MAIL FROM: <%s>\r\n", from);
     
    if((ret = send(sockfd, From, strlen(From), 0)) == SOCKET_ERROR){
         printf("3");
         return -1;
    }
     
    if(getResponse() < 0){
         printf("4");
         return -1;
    }
     
    sprintf(To, "RCPT TO: <%s>\r\n", to);
    if((ret = send(sockfd, To, strlen(To),0)) == SOCKET_ERROR){
          printf("5");
          return -1;
    }
    if(getResponse() < 0){
          printf("6");
          return -1;
    }
     
    send_data = "DATA\r\n";
    if((ret = send(sockfd,send_data,strlen(send_data),0)) == SOCKET_ERROR){
        printf("7");
        return -1;
    }
    if(getResponse() < 0){
        printf("8");
        return -1;
    }

    sprintf(Content,"from:%s\nto:%s\nsubject:%s\n%s\r\n.\r\n",from,to,subject,content);

    if((ret= send(sockfd, Content, strlen(Content), 0)) == SOCKET_ERROR){
          printf("9");
          return -1;
    }
    
    memset(buffer, '\0', sizeof(buffer));
    
    if(getResponse() < 0){
         printf("10");
         return -1;    
    }
 
    if((ret = send(sockfd,"QUIT\r\n",strlen("QUIT\r\n"), 0)) == SOCKET_ERROR){
          printf("11");
          return -1;
    }
    if(getResponse() < 0){
          printf("12");
        return -1;
    }
 
    printf("发送成功！\n");
    return 0;
}

void send_mail(char* to){
    //获取标题
    printf("Subject: ");
    char subject[512];
    fgets(subject,512,stdin);

    //获取邮件内容
    printf("Content: ");
    char c;
    int p = 0;
    char content[6000];
    scanf("%s",&content);
    printf("wangbo");

    char name[100];
    char passwd[100];
    getNamePasswd(name,passwd);
    char* from = base64_decode(name);
    printf("3eg5egeg");
    sendmail(name,passwd,from, to, subject, content);
}
#endif
