#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<windows.h>


#define SIZE 20 //�迭ũ��
#define MAX 10 //�ִ� 10��
#define FAIL 3 //�Է½��� ���� Ƚ�� 

typedef struct Info//��ȭ��ȣ��
{
   char ca_Name[SIZE];//�̸�
   char ca_Number[9];//��ȭ��ȣ
   unsigned int ui_Age;//����
   char ca_Addr[SIZE];//�ּ�
   int i_Auth;  //����
}Info;

typedef struct Login//�α���
{
   char ca_Name[SIZE];   //����� �̸�   
   char ca_Id[SIZE];   //���̵�
   char ca_Pwd[SIZE];  //��й�ȣ   
   int i_Auth;         //����
}Login;

Info sta_Info[MAX] = {
   {{"������"},{"12345678"},30,{"��⵵ ���ֽ�"},1},
   {{"������"},{"12345678"},30,{"��⵵ ���ֽ�"},3},
   {{"������"},{"11112222"},30,{"��⵵ ���ֽ�"},3},
   {{"�����"},{"11112222"},20,{"��⵵ ���ֽ�"},2}
};
Login sta_Login[MAX]= {
   {"������","admin","admin",3},
   {"������","jang","3",3},
   {"�����","yoo","2",2},
   {"������","kam","1",1},
};

int alli_Auth=0;   // �α��� ����� ���� ���� 
char allca_Name[SIZE]="";   // �α��� ����� �̸� ����
int alli_LoginCnt=4;   // ��ϵ� ����� index
int alli_Cnt=4;   // ��ϵ� ��ȭ��ȣ�� index 
/**** �Լ� ����� ****/
void gotoxy(int, int);   // Ŀ�� ��ġ ����
void setColor(unsigned short, unsigned short); // Text �� ���� �Լ� 
int login(void);   // �α��� �Լ�
void Regit(void);   // ����� ��� �Լ� 
int PwCheck(void);   // �н����� üũ �Լ�
int Login_Menu(void);   // �α��� �޴�  
int Menu(void);      // Main�޴� 
void Input(void);   // �Է��Լ�  
void Output_page2(void);   // ��� ������ ó�� �Լ�
void Ouput(void);   //����Լ�
int InfoModify(int idx);   //// ���� ���� ���� �Լ� 
void Edit();   // ������ ���� �Լ�  
void Delete();   //������ ���� �Լ� 
void Search();   //������ �˻� �Լ�
void run();      // ���� �Լ� 
void Alarm(int);   // �˶� �Լ�
void AlarmModify(int,int,int);   // ���� ȭ�� �˶� �Լ� 
void AlarmSearch(int);   // �˻� �˶� �Լ�
void NumberChange(char*,int);   // ��ȭ��ȣ ��� ���� 

/**** Main�Լ� ****/
int main(void)
{
   run();
   return 0;
}

/**** �Լ� ������ ****/
//Ŀ�� ��ġ ����
void gotoxy(int x, int y){
   COORD Cur;
   Cur.X=x;
   Cur.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

//Text �� ���� �Լ� 
void setColor(unsigned short text, unsigned short back){
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back<<4));
}

//�α��� �Լ�
int login(void){
   int i,j,i_Idx,i_Count=0;
   char ca_TmpID[20],ca_TmpPW[20];
   for(i=0;i<MAX;i++){
      if(sta_Login[i].ca_Id != NULL){
         i_Count++;
      }
   }
   
   for(j=0;j<FAIL;j++){
      system("cls");
      Alarm(12);   // �α��� ID,PW �Է� ������ 
      
      if(j==2){
         gotoxy(22,4);printf("�ش��� ������ ���α׷��� �ڵ� �����մϴ�.��");      
      } 
      
      gotoxy(34,9);scanf("%s",&ca_TmpID);
      gotoxy(34,11);scanf("%s",&ca_TmpPW);  
      
        for(i=0;i<i_Count;i++){
           if(strcmp(ca_TmpID,sta_Login[i].ca_Id) == 0){
            if(strcmp(ca_TmpPW,sta_Login[i].ca_Pwd) == 0){
               system("cls");
               i_Idx = i;
               return i_Idx;
            }else{
               gotoxy(31,16);printf("��PW�� Ʋ�Ƚ��ϴ�.��");
               Sleep(1000);
               break; // for(i=0;i<index;i++) �� ���� ���� for���� ������ 
            }
         }
         
         if(i == i_Count-1){
            gotoxy(25,16);printf("���Է��Ͻ� %s�� ���� ID �Դϴ�.��",ca_TmpID);
            Sleep(1000);
         }
      } //for(i=0;i<index;i++)
   }
   Sleep(1000);
   return -1;   
}

// ����� ��� �Լ�
void Regit(void){
   int i;
   Alarm(10);   // ����� �̸� ��� ������ 
   char tmp[SIZE];
   bool b_Pass = false;
   gotoxy(35,11);scanf("%s",&sta_Login[alli_LoginCnt].ca_Name);

   printf("���� �Է� : \n");
   while(1){
      Alarm(4);
      gotoxy(33,17);scanf("%d",&sta_Login[alli_LoginCnt].i_Auth);
      if(sta_Login[alli_LoginCnt].i_Auth > 0 && sta_Login[alli_LoginCnt].i_Auth < 4){
         break;
      }else{
         gotoxy(18,17);printf("�ر��� ������ 1~3 �Դϴ�.��");
         Sleep(1000);
         rewind(stdin);
      }
   }
   system("cls");
   gotoxy(24,11);printf("�ػ���Ͻ� ID�� PW�� ������ �ּ���.��");
   Sleep(1000);   
   while(1){
      system("cls");
      Alarm(11);   // ����� ��� ID,PW �Է� ������
      gotoxy(30,10);
      scanf("%s",&tmp);
      for(i=0;i<alli_LoginCnt;i++){
         if( (strcmp(tmp, sta_Login[i].ca_Id)) == 0){
            gotoxy(19,18);printf("�ص����� ID�� �ֽ��ϴ�. ID�� ���� �Է��ϼ���.��");
            Sleep(1000);
            break;
         }
         if(i >= alli_LoginCnt-1){
            strcpy(sta_Login[alli_LoginCnt].ca_Id,tmp);
            b_Pass = true;
         }
      }//for(i=0;i<alli_LoginCnt;i++)
      if(b_Pass){   // ������ ID�� ������ while���� �������� 
         break;
      }
   }// while(1)
   
   gotoxy(30,12);scanf("%s",&sta_Login[alli_LoginCnt].ca_Pwd);
   
   do{
      i = PwCheck();
   }while(i != 0);   // pw ��Ȯ�ν� ��ġ�ϸ� �Ϸ�Ǹ� ���� 
   
   alli_LoginCnt++;   // ����� ��� �Ϸ�� index���� 
} //void Regit(int idx)

// �н����� üũ �Լ�
int PwCheck(void){
   char ca_Password[20]={0};   // password Ȯ���� ���� �Է� ���� 
   gotoxy(23,14);printf("PW ��Ȯ�� :__________________________");
   gotoxy(35,14);scanf("%s",&ca_Password);       
   
   return strcmp(ca_Password,sta_Login[alli_LoginCnt].ca_Pwd);   // pw ��Ȯ�ν� �Է��� pw�� �����ϸ� 0 return 
} //int PwCheck(int idx)

// �α��� �޴�
int Login_Menu(void){
   int m;
   system( "cls" );
   Alarm(2);
   scanf("%d",&m);
   return m;
}

// Main �޴� 
int Menu(void){
   int m;
   Alarm(3);
   scanf("%d",&m);
   return m;
}

//�Է��Լ�
void Input(void){
   int i;  //�ݺ��� ���� ���� ���� 
   char ch_ans; //�ּ� ���� �Ⱦ��� Y or N 
   int i_menu1; //���Ժ� �پ��� ��� ���� ���ư��� 
       
   for(;;){      
      Alarm(13);   // ��ȭ��ȣ�� �Է� ���� ������ ���       
      
      if(alli_Cnt<10){
         Alarm(14);   // ��ȭ��ȣ�� �Է� ������ ���   
         gotoxy(30,9);scanf("%s",&sta_Info[alli_Cnt].ca_Name);            
         for(;;){  
            Alarm(14);   // ��ȭ��ȣ�� �Է� ������ ���
            gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);            
            gotoxy(30,12);
            while (!scanf_s("%d", &sta_Info[alli_Cnt].ui_Age)){   // ���ڸ� �Է� �ޱ����� �߰�             
               setColor(1,12);gotoxy(28,22);printf("�������� �Է� ���� �ٽ� �Է� �ϼ����\n");
               Sleep(800);
               setColor(0,15);
               Alarm(14);   // ��ȭ��ȣ�� �Է� ������ ���             
               gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);
               gotoxy(30,12);while (getchar() != '\n');
            }
            
            if(sta_Info[alli_Cnt].ui_Age>=0 && sta_Info[alli_Cnt].ui_Age<=120){
               break;
            }else{               
               setColor(1,12);gotoxy(28,22);printf("���̸� �ٽ��Է� �ϼ���");
               Sleep(800);
               setColor(0,15);
            }
         }//for(;;)  ����
         rewind(stdin);
         for(;;){
            Alarm(14);   // ��ȭ��ȣ�� �Է� ������ ���
            
            gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);
            gotoxy(30,12);printf("%d",sta_Info[alli_Cnt].ui_Age);
            
            gotoxy(37,15);scanf(" %s",&sta_Info[alli_Cnt].ca_Number);
            if(strlen(sta_Info[alli_Cnt].ca_Number)==8){  //8�ڸ� ������ �ȵ�.  
               for(i=0;i<8;i++){
                  if(sta_Info[alli_Cnt].ca_Number[i]>=48 && sta_Info[alli_Cnt].ca_Number[i]<=57){               
                  }
               }//for(i=0;i<8;i++)
               break;
            }//8�ڸ� ���� 
            else{
               setColor(1,12);gotoxy(28,22);printf("��ȭ��ȣ�� �ٽ� �Է����ּ���.");
               Sleep(800);
               setColor(0,15);
            }
         } //for(;;) ��ȭ��ȣ 
         
         for(;;){
            Alarm(14);   // ��ȭ��ȣ�� �Է� ������ ���               
            gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);
            gotoxy(30,12);printf("%d",sta_Info[alli_Cnt].ui_Age);
            gotoxy(37,15);printf("%s",sta_Info[alli_Cnt].ca_Number);
            
            gotoxy(28,22);printf("�ּҴ� �����Դϴ�. ���ðڽ��ϱ�?(Y/N)");scanf(" %c",&ch_ans);
            if(ch_ans=='Y'||ch_ans=='y'){
               Alarm(14);   // ��ȭ��ȣ�� �Է� ������ ���               
               gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);
               gotoxy(30,12);printf("%d",sta_Info[alli_Cnt].ui_Age);
               gotoxy(37,15);printf("%s",sta_Info[alli_Cnt].ca_Number);
               gotoxy(28,22);printf("���� �ø� �Է��� �ּ���.");
               Sleep(100);
               gotoxy(30,18);scanf(" %[^\n]s",&sta_Info[alli_Cnt].ca_Addr);
               break;
            } else if(ch_ans=='N'||ch_ans=='n'){
               strcpy(sta_Info[alli_Cnt].ca_Addr,"-");
               gotoxy(28,23);printf("�ּҸ� ���� �ʽ��ϴ�.");
               Sleep(800);
               break;
            } else{ 
                         
                  Alarm(14);   // ��ȭ��ȣ�� �Է� ������ ���                 
                  gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);
                  gotoxy(30,12);printf("%d",sta_Info[alli_Cnt].ui_Age);
                  gotoxy(37,15);printf("%s",sta_Info[alli_Cnt].ca_Number);
                  setColor(1,12);gotoxy(28,22);printf("Y��N �� �ϳ��� �����ϼ���.");
                  Sleep(700);setColor(0,15);
            } //if(ch_ans=='Y'||ch_ans=='y')
         }//for(;;) �ּ�
         sta_Info[alli_Cnt].i_Auth = alli_Auth;
         
         alli_Cnt++;
      }//if(alli_Cnt<10)
           
      Alarm(9);
      scanf("%d",&i_menu1);
      if(i_menu1==1){
         continue;
      }else if(i_menu1==2){
         break;
      }else if(alli_Cnt=10){
         printf("10�� ������ �Է� �����մϴ�.\n");
         printf("�����͸� ���� �� �Է��� �ּ���.");
         break;
      }//if(i_menu1==1)
    }//for(;;)  ��ȭ��ȣ�� �Է� 
}//void Input(void)

// ��� ������ ó�� �Լ� 
void Output_page2(){
   int i,s,i_back1,i_back2;
   
   for(;;){
      system("cls");
      for(i=0;i<5;i++){
         printf("\n�̸�: %s\n",sta_Info[i].ca_Name);
         printf("����: %d\n",sta_Info[i].ui_Age);
         NumberChange(sta_Info[i].ca_Number,1);   // ��ȭ��ȣ ��� ���� 
         printf("\n�ּ�: %s\n",sta_Info[i].ca_Addr);  
         printf("-----------------------------------");                   
      }//for(i=0;i<5;i++)  ù������  
      
      Alarm(16);   // 1������ ���ư��� ������ ��� 
      gotoxy(73,19);scanf("%d",&i_back1);               
      
      if(i_back1==0){
         Alarm(15);   // �޴��� ���ư��� ������ ��� 
         break;
      } //if(i_back1==0)
      
      if(i_back1==2){
         system("cls");
         for(i=5;i<alli_Cnt;i++){                      
            printf("\n�̸�: %s\n",sta_Info[i].ca_Name);
            printf("����: %d\n",sta_Info[i].ui_Age);
            NumberChange(sta_Info[i].ca_Number,1);   // ��ȭ��ȣ ��� ����             
            printf("\n�ּ�: %s\n",sta_Info[i].ca_Addr);  
            printf("-----------------------------------");              
         }//for(i=5;i<alli_Cnt;i++)
         Alarm(17);   // 2������ ���ư��� ������ ��� 
         
         
         gotoxy(71,19);scanf("%d",&i_back2);
         if(i_back2==0){
            Alarm(15);   // �޴��� ���ư��� ������ ��� 
            break;
         } //if(i_back1==2)
      } //if(i_back==1) ���������� 
   }//for(;;)
}//void Output_page2()

//����Լ�
void Ouput(void){
   int i_menu;//��ȭ��ȣ ��� �� �ǵ��ư��� �޴�
   int i;  //for�� ������, ��ü ����Ҷ� ����ϴ� ����  
   int s;  // for �� ������, ��ȭ��ȣ 4�ڸ��� ����Ҷ� ����ϴ� ���� 
   int i_back; //õü����� ���ư��� �ϰ� ������ ���� ����. 
      
   if(alli_Cnt==0){
      system("cls");
      printf("����� ������ �����ϴ�.");
      Sleep(700);
      Alarm(15);   // �޴��� ���ư��� ������ ��� 
   }//if(alli_Cnt==0)}
   
    if(alli_Cnt>0){
      for(;;){ 
         system("cls");
         Alarm(8);
         scanf("%d",&i_menu);
         if(i_menu==1){
            gotoxy(30,8);printf("��ȭ ��ȣ�� ��ü ���");
            Sleep(700);
            
            system("cls");
            
            if(alli_Cnt<=5){
               for(i=0;i<alli_Cnt;i++){
               printf("\n�̸�: %s\n",sta_Info[i].ca_Name);
               printf("����: %d\n",sta_Info[i].ui_Age);
               NumberChange(sta_Info[i].ca_Number,1);   // ��ȭ��ȣ ��� ���� 
               printf("\n�ּ�: %s\n",sta_Info[i].ca_Addr);
               printf("-----------------------------------");
               }//for(i=0;i<=cnt;i++)  
               Alarm(18);   // �Է� ���ư��� ������ ���
                
                gotoxy(71,19);scanf("%d",&i_back);           
               
                  if(i_back==0){
               Alarm(15);   // �޴��� ���ư��� ������ ��� 
               break;               
                  }
            } //if(alli_Cnt<=5)
            
            //---------------------------------------1~4�� �϶� �������� 1��--------------------------------
            if(alli_Cnt>5 && alli_Cnt<=10){
               Output_page2();               
            }//if(alli_Cnt>4 && alli_Cnt<=8) �� �������� ��� 
         
         }//if(menu_1==1)
         
         if(i_menu==2){
            Alarm(15);   // �޴��� ���ư��� ������ ��� 
            break;
         }      
      }//for(;;)   
    }//   if(alli_Cnt>0)
}//void Ouput(void)

// ���� ���� ���� �Լ� 
int InfoModify(int idx){
   int i_Select;
   
   Alarm(5);
   scanf("%d",&i_Select);
   system("cls");
   rewind(stdin);
   
   if(i_Select == 1){
      AlarmModify(0,idx,i_Select);   // ������ ������ ���       
      AlarmModify(1,idx,i_Select);   // ������ ������ ��� 
      
      gotoxy(53,8);scanf("%s",&sta_Info[idx].ca_Name);
   }else if(i_Select == 2){
      AlarmModify(0,idx,i_Select);   // ������ ������ ���       
      AlarmModify(1,idx,i_Select);   // ������ ������ ��� 
      
         gotoxy(60,12);scanf("%s",&sta_Info[idx].ca_Number);
   }else if(i_Select == 3){
      AlarmModify(0,idx,i_Select);   // ������ ������ ���       
      AlarmModify(1,idx,i_Select);   // ������ ������ ��� 
      
      gotoxy(53,10);
      while(!scanf_s("%d", &sta_Info[idx].ui_Age)){   // ���ڸ� �Է� �ޱ����� �߰� 
        gotoxy(20,20);printf("�������� �Է� ���� �ٽ� �Է� �ϼ���.��");
        AlarmModify(0,idx,i_Select);   // ������ ������ ���       
         AlarmModify(1,idx,i_Select);   // ������ ������ ��� 
        while (getchar() != '\n');
        gotoxy(53,10);
      }
   }else if(i_Select == 4){
      AlarmModify(0,idx,i_Select);   // ������ ������ ���       
      AlarmModify(1,idx,i_Select);   // ������ ������ ��� 
      
      gotoxy(53,14);scanf(" %[^\n]s",&sta_Info[idx].ca_Addr);
   }else if(i_Select == 5){
         gotoxy(20,10);printf("�ؼ����� ��� �Ͽ����ϴ�.��");
//      printf("������ ��� �Ͽ����ϴ�.\n");
      Sleep(1000);
      system( "cls" );
 return -1;
   }else{
      system( "cls" );
      printf("���� ���� ��ȣ�� 1~5 ���� �Դϴ�.\n");
      InfoModify(idx);
   }
   return 0;
}

//������ ���� �Լ�  
void Edit(){
   int i,i_Pass,i_Idx=0,i_Mod; // i_Mod ������ ��ȭ��ȣ�� ���� ���� 
   int ia_ModIdx[MAX] = {0}; // modIdx : ������ ��ȭ��ȣ���� index��ȣ  
   gotoxy(30,10);printf("������");Sleep(500);
   Alarm(19);   // ���̵� �޽��� 
      
   for(;;){
      system("cls");
      setColor(0,15);
      printf("\n--------------------------���� ������ ��ȭ��ȣ�� ���------------------------\n");
      for(i=0;i<alli_Cnt;i++){
         if(sta_Info[i].i_Auth <= alli_Auth){
            ia_ModIdx[i_Idx] = i;
            printf("%d. �̸� : %s , ",i_Idx+1,sta_Info[i].ca_Name);
            NumberChange(sta_Info[i].ca_Number,1);   // ��ȭ��ȣ ��� ���� 
            printf(" , ���� : %d , �ּ� : %s\n",sta_Info[i].ui_Age,sta_Info[i].ca_Addr);
            printf("-----------------------------------------------------------------------------\n");
            i_Idx++;
         } //if(ph[i].auth <= auth)      
      } //for(i=0;i<number;i++)
      if(i_Idx == 0){
         gotoxy(20,15);printf("�ؼ��� ������ ��ȭ��ȣ�� �����ϴ�.��");
         Sleep(1000);
         break;
      }   
      
      printf("----------------------�������� ���ư����� 0�� �Է��ϼ���.--------------------\n");
      if(i_Idx != 0){
         printf("��ȣ�Է�>>>>> ");
         scanf("%d",&i_Mod);
         if(i_Mod == 0){
            Alarm(15);   // �޴��� ���ư��� ������ ��� 
            break;
         } else if(i_Idx < i_Mod){
            gotoxy(24,24);printf("���߸��� ���ڸ� �����ϼ̽��ϴ�.��");
            Sleep(1000);
            system( "cls" );
            i_Idx = 0;
            continue;
         }
         system( "cls" );
         i_Pass = InfoModify(ia_ModIdx[i_Mod-1]);   // ���ڰ��� ��ü ��ȣ ����Ʈ�� ������ ��ȭ��ȣ�� index��. 
         if(i_Pass == -1){
            break;
         }
         i_Idx = 0;
         system( "cls" );
      }
   }
   
//   Sleep(1000);
} 

//������ ���� �Լ� 
void Delete(){
   int i,j;
   int i_Delete;
   int i_Cnt[MAX];
   int i_Scnt=0;
   int i_Check_Auth_Cnt=0;
   char ca_Tmp[SIZE];
   
      
    gotoxy(30,10);printf("������");Sleep(500);
    Alarm(19);   //���̵� �޽���    
   
   for(;;)
   {
      system("cls");
      printf("\n                        ���� ������ ��ȭ��ȣ�� ���\n");
      printf("-----------------------------------------------------------------------------\n");
      
      for(i=0;i<alli_Cnt;i++) {
         if(alli_Auth >= sta_Info[i].i_Auth) {
            i_Cnt[i_Scnt]=i;
            i_Scnt++;
            printf("%d. �̸� : %s, ",i_Check_Auth_Cnt+1,sta_Info[i].ca_Name);
            NumberChange(sta_Info[i].ca_Number,1);   // ��ȭ��ȣ ��� ����             
            printf(", ���� : %d, �ּ� : %s\n",sta_Info[i].ui_Age,sta_Info[i].ca_Addr);
            printf("-----------------------------------------------------------------------------\n");
            
            i_Check_Auth_Cnt++;
         }
      } //for(i=0;i<alli_Cnt;i++)
        if(i_Check_Auth_Cnt==0)   {
           gotoxy(20,15);printf("������ �� �ִ� ��ȭ��ȣ�ΰ� �����ϴ�.\n");
           Sleep(1000);
            return;
      }
      
         printf("��ȣ�Է�(0�� ����)>>>>"); scanf("%d",&i_Delete);
      
         if(i_Delete <= i_Check_Auth_Cnt && i_Delete>0) {   // i_Delete>=0 ���� ������ ��ȣ�� 0���� ū���̾�� ��. 
           alli_Cnt--;
           for(i=0;i<alli_Cnt;i++){
               if(i >= i_Cnt[i_Delete-1]) {
                     sta_Info[i] = sta_Info[i+1];
            }
         } //for(i=0;i<alli_Cnt;i++)
        gotoxy(33,23);printf("��%d�� �����Ϸ��",i_Delete);
        Sleep(1000);
        break;
      } 
        else if(i_Delete==0){
           Alarm(15);   // �޴��� ���ư��� ������ ��� 
           break;           
        }
        else {
         printf("�߸��� ���ڸ� �����ϼ̽��ϴ�.\n");
         Sleep(1000);
         i_Check_Auth_Cnt=0;
      }
   }
}

//������ �˻� �Լ� 
void Search(){
   int i,j,k;
   int i_C=0;
   int i_Cnt[MAX];
   int i_Scnt=0;
   int i_Search_Menu;
   unsigned int ui_Tmp;
   char ca_Tmp[SIZE];
   char ca_CMP_Tmp[SIZE];
   char ca_back[10];
   for(;;)   {
        system("cls");
        Alarm(6);
      
        scanf("%d",&i_Search_Menu);
        system("cls");
      if(i_Search_Menu==1) {
         AlarmSearch(0);   // �˼���� ������ ��� 
         gotoxy(36,3);scanf("%s",&ca_Tmp);
         for(i=0;i<alli_Cnt;i++)   {
            if(strcmp(sta_Info[i].ca_Name,ca_Tmp)==0){
               i_Cnt[i_Scnt]=i;
               i_Scnt++;
            }
         } //for(i=0;i<alli_Cnt;i++)
         for(i=0;i<i_Scnt;i++) {         
            gotoxy(1,7+i);printf("%d. �̸� : %s��",i+1,sta_Info[i_Cnt[i]].ca_Name);            
            NumberChange(sta_Info[i_Cnt[i]].ca_Number,1);   // ��ȭ��ȣ ��� ����             
            printf("������ : %d���ּ� : %s��\n",sta_Info[i_Cnt[i]].ui_Age,sta_Info[i_Cnt[i]].ca_Addr);
            printf("--------------------------------------------------------------------------------");
         } //for(i=0;i<i_Scnt;i++)
         if(i_Scnt==0) {
            gotoxy(30,5);printf("��ã�� �̸��� �����ϴ�.��");
            Sleep(600);
            system("cls");
         }   
         Alarm(20);
         gotoxy(1,23);printf("���ư���(�ƹ�Ű)"); scanf("%s",&ca_back);
         i_Scnt=0;   
      }//if(i_Search_Menu==1) �Ƹ��˻� ��.
      else if(i_Search_Menu==2){
         AlarmSearch(1);   // ������� ������ ��� 
         gotoxy(41,3);scanf("%s",&ca_Tmp);
         for(i=0;i<alli_Cnt;i++)   {
            if(strcmp(sta_Info[i].ca_Number,ca_Tmp)==0)   {
               i_Cnt[i_Scnt]=i;
               i_Scnt++;
            }
         }
         
         for(i=0;i<i_Scnt;i++){
            gotoxy(1,7+i);printf("%d. �̸� : %s��",i+1,sta_Info[i_Cnt[i]].ca_Name);            
            NumberChange(sta_Info[i_Cnt[i]].ca_Number,1);   // ��ȭ��ȣ ��� ����             
            printf("������ : %d���ּ� : %s��\n",sta_Info[i_Cnt[i]].ui_Age,sta_Info[i_Cnt[i]].ca_Addr);
            printf("--------------------------------------------------------------------------------");
         }
         if(i_Scnt==0){
            gotoxy(30,5);printf("��ã�� ��ȣ�� �����ϴ�.��");  
            Sleep(600);
            system("cls");    
         }
         Alarm(20);
         gotoxy(1,23);printf("���ư���(�ƹ�Ű)"); scanf("%s",&ca_back);
         i_Scnt=0;
      } // else if(i_Search_Menu==2)
      else if(i_Search_Menu==3){
         AlarmSearch(2);   // ������� ������ ��� 
         gotoxy(36,3);
         while (!scanf_s("%d", &ui_Tmp)){   // ���ڸ� �Է� �ޱ����� �߰�          
            gotoxy(25,5);printf("�������� �Է� ���� �ٽ� �Է� �ϼ���.��");
            Sleep(500);
            system("cls");
            gotoxy(36,3);
            AlarmSearch(2);   // ������� ������ ��� 
            gotoxy(36,3);while (getchar() != '\n');
         }
         
         for(i=0;i<alli_Cnt;i++){
            if(sta_Info[i].ui_Age==ui_Tmp){
               i_Cnt[i_Scnt]=i;
               i_Scnt++;
            }
         }
         
         for(i=0;i<i_Scnt;i++){
            gotoxy(1,7+2*i);printf("%d. �̸� : %s��",i+1,sta_Info[i_Cnt[i]].ca_Name);            
            NumberChange(sta_Info[i_Cnt[i]].ca_Number,1);   // ��ȭ��ȣ ��� ����             
            printf("������ : %d���ּ� : %s��\n",sta_Info[i_Cnt[i]].ui_Age,sta_Info[i_Cnt[i]].ca_Addr);
            printf("--------------------------------------------------------------------------------");
         }
         
         if(i_Scnt==0){
            gotoxy(30,5);printf("��ã�� ���̰� �����ϴ�.��");     
            Sleep(600);
            system("cls");  
         }
         Alarm(20);
         gotoxy(1,23);printf("���ư���(�ƹ�Ű)"); scanf("%s",&ca_back);
         i_Scnt=0;
      }
      else if(i_Search_Menu==4) {
         AlarmSearch(3);   // ������� ������ ��� 
         gotoxy(36,3);scanf("%s",&ca_Tmp);
         
         for(i=0;i<alli_Cnt;i++) {
            for(j=0;j<SIZE;j++)   {
               if(sta_Info[i].ca_Addr[j]==' '|| sta_Info[i].ca_Addr[j]=='\0') {
                  for(k=0;k<j-i_C;k++){
                     ca_CMP_Tmp[k]=sta_Info[i].ca_Addr[k+i_C];
                     if(k==j-1){
                        ca_CMP_Tmp[k+1]='\0';
                     }
                  }
                  i_C=j+1;
                  if(strcmp(ca_CMP_Tmp,ca_Tmp)==0){
                     i_Cnt[i_Scnt]=i;
                     i_Scnt++;
                  }
                  if(sta_Info[i].ca_Addr[j]=='\0'){
                     break;
                  }
               }
            }
            i_C=0;      
         }
         
         for(i=0;i<i_Scnt;i++){
            gotoxy(1,7+2*i);printf("%d. �̸� : %s��",i+1,sta_Info[i_Cnt[i]].ca_Name);            
            NumberChange(sta_Info[i_Cnt[i]].ca_Number,1);   // ��ȭ��ȣ ��� ����             
            printf("������ : %d���ּ� : %s��\n",sta_Info[i_Cnt[i]].ui_Age,sta_Info[i_Cnt[i]].ca_Addr);
            printf("--------------------------------------------------------------------------------");
         }
         
         if(i_Scnt==0){
            gotoxy(30,5);printf("ã�� �ּҰ� �����ϴ�.\n");
            Sleep(600);
            system("cls");   
         }
         Alarm(20);
         gotoxy(1,23);printf("���ư���(�ƹ�Ű)");scanf("%s",&ca_back);
         i_Scnt=0;
      }
      else if(i_Search_Menu==5){
         Alarm(15);   // �޴��� ���ư��� ������ ��� 
         break;
      }
      else{
         Alarm(7);   // �޴����� ���� �޽��� ��� 
         Sleep(1000);
      }
   } // for(;;)
}

// ���� �Լ� 
void run(){
   int i_Login_Menu;//�α��θ޴�����
   int i_Menu;//���θ޴�
   int i_LoginIndex; //�α��� ����� index ��ȣ
   
   for(;;){ //���α׷�����   
      i_Login_Menu=Login_Menu();//�޴��Լ�ȣ���� �޴�����
      system( "cls" ); //  - kam �߰�
      if(i_Login_Menu==1)   {
         i_LoginIndex=login();
         if(i_LoginIndex == -1){   // �α��� 3ȸ ���н� ���α׷� ����             
            ("�α��� 3ȸ �����Ͽ����ϴ�.\n");
         Alarm(21);
            break;
         }
         alli_Auth=sta_Login[i_LoginIndex].i_Auth;
         strcpy(allca_Name,sta_Login[i_LoginIndex].ca_Name);
         Alarm(1);   // �α��� �˶�
         Sleep(2000); 
         for(;;) {
            i_Menu=Menu();
            system( "cls" );
            if(i_Menu==1){
               Input();
            }else if(i_Menu==2) {
               Edit();
            }else if(i_Menu==3) {
               Delete();
            }else if(i_Menu==4) {
               Ouput();
            }else if(i_Menu==5) {
               if(alli_Auth==3){ 
                  Search();
               }else {
                  gotoxy(20,10);printf("������ �������δ� �˻��� �Ұ����մϴ�.��");
                  Sleep(1000);
               }
            }else if(i_Menu==6) {
               Alarm(0);   // �α׾ƿ� �޽��� ��� - kam �߰�
               Sleep(2000);
               setColor(7,0);
               break;
            }else{
               Alarm(7);        
               Sleep(1000);
            }
         } //for(;;)   Main�޴� 
      }else if(i_Login_Menu==2){
         Regit();
        system( "cls" );
        gotoxy(25,10);printf("�ػ���ڵ���� �Ϸ�Ǿ����ϴ�.��");
         Sleep(1000);
      }else if(i_Login_Menu==3)
      {         
         Alarm(21);   // �����λ� �޽��� 
         Sleep(1000);
         break;
      }else{
         Alarm(7);
         Sleep(1000);
      } //if(i_Login_Menu==1)
   } // for(;;) ��ü ���α׷� 
}

// �˶� �Լ�
void Alarm(int check){
   switch(check){
      case 0:
            printf("%s ���� �α׾ƿ� �ϼ̽��ϴ�.\n",allca_Name);
            setColor(0,15);
            gotoxy(10,7);printf("  ���        ��      ����  ����    ����  ��  ��    ��    ");
            gotoxy(10,8);printf("��    ��      ��      ��  ��  ��  ��    ��  ��  ��  ��    ��    ");
            gotoxy(10,9);printf("��    ��      ��      ��  ��  ����    ��  ��  ��  ��  ����  "); 
         gotoxy(10,10);printf("�����      ��      ��  ��      ��    ��  ��  ��  ��    ��    ");
            gotoxy(10,11);printf("�����      ��      ��  ��      ��    ��  ��  ��  ��    ��    ");
            gotoxy(10,12);printf("�����      ����  ����  ����    ����  ����    ���  ");
            break;
      case 1:
         if(alli_Auth == 1){
            setColor(7,2);
            printf("(�Ϲݻ����)");
            setColor(7,0);
         }else if(alli_Auth == 2){
            setColor(7,5);
            printf("(����������)");
            setColor(7,0);
         }else if(alli_Auth == 3){
            setColor(7,4);
            printf("(������)");
            setColor(7,0);   
         }         
            printf("%s ���� �α��� �ϼ̽��ϴ�.\n",allca_Name);
            setColor(0,15);
            gotoxy(18,7);printf("  ���        ��      ����  ����    ��        ");
            gotoxy(18,8);printf("��    ��      ��      ��  ��  ��  ��        ����");
            gotoxy(18,9);printf("��    ��      ��      ��  ��  ����    ��  ��  ��"); 
            gotoxy(18,10);printf("�����      ��      ��  ��      ��    ��  ��  ��");
            gotoxy(18,11);printf("�����      ��      ��  ��      ��    ��  ��  ��");
            gotoxy(18,12);printf("�����      ����  ����  ����    ��  ��  ��");
         break;
      case 2:
         gotoxy(35,5);printf(" ��    ��");
         gotoxy(28,6);printf("������������������������");
         gotoxy(28,7);printf("��1.   ��  ��  ��     ��");
         gotoxy(28,8);printf("������������������������");
         gotoxy(28,9);printf("��2.   ����ڵ��     ��");
         gotoxy(28,10);printf("������������������������");
         gotoxy(28,11);printf("��3.    ��    ��      ��");
         gotoxy(28,12);printf("������������������������");
         gotoxy(28,13);printf("����>>> "); 
         break;
       case 3:
         system( "cls" );
         gotoxy(28,5);printf("���������������޴���������������");
         gotoxy(28,6);printf("��                            ��");
         gotoxy(28,7);printf("�� 1.   ��ȭ��ȣ�� �Է�       ��");
         gotoxy(28,8);printf("��                            ��");
         gotoxy(28,9);printf("�� 2.   ��ȭ��ȣ�� ����       ��");
         gotoxy(28,10);printf("��                            ��");
         gotoxy(28,11);printf("�� 3.   ��ȭ��ȣ�� ����       ��");
         gotoxy(28,12);printf("��                            ��");
         gotoxy(28,13);printf("�� 4.  ��ȭ��ȣ�� ��ü����    ��");
         gotoxy(28,14);printf("��                            ��");
         gotoxy(28,15);printf("�� 5.   ��ȭ��ȣ�� ã��       ��");
         gotoxy(28,16);printf("��                            ��");
         gotoxy(28,17);printf("�� 6.     �� �� �� ��         ��");
         gotoxy(28,18);printf("��������������������������������");
         gotoxy(28,19);printf(">>>>> ");
         break;
      case 4:
         system("cls");
         gotoxy(18,6);printf("�������������������������  ��Ϧ�����������������");
         gotoxy(18,7);printf("��                                              ��");
         gotoxy(18,8);printf("��  �������������������Ѽ��æ�����������������  ��");
         gotoxy(18,9);printf("��  ��                                      ��  ��");
         gotoxy(18,10);printf("��  ��      1.      ����� ����             ��  ��");
         gotoxy(18,11);printf("��  ��                                      ��  �� ");
         gotoxy(18,12);printf("��  ��      2.    ���������� ����           ��  ��");
         gotoxy(18,13);printf("��  ��                                      ��  ��");
         gotoxy(18,14);printf("��  ��      3.     ������ ����              ��  ��");
         gotoxy(18,15);printf("��  ������������������������������������������  ��");
         gotoxy(18,16);printf("��������������������������������������������������");
         gotoxy(19,17);printf("���Ѽ���>>>>> ");
         break;
      case 5:
         gotoxy(27,6);printf("�������������� �׸� ���æ�������");
         gotoxy(27,7);printf("��                            ��");
         gotoxy(27,8);printf("�� 1.      �̸� ����          ��");
         gotoxy(27,9);printf("��                            ��");
         gotoxy(27,10);printf("�� 2.    ��ȭ��ȣ ����        ��");
         gotoxy(27,11);printf("��                            ��");
         gotoxy(27,12);printf("�� 3.      ���� ����          ��");
         gotoxy(27,13);printf("��                            ��");
         gotoxy(27,14);printf("�� 4.      �ּ� ����          ��");
         gotoxy(27,15);printf("��                            ��");
         gotoxy(27,16);printf("�� 5.      ���� ���          ��");
         gotoxy(27,17);printf("��                            ��");   
         gotoxy(27,18);printf("��������������������������������");
         gotoxy(27,19);printf(">>>>> "); 
         break;
      case 6:
         gotoxy(28,7);printf("������������ã��  �޴�����������");
         gotoxy(28,8);printf("��                            ��"); 
         gotoxy(28,9);printf("�� 1.     �̸����� �˻�       ��");
         gotoxy(28,10);printf("��                            ��");
         gotoxy(28,11);printf("�� 2.   ��ȭ��ȣ��  �˻�      ��");
         gotoxy(28,12);printf("��                            ��");
         gotoxy(28,13);printf("�� 3.     ���̷� �˻�         ��");
         gotoxy(28,14);printf("��                            ��");
         gotoxy(28,15);printf("�� 4.   �ּҷ� �˻�(��,��)    ��");
         gotoxy(28,16);printf("��                            ��");
         gotoxy(28,17);printf("�� 5.      ���� �޴�          ��");
         gotoxy(28,18);printf("��������������������������������");
         gotoxy(28,19);printf(">>>>> ");
         break;
      case 7:
         rewind(stdin);   // ���ڼ��ý� ���ڷ� �Է��� ������ buffer ����� ���� ��� 
         printf("�޴� ���� ����\n");
         break;
      case 8:
         gotoxy(27,8);printf("������������ȭ ��ȣ ��¦���������");
         gotoxy(27,9);printf("��                              ��");
         gotoxy(27,10);printf("�� 1.     ��ü ��ȭ��ȣ ���    ��");
         gotoxy(27,11);printf("��                              ��");  
         gotoxy(27,12);printf("�� 2.       �� �� �� ��         ��");
         gotoxy(27,13);printf("��                              ��");
         gotoxy(27,14);printf("����������������������������������") ;
         gotoxy(27,15);printf(">>>>> ");
         break;
      case 9:
         system("cls");
         gotoxy(28,7);printf("��������������������������");
         gotoxy(28,8);printf("��                      ��");
         gotoxy(28,9);printf("��  1. ��� �Է��ϱ�    ��");
         gotoxy(28,10);printf("��                      ��");
         gotoxy(28,11);printf("��  2.  �� �� �� ��     ��");
         gotoxy(28,12);printf("��                      ��");
         gotoxy(28,13);printf("��������������������������");
         gotoxy(28,14);printf(">>>>> ");
         break;
      case 10:
         gotoxy(18,6);printf("�������������������������  ��Ϧ�����������������");
         gotoxy(18,7);printf("��                                              ��");
         gotoxy(18,8);printf("��                                              ��");
         gotoxy(18,9);printf("��                                              ��");      
         gotoxy(18,10);printf("��  ������������������������������������������  ��");
         gotoxy(18,11);printf("��  ���̸� �Է�:                            ��  ��");
         gotoxy(18,12);printf("��  ������������������������������������������  ��");
         gotoxy(18,13);printf("��                                              ��");
         gotoxy(18,14);printf("��                                              ��");
         gotoxy(18,15);printf("��                                              ��");
         gotoxy(18,16);printf("��������������������������������������������������");   
         break; 
      case 11:
         gotoxy(18,6);printf("�������������������������  ��Ϧ�����������������");
         gotoxy(18,7);printf("��                                              ��");
         gotoxy(18,8);printf("��                                              ��");
         gotoxy(18,9);printf("��  ������������������������������������������  ��");
         gotoxy(18,10);printf("��  ��  ID :                                ��  ��");
         gotoxy(18,11);printf("��  ������������������������������������������  ��");
         gotoxy(18,12);printf("��  ��  PW :                                ��  ��");
         gotoxy(18,13);printf("��  ������������������������������������������  ��"); 
         gotoxy(18,14);printf("��                                              ��");
         gotoxy(18,15);printf("��                                              ��");
         gotoxy(18,16);printf("��������������������������������������������������"); 
         break;
      case 12:
         system("cls");
         gotoxy(25,6);printf("��Login ��������������������������");
         gotoxy(25,7);printf("��                              ��");
         gotoxy(25,8);printf("�� ������������������������     ��");
         gotoxy(25,9);printf("�� ��ID:                 ��     ��");
         gotoxy(25,10);printf("�� ������������������������     ��");
         gotoxy(25,11);printf("�� ��PW:                 ��     ��");
         gotoxy(25,12);printf("�� ������������������������     ��");
         gotoxy(25,13);printf("��                              ��");
         gotoxy(25,14);printf("����������������������������������"); 
         break;
      case 13:
         system("cls");
         gotoxy(30,8);printf("��ȭ��ȣ�� �Է���");Sleep(800);
         gotoxy(30,10);printf("�̸�");Sleep(800);
         gotoxy(36,10);printf("����");Sleep(800); 
         gotoxy(42,10);printf("��ȭ��ȣ");Sleep(800);
         gotoxy(52,10);printf("�ּ�");  Sleep(800);
         gotoxy(30,12);printf("������ �Է��Ͻø� �˴ϴ�."); Sleep(800); 
         break;
      case 14:
         system("cls");
         gotoxy(18,6);printf("��������������������ȭ��ȣ��  �Է¦�����������������");
         gotoxy(18,7);printf("��                                                ��");
         gotoxy(18,8);printf("��  ��������������������������������������������  ��");
         gotoxy(18,9);printf("��  ���̸�:                                   ��  ��");
         gotoxy(18,10);printf("��  ��������������������������������������������  ��");
         gotoxy(18,11);printf("��  ��������������������������������������������  ��");
         gotoxy(18,12);printf("��  ������:                                   ��  ��");
         gotoxy(18,13);printf("��  ��������������������������������������������  ��");
         gotoxy(18,14);printf("��  ��������������������������������������������  ��"); 
         gotoxy(18,15);printf("��  ����ȭ��ȣ:010-                           ��  ��");
         gotoxy(18,16);printf("��  ��������������������������������������������  ��");
         gotoxy(18,17);printf("��  ��������������������������������������������  ��"); 
         gotoxy(18,18);printf("��  ���ּ�:                                   ��  ��");
         gotoxy(18,19);printf("��  ��������������������������������������������  ��");
         gotoxy(18,20);printf("����������������������������������������������������"); 
         break;         
        case 15:
         system("cls");
         gotoxy(28,10);printf("������������������������������"); 
         gotoxy(28,11);printf("�� �ظ޴��� �ǵ��ư��ϴ�.�� ��");
         gotoxy(28,12);printf("������������������������������"); 
         Sleep(800);
         break;
      case 16:
         gotoxy(36,0);printf("������������������������������������������");
         gotoxy(36,1);printf("��                                      ��"); 
         gotoxy(36,2);printf("��                                      ��");
         gotoxy(36,3);printf("��                                      ��");
         gotoxy(36,4);printf("��                                      ��");
         gotoxy(36,5);printf("��                                      ��");
         gotoxy(36,6);printf("��          ��              ��          ��");
         gotoxy(36,7);printf("��        ��                  ��        ��");
         gotoxy(36,8);printf("��      �������  �������      ��");
         gotoxy(36,9);printf("��        ��                  ��        ��");
         gotoxy(36,10);printf("��          ��              ��          ��");
         gotoxy(36,11);printf("��                                      ��");
         gotoxy(36,12);printf("��                                      ��");
         gotoxy(36,13);printf("��                                      ��");
         gotoxy(36,14);printf("��                                      ��");
         gotoxy(36,15);printf("��                                      ��");
         gotoxy(36,16);printf("��                                      ��");
         gotoxy(36,17);printf("������������������������������������������");
         gotoxy(36,18);printf("��                                      ��");
         gotoxy(36,19);printf("��     ���ư���(0��),����������(2��)    ��");
         gotoxy(36,20);printf("������������������������������������������"); 
         break;
      case 17: 
           gotoxy(36,0);printf("������������������������������������������");
           gotoxy(36,1);printf("��                                      ��"); 
           gotoxy(36,2);printf("��                                      ��");
           gotoxy(36,3);printf("��                                      ��");
           gotoxy(36,4);printf("��                                      ��");
           gotoxy(36,5);printf("��                                      ��");
           gotoxy(36,6);printf("��          ��              ��          ��");
           gotoxy(36,7);printf("��        ��                  ��        ��");
           gotoxy(36,8);printf("��      �������  �������      ��");
           gotoxy(36,9);printf("��        ��                  ��        ��");
           gotoxy(36,10);printf("��          ��              ��          ��");
           gotoxy(36,11);printf("��                                      ��");
           gotoxy(36,12);printf("��                                      ��");
           gotoxy(36,13);printf("��                                      ��");
           gotoxy(36,14);printf("��                                      ��");
           gotoxy(36,15);printf("��                                      ��");
           gotoxy(36,16);printf("��                                      ��");
           gotoxy(36,17);printf("������������������������������������������");
           gotoxy(36,18);printf("��                                      ��");
           gotoxy(36,19);printf("��    ����������(1��),���ư���(0��)     ��");
           gotoxy(36,20);printf("������������������������������������������"); 
           break; 
        case 18:
            gotoxy(36,0);printf("������������������������������������������");
            gotoxy(36,1);printf("��                                      ��"); 
            gotoxy(36,2);printf("��                                      ��");
            gotoxy(36,3);printf("��                                      ��");
            gotoxy(36,4);printf("��                                      ��");
            gotoxy(36,5);printf("��              ��                      ��");
            gotoxy(36,6);printf("��            ��                        ��");
            gotoxy(36,7);printf("��          ��                          ��");
            gotoxy(36,8);printf("��        ������������        ��");
            gotoxy(36,9);printf("��          ��                          ��");
            gotoxy(36,10);printf("��            ��                        ��");
            gotoxy(36,11);printf("��              ��                      ��");
            gotoxy(36,12);printf("��                                      ��");
            gotoxy(36,13);printf("��                                      ��");
            gotoxy(36,14);printf("��                                      ��");
            gotoxy(36,15);printf("��                                      ��");
            gotoxy(36,16);printf("��                                      ��");
            gotoxy(36,17);printf("������������������������������������������");
            gotoxy(36,18);printf("��                                      ��");
            gotoxy(36,19);printf("��      ���ư�����(0���� ��������)      ��");
            gotoxy(36,20);printf("������������������������������������������");
            break;
        case 19:           
         gotoxy(37,10);printf("������");Sleep(500);
         gotoxy(30,12);printf("��ȣ��");Sleep(500);
         gotoxy(37,12);printf("�Է��ϼ���.");Sleep(500);
         gotoxy(30,13);printf("��");Sleep(200);gotoxy(32,13);printf("��");Sleep(200);gotoxy(34,13);printf("��");Sleep(200);
         gotoxy(28,12);printf("��");Sleep(800);
         break;
         
         case 20:
            gotoxy(23,19);printf("���      ��      ���  ��  ��        ��      ");
            gotoxy(23,20);printf("��  ��  ��  ��  ��      ��  ��      ��        ");
            gotoxy(23,21);printf("���    ����  ��      ���      ��  �����");
            gotoxy(23,22);printf("��  ��  ��  ��  ��      ��  ��      ��        ");   
            gotoxy(23,23);printf("���    ��  ��    ���  ��  ��        ��      ");
            break;
        case 21:
           system("cls");
           	printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
		 		printf("\n                            �����մϴ�\n");
		 		system("cls");	
		 		printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("  �����٦�");
		 		printf("\n�����ʢɦ���\n"); 
		 		printf("���ݦ����ݦ����� ���� ��");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("    �����٦�");
		 		printf("\n  �����ʢɦ���\n"); 
		 		printf("  ���ݦ����ݦ����� ����");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("      �����٦�");
		 		printf("\n    �����ʢɦ���\n"); 
		 		printf("    ���ݦ����ݦ����� ����");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(100); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("        �����٦�");
		 		printf("\n      �����ʢɦ���\n"); 
		 		printf("      ���ݦ����ݦ����� ��");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(100); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("          �����٦�");
		 		printf("\n        �����ʢɦ���\n"); 
		 		printf("        ���ݦ����ݦ����� ");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(100);
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("            �����٦�");
		 		printf("\n          �����ʢɦ���\n"); 
		 		printf("          ���ݦ����ݦ�����");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(100); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("              �����٦�");
		 		printf("\n            �����ʢɦ���\n"); 
		 		printf("            ���ݦ����ݦ���");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("                �����٦�");
		 		printf("\n              �����ʢɦ���\n"); 
		 		printf("              ���ݦ����ݦ�");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("���                �����٦�");
		 		printf("\n�ᦡ              �����ʢɦ���\n"); 
		 		printf("���              ���ݦ����ݦ�");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("   �� ���               �����٦�");
		 		printf("\n ��   �ᦡ             �����ʢɦ���\n"); 
		 		printf(" ��   ���             ���ݦ����ݦ�");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("��   �� �� ���               �����٦�");
		 		printf("\n���   ��   �ᦡ             �����ʢɦ���\n"); 
		 		printf("���   ��   ���             ���ݦ����ݦ�");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("    ��    �� �� ���               �����٦�");
		 		printf("\n    ���   ��   �ᦡ             �����ʢɦ���\n"); 
		 		printf("    ���   ��   ���             ���ݦ����ݦ�");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("        ��    �� �� ���               �����٦�");
		 		printf("\n        ���   ��   �ᦡ             �����ʢɦ���\n"); 
		 		printf("        ���   ��   ���             ���ݦ����ݦ�");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("             ��    �� �� ���               �����٦�");
		 		printf("\n             ���   ��   �ᦡ             �����ʢɦ���\n"); 
		 		printf("             ���   ��   ���             ���ݦ����ݦ�");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("                   ��    �� �� ���               �����٦�");
		 		printf("\n                   ���   ��   �ᦡ             �����ʢɦ���\n"); 
		 		printf("                   ���   ��   ���             ���ݦ����ݦ�");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("                         ��    �� �� ���               �����٦�");
		 		printf("\n                         ���   ��   �ᦡ             �����ʢɦ���\n"); 
		 		printf("                         ���   ��   ���             ���ݦ����ݦ�");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n"); 
		 		printf("                             ��    �� �� ���               �����٦�");
		 		printf("\n                             ���   ��   �ᦡ             �����ʢɦ���\n"); 
		 		printf("                             ���   ��   ���             ���ݦ����ݦ�");
		 		printf("\n��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��\n");
				Sleep(1000); 
				system("cls");
           break;
        default:
            break;         
   }
} 

// ���� ȭ�� �˶� �Լ� 
void AlarmModify(int check, int idx, int select){
   if(check == 0){
      gotoxy(2,6);printf("�������������� �� ��������������");
      gotoxy(2,7);printf("��                            ��");
      gotoxy(2,8);printf("���̸�:                       ��");gotoxy(10,8);printf("%s",sta_Info[idx].ca_Name);
      gotoxy(2,9);printf("��                            ��"); 
      gotoxy(2,10);printf("������:                       ��");gotoxy(10,10);printf("%d",sta_Info[idx].ui_Age);
      gotoxy(2,11);printf("��                            ��"); 
      gotoxy(2,12);printf("����ȭ��ȣ:010-               ��");gotoxy(17,12);NumberChange(sta_Info[idx].ca_Number,0);   // ��ȭ��ȣ ��� ���� 
      gotoxy(2,13);printf("��                            ��"); 
      gotoxy(2,14);printf("���ּ�:                       ��");gotoxy(10,14);printf("%s",sta_Info[idx].ca_Addr);  
      gotoxy(2,15);printf("��                            ��"); 
      gotoxy(2,16);printf("��������������������������������"); 
   }else if(check == 1){
      gotoxy(38,11);printf(" ��");
      gotoxy(45,6);printf("���������� �̸�  ���� ����������");
      gotoxy(45,7);printf("��                            ��");
      gotoxy(45,8);printf("���̸�:                       ��");
      if(select != 1){
         gotoxy(53,8);printf("%s",sta_Info[idx].ca_Name);
      }
      gotoxy(45,9);printf("��                            ��"); 
      gotoxy(45,10);printf("������:                       ��");
      if(select != 3){
         gotoxy(53,10);printf("%d",sta_Info[idx].ui_Age);
      }      
      gotoxy(45,11);printf("��                            ��"); 
      gotoxy(45,12);printf("����ȭ��ȣ:010-               ��");
      if(select != 2){
         gotoxy(60,12);NumberChange(sta_Info[idx].ca_Number,0);   // ��ȭ��ȣ ��� ����    
      }
      gotoxy(45,13);printf("��                            ��"); 
      gotoxy(45,14);printf("���ּ�:                       ��");
      if(select != 4){
         gotoxy(53,14);printf("%s",sta_Info[idx].ca_Addr);
      }
      gotoxy(45,15);printf("��                            ��"); 
      gotoxy(45,16);printf("��������������������������������"); 
   } 
} 

// �˻� �˶� �Լ� 
void AlarmSearch(int check){   
   gotoxy(36,1);printf("�˻� ���");
   gotoxy(26,2);printf("��������������������������������"); 
   if(check == 0){
      gotoxy(26,3);printf("���̸� :                      ��"); 
   }else if(check == 1) {
      gotoxy(26,3);printf("����ȭ��ȣ:010-               ��"); 
   }else if(check == 2){
      gotoxy(26,3);printf("������ :                      ��"); 
   }else if(check == 3){
      gotoxy(26,3);printf("���ּ� :                      ��"); 
   }
   gotoxy(26,4);printf("��������������������������������");
}

void NumberChange(char* num, int check){
   int s;
   if(check == 1){
      printf("��ȭ��ȣ: 010-");   
   }
   for(s=0;s<8;s++){
      printf("%c",num[s]);
      if(s==3) {
         printf("-");   
      }
   }   
}
