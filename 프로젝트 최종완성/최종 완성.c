#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<windows.h>


#define SIZE 20 //배열크기
#define MAX 10 //최대 10명
#define FAIL 3 //입력실패 제한 횟수 

typedef struct Info//전화번호부
{
   char ca_Name[SIZE];//이름
   char ca_Number[9];//전화번호
   unsigned int ui_Age;//나이
   char ca_Addr[SIZE];//주소
   int i_Auth;  //권한
}Info;

typedef struct Login//로그인
{
   char ca_Name[SIZE];   //사용자 이름   
   char ca_Id[SIZE];   //아이디
   char ca_Pwd[SIZE];  //비밀번호   
   int i_Auth;         //권한
}Login;

Info sta_Info[MAX] = {
   {{"감달현"},{"12345678"},30,{"경기도 여주시"},1},
   {{"감달현"},{"12345678"},30,{"경기도 광주시"},3},
   {{"장은희"},{"11112222"},30,{"경기도 여주시"},3},
   {{"유대균"},{"11112222"},20,{"경기도 광주시"},2}
};
Login sta_Login[MAX]= {
   {"관리자","admin","admin",3},
   {"장은희","jang","3",3},
   {"유대균","yoo","2",2},
   {"감달현","kam","1",1},
};

int alli_Auth=0;   // 로그인 사용자 권한 저장 
char allca_Name[SIZE]="";   // 로그인 사용자 이름 저장
int alli_LoginCnt=4;   // 등록된 사용자 index
int alli_Cnt=4;   // 등록된 전화번호부 index 
/**** 함수 선언부 ****/
void gotoxy(int, int);   // 커서 위치 조정
void setColor(unsigned short, unsigned short); // Text 색 변경 함수 
int login(void);   // 로그인 함수
void Regit(void);   // 사용자 등록 함수 
int PwCheck(void);   // 패스워드 체크 함수
int Login_Menu(void);   // 로그인 메뉴  
int Menu(void);      // Main메뉴 
void Input(void);   // 입력함수  
void Output_page2(void);   // 출력 페이지 처리 함수
void Ouput(void);   //출력함수
int InfoModify(int idx);   //// 정보 수정 선택 함수 
void Edit();   // 데이터 수정 함수  
void Delete();   //데이터 삭제 함수 
void Search();   //데이터 검색 함수
void run();      // 실행 함수 
void Alarm(int);   // 알람 함수
void AlarmModify(int,int,int);   // 수정 화면 알람 함수 
void AlarmSearch(int);   // 검색 알람 함수
void NumberChange(char*,int);   // 전화번호 출력 변경 

/**** Main함수 ****/
int main(void)
{
   run();
   return 0;
}

/**** 함수 구현부 ****/
//커서 위치 조정
void gotoxy(int x, int y){
   COORD Cur;
   Cur.X=x;
   Cur.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

//Text 색 변경 함수 
void setColor(unsigned short text, unsigned short back){
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back<<4));
}

//로그인 함수
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
      Alarm(12);   // 로그인 ID,PW 입력 디자인 
      
      if(j==2){
         gotoxy(22,4);printf("※다음 오류시 프로그램을 자동 종료합니다.※");      
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
               gotoxy(31,16);printf("※PW가 틀렸습니다.※");
               Sleep(1000);
               break; // for(i=0;i<index;i++) 문 종료 상위 for문은 동작함 
            }
         }
         
         if(i == i_Count-1){
            gotoxy(25,16);printf("※입력하신 %s는 없는 ID 입니다.※",ca_TmpID);
            Sleep(1000);
         }
      } //for(i=0;i<index;i++)
   }
   Sleep(1000);
   return -1;   
}

// 사용자 등록 함수
void Regit(void){
   int i;
   Alarm(10);   // 사용자 이름 등록 디자인 
   char tmp[SIZE];
   bool b_Pass = false;
   gotoxy(35,11);scanf("%s",&sta_Login[alli_LoginCnt].ca_Name);

   printf("권한 입력 : \n");
   while(1){
      Alarm(4);
      gotoxy(33,17);scanf("%d",&sta_Login[alli_LoginCnt].i_Auth);
      if(sta_Login[alli_LoginCnt].i_Auth > 0 && sta_Login[alli_LoginCnt].i_Auth < 4){
         break;
      }else{
         gotoxy(18,17);printf("※권한 선택은 1~3 입니다.※");
         Sleep(1000);
         rewind(stdin);
      }
   }
   system("cls");
   gotoxy(24,11);printf("※사용하실 ID와 PW를 생성해 주세요.※");
   Sleep(1000);   
   while(1){
      system("cls");
      Alarm(11);   // 사용자 등록 ID,PW 입력 디자인
      gotoxy(30,10);
      scanf("%s",&tmp);
      for(i=0;i<alli_LoginCnt;i++){
         if( (strcmp(tmp, sta_Login[i].ca_Id)) == 0){
            gotoxy(19,18);printf("※동일한 ID가 있습니다. ID를 새로 입력하세요.※");
            Sleep(1000);
            break;
         }
         if(i >= alli_LoginCnt-1){
            strcpy(sta_Login[alli_LoginCnt].ca_Id,tmp);
            b_Pass = true;
         }
      }//for(i=0;i<alli_LoginCnt;i++)
      if(b_Pass){   // 동일한 ID가 없으면 while루프 빠져나옴 
         break;
      }
   }// while(1)
   
   gotoxy(30,12);scanf("%s",&sta_Login[alli_LoginCnt].ca_Pwd);
   
   do{
      i = PwCheck();
   }while(i != 0);   // pw 재확인시 일치하면 완료되면 종료 
   
   alli_LoginCnt++;   // 사용자 등록 완료시 index증가 
} //void Regit(int idx)

// 패스워드 체크 함수
int PwCheck(void){
   char ca_Password[20]={0};   // password 확인을 위한 입력 변수 
   gotoxy(23,14);printf("PW 재확인 :__________________________");
   gotoxy(35,14);scanf("%s",&ca_Password);       
   
   return strcmp(ca_Password,sta_Login[alli_LoginCnt].ca_Pwd);   // pw 재확인시 입력한 pw가 동일하면 0 return 
} //int PwCheck(int idx)

// 로그인 메뉴
int Login_Menu(void){
   int m;
   system( "cls" );
   Alarm(2);
   scanf("%d",&m);
   return m;
}

// Main 메뉴 
int Menu(void){
   int m;
   Alarm(3);
   scanf("%d",&m);
   return m;
}

//입력함수
void Input(void){
   int i;  //반복문 쓸때 쓰는 변수 
   char ch_ans; //주소 쓸지 안쓸지 Y or N 
   int i_menu1; //출입부 다쓰고 계속 쓸지 돌아갈지 
       
   for(;;){      
      Alarm(13);   // 전화번호부 입력 설명 디자인 출력       
      
      if(alli_Cnt<10){
         Alarm(14);   // 전화번호부 입력 디자인 출력   
         gotoxy(30,9);scanf("%s",&sta_Info[alli_Cnt].ca_Name);            
         for(;;){  
            Alarm(14);   // 전화번호부 입력 디자인 출력
            gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);            
            gotoxy(30,12);
            while (!scanf_s("%d", &sta_Info[alli_Cnt].ui_Age)){   // 숫자만 입력 받기위해 추가             
               setColor(1,12);gotoxy(28,22);printf("※정수만 입력 가능 다시 입력 하세요※\n");
               Sleep(800);
               setColor(0,15);
               Alarm(14);   // 전화번호부 입력 디자인 출력             
               gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);
               gotoxy(30,12);while (getchar() != '\n');
            }
            
            if(sta_Info[alli_Cnt].ui_Age>=0 && sta_Info[alli_Cnt].ui_Age<=120){
               break;
            }else{               
               setColor(1,12);gotoxy(28,22);printf("나이를 다시입력 하세요");
               Sleep(800);
               setColor(0,15);
            }
         }//for(;;)  나이
         rewind(stdin);
         for(;;){
            Alarm(14);   // 전화번호부 입력 디자인 출력
            
            gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);
            gotoxy(30,12);printf("%d",sta_Info[alli_Cnt].ui_Age);
            
            gotoxy(37,15);scanf(" %s",&sta_Info[alli_Cnt].ca_Number);
            if(strlen(sta_Info[alli_Cnt].ca_Number)==8){  //8자리 넘으면 안됨.  
               for(i=0;i<8;i++){
                  if(sta_Info[alli_Cnt].ca_Number[i]>=48 && sta_Info[alli_Cnt].ca_Number[i]<=57){               
                  }
               }//for(i=0;i<8;i++)
               break;
            }//8자리 숫자 
            else{
               setColor(1,12);gotoxy(28,22);printf("전화번호를 다시 입력해주세요.");
               Sleep(800);
               setColor(0,15);
            }
         } //for(;;) 전화번호 
         
         for(;;){
            Alarm(14);   // 전화번호부 입력 디자인 출력               
            gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);
            gotoxy(30,12);printf("%d",sta_Info[alli_Cnt].ui_Age);
            gotoxy(37,15);printf("%s",sta_Info[alli_Cnt].ca_Number);
            
            gotoxy(28,22);printf("주소는 선택입니다. 쓰시겠습니까?(Y/N)");scanf(" %c",&ch_ans);
            if(ch_ans=='Y'||ch_ans=='y'){
               Alarm(14);   // 전화번호부 입력 디자인 출력               
               gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);
               gotoxy(30,12);printf("%d",sta_Info[alli_Cnt].ui_Age);
               gotoxy(37,15);printf("%s",sta_Info[alli_Cnt].ca_Number);
               gotoxy(28,22);printf("도와 시만 입력해 주세요.");
               Sleep(100);
               gotoxy(30,18);scanf(" %[^\n]s",&sta_Info[alli_Cnt].ca_Addr);
               break;
            } else if(ch_ans=='N'||ch_ans=='n'){
               strcpy(sta_Info[alli_Cnt].ca_Addr,"-");
               gotoxy(28,23);printf("주소를 쓰지 않습니다.");
               Sleep(800);
               break;
            } else{ 
                         
                  Alarm(14);   // 전화번호부 입력 디자인 출력                 
                  gotoxy(30,9);printf("%s",sta_Info[alli_Cnt].ca_Name);
                  gotoxy(30,12);printf("%d",sta_Info[alli_Cnt].ui_Age);
                  gotoxy(37,15);printf("%s",sta_Info[alli_Cnt].ca_Number);
                  setColor(1,12);gotoxy(28,22);printf("Y와N 중 하나만 선택하세요.");
                  Sleep(700);setColor(0,15);
            } //if(ch_ans=='Y'||ch_ans=='y')
         }//for(;;) 주소
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
         printf("10명 까지만 입력 가능합니다.\n");
         printf("데이터를 삭제 후 입력해 주세요.");
         break;
      }//if(i_menu1==1)
    }//for(;;)  전화번호부 입력 
}//void Input(void)

// 출력 페이지 처리 함수 
void Output_page2(){
   int i,s,i_back1,i_back2;
   
   for(;;){
      system("cls");
      for(i=0;i<5;i++){
         printf("\n이름: %s\n",sta_Info[i].ca_Name);
         printf("나이: %d\n",sta_Info[i].ui_Age);
         NumberChange(sta_Info[i].ca_Number,1);   // 전화번호 출력 변경 
         printf("\n주소: %s\n",sta_Info[i].ca_Addr);  
         printf("-----------------------------------");                   
      }//for(i=0;i<5;i++)  첫페이지  
      
      Alarm(16);   // 1페이지 돌아가기 디자인 출력 
      gotoxy(73,19);scanf("%d",&i_back1);               
      
      if(i_back1==0){
         Alarm(15);   // 메뉴로 돌아가기 디자인 출력 
         break;
      } //if(i_back1==0)
      
      if(i_back1==2){
         system("cls");
         for(i=5;i<alli_Cnt;i++){                      
            printf("\n이름: %s\n",sta_Info[i].ca_Name);
            printf("나이: %d\n",sta_Info[i].ui_Age);
            NumberChange(sta_Info[i].ca_Number,1);   // 전화번호 출력 변경             
            printf("\n주소: %s\n",sta_Info[i].ca_Addr);  
            printf("-----------------------------------");              
         }//for(i=5;i<alli_Cnt;i++)
         Alarm(17);   // 2페이지 돌아가기 디자인 출력 
         
         
         gotoxy(71,19);scanf("%d",&i_back2);
         if(i_back2==0){
            Alarm(15);   // 메뉴로 돌아가기 디자인 출력 
            break;
         } //if(i_back1==2)
      } //if(i_back==1) 다음페이지 
   }//for(;;)
}//void Output_page2()

//출력함수
void Ouput(void){
   int i_menu;//전화번호 출력 및 되돌아가기 메뉴
   int i;  //for문 돌릴때, 전체 출력할때 사용하는 변수  
   int s;  // for 문 돌릴때, 전화번호 4자리씩 출력할때 사용하는 변수 
   int i_back; //천체출력후 돌아가기 하고 싶을때 쓰는 변수. 
      
   if(alli_Cnt==0){
      system("cls");
      printf("출력할 정보가 없습니다.");
      Sleep(700);
      Alarm(15);   // 메뉴로 돌아가기 디자인 출력 
   }//if(alli_Cnt==0)}
   
    if(alli_Cnt>0){
      for(;;){ 
         system("cls");
         Alarm(8);
         scanf("%d",&i_menu);
         if(i_menu==1){
            gotoxy(30,8);printf("전화 번호부 전체 출력");
            Sleep(700);
            
            system("cls");
            
            if(alli_Cnt<=5){
               for(i=0;i<alli_Cnt;i++){
               printf("\n이름: %s\n",sta_Info[i].ca_Name);
               printf("나이: %d\n",sta_Info[i].ui_Age);
               NumberChange(sta_Info[i].ca_Number,1);   // 전화번호 출력 변경 
               printf("\n주소: %s\n",sta_Info[i].ca_Addr);
               printf("-----------------------------------");
               }//for(i=0;i<=cnt;i++)  
               Alarm(18);   // 입력 돌아가기 디자인 출력
                
                gotoxy(71,19);scanf("%d",&i_back);           
               
                  if(i_back==0){
               Alarm(15);   // 메뉴로 돌아가기 디자인 출력 
               break;               
                  }
            } //if(alli_Cnt<=5)
            
            //---------------------------------------1~4명 일때 페이지수 1개--------------------------------
            if(alli_Cnt>5 && alli_Cnt<=10){
               Output_page2();               
            }//if(alli_Cnt>4 && alli_Cnt<=8) 두 페이지에 출력 
         
         }//if(menu_1==1)
         
         if(i_menu==2){
            Alarm(15);   // 메뉴로 돌아가기 디자인 출력 
            break;
         }      
      }//for(;;)   
    }//   if(alli_Cnt>0)
}//void Ouput(void)

// 정보 수정 선택 함수 
int InfoModify(int idx){
   int i_Select;
   
   Alarm(5);
   scanf("%d",&i_Select);
   system("cls");
   rewind(stdin);
   
   if(i_Select == 1){
      AlarmModify(0,idx,i_Select);   // 수정전 데이터 출력       
      AlarmModify(1,idx,i_Select);   // 수정할 데이터 출력 
      
      gotoxy(53,8);scanf("%s",&sta_Info[idx].ca_Name);
   }else if(i_Select == 2){
      AlarmModify(0,idx,i_Select);   // 수정전 데이터 출력       
      AlarmModify(1,idx,i_Select);   // 수정할 데이터 출력 
      
         gotoxy(60,12);scanf("%s",&sta_Info[idx].ca_Number);
   }else if(i_Select == 3){
      AlarmModify(0,idx,i_Select);   // 수정전 데이터 출력       
      AlarmModify(1,idx,i_Select);   // 수정할 데이터 출력 
      
      gotoxy(53,10);
      while(!scanf_s("%d", &sta_Info[idx].ui_Age)){   // 숫자만 입력 받기위해 추가 
        gotoxy(20,20);printf("※정수만 입력 가능 다시 입력 하세요.※");
        AlarmModify(0,idx,i_Select);   // 수정전 데이터 출력       
         AlarmModify(1,idx,i_Select);   // 수정할 데이터 출력 
        while (getchar() != '\n');
        gotoxy(53,10);
      }
   }else if(i_Select == 4){
      AlarmModify(0,idx,i_Select);   // 수정전 데이터 출력       
      AlarmModify(1,idx,i_Select);   // 수정할 데이터 출력 
      
      gotoxy(53,14);scanf(" %[^\n]s",&sta_Info[idx].ca_Addr);
   }else if(i_Select == 5){
         gotoxy(20,10);printf("※수정을 취소 하였습니다.※");
//      printf("수정을 취소 하였습니다.\n");
      Sleep(1000);
      system( "cls" );
 return -1;
   }else{
      system( "cls" );
      printf("선택 가능 번호는 1~5 까지 입니다.\n");
      InfoModify(idx);
   }
   return 0;
}

//데이터 수정 함수  
void Edit(){
   int i,i_Pass,i_Idx=0,i_Mod; // i_Mod 수정할 전화번호부 선택 변수 
   int ia_ModIdx[MAX] = {0}; // modIdx : 수정할 전화번호부의 index번호  
   gotoxy(30,10);printf("수정할");Sleep(500);
   Alarm(19);   // 가이드 메시지 
      
   for(;;){
      system("cls");
      setColor(0,15);
      printf("\n--------------------------수정 가능한 전화번호부 목록------------------------\n");
      for(i=0;i<alli_Cnt;i++){
         if(sta_Info[i].i_Auth <= alli_Auth){
            ia_ModIdx[i_Idx] = i;
            printf("%d. 이름 : %s , ",i_Idx+1,sta_Info[i].ca_Name);
            NumberChange(sta_Info[i].ca_Number,1);   // 전화번호 출력 변경 
            printf(" , 나이 : %d , 주소 : %s\n",sta_Info[i].ui_Age,sta_Info[i].ca_Addr);
            printf("-----------------------------------------------------------------------------\n");
            i_Idx++;
         } //if(ph[i].auth <= auth)      
      } //for(i=0;i<number;i++)
      if(i_Idx == 0){
         gotoxy(20,15);printf("※수정 가능한 전화번호가 없습니다.※");
         Sleep(1000);
         break;
      }   
      
      printf("----------------------메인으로 돌아가려면 0을 입력하세요.--------------------\n");
      if(i_Idx != 0){
         printf("번호입력>>>>> ");
         scanf("%d",&i_Mod);
         if(i_Mod == 0){
            Alarm(15);   // 메뉴로 돌아가기 디자인 출력 
            break;
         } else if(i_Idx < i_Mod){
            gotoxy(24,24);printf("※잘못된 숫자를 선택하셨습니다.※");
            Sleep(1000);
            system( "cls" );
            i_Idx = 0;
            continue;
         }
         system( "cls" );
         i_Pass = InfoModify(ia_ModIdx[i_Mod-1]);   // 인자값은 전체 번호 리스트의 수정할 전화번호의 index임. 
         if(i_Pass == -1){
            break;
         }
         i_Idx = 0;
         system( "cls" );
      }
   }
   
//   Sleep(1000);
} 

//데이터 삭제 함수 
void Delete(){
   int i,j;
   int i_Delete;
   int i_Cnt[MAX];
   int i_Scnt=0;
   int i_Check_Auth_Cnt=0;
   char ca_Tmp[SIZE];
   
      
    gotoxy(30,10);printf("삭제할");Sleep(500);
    Alarm(19);   //가이드 메시지    
   
   for(;;)
   {
      system("cls");
      printf("\n                        삭제 가능한 전화번호부 목록\n");
      printf("-----------------------------------------------------------------------------\n");
      
      for(i=0;i<alli_Cnt;i++) {
         if(alli_Auth >= sta_Info[i].i_Auth) {
            i_Cnt[i_Scnt]=i;
            i_Scnt++;
            printf("%d. 이름 : %s, ",i_Check_Auth_Cnt+1,sta_Info[i].ca_Name);
            NumberChange(sta_Info[i].ca_Number,1);   // 전화번호 출력 변경             
            printf(", 나이 : %d, 주소 : %s\n",sta_Info[i].ui_Age,sta_Info[i].ca_Addr);
            printf("-----------------------------------------------------------------------------\n");
            
            i_Check_Auth_Cnt++;
         }
      } //for(i=0;i<alli_Cnt;i++)
        if(i_Check_Auth_Cnt==0)   {
           gotoxy(20,15);printf("삭제할 수 있는 전화번호부가 없습니다.\n");
           Sleep(1000);
            return;
      }
      
         printf("번호입력(0번 종료)>>>>"); scanf("%d",&i_Delete);
      
         if(i_Delete <= i_Check_Auth_Cnt && i_Delete>0) {   // i_Delete>=0 수정 삭제할 번호는 0보다 큰값이어야 함. 
           alli_Cnt--;
           for(i=0;i<alli_Cnt;i++){
               if(i >= i_Cnt[i_Delete-1]) {
                     sta_Info[i] = sta_Info[i+1];
            }
         } //for(i=0;i<alli_Cnt;i++)
        gotoxy(33,23);printf("※%d번 삭제완료※",i_Delete);
        Sleep(1000);
        break;
      } 
        else if(i_Delete==0){
           Alarm(15);   // 메뉴로 돌아가기 디자인 출력 
           break;           
        }
        else {
         printf("잘못된 숫자를 선택하셨습니다.\n");
         Sleep(1000);
         i_Check_Auth_Cnt=0;
      }
   }
}

//데이터 검색 함수 
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
         AlarmSearch(0);   // 검섹모드 디자인 출력 
         gotoxy(36,3);scanf("%s",&ca_Tmp);
         for(i=0;i<alli_Cnt;i++)   {
            if(strcmp(sta_Info[i].ca_Name,ca_Tmp)==0){
               i_Cnt[i_Scnt]=i;
               i_Scnt++;
            }
         } //for(i=0;i<alli_Cnt;i++)
         for(i=0;i<i_Scnt;i++) {         
            gotoxy(1,7+i);printf("%d. 이름 : %s┃",i+1,sta_Info[i_Cnt[i]].ca_Name);            
            NumberChange(sta_Info[i_Cnt[i]].ca_Number,1);   // 전화번호 출력 변경             
            printf("┃나이 : %d┃주소 : %s┃\n",sta_Info[i_Cnt[i]].ui_Age,sta_Info[i_Cnt[i]].ca_Addr);
            printf("--------------------------------------------------------------------------------");
         } //for(i=0;i<i_Scnt;i++)
         if(i_Scnt==0) {
            gotoxy(30,5);printf("※찾는 이름이 없습니다.※");
            Sleep(600);
            system("cls");
         }   
         Alarm(20);
         gotoxy(1,23);printf("돌아가기(아무키)"); scanf("%s",&ca_back);
         i_Scnt=0;   
      }//if(i_Search_Menu==1) 아름검색 끝.
      else if(i_Search_Menu==2){
         AlarmSearch(1);   // 감섹모드 디자인 출력 
         gotoxy(41,3);scanf("%s",&ca_Tmp);
         for(i=0;i<alli_Cnt;i++)   {
            if(strcmp(sta_Info[i].ca_Number,ca_Tmp)==0)   {
               i_Cnt[i_Scnt]=i;
               i_Scnt++;
            }
         }
         
         for(i=0;i<i_Scnt;i++){
            gotoxy(1,7+i);printf("%d. 이름 : %s┃",i+1,sta_Info[i_Cnt[i]].ca_Name);            
            NumberChange(sta_Info[i_Cnt[i]].ca_Number,1);   // 전화번호 출력 변경             
            printf("┃나이 : %d┃주소 : %s┃\n",sta_Info[i_Cnt[i]].ui_Age,sta_Info[i_Cnt[i]].ca_Addr);
            printf("--------------------------------------------------------------------------------");
         }
         if(i_Scnt==0){
            gotoxy(30,5);printf("※찾는 번호가 없습니다.※");  
            Sleep(600);
            system("cls");    
         }
         Alarm(20);
         gotoxy(1,23);printf("돌아가기(아무키)"); scanf("%s",&ca_back);
         i_Scnt=0;
      } // else if(i_Search_Menu==2)
      else if(i_Search_Menu==3){
         AlarmSearch(2);   // 감섹모드 디자인 출력 
         gotoxy(36,3);
         while (!scanf_s("%d", &ui_Tmp)){   // 숫자만 입력 받기위해 추가          
            gotoxy(25,5);printf("※정수만 입력 가능 다시 입력 하세요.※");
            Sleep(500);
            system("cls");
            gotoxy(36,3);
            AlarmSearch(2);   // 감섹모드 디자인 출력 
            gotoxy(36,3);while (getchar() != '\n');
         }
         
         for(i=0;i<alli_Cnt;i++){
            if(sta_Info[i].ui_Age==ui_Tmp){
               i_Cnt[i_Scnt]=i;
               i_Scnt++;
            }
         }
         
         for(i=0;i<i_Scnt;i++){
            gotoxy(1,7+2*i);printf("%d. 이름 : %s┃",i+1,sta_Info[i_Cnt[i]].ca_Name);            
            NumberChange(sta_Info[i_Cnt[i]].ca_Number,1);   // 전화번호 출력 변경             
            printf("┃나이 : %d┃주소 : %s┃\n",sta_Info[i_Cnt[i]].ui_Age,sta_Info[i_Cnt[i]].ca_Addr);
            printf("--------------------------------------------------------------------------------");
         }
         
         if(i_Scnt==0){
            gotoxy(30,5);printf("※찾는 나이가 없습니다.※");     
            Sleep(600);
            system("cls");  
         }
         Alarm(20);
         gotoxy(1,23);printf("돌아가기(아무키)"); scanf("%s",&ca_back);
         i_Scnt=0;
      }
      else if(i_Search_Menu==4) {
         AlarmSearch(3);   // 감섹모드 디자인 출력 
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
            gotoxy(1,7+2*i);printf("%d. 이름 : %s┃",i+1,sta_Info[i_Cnt[i]].ca_Name);            
            NumberChange(sta_Info[i_Cnt[i]].ca_Number,1);   // 전화번호 출력 변경             
            printf("┃나이 : %d┃주소 : %s┃\n",sta_Info[i_Cnt[i]].ui_Age,sta_Info[i_Cnt[i]].ca_Addr);
            printf("--------------------------------------------------------------------------------");
         }
         
         if(i_Scnt==0){
            gotoxy(30,5);printf("찾는 주소가 없습니다.\n");
            Sleep(600);
            system("cls");   
         }
         Alarm(20);
         gotoxy(1,23);printf("돌아가기(아무키)");scanf("%s",&ca_back);
         i_Scnt=0;
      }
      else if(i_Search_Menu==5){
         Alarm(15);   // 메뉴로 돌아가기 디자인 출력 
         break;
      }
      else{
         Alarm(7);   // 메뉴선택 오류 메시지 출력 
         Sleep(1000);
      }
   } // for(;;)
}

// 실행 함수 
void run(){
   int i_Login_Menu;//로그인메뉴변수
   int i_Menu;//메인메뉴
   int i_LoginIndex; //로그인 사용자 index 번호
   
   for(;;){ //프로그램시작   
      i_Login_Menu=Login_Menu();//메뉴함수호출후 메뉴리턴
      system( "cls" ); //  - kam 추가
      if(i_Login_Menu==1)   {
         i_LoginIndex=login();
         if(i_LoginIndex == -1){   // 로그인 3회 실패시 프로그램 종료             
            ("로그인 3회 실패하였습니다.\n");
         Alarm(21);
            break;
         }
         alli_Auth=sta_Login[i_LoginIndex].i_Auth;
         strcpy(allca_Name,sta_Login[i_LoginIndex].ca_Name);
         Alarm(1);   // 로그인 알람
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
                  gotoxy(20,10);printf("※현재 권한으로는 검색이 불가능합니다.※");
                  Sleep(1000);
               }
            }else if(i_Menu==6) {
               Alarm(0);   // 로그아웃 메시지 출력 - kam 추가
               Sleep(2000);
               setColor(7,0);
               break;
            }else{
               Alarm(7);        
               Sleep(1000);
            }
         } //for(;;)   Main메뉴 
      }else if(i_Login_Menu==2){
         Regit();
        system( "cls" );
        gotoxy(25,10);printf("※사용자등록이 완료되었습니다.※");
         Sleep(1000);
      }else if(i_Login_Menu==3)
      {         
         Alarm(21);   // 종료인사 메시지 
         Sleep(1000);
         break;
      }else{
         Alarm(7);
         Sleep(1000);
      } //if(i_Login_Menu==1)
   } // for(;;) 전체 프로그램 
}

// 알람 함수
void Alarm(int check){
   switch(check){
      case 0:
            printf("%s 님이 로그아웃 하셨습니다.\n",allca_Name);
            setColor(0,15);
            gotoxy(10,7);printf("  ■■        ■      ■■■  ■■■    ■■■  ■  ■    ■    ");
            gotoxy(10,8);printf("■    ■      ■      ■  ■  ■  ■    ■  ■  ■  ■    ■    ");
            gotoxy(10,9);printf("■    ■      ■      ■  ■  ■■■    ■  ■  ■  ■  ■■■  "); 
         gotoxy(10,10);printf("■■■■      ■      ■  ■      ■    ■  ■  ■  ■    ■    ");
            gotoxy(10,11);printf("■■■■      ■      ■  ■      ■    ■  ■  ■  ■    ■    ");
            gotoxy(10,12);printf("■■■■      ■■■  ■■■  ■■■    ■■■  ■■■    ■■  ");
            break;
      case 1:
         if(alli_Auth == 1){
            setColor(7,2);
            printf("(일반사용자)");
            setColor(7,0);
         }else if(alli_Auth == 2){
            setColor(7,5);
            printf("(보조관리자)");
            setColor(7,0);
         }else if(alli_Auth == 3){
            setColor(7,4);
            printf("(관리자)");
            setColor(7,0);   
         }         
            printf("%s 님이 로그인 하셨습니다.\n",allca_Name);
            setColor(0,15);
            gotoxy(18,7);printf("  ■■        ■      ■■■  ■■■    ■        ");
            gotoxy(18,8);printf("■    ■      ■      ■  ■  ■  ■        ■■■");
            gotoxy(18,9);printf("■    ■      ■      ■  ■  ■■■    ■  ■  ■"); 
            gotoxy(18,10);printf("■■■■      ■      ■  ■      ■    ■  ■  ■");
            gotoxy(18,11);printf("■■■■      ■      ■  ■      ■    ■  ■  ■");
            gotoxy(18,12);printf("■■■■      ■■■  ■■■  ■■■    ■  ■  ■");
         break;
      case 2:
         gotoxy(35,5);printf(" 메    뉴");
         gotoxy(28,6);printf("┏━━━━━━━━━━┓");
         gotoxy(28,7);printf("┃1.   로  그  인     ┃");
         gotoxy(28,8);printf("┠━━━━━━━━━━┫");
         gotoxy(28,9);printf("┃2.   사용자등록     ┃");
         gotoxy(28,10);printf("┠━━━━━━━━━━┫");
         gotoxy(28,11);printf("┃3.    종    료      ┃");
         gotoxy(28,12);printf("┗━━━━━━━━━━┛");
         gotoxy(28,13);printf("선택>>> "); 
         break;
       case 3:
         system( "cls" );
         gotoxy(28,5);printf("┏━━━━━━메뉴━━━━━━┓");
         gotoxy(28,6);printf("┃                            ┃");
         gotoxy(28,7);printf("┃ 1.   전화번호부 입력       ┃");
         gotoxy(28,8);printf("┃                            ┃");
         gotoxy(28,9);printf("┃ 2.   전화번호부 수정       ┃");
         gotoxy(28,10);printf("┃                            ┃");
         gotoxy(28,11);printf("┃ 3.   전화번호부 삭제       ┃");
         gotoxy(28,12);printf("┃                            ┃");
         gotoxy(28,13);printf("┃ 4.  전화번호부 전체보기    ┃");
         gotoxy(28,14);printf("┃                            ┃");
         gotoxy(28,15);printf("┃ 5.   전화번호부 찾기       ┃");
         gotoxy(28,16);printf("┃                            ┃");
         gotoxy(28,17);printf("┃ 6.     로 그 아 웃         ┃");
         gotoxy(28,18);printf("┗━━━━━━━━━━━━━━┛");
         gotoxy(28,19);printf(">>>>> ");
         break;
      case 4:
         system("cls");
         gotoxy(18,6);printf("┏━━━━━━━━━사용자  등록━━━━━━━━┓");
         gotoxy(18,7);printf("┃                                              ┃");
         gotoxy(18,8);printf("┃  ┏━━━━━━━권한선택━━━━━━━━┓  ┃");
         gotoxy(18,9);printf("┃  ┃                                      ┃  ┃");
         gotoxy(18,10);printf("┃  ┃      1.      사용자 권한             ┃  ┃");
         gotoxy(18,11);printf("┃  ┃                                      ┃  ┃ ");
         gotoxy(18,12);printf("┃  ┃      2.    보조관리자 권한           ┃  ┃");
         gotoxy(18,13);printf("┃  ┃                                      ┃  ┃");
         gotoxy(18,14);printf("┃  ┃      3.     관리자 권한              ┃  ┃");
         gotoxy(18,15);printf("┃  ┗━━━━━━━━━━━━━━━━━━━┛  ┃");
         gotoxy(18,16);printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
         gotoxy(19,17);printf("권한선택>>>>> ");
         break;
      case 5:
         gotoxy(27,6);printf("┏━━━━수정 항목 선택━━━┓");
         gotoxy(27,7);printf("┃                            ┃");
         gotoxy(27,8);printf("┃ 1.      이름 수정          ┃");
         gotoxy(27,9);printf("┃                            ┃");
         gotoxy(27,10);printf("┃ 2.    전화번호 수정        ┃");
         gotoxy(27,11);printf("┃                            ┃");
         gotoxy(27,12);printf("┃ 3.      나이 수정          ┃");
         gotoxy(27,13);printf("┃                            ┃");
         gotoxy(27,14);printf("┃ 4.      주소 수정          ┃");
         gotoxy(27,15);printf("┃                            ┃");
         gotoxy(27,16);printf("┃ 5.      수정 취소          ┃");
         gotoxy(27,17);printf("┃                            ┃");   
         gotoxy(27,18);printf("┗━━━━━━━━━━━━━━┛");
         gotoxy(27,19);printf(">>>>> "); 
         break;
      case 6:
         gotoxy(28,7);printf("┏━━━━━찾기  메뉴━━━━┓");
         gotoxy(28,8);printf("┃                            ┃"); 
         gotoxy(28,9);printf("┃ 1.     이름으로 검색       ┃");
         gotoxy(28,10);printf("┃                            ┃");
         gotoxy(28,11);printf("┃ 2.   전화번호로  검색      ┃");
         gotoxy(28,12);printf("┃                            ┃");
         gotoxy(28,13);printf("┃ 3.     나이로 검색         ┃");
         gotoxy(28,14);printf("┃                            ┃");
         gotoxy(28,15);printf("┃ 4.   주소로 검색(도,시)    ┃");
         gotoxy(28,16);printf("┃                            ┃");
         gotoxy(28,17);printf("┃ 5.      메인 메뉴          ┃");
         gotoxy(28,18);printf("┗━━━━━━━━━━━━━━┛");
         gotoxy(28,19);printf(">>>>> ");
         break;
      case 7:
         rewind(stdin);   // 숫자선택시 문자로 입력이 들어오면 buffer 지우기 위해 사용 
         printf("메뉴 선택 오류\n");
         break;
      case 8:
         gotoxy(27,8);printf("┏━━━━전화 번호 출력━━━━┓");
         gotoxy(27,9);printf("┃                              ┃");
         gotoxy(27,10);printf("┃ 1.     전체 전화번호 출력    ┃");
         gotoxy(27,11);printf("┃                              ┃");  
         gotoxy(27,12);printf("┃ 2.       돌 아 가 기         ┃");
         gotoxy(27,13);printf("┃                              ┃");
         gotoxy(27,14);printf("┗━━━━━━━━━━━━━━━┛") ;
         gotoxy(27,15);printf(">>>>> ");
         break;
      case 9:
         system("cls");
         gotoxy(28,7);printf("┏━━━━━━━━━━━┓");
         gotoxy(28,8);printf("┃                      ┃");
         gotoxy(28,9);printf("┃  1. 계속 입력하기    ┃");
         gotoxy(28,10);printf("┃                      ┃");
         gotoxy(28,11);printf("┃  2.  돌 아 가 기     ┃");
         gotoxy(28,12);printf("┃                      ┃");
         gotoxy(28,13);printf("┗━━━━━━━━━━━┛");
         gotoxy(28,14);printf(">>>>> ");
         break;
      case 10:
         gotoxy(18,6);printf("┏━━━━━━━━━사용자  등록━━━━━━━━┓");
         gotoxy(18,7);printf("┃                                              ┃");
         gotoxy(18,8);printf("┃                                              ┃");
         gotoxy(18,9);printf("┃                                              ┃");      
         gotoxy(18,10);printf("┃  ┏━━━━━━━━━━━━━━━━━━━┓  ┃");
         gotoxy(18,11);printf("┃  ┃이름 입력:                            ┃  ┃");
         gotoxy(18,12);printf("┃  ┗━━━━━━━━━━━━━━━━━━━┛  ┃");
         gotoxy(18,13);printf("┃                                              ┃");
         gotoxy(18,14);printf("┃                                              ┃");
         gotoxy(18,15);printf("┃                                              ┃");
         gotoxy(18,16);printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");   
         break; 
      case 11:
         gotoxy(18,6);printf("┏━━━━━━━━━사용자  등록━━━━━━━━┓");
         gotoxy(18,7);printf("┃                                              ┃");
         gotoxy(18,8);printf("┃                                              ┃");
         gotoxy(18,9);printf("┃  ┏━━━━━━━━━━━━━━━━━━━┓  ┃");
         gotoxy(18,10);printf("┃  ┃  ID :                                ┃  ┃");
         gotoxy(18,11);printf("┃  ┣━━━━━━━━━━━━━━━━━━━┫  ┃");
         gotoxy(18,12);printf("┃  ┃  PW :                                ┃  ┃");
         gotoxy(18,13);printf("┃  ┗━━━━━━━━━━━━━━━━━━━┛  ┃"); 
         gotoxy(18,14);printf("┃                                              ┃");
         gotoxy(18,15);printf("┃                                              ┃");
         gotoxy(18,16);printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛"); 
         break;
      case 12:
         system("cls");
         gotoxy(25,6);printf("┏Login ━━━━━━━━━━━━┓");
         gotoxy(25,7);printf("┃                              ┃");
         gotoxy(25,8);printf("┃ ┏━━━━━━━━━━┓     ┃");
         gotoxy(25,9);printf("┃ ┃ID:                 ┃     ┃");
         gotoxy(25,10);printf("┃ ┠━━━━━━━━━━┫     ┃");
         gotoxy(25,11);printf("┃ ┃PW:                 ┃     ┃");
         gotoxy(25,12);printf("┃ ┗━━━━━━━━━━┛     ┃");
         gotoxy(25,13);printf("┃                              ┃");
         gotoxy(25,14);printf("┗━━━━━━━━━━━━━━━┛"); 
         break;
      case 13:
         system("cls");
         gotoxy(30,8);printf("전화번호부 입력은");Sleep(800);
         gotoxy(30,10);printf("이름");Sleep(800);
         gotoxy(36,10);printf("나이");Sleep(800); 
         gotoxy(42,10);printf("전화번호");Sleep(800);
         gotoxy(52,10);printf("주소");  Sleep(800);
         gotoxy(30,12);printf("순으로 입력하시면 됩니다."); Sleep(800); 
         break;
      case 14:
         system("cls");
         gotoxy(18,6);printf("┏━━━━━━━━전화번호부  입력━━━━━━━━┓");
         gotoxy(18,7);printf("┃                                                ┃");
         gotoxy(18,8);printf("┃  ┏━━━━━━━━━━━━━━━━━━━━┓  ┃");
         gotoxy(18,9);printf("┃  ┃이름:                                   ┃  ┃");
         gotoxy(18,10);printf("┃  ┗━━━━━━━━━━━━━━━━━━━━┛  ┃");
         gotoxy(18,11);printf("┃  ┏━━━━━━━━━━━━━━━━━━━━┓  ┃");
         gotoxy(18,12);printf("┃  ┃나이:                                   ┃  ┃");
         gotoxy(18,13);printf("┃  ┗━━━━━━━━━━━━━━━━━━━━┛  ┃");
         gotoxy(18,14);printf("┃  ┏━━━━━━━━━━━━━━━━━━━━┓  ┃"); 
         gotoxy(18,15);printf("┃  ┃전화번호:010-                           ┃  ┃");
         gotoxy(18,16);printf("┃  ┗━━━━━━━━━━━━━━━━━━━━┛  ┃");
         gotoxy(18,17);printf("┃  ┏━━━━━━━━━━━━━━━━━━━━┓  ┃"); 
         gotoxy(18,18);printf("┃  ┃주소:                                   ┃  ┃");
         gotoxy(18,19);printf("┃  ┗━━━━━━━━━━━━━━━━━━━━┛  ┃");
         gotoxy(18,20);printf("┗━━━━━━━━━━━━━━━━━━━━━━━━┛"); 
         break;         
        case 15:
         system("cls");
         gotoxy(28,10);printf("┏━━━━━━━━━━━━━┓"); 
         gotoxy(28,11);printf("┃ ※메뉴로 되돌아갑니다.※ ┃");
         gotoxy(28,12);printf("┗━━━━━━━━━━━━━┛"); 
         Sleep(800);
         break;
      case 16:
         gotoxy(36,0);printf("┏━━━━━━━━━━━━━━━━━━━┓");
         gotoxy(36,1);printf("┃                                      ┃"); 
         gotoxy(36,2);printf("┃                                      ┃");
         gotoxy(36,3);printf("┃                                      ┃");
         gotoxy(36,4);printf("┃                                      ┃");
         gotoxy(36,5);printf("┃                                      ┃");
         gotoxy(36,6);printf("┃          ■              ■          ┃");
         gotoxy(36,7);printf("┃        ■                  ■        ┃");
         gotoxy(36,8);printf("┃      ■■■■■■  ■■■■■■      ┃");
         gotoxy(36,9);printf("┃        ■                  ■        ┃");
         gotoxy(36,10);printf("┃          ■              ■          ┃");
         gotoxy(36,11);printf("┃                                      ┃");
         gotoxy(36,12);printf("┃                                      ┃");
         gotoxy(36,13);printf("┃                                      ┃");
         gotoxy(36,14);printf("┃                                      ┃");
         gotoxy(36,15);printf("┃                                      ┃");
         gotoxy(36,16);printf("┃                                      ┃");
         gotoxy(36,17);printf("┣━━━━━━━━━━━━━━━━━━━┫");
         gotoxy(36,18);printf("┃                                      ┃");
         gotoxy(36,19);printf("┃     돌아가기(0번),다음페이지(2번)    ┃");
         gotoxy(36,20);printf("┗━━━━━━━━━━━━━━━━━━━┛"); 
         break;
      case 17: 
           gotoxy(36,0);printf("┏━━━━━━━━━━━━━━━━━━━┓");
           gotoxy(36,1);printf("┃                                      ┃"); 
           gotoxy(36,2);printf("┃                                      ┃");
           gotoxy(36,3);printf("┃                                      ┃");
           gotoxy(36,4);printf("┃                                      ┃");
           gotoxy(36,5);printf("┃                                      ┃");
           gotoxy(36,6);printf("┃          ■              ■          ┃");
           gotoxy(36,7);printf("┃        ■                  ■        ┃");
           gotoxy(36,8);printf("┃      ■■■■■■  ■■■■■■      ┃");
           gotoxy(36,9);printf("┃        ■                  ■        ┃");
           gotoxy(36,10);printf("┃          ■              ■          ┃");
           gotoxy(36,11);printf("┃                                      ┃");
           gotoxy(36,12);printf("┃                                      ┃");
           gotoxy(36,13);printf("┃                                      ┃");
           gotoxy(36,14);printf("┃                                      ┃");
           gotoxy(36,15);printf("┃                                      ┃");
           gotoxy(36,16);printf("┃                                      ┃");
           gotoxy(36,17);printf("┣━━━━━━━━━━━━━━━━━━━┫");
           gotoxy(36,18);printf("┃                                      ┃");
           gotoxy(36,19);printf("┃    이전페이지(1번),돌아가기(0번)     ┃");
           gotoxy(36,20);printf("┗━━━━━━━━━━━━━━━━━━━┛"); 
           break; 
        case 18:
            gotoxy(36,0);printf("┏━━━━━━━━━━━━━━━━━━━┓");
            gotoxy(36,1);printf("┃                                      ┃"); 
            gotoxy(36,2);printf("┃                                      ┃");
            gotoxy(36,3);printf("┃                                      ┃");
            gotoxy(36,4);printf("┃                                      ┃");
            gotoxy(36,5);printf("┃              ■                      ┃");
            gotoxy(36,6);printf("┃            ■                        ┃");
            gotoxy(36,7);printf("┃          ■                          ┃");
            gotoxy(36,8);printf("┃        ■■■■■■■■■■■        ┃");
            gotoxy(36,9);printf("┃          ■                          ┃");
            gotoxy(36,10);printf("┃            ■                        ┃");
            gotoxy(36,11);printf("┃              ■                      ┃");
            gotoxy(36,12);printf("┃                                      ┃");
            gotoxy(36,13);printf("┃                                      ┃");
            gotoxy(36,14);printf("┃                                      ┃");
            gotoxy(36,15);printf("┃                                      ┃");
            gotoxy(36,16);printf("┃                                      ┃");
            gotoxy(36,17);printf("┣━━━━━━━━━━━━━━━━━━━┫");
            gotoxy(36,18);printf("┃                                      ┃");
            gotoxy(36,19);printf("┃      돌아가려면(0번을 누르세요)      ┃");
            gotoxy(36,20);printf("┗━━━━━━━━━━━━━━━━━━━┛");
            break;
        case 19:           
         gotoxy(37,10);printf("정보의");Sleep(500);
         gotoxy(30,12);printf("번호를");Sleep(500);
         gotoxy(37,12);printf("입력하세요.");Sleep(500);
         gotoxy(30,13);printf("━");Sleep(200);gotoxy(32,13);printf("━");Sleep(200);gotoxy(34,13);printf("━");Sleep(200);
         gotoxy(28,12);printf("★");Sleep(800);
         break;
         
         case 20:
            gotoxy(23,19);printf("■■      ■      ■■  ■  ■        ■      ");
            gotoxy(23,20);printf("■  ■  ■  ■  ■      ■  ■      ■        ");
            gotoxy(23,21);printf("■■    ■■■  ■      ■■      ■  ■■■■");
            gotoxy(23,22);printf("■  ■  ■  ■  ■      ■  ■      ■        ");   
            gotoxy(23,23);printf("■■    ■  ■    ■■  ■  ■        ■      ");
            break;
        case 21:
           system("cls");
           	printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
		 		printf("\n                            종료합니다\n");
		 		system("cls");	
		 		printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("  ┌─☆┐");
		 		printf("\n┌┘▧▨└┐\n"); 
		 		printf("└◎──◎┘。˚ 。˚ 。");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("    ┌─☆┐");
		 		printf("\n  ┌┘▧▨└┐\n"); 
		 		printf("  └◎──◎┘。˚ 。˚");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("      ┌─☆┐");
		 		printf("\n    ┌┘▧▨└┐\n"); 
		 		printf("    └◎──◎┘。˚ 。˚");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(100); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("        ┌─☆┐");
		 		printf("\n      ┌┘▧▨└┐\n"); 
		 		printf("      └◎──◎┘。˚ 。");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(100); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("          ┌─☆┐");
		 		printf("\n        ┌┘▧▨└┐\n"); 
		 		printf("        └◎──◎┘。˚ ");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(100);
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("            ┌─☆┐");
		 		printf("\n          ┌┘▧▨└┐\n"); 
		 		printf("          └◎──◎┘。˚");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(100); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("              ┌─☆┐");
		 		printf("\n            ┌┘▧▨└┐\n"); 
		 		printf("            └◎──◎┘。");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("                ┌─☆┐");
		 		printf("\n              ┌┘▧▨└┐\n"); 
		 		printf("              └◎──◎┘");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("■■                ┌─☆┐");
		 		printf("\n■─              ┌┘▧▨└┐\n"); 
		 		printf("■■              └◎──◎┘");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("   ■ ■■               ┌─☆┐");
		 		printf("\n ■   ■─             ┌┘▧▨└┐\n"); 
		 		printf(" ■   ■■             └◎──◎┘");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("■   ■ ■ ■■               ┌─☆┐");
		 		printf("\n■■   ■   ■─             ┌┘▧▨└┐\n"); 
		 		printf("■■   ■   ■■             └◎──◎┘");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("    ■    ■ ■ ■■               ┌─☆┐");
		 		printf("\n    ■■   ■   ■─             ┌┘▧▨└┐\n"); 
		 		printf("    ■■   ■   ■■             └◎──◎┘");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("        ■    ■ ■ ■■               ┌─☆┐");
		 		printf("\n        ■■   ■   ■─             ┌┘▧▨└┐\n"); 
		 		printf("        ■■   ■   ■■             └◎──◎┘");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("             ■    ■ ■ ■■               ┌─☆┐");
		 		printf("\n             ■■   ■   ■─             ┌┘▧▨└┐\n"); 
		 		printf("             ■■   ■   ■■             └◎──◎┘");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("                   ■    ■ ■ ■■               ┌─☆┐");
		 		printf("\n                   ■■   ■   ■─             ┌┘▧▨└┐\n"); 
		 		printf("                   ■■   ■   ■■             └◎──◎┘");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("                         ■    ■ ■ ■■               ┌─☆┐");
		 		printf("\n                         ■■   ■   ■─             ┌┘▧▨└┐\n"); 
		 		printf("                         ■■   ■   ■■             └◎──◎┘");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(50); 
				system("cls");
				printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");printf("\n");
				printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n"); 
		 		printf("                             ■    ■ ■ ■■               ┌─☆┐");
		 		printf("\n                             ■■   ■   ■─             ┌┘▧▨└┐\n"); 
		 		printf("                             ■■   ■   ■■             └◎──◎┘");
		 		printf("\n▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒*▒\n");
				Sleep(1000); 
				system("cls");
           break;
        default:
            break;         
   }
} 

// 수정 화면 알람 함수 
void AlarmModify(int check, int idx, int select){
   if(check == 0){
      gotoxy(2,6);printf("┏━━━━수정 전 정보━━━━┓");
      gotoxy(2,7);printf("┃                            ┃");
      gotoxy(2,8);printf("┃이름:                       ┃");gotoxy(10,8);printf("%s",sta_Info[idx].ca_Name);
      gotoxy(2,9);printf("┃                            ┃"); 
      gotoxy(2,10);printf("┃나이:                       ┃");gotoxy(10,10);printf("%d",sta_Info[idx].ui_Age);
      gotoxy(2,11);printf("┃                            ┃"); 
      gotoxy(2,12);printf("┃전화번호:010-               ┃");gotoxy(17,12);NumberChange(sta_Info[idx].ca_Number,0);   // 전화번호 출력 변경 
      gotoxy(2,13);printf("┃                            ┃"); 
      gotoxy(2,14);printf("┃주소:                       ┃");gotoxy(10,14);printf("%s",sta_Info[idx].ca_Addr);  
      gotoxy(2,15);printf("┃                            ┃"); 
      gotoxy(2,16);printf("┗━━━━━━━━━━━━━━┛"); 
   }else if(check == 1){
      gotoxy(38,11);printf(" →");
      gotoxy(45,6);printf("┏━━━━ 이름  수정 ━━━━┓");
      gotoxy(45,7);printf("┃                            ┃");
      gotoxy(45,8);printf("┃이름:                       ┃");
      if(select != 1){
         gotoxy(53,8);printf("%s",sta_Info[idx].ca_Name);
      }
      gotoxy(45,9);printf("┃                            ┃"); 
      gotoxy(45,10);printf("┃나이:                       ┃");
      if(select != 3){
         gotoxy(53,10);printf("%d",sta_Info[idx].ui_Age);
      }      
      gotoxy(45,11);printf("┃                            ┃"); 
      gotoxy(45,12);printf("┃전화번호:010-               ┃");
      if(select != 2){
         gotoxy(60,12);NumberChange(sta_Info[idx].ca_Number,0);   // 전화번호 출력 변경    
      }
      gotoxy(45,13);printf("┃                            ┃"); 
      gotoxy(45,14);printf("┃주소:                       ┃");
      if(select != 4){
         gotoxy(53,14);printf("%s",sta_Info[idx].ca_Addr);
      }
      gotoxy(45,15);printf("┃                            ┃"); 
      gotoxy(45,16);printf("┗━━━━━━━━━━━━━━┛"); 
   } 
} 

// 검색 알람 함수 
void AlarmSearch(int check){   
   gotoxy(36,1);printf("검색 모드");
   gotoxy(26,2);printf("┏━━━━━━━━━━━━━━┓"); 
   if(check == 0){
      gotoxy(26,3);printf("┃이름 :                      ┃"); 
   }else if(check == 1) {
      gotoxy(26,3);printf("┃전화번호:010-               ┃"); 
   }else if(check == 2){
      gotoxy(26,3);printf("┃나이 :                      ┃"); 
   }else if(check == 3){
      gotoxy(26,3);printf("┃주소 :                      ┃"); 
   }
   gotoxy(26,4);printf("┗━━━━━━━━━━━━━━┛");
}

void NumberChange(char* num, int check){
   int s;
   if(check == 1){
      printf("전화번호: 010-");   
   }
   for(s=0;s<8;s++){
      printf("%c",num[s]);
      if(s==3) {
         printf("-");   
      }
   }   
}
