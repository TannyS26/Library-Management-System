#include <windows.h>          // contains declarations for all of the functions in the Windows API, all the common macros used by Windows programmers
#include <stdio.h>
#include <conio.h>            // contains delay(),getch(),gotoxy(),etc.
#include <stdlib.h>
#include <string.h>           // contains strcmp(),strcpy(),strlen(),etc
#include <ctype.h>            // contains toupper(), tolower(),etc
#include <dos.h>              // contains _dos_getdate
#include <time.h>

//list of function prototype
void DisplayScr(void);        // common screen look
void MainMenu(void);          // main menu of the system
void AddSec(void);            // add books in library
void DeleteSec(void);         // delete books from library
void SearchSec(void);         // search for book
void IssueSec(void);          // issue a book
void EditSec(void);           // edit book details
void ViewSec(void);           // view the book list
void CloseApp(void);          // exit
void Member(void);            // member details
void EditMember(void);        // edit members details
int InputData();              // retrieve data
int CheckID(int);             // check for id
void LoadingBar(void);        // loading bar
int t(void);                  // display time
void LoginPortal(void);       // login portal
void IssuedRec();             // issued books
void gotoxy(int x, int y);
// co-ordinate section starts
COORD coord = {0, 0};         // sets coordinates to 0,0
COORD max_res,cursor_size;
void gotoxy(int x, int y)
{
        coord.X = x; coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// function for delaying
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

FILE *fp,*ft,*fs,*fdel,*fm;  //list of global files that can be accessed from anywhere in program

//list of global variable
int s,cou=0,i,j,find;
char categories[][15]={"Computer","Electronics","Electrical","Civil","Mechanical","Architecture"};
char empname[][25]={"Pradyumn Singh","Himanshu Sharma","Tanmay Singh","Sharang","Apoorav"};
int age[]={19,18,19,19,18};
char desig[][20]={"Leader","Staff","Receptionist","Staff","Staff"};
int employid[]={8,67,26,89,90};
char username[][15]={"kps","himanshu","fathomout","sharang","apoorav"};
char password[][10]={"tanmay","himanshu","tanny","saurabh","mahajan"};

struct merodate    // structure for date
{
    int mm,dd,yy;
};

struct member      // structure for librarians
{
    char mnam[20],desi[20],pas[20],usr[20];
    int mid,age;
}me;

struct student     // structure for students
{
    char nam[20],bt[4],bknam[20];
    int enrol,sem,bkid;
    struct merodate issued;
    struct merodate duedate;
}b;

struct books       // structure for book details
{
    int id,quantity,count,rackno;
    char name[20],Author[20];
    float Price;
    char *cat;
}a;

// main function containing the cover look of the whole management system
int main(void)
{
    system("COLOR F1");
    i=0;
    fm=fopen("Member.dat","rb");
    while(fread(&me,sizeof(me),1,fm)==1)
        i++;
    fclose(fm);
    fm=fopen("Member.dat","ab+");
    if(fm!=NULL && i==0)
    {
        i=0;
        while(i<5)
        {
            strcpy(me.mnam,empname[i]);
            me.mid=employid[i];
            strcpy(me.desi,desig[i]);
            strcpy(me.usr,username[i]);
            me.age=age[i];
            strcpy(me.pas,password[i]);

            fseek(fm,0,SEEK_END);
            fwrite(&me,sizeof(me),1,fm);
            i++;
        }
    }
    fclose(fm);
    system("cls");
    DisplayScr();
    gotoxy(55,1);    printf("FATHOM OUT");
    // cover look starts
    gotoxy(41,6);    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(41,7);    printf("\xDB\xDB                                   \xDB\xDB");
    gotoxy(41,8);    printf("\xDB\xDB                                   \xDB\xDB");
    gotoxy(41,9);    printf("\xDB\xDB                                   \xDB\xDB");
    gotoxy(41,10);   printf("\xDB\xDB                                   \xDB\xDB");
    gotoxy(41,11);   printf("\xDB\xDB                                   \xDB\xDB");
    gotoxy(41,12);   printf("\xDB\xDB                                   \xDB\xDB");
    gotoxy(41,13);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(54,8);    printf("Mini  Project");
    gotoxy(53,9);    printf("---------------");
    gotoxy(48,10);   printf("Library Management System");
    gotoxy(47,11);   printf("---------------------------");

    gotoxy(19,17);   printf("--------------------------");
    gotoxy(19,18);   printf("|   MEMBER DETAILS : 1   |");
    gotoxy(19,19);   printf("--------------------------");

    gotoxy(75,17);   printf("--------------------------");
    gotoxy(75,18);   printf("|    LOGIN PORTAL : 2    |");
    gotoxy(75,19);   printf("--------------------------");

    gotoxy(57,18);   printf("->   <-");
    gotoxy(60,18);   fflush(stdin);    int choi=getch();

    if(choi=='1')
        Member();
    else if(choi=='2')
        LoginPortal();
    else
        main();

    getch();
    return 0;
}

// function for displaying date and time
int t(void)
{
   time_t t;
   time(&t);
   printf("%s\n",ctime(&t));
   return 0;
}

// function for common screen view
void DisplayScr(void)
{
   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
   gotoxy(0,1);
   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(68,1);
   printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(0,2);
   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");

   gotoxy(0,3);    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,4);    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,5);    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,6);    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,7);    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,8);    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,9);    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,10);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,11);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,12);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,13);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,14);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,15);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,16);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,17);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,18);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,19);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,20);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");
   gotoxy(0,21);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");

   gotoxy(111,3);  printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,4);  printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,5);  printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,6);  printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,7);  printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,8);  printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,9);  printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,10); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,11); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,12); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,13); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,14); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,15); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,16); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,17); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,18); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,19); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,20); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
   gotoxy(111,21); printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");

   gotoxy(0,22);
   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
   gotoxy(0,23);
   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB2");

   gotoxy(48,23);
   t(); // date and time

   gotoxy(75,23);
   printf("\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");

   gotoxy(0,24);
   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
}

// function for exiting from the system
void CloseApp(void)
{
   system("cls");
   DisplayScr();
   gotoxy(55,1);   printf("FATHOM OUT");
   gotoxy(55,6);   printf("THANK YOU!");
   gotoxy(54,7);   printf("------------");
   gotoxy(50,9);   printf("- Have A *Good Day -");
   gotoxy(52,10);  printf("----------------");
   gotoxy(54,12);  printf("Visit  Again");
   gotoxy(53,13);  printf("--------------");

   gotoxy(50,17);  printf("Exiting in 5 seconds");
   for(i=4;i>0;i--)
   {
      gotoxy(61,17);  delay(1000);   printf("%d",i);
   }
   delay(1000);   gotoxy(50,17);   printf("********************");
   gotoxy(0,25);  exit(0);
}

// function to display librarians details
void Member(void)
{
   system("cls");
   DisplayScr();
   gotoxy(55,1);        printf("LIBRARIANS");
   gotoxy(53,5);        printf("MEMBER DETAILS");
   gotoxy(52,6);        printf("----------------");
   gotoxy(11,7);        printf("--------------------------------------------------------------------------------------------------");
   gotoxy(11,8);        printf("|       LIBRARIAN  NAME       |      ID      |       DESIGNATION       |    USER NAME    |  AGE  |");
   gotoxy(11,9);        printf("|------------------------------------------------------------------------------------------------|");

   for(i=10;i<15;)
   {
      gotoxy(11,i++);   printf("|                             |              |                         |                 |       |");
   }
   gotoxy(11,i);        printf("--------------------------------------------------------------------------------------------------");

   gotoxy(19,17);   printf("--------------------------");
   gotoxy(19,18);   printf("|    EDIT DETAILS : 1    |");
   gotoxy(19,19);   printf("--------------------------");

   gotoxy(75,17);   printf("--------------------------");
   gotoxy(75,18);   printf("|    LOGIN PORTAL : 2    |");
   gotoxy(75,19);   printf("--------------------------");

   gotoxy(57,18);   printf("->   <-");
   i=10;
   fm=fopen("Member.dat","rb");
   while(fread(&me,sizeof(me),1,fm)==1)
   {
       gotoxy(14,i);   printf("%s",me.mnam);
       gotoxy(44,i);   printf("%d",me.mid);
       gotoxy(59,i);   printf("%s",me.desi);
       gotoxy(85,i);   printf("%s",me.usr);
       gotoxy(103,i);  printf("%d",me.age);
       i++;
   }

   fclose(fm);
   gotoxy(60,18);   fflush(stdin);    int c=getch();
   if(c=='1')
        EditMember();
   else if(c=='2')
        LoginPortal();
   else
        Member();
}

// function to edit the details of librarians
void EditMember(void)
{
    system("cls");
    DisplayScr();
    int d,fo;
    char temp,temp1,ch,memid,passw[15];
    passw[0]='\0';
    gotoxy(54,1);     printf("EDIT  MEMBER");
    gotoxy(11,20);    printf("--------------------------------------------------------------------------------------------------");
    char another='y';
    while(another=='y')
    {
        gotoxy(11,4);   printf("Member ID : ");
        gotoxy(85,4);   printf("Password  : ");
        gotoxy(23,4);   fflush(stdin);   scanf("%d",&memid);
        i=0;
        gotoxy(97,4);
        while(ch!=13)      // input password portion
        {
          fflush(stdin);
          ch=getch();
          if(ch!=13 && ch!=8)
          {
            putch('*');
            passw[i] = ch;
            i++;
          }
        }
        passw[i] = '\0';     // ending with NULL

        fm=fopen("Member.dat","rb+");
        while(fread(&me,sizeof(me),1,fm)==1)
        {
            if(((memid==me.mid) && (strcmp(passw,me.pas)==0))==1)
            {
                fo==1;
                gotoxy(52,5);      printf("MEMBER AVAILABLE");
                gotoxy(51,6);      printf("------------------");

                gotoxy(24,7);      printf("Present  Details");
                gotoxy(23,8);      printf("------------------");

                gotoxy(59,10);     printf("\xB2\xB2");
                gotoxy(59,11);     printf("\xB2\xB2");
                gotoxy(59,12);     printf("\xB2\xB2");
                gotoxy(59,13);     printf("\xB2\xB2");
                gotoxy(59,14);     printf("\xB2\xB2");

                gotoxy(15,10);     printf("Member ID             : %d",me.mid);
                gotoxy(15,11);     printf("Current Name          : %s",me.mnam);
                gotoxy(15,12);     printf("Current Designation   : %s",me.desi);
                gotoxy(15,13);     printf("Current Age           : %d",me.age);
                gotoxy(15,14);     printf("Current User Name     : %s",me.usr);

                gotoxy(82,7);      printf("New  Details");
                gotoxy(79,8);      printf("------------------");

                gotoxy(65,10);     printf("Enter New Name        : ");     scanf("%[^\n]",me.mnam); // temp variable to clear buffer
	            gotoxy(65,11);     printf("Enter New Designation : ");     scanf("%c",&temp1); scanf("%[^\n]",me.desi);
                gotoxy(65,12);     printf("Enter New Age         : ");     scanf("%d",&me.age);
                gotoxy(65,13);     printf("Enter New User Name   : ");     scanf("%s",me.usr);
                gotoxy(65,14);     printf("Enter New Password    : ");     scanf("%s",me.pas);
                gotoxy(52,17);     printf("Record  Modified");
                gotoxy(51,18);     printf("------------------");

                fseek(fm,ftell(fm)-sizeof(me),0);   // ftell is used to find position of the file pointer
                fwrite(&me,sizeof(me),1,fm);
                fclose(fm);
            }
        }
        if(fo==0)
        {
            gotoxy(50,12);     printf("MEMBER NOT AVAILABLE");
            gotoxy(49,13);     printf("----------------------");
        }

        gotoxy(11,21);       printf("Modify Another Record(Y / N) : ");
        rety:
        gotoxy(42,21);
        fflush(stdin);
        another=getch();
        if(another=='y')
        {
            EditMember();
        }
        else if(another=='n')
            Member();
        else
        {
            goto rety;
        }
    }

}

// function for main menu
void MainMenu(void)
{
    system("cls");
    DisplayScr();
    int i;
    gotoxy(55,1);    printf("MAIN  MENU");
    gotoxy(54,5);    printf("SELECT  TASK");
    gotoxy(53,6);    printf("--------------");

    gotoxy(11,9);    printf("\xDB\xDB\xDB\xDB\xB2   Add Books   ");
    gotoxy(11,11);   printf("\xDB\xDB\xDB\xDB\xB2   Delete Books");
    gotoxy(11,13);   printf("\xDB\xDB\xDB\xDB\xB2   Search Books");

    gotoxy(53,9);    printf("\xB2  1  \xDB\xDB  4  \xB2");
    gotoxy(53,11);   printf("\xB2  2  \xDB\xDB  5  \xB2");
    gotoxy(53,13);   printf("\xB2  3  \xDB\xDB  6  \xB2");

    gotoxy(90,9);    printf("Issue Books   ");
    gotoxy(104,9);   printf("\xB2\xDB\xDB\xDB\xDB");
    gotoxy(92,11);   printf("View List   ");
    gotoxy(104,11);  printf("\xB2\xDB\xDB\xDB\xDB");
    gotoxy(90,13);   printf("Edit Record   ");
    gotoxy(104,13);  printf("\xB2\xDB\xDB\xDB\xDB");
    gotoxy(19,17);   printf("--------------------------");
    gotoxy(19,18);   printf("| CLOSE  APPLICATION : 7 |");
    gotoxy(19,19);   printf("--------------------------");

    gotoxy(75,17);   printf("--------------------------");
    gotoxy(75,18);   printf("|       LOGOUT : 8       |");
    gotoxy(75,19);   printf("--------------------------");

    gotoxy(57,18);   printf("->   <-");
    gotoxy(60,18);

    switch(getch())
    {
        case '1':
            AddSec();
            break;
        case '2':
            DeleteSec();
            break;
        case '3':
            SearchSec();
            break;
        case '4':
            IssueSec();
            break;
        case '5':
            ViewSec();
            break;
        case '6':
            EditSec();
            break;
        case '7':
            CloseApp();
            break;
        case '8':
            LoginPortal();
            break;
        default:
            MainMenu();
    }
}

//function to add books (Add Section)
void AddSec(void)
{
    readd:
    system("cls");
    DisplayScr();
    int i;
    gotoxy(54,1);    printf("ADD  SECTION");
    gotoxy(52,5);    printf("SELECT  CATEGORY");
    gotoxy(51,6);    printf("------------------");

    gotoxy(11,9);    printf("\xDB\xDB\xDB\xDB\xB2   Computer");
    gotoxy(11,11);   printf("\xDB\xDB\xDB\xDB\xB2   Electronics");
    gotoxy(11,13);   printf("\xDB\xDB\xDB\xDB\xB2   Electrical");

    gotoxy(51,9);    printf("\xB2   1   \xDB\xDB   4   \xB2");
    gotoxy(51,11);   printf("\xB2   2   \xDB\xDB   5   \xB2");
    gotoxy(51,13);   printf("\xB2   3   \xDB\xDB   6   \xB2");

    gotoxy(96,9);    printf("Civil   ");
    gotoxy(104,9);   printf("\xB2\xDB\xDB\xDB\xDB");
    gotoxy(91,11);   printf("Mechanical   ");
    gotoxy(104,11);  printf("\xB2\xDB\xDB\xDB\xDB");
    gotoxy(89,13);   printf("Architecture   ");
    gotoxy(104,13);  printf("\xB2\xDB\xDB\xDB\xDB");

    gotoxy(19,17);   printf("--------------------------");
    gotoxy(19,18);   printf("|     MAIN  MENU : 7     |");
    gotoxy(19,19);   printf("--------------------------");

    gotoxy(75,17);   printf("--------------------------");
    gotoxy(75,18);   printf("|       LOGOUT : 8       |");
    gotoxy(75,19);   printf("--------------------------");

    gotoxy(57,18);   printf("->   <-");
    gotoxy(60,18);   scanf("%d",&s);

    if(s==7)
       MainMenu();
    if(s==8)
       LoginPortal();
    system("cls");

    fp=fopen("Record.dat","ab+");

    if(InputData()==1)   // calling function to input data
    {
      a.cat=categories[s-1];
      fseek(fp,0,SEEK_END);
      fwrite(&a,sizeof(a),1,fp);
      fclose(fp);
      gotoxy(54,17);     printf("Record Saved");
      gotoxy(53,18);     printf("--------------");

      gotoxy(11,21);     printf("Add More Books(Y / N) : ");
      if(getch()=='n')
        MainMenu();
      else
        system("cls");
        AddSec();
    }
    else
        goto readd;
    fclose(fp);
}

// function to delete books (Delete Section)
void DeleteSec(void)
{
    system("cls");
    int d,con;
    char another='y';
    while(another=='y')             // infinite loop
    {
     con=0,find=0;
     system("cls");
     DisplayScr();
     gotoxy(53,1);     printf("DELETE SECTION");
     gotoxy(11,20);    printf("--------------------------------------------------------------------------------------------------");

     gotoxy(11,4);     printf("Enter Book ID To Be Deleted : ");
     scanf("%d",&d);
     fp=fopen("Record.dat","rb+");
     rewind(fp);
     while(fread(&a,sizeof(a),1,fp)==1)
     {
        if(a.id==d)
        {
           gotoxy(53,6);      printf("BOOK AVAILABLE");
           gotoxy(52,7);      printf("----------------");
           gotoxy(21,10);     printf("Category  :  %s",a.cat);
           gotoxy(21,12);     printf("Name      :  %s",a.name);
           gotoxy(21,14);     printf("Author    :  %s",a.Author);
           gotoxy(59,10);     printf("\xB2\xB2");
           gotoxy(59,11);     printf("\xB2\xB2");
           gotoxy(59,12);     printf("\xB2\xB2");
           gotoxy(59,13);     printf("\xB2\xB2");
           gotoxy(59,14);     printf("\xB2\xB2");

           gotoxy(71,10);     printf("Quantity  :  %d",a.quantity);
           gotoxy(71,12);     printf("Price     :  Rs. %.1f",a.Price);
           gotoxy(71,14);     printf("Rack No.  :  %d",a.rackno);
           printf("\n");
           find=1;
        }
     }
     if(find==0)
     {
        char ge;
        gotoxy(51,12);        printf("Book ID Not Found");
        gotoxy(50,13);        printf("-------------------");
        gotoxy(11,21);        printf("Delete Another Book(Y / N) : ");
        getit:
        fflush(stdin);
        ge=getch();
        if(ge=='y')
            DeleteSec();
        else if(ge=='n')
            MainMenu();
        else
        {
            gotoxy(93,21);     printf("Invalid Choice!!");
            goto getit;
        }
     }
     if(find==1)
     {
        gotoxy(11,21);        printf("Confirm Delete(Y / N) : ");
        if(getch()=='y')
        {
          con=1;
          ft=fopen("test.dat","wb+");          // temporary file for delete
          fdel=fopen("del.dat","wb+");
          rewind(fp);
          while(fread(&a,sizeof(a),1,fp)==1)
          {
            if(a.id==d)
            {
               fseek(fdel,0,SEEK_CUR);
               fwrite(&a,sizeof(a),1,fdel);      // write all in temporary file except that we want to delete
            }
            else
            {
               fseek(ft,0,SEEK_CUR);
               fwrite(&a,sizeof(a),1,ft);
            }
          }
        fclose(fdel);
        fclose(ft);
        fclose(fp);
        remove("Record.dat");
        rename("test.dat","Record.dat");        //copy all item from temporary file to fp except that we want to delete
        }
     }
     if(find==1 && con==1)
     {
        gotoxy(52,17);     printf("Record  Deleted");
        gotoxy(51,18);     printf("-----------------");
        gotoxy(11,21);     printf("Delete Another Record(Y / N) : ");

        fflush(stdin);
        another=getch();
     }
     else
     {
        gotoxy(51,17);     printf("Record Not Deleted");
        gotoxy(50,18);     printf("--------------------");
        gotoxy(11,21);     printf("Delete Another Record(Y / N) : ");

        fflush(stdin);
        another=getch();
     }
    }
    MainMenu();
}

// function to search book(s)
void SearchSec()
{
    system("cls");
    DisplayScr();
    int d;
    gotoxy(53,1);    printf("SEARCH SECTION");
    gotoxy(50,4);    printf("SELECT SEARCH OPTION");
    gotoxy(49,5);    printf("----------------------");

    gotoxy(11,8);    printf("\xDB\xDB\xDB\xDB\xB2   Search By ID");
    gotoxy(11,10);   printf("\xDB\xDB\xDB\xDB\xB2   Search By Name");
    gotoxy(11,12);   printf("\xDB\xDB\xDB\xDB\xB2   Search By Author");

    gotoxy(49,8);    printf("\xB2    1    \xDB\xDB    4    \xB2");
    gotoxy(49,10);   printf("\xB2    2    \xDB\xDB    5    \xB2");
    gotoxy(49,12);   printf("\xB2    3    \xDB\xDB    6    \xB2");


    gotoxy(83,8);    printf("Search By Category   \xB2\xDB\xDB\xDB\xDB");
    gotoxy(83,10);   printf("Search By Rack No.   \xB2\xDB\xDB\xDB\xDB");
    gotoxy(80,12);   printf("Search By Price Range   \xB2\xDB\xDB\xDB\xDB");

    gotoxy(19,14);   printf("--------------------------");
    gotoxy(19,15);   printf("|     MAIN  MENU : 7     |");
    gotoxy(19,16);   printf("--------------------------");

    gotoxy(75,14);   printf("--------------------------");
    gotoxy(75,15);   printf("|       LOGOUT : 8       |");
    gotoxy(75,16);   printf("--------------------------");

    gotoxy(11,18);   printf("--------------------------------------------------------------------------------------------------");
    gotoxy(11,20);   printf("Enter Your Choice  :  ");
    fp=fopen("Record.dat","rb+");      //open file for reading propose
    rewind(fp);                       //move pointer at the beginning of file
    switch(getch())
    {
      case '1':
      {
        system("cls");
        DisplayScr();
        gotoxy(57,1);    printf("SEARCH");
        gotoxy(54,4);    printf("SEARCH BY ID");
        gotoxy(53,5);    printf("--------------");

        gotoxy(11,7);    printf("Enter Book ID : ");
        scanf("%d",&d);

        while(fread(&a,sizeof(a),1,fp)==1)
        {
          if(a.id==d)
          {
            delay(2);
            gotoxy(53,9);    printf("BOOK AVAILABLE");
            gotoxy(52,10);   printf("----------------");
            gotoxy(20,13);   printf("Category :  %s",a.cat);
            gotoxy(59,13);   printf("\xB2\xB2");   gotoxy(59,14);   printf("\xB2\xB2");
            gotoxy(20,15);   printf("Name     :  %s",a.name);
            gotoxy(59,15);   printf("\xB2\xB2");   gotoxy(59,16);   printf("\xB2\xB2");
            gotoxy(20,17);   printf("Author   :  %s ",a.Author);
            gotoxy(59,17);   printf("\xB2\xB2");
            gotoxy(70,13);   printf("Quantity :  %d ",a.quantity);
            gotoxy(70,15);   printf("Price    :  Rs.%.2f",a.Price);
            gotoxy(70,17);   printf("Rack No  :  %d ",a.rackno);

            find='t';
          }
        }

        if(find!='t')  //checks whether the book found or not
        {
           gotoxy(53,9);    printf("Book Not Found");
           gotoxy(52,10);   printf("----------------");
           gotoxy(55,13);   printf("Thank You!");
           gotoxy(54,14);   printf("------------");
        }

        gotoxy(11,20);    printf("--------------------------------------------------------------------------------------------------");
        gotoxy(11,21);    printf("Search Another Book(Y / N) : ");

        if(getch()=='y')
           SearchSec();
        else
           MainMenu();
        break;
    }
    case '2':
    {
        char s[15];
        system("cls");
        DisplayScr();
        gotoxy(57,1);    printf("SEARCH");
        gotoxy(53,4);    printf("SEARCH BY NAME");
        gotoxy(52,5);    printf("----------------");

        gotoxy(11,7);    printf("Enter Book Name : ");    scanf("%s",s);
        int d=0;
        while(fread(&a,sizeof(a),1,fp)==1)
        {
        if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
        {
            delay(2);
            gotoxy(53,9);    printf("BOOK AVAILABLE");
            gotoxy(52,10);   printf("----------------");
            gotoxy(20,13);   printf("Category :  %s",a.cat);
            gotoxy(59,13);   printf("\xB2\xB2");   gotoxy(59,14);   printf("\xB2\xB2");
            gotoxy(20,15);   printf("Name     :  %s",a.name);
            gotoxy(59,15);   printf("\xB2\xB2");   gotoxy(59,16);   printf("\xB2\xB2");
            gotoxy(20,17);   printf("Author   :  %s ",a.Author);
            gotoxy(59,17);   printf("\xB2\xB2");
            gotoxy(70,13);   printf("Quantity :  %d ",a.quantity);
            gotoxy(70,15);   printf("Price    :  Rs.%.2f",a.Price);
            gotoxy(70,17);   printf("Rack No  :  %d ",a.rackno);

            d++;
        }

        }
        if(d==0)
        {
           gotoxy(53,9);    printf("Book Not Found");
           gotoxy(52,10);   printf("----------------");
           gotoxy(55,13);   printf("Thank You!");
           gotoxy(54,14);   printf("------------");
        }

        gotoxy(11,20);      printf("--------------------------------------------------------------------------------------------------");
        gotoxy(11,21);      printf("Search Another Book(Y/N) : ");

        if(getch()=='y')
           SearchSec();
        else
           MainMenu();
        break;
    }
    case '3':
    {
        char s[15];
        author:
        system("cls");
        DisplayScr();
        gotoxy(57,1);    printf("SEARCH");
        gotoxy(52,4);    printf("SEARCH BY AUTHOR");
        gotoxy(51,5);    printf("------------------");

        gotoxy(11,7);    printf("Enter Author Name : ");   scanf("%s",s);
        int d=0;
        while(fread(&a,sizeof(a),1,fp)==1)
        {
        if(strcmp(a.Author,s)==0) //checks whether a.name is equal to s or not
        {
            delay(2);
            gotoxy(53,9);    printf("BOOK AVAILABLE");
            gotoxy(52,10);   printf("----------------");
            gotoxy(20,13);   printf("Category :  %s",a.cat);
            gotoxy(59,13);   printf("\xB2\xB2");   gotoxy(59,14);   printf("\xB2\xB2");
            gotoxy(20,15);   printf("Book ID  :  %d",a.id);
            gotoxy(59,15);   printf("\xB2\xB2");    gotoxy(59,16);   printf("\xB2\xB2");
            gotoxy(20,17);   printf("Name     :  %s ",a.name);
            gotoxy(59,17);   printf("\xB2\xB2");
            gotoxy(70,13);   printf("Quantity :  %d ",a.quantity);
            gotoxy(70,15);   printf("Price    :  Rs.%.2f",a.Price);
            gotoxy(70,17);   printf("Rack No  :  %d ",a.rackno);

            d++;
        }

        }
        if(d==0)
        {
           gotoxy(53,9);      printf("Book Not Found");
           gotoxy(52,10);     printf("----------------");
           gotoxy(55,13);     printf("Thank You!");
           gotoxy(54,14);     printf("------------");
        }

        gotoxy(11,20);        printf("--------------------------------------------------------------------------------------------------");
        gotoxy(11,21);        printf("Search Another Book(Y / N) : ");

        if(getch()=='y')
           SearchSec();
        else
           MainMenu();
        break;
    }
    case '4':
    {
        replay:
        fflush(stdin);
        int s,x=7,i=0,d;
        char r;
        system("cls");
        DisplayScr();
        gotoxy(55,1);        printf("CATEGORIES");
        gotoxy(52,6);        printf("SELECT  CATEGORY");
        gotoxy(51,7);        printf("------------------");

        gotoxy(11,10);       printf("\xDB\xDB\xDB\xDB\xB2   Computer");
        gotoxy(11,12);       printf("\xDB\xDB\xDB\xDB\xB2   Electronics");
        gotoxy(11,14);       printf("\xDB\xDB\xDB\xDB\xB2   Electrical");

        gotoxy(51,10);       printf("\xB2   1   \xDB\xDB   4   \xB2");
        gotoxy(51,12);       printf("\xB2   2   \xDB\xDB   5   \xB2");
        gotoxy(51,14);       printf("\xB2   3   \xDB\xDB   6   \xB2");

        gotoxy(96,10);       printf("Civil   ");
        gotoxy(104,10);      printf("\xB2\xDB\xDB\xDB\xDB");
        gotoxy(91,12);       printf("Mechanical   ");
        gotoxy(104,12);      printf("\xB2\xDB\xDB\xDB\xDB");
        gotoxy(89,14);       printf("Architecture   ");
        gotoxy(104,14);      printf("\xB2\xDB\xDB\xDB\xDB");


        gotoxy(11,18);       printf("--------------------------------------------------------------------------------------------------");
        j=12;

        gotoxy(11,20);       printf("Enter Your Choice : ");
        scanf("%d",&s);

        if((s>0) && (s<7))
        {
            system("cls");
            DisplayScr();
            gotoxy(58,1);       printf("LIST");
            gotoxy(11,3);       printf("Category : %s",categories[s-1]);
            gotoxy(11,4);       printf("--------------------------------------------------------------------------------------------------");
            gotoxy(11,5);       printf("|      ID      |        BOOK NAME        |        AUTHOR        |   QTY   |    PRICE    |  RACK  |");
            gotoxy(11,6);       printf("|------------------------------------------------------------------------------------------------|");

            while(x<17)
            {
               gotoxy(11,x++);  printf("|              |                         |                      |         |             |        |");
            }

            gotoxy(11,17);      printf("--------------------------------------------------------------------------------------------------");

            gotoxy(19,18);   printf("--------------------------");
            gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
            gotoxy(19,20);   printf("--------------------------");

            gotoxy(75,18);   printf("--------------------------");
            gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
            gotoxy(75,20);   printf("--------------------------");
            gotoxy(57,19);   printf("->   <-");
            x=7;
            i=0;
            while(fread(&a,sizeof(a),1,fp)==1)
            {
             if(strcmp(a.cat,categories[s-1])==0)       //checks whether a.name is equal to s or not
             {
               delay(2);
               gotoxy(14,x);      printf("%d",a.id);
               gotoxy(29,x);      printf("%s",a.name);
               gotoxy(55,x);      printf("%s",a.Author);
               gotoxy(78,x);      printf("%d",a.quantity);
               gotoxy(88,x);      printf("%.2f",a.Price);
               gotoxy(102,x);     printf("%d",a.rackno);
               x++;
               d++;
               i++;

               if(i==10)
               {
                   i=0;
                   recaty:
                   gotoxy(60,18);
                   fflush(stdin);
                   r=getch();
                   switch(r)
                   {
                       case '1':
                           MainMenu();
                           break;
                       case '2':
                       {
                           system("cls");
                           DisplayScr();       x=7;
                           gotoxy(58,1);       printf("LIST");
                           gotoxy(11,4);       printf("--------------------------------------------------------------------------------------------------");
                           gotoxy(11,5);       printf("|      ID      |        BOOK NAME        |        AUTHOR        |   QTY   |    PRICE    |  RACK  |");
                           gotoxy(11,6);       printf("|------------------------------------------------------------------------------------------------|");

                           while(x<17)
                           {
                               gotoxy(11,x++);  printf("|              |                         |                      |         |             |        |");
                           }

                           gotoxy(11,17);      printf("--------------------------------------------------------------------------------------------------");

                           gotoxy(19,18);   printf("--------------------------");
                           gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
                           gotoxy(19,20);   printf("--------------------------");

                           gotoxy(75,18);   printf("--------------------------");
                           gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
                           gotoxy(75,20);   printf("--------------------------");
                           gotoxy(57,19);   printf("->   <-");
                           x=7;
                           continue;
                       }
                       default:
                       {
                           gotoxy(53,21);   printf("Invalid  Choice");
                           goto recaty;
                           break;
                       }

                   }
               }
            }
          }
        }
          if(d==0)
          {
             system("cls");
             DisplayScr();
             gotoxy(52,1);    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
             gotoxy(11,3);    printf("Category : %s",categories[s-1]);
             gotoxy(44,8);    printf("No Book Found Under This Category");
             gotoxy(43,9);    printf("-----------------------------------");
             gotoxy(55,12);   printf("Thank You!");
             gotoxy(54,13);   printf("------------");
             gotoxy(19,18);   printf("--------------------------");
             gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
             gotoxy(19,20);   printf("--------------------------");
             gotoxy(75,18);   printf("--------------------------");
             gotoxy(75,19);   printf("|    SEARCH AGAIN : 0    |");
             gotoxy(75,20);   printf("--------------------------");
             gotoxy(57,19);   printf("->   <-");
          }

        getcatagain:
        gotoxy(60,19);       fflush(stdin);     r=getch();
        switch(r)
        {
          case '0':
            goto replay;
            break;
          case '1':
          {
            fclose(fp);        MainMenu();
            break;
          }
          case '2':
          {
            gotoxy(46,21);     printf("                      ");
            gotoxy(55,21);     printf("No More Data");        goto getcatagain;
            break;
          }
          default:
          {
            gotoxy(53,21);     printf("Invalid  Choice");     goto getcatagain;
            break;
          }
        }
        break;
    }
    case '5':
    {
        rerackagain:
        fflush(stdin);
        int rn,x=7,tem=0,i=0;
        char r;
        system("cls");
        DisplayScr();
        gotoxy(58,1);       printf("LIST");
        gotoxy(11,3);       printf("Enter Rack Number : ");        scanf("%d",&rn);

        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
          if(a.rackno==rn)
          {
                 tem=1;
                 break;
          }
        }

        if(tem==1)
        {
          gotoxy(11,4);        printf("--------------------------------------------------------------------------------------------------");
          gotoxy(11,5);        printf("|     CATEGORY     |      ID      |      BOOK NAME      |      AUTHOR      |   QTY   |   PRICE   |");
          gotoxy(11,6);        printf("|------------------------------------------------------------------------------------------------|");

          while(x<17)
          {
            gotoxy(11,x++);    printf("|                  |              |                     |                  |         |           |");
          }

          gotoxy(11,17);       printf("--------------------------------------------------------------------------------------------------");
          gotoxy(19,18);   printf("--------------------------");
          gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
          gotoxy(19,20);   printf("--------------------------");

          gotoxy(75,18);   printf("--------------------------");
          gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
          gotoxy(75,20);   printf("--------------------------");
          gotoxy(57,19);   printf("->   <-");

          x=7;
          rewind(fp);
          while(fread(&a,sizeof(a),1,fp)==1)
          {
             if(a.rackno==rn)             //checks whether a.rackno is equal to r or not
             {
               delay(2);
               gotoxy(14,x);   printf("%s",a.cat);
               gotoxy(33,x);   printf("%d",a.id);
               gotoxy(48,x);   printf("%s",a.name);
               gotoxy(70,x);   printf("%s",a.Author);
               gotoxy(89,x);   printf("%d",a.quantity);
               gotoxy(99,x);   printf("%.2f",a.Price);
               x++;
               i++;

               if(i==10)
               {
                   i=0;
                   rerack:
                   gotoxy(60,18);
                   fflush(stdin);
                   r=getch();
                   switch(r)
                   {
                       case '1':
                           MainMenu();
                           break;
                       case '2':
                       {
                           system("cls");
                           DisplayScr();        x=7;
                           gotoxy(58,1);        printf("LIST");
                           gotoxy(11,20);       printf("--------------------------------------------------------------------------------------------------");
                           gotoxy(11,4);        printf("--------------------------------------------------------------------------------------------------");
                           gotoxy(11,5);        printf("|     CATEGORY     |      ID      |      BOOK NAME      |      AUTHOR      |   QTY   |   PRICE   |");
                           gotoxy(11,6);        printf("|------------------------------------------------------------------------------------------------|");

                           while(x<17)
                           {
                               gotoxy(11,x++);    printf("|                  |              |                     |                  |         |           |");
                           }

                           gotoxy(11,17);       printf("--------------------------------------------------------------------------------------------------");
                           gotoxy(19,18);   printf("--------------------------");
                           gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
                           gotoxy(19,20);   printf("--------------------------");

                           gotoxy(75,18);   printf("--------------------------");
                           gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
                           gotoxy(75,20);   printf("--------------------------");
                           gotoxy(57,19);   printf("->   <-");

                           x=7;
                           continue;
                       }
                       default:
                       {
                            gotoxy(53,21);   printf("Invalid  Choice");
                            goto rerack;
                            break;
                       }
                   }
             }
           }
         }
        }
        else
        {
             gotoxy(58,1);     printf("LIST");
             gotoxy(47,8);     printf("No Book Found On This Rack");
             gotoxy(46,9);     printf("----------------------------");
             gotoxy(55,12);    printf("Thank You!");
             gotoxy(54,13);    printf("------------");
             gotoxy(19,18);    printf("--------------------------");
             gotoxy(19,19);    printf("|     MAIN  MENU : 1     |");
             gotoxy(19,20);    printf("--------------------------");
             gotoxy(75,18);    printf("--------------------------");
             gotoxy(75,19);    printf("|    SEARCH AGAIN : 0    |");
             gotoxy(75,20);    printf("--------------------------");
             gotoxy(57,19);    printf("->   <-");
        }
        getrackagain:
        gotoxy(60,19);       fflush(stdin);     r=getch();
        switch(r)
        {
          case '0':
            goto rerackagain;
            break;
          case '1':
          {
            fclose(fp);        MainMenu();
            break;
          }
          case '2':
          {
            gotoxy(46,21);     printf("                       ");
            gotoxy(55,21);     printf("No More Data");        goto getrackagain;
            break;
          }
          default:
          {
            gotoxy(53,21);     printf("Invalid  Choice");     goto getrackagain;
            break;
          }
        }
        break;
    }
    case '6':
    {
        reprice:
        fflush(stdin);
        int lp,up,x=7,tem=0;i=0;
        char geti,research;
        system("cls");
        DisplayScr();
        gotoxy(58,1);        printf("LIST");

        gotoxy(11,3);        printf("Enter Price Range : ");
        gotoxy(31,3);        scanf("%d",&lp);
        gotoxy(37,3);        printf("- ");
        gotoxy(39,3);        scanf("%d",&up);

        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
          if((a.Price>=lp)&&(a.Price<=up))
          {
                 tem=1;
                 break;
          }
        }

        if(tem==1)
        {
          gotoxy(11,4);         printf("--------------------------------------------------------------------------------------------------");
          gotoxy(11,5);         printf("|     CATEGORY     |      ID      |      BOOK  NAME      |      AUTHOR      |   QTY   |   RACK   |");
          gotoxy(11,6);         printf("|------------------------------------------------------------------------------------------------|");

          while(x<17)
          {
            gotoxy(11,x++);     printf("|                  |              |                      |                  |         |          |");
          }

          gotoxy(11,17);        printf("--------------------------------------------------------------------------------------------------");
          gotoxy(19,18);   printf("--------------------------");
          gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
          gotoxy(19,20);   printf("--------------------------");

          gotoxy(75,18);   printf("--------------------------");
          gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
          gotoxy(75,20);   printf("--------------------------");
          gotoxy(57,19);   printf("->   <-");
          x=7; i=0;

          rewind(fp);
          while(fread(&a,sizeof(a),1,fp)==1)
          {
             if((a.Price>=lp)&&(a.Price<=up))         //checks whether a.Price is within range
             {
               delay(2);
               gotoxy(14,x);    printf("%s",a.cat);
               gotoxy(33,x);    printf("%d",a.id);
               gotoxy(48,x);    printf("%s",a.name);
               gotoxy(71,x);    printf("%s",a.Author);
               gotoxy(90,x);    printf("%d",a.quantity);
               gotoxy(100,x);   printf("%d",a.rackno);
               x++;
               i++;

               if(i==10)
               {
                   i=0;
                   pricerange:
                   gotoxy(60,19);
                   fflush(stdin);
                   geti=getch();
                   switch(geti)
                   {
                    case '1':
                        MainMenu();
                        break;
                    case '2':
                    {
                       system("cls");
                       DisplayScr();         x=7;
                       gotoxy(58,1);         printf("LIST");
                       gotoxy(11,4);         printf("--------------------------------------------------------------------------------------------------");
                       gotoxy(11,5);         printf("|     CATEGORY     |      ID      |      BOOK  NAME      |      AUTHOR      |   QTY   |   RACK   |");
                       gotoxy(11,6);         printf("|------------------------------------------------------------------------------------------------|");

                       while(x<17)
                       {
                          gotoxy(11,x++);    printf("|                  |              |                      |                  |         |          |");
                       }

                       gotoxy(11,17);        printf("--------------------------------------------------------------------------------------------------");
                       gotoxy(19,18);   printf("--------------------------");
                       gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
                       gotoxy(19,20);   printf("--------------------------");

                       gotoxy(75,18);   printf("--------------------------");
                       gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
                       gotoxy(75,20);   printf("--------------------------");
                       gotoxy(57,19);   printf("->   <-");
                       x=7;
                       continue;
                    }
                    default:
                        {
                            gotoxy(53,21);   printf("Invalid  Choice");
                            goto pricerange;
                            break;
                        }
                  }
               }
             }
          }
        }
        else
        {
             gotoxy(58,1);     printf("LIST");
             gotoxy(37,8);     printf("No Book Found With The Price In The Given Range");
             gotoxy(36,9);     printf("-------------------------------------------------");
             gotoxy(55,12);    printf("Thank You!");
             gotoxy(54,13);    printf("------------");
             gotoxy(19,18);    printf("--------------------------");
             gotoxy(19,19);    printf("|     MAIN  MENU : 1     |");
             gotoxy(19,20);    printf("--------------------------");
             gotoxy(75,18);    printf("--------------------------");
             gotoxy(75,19);    printf("|    SEARCH AGAIN : 0    |");
             gotoxy(75,20);    printf("--------------------------");
             gotoxy(57,19);    printf("->   <-");
        }

        getinpagain:
        gotoxy(60,19);       fflush(stdin);     research=getch();
        switch(research)
        {
          case '0':
            goto reprice;
            break;
          case '1':
          {
            fclose(fp);        MainMenu();
            break;
          }
          case '2':
          {
            gotoxy(46,21);     printf("                      ");
            gotoxy(55,21);     printf("No More Data");        goto getinpagain;
            break;
          }
          default:
          {
            gotoxy(53,21);     printf("Invalid  Choice");     goto getinpagain;
            break;
          }
        }
        break;
    }
    case '7':
        MainMenu();
        break;
    case '8':
        LoginPortal();
        break;
    default :
        getch();
        SearchSec();
    }
    fclose(fp);
}

//function that issue books from library
void IssueSec(void)
{
    int t; char temp,temp1;
    system("cls");
    DisplayScr();
    gotoxy(53,1);    printf("ISSUE  SECTION");

    gotoxy(54,4);    printf("SELECT  TASK");
    gotoxy(53,5);    printf("--------------");

    gotoxy(11,8);    printf("\xDB\xDB\xDB\xDb\xB2   Issue a Book");
    gotoxy(89,8);    printf("Issued Books   \xB2\xDB\xDB\xDB\xDb");

    gotoxy(53,8);    printf("\xB2  1  \xDB\xDB  2  \xB2");
    gotoxy(53,10);   printf("\xB2  3  \xDB\xDB  4  \xB2");

    gotoxy(11,10);   printf("\xDB\xDB\xDB\xDb\xB2   Search Issued Book");
    gotoxy(83,10);   printf("Remove Issued Book   \xB2\xDB\xDB\xDB\xDb");

    gotoxy(19,14);   printf("--------------------------");
    gotoxy(19,15);   printf("|     MAIN  MENU : 5     |");
    gotoxy(19,16);   printf("--------------------------");

    gotoxy(75,14);   printf("--------------------------");
    gotoxy(75,15);   printf("|       LOGOUT : 6       |");
    gotoxy(75,16);   printf("--------------------------");
    gotoxy(11,18);   printf("--------------------------------------------------------------------------------------------------");

    gotoxy(11,20);   printf("Enter your choice : ");
    gotoxy(32,20);

    switch(getch())
    {
    case '1':  //issue book
    {
        reissue:
        system("cls");
        int c=0;
        char another='y';
        while(another=='y')
        {
            system("cls");
            DisplayScr();
            gotoxy(55,1);          printf("ISSUE BOOK");
            gotoxy(11,4);          printf("Enter the Book Id : ");      scanf("%d",&t);
            fp=fopen("Record.dat","rb");
            fs=fopen("Issue.dat","ab+");
            if(CheckID(t)==0) //check for the availability of the book
            {
                gotoxy(53,5);      printf("BOOK AVAILABLE");
                gotoxy(52,6);      printf("----------------");

                gotoxy(25,7);      printf("BOOK  DETAILS");
                gotoxy(23,8);      printf("-----------------");

                gotoxy(59,10);     printf("\xB2\xB2");
                gotoxy(59,11);     printf("\xB2\xB2");
                gotoxy(59,12);     printf("\xB2\xB2");
                gotoxy(59,13);     printf("\xB2\xB2");
                gotoxy(59,14);     printf("\xB2\xB2");
                gotoxy(59,15);     printf("\xB2\xB2");

                gotoxy(15,10);     printf("Book ID        :  %d",a.id);
                gotoxy(15,11);     printf("Name           :  %s",a.name);
                gotoxy(15,12);     printf("Author         :  %s",a.Author);
                gotoxy(15,13);     printf("Quantity       :  %d",a.quantity);
                gotoxy(15,14);     printf("Price          :  %0.2f",a.Price);
                gotoxy(15,15);     printf("Rack No.       :  %d",a.rackno);

                gotoxy(80,7);     printf("STUDENT  DETAILS");
                gotoxy(79,8);     printf("------------------");

                gotoxy(65,11);    printf("Student Name    :  ");    scanf("%c",&temp); scanf("%[^\n]",b.nam);
                gotoxy(65,12);    printf("Enrollment ID   :  ");    scanf("%d",&b.enrol);
                gotoxy(65,13);    printf("Batch           :  ");    scanf("%c",&temp1); scanf("%[^\n]",b.bt);
                gotoxy(65,14);    printf("Semester        :  ");    scanf("%d",&b.sem);

                strcpy(b.bknam,a.name);
                b.bkid  = a.id;
                a.quantity=a.quantity-1;
                fwrite(&a,sizeof(a),1,fp);

                time_t now=time(NULL);
                struct tm *d = localtime(&now);
                b.issued.dd=d->tm_mday;
                b.issued.mm=d->tm_mon+1;
                b.issued.yy=d->tm_year+1900;

                gotoxy(54,17);    printf("BOOK  ISSUED");
                gotoxy(53,18);    printf("--------------");

                gotoxy(11,19);    printf("Issued Date : %d-%d-%d",b.issued.dd,b.issued.mm,b.issued.yy);

                b.duedate.dd=b.issued.dd+15;   //for return date
                b.duedate.mm=b.issued.mm;
                b.duedate.yy=b.issued.yy;

                // taking month of 30 days
                if(b.duedate.dd>30)
                {
                   b.duedate.mm+=b.duedate.dd/30;
                   b.duedate.dd-=30;
                }

                if(b.duedate.mm>12)
                {
                   b.duedate.yy+=b.duedate.mm/12;
                   b.duedate.mm-=12;
                }
                gotoxy(84,19);    printf("Return Date : %d-%d-%d",b.duedate.dd,b.duedate.mm,b.duedate.yy);

                fseek(fs,sizeof(b),SEEK_END);
                fwrite(&b,sizeof(b),1,fs);
                fclose(fs);

                c=1;
            }
            if(c==0)
            {
              gotoxy(51,11);      printf("Book Not Available");
              gotoxy(50,12);      printf("--------------------");
            }
            gotoxy(11,20);        printf("--------------------------------------------------------------------------------------------------");

            gotoxy(11,21);        printf("Issue Any More(Y / N) : ");
            fflush(stdin);
            repeat:
            gotoxy(35,21);
            another=getch();
            fclose(fp);
            if(another=='y')
            {
                goto reissue;
            }
            else if(another=='n')
            {
                IssueSec();
            }
            else
            {
                gotoxy(93,21);    printf("Invalid Choice!!");
                goto repeat;
            }
        }
        break;
    }
    case '2':  //show issued book list
    {
        system("cls");
        DisplayScr();
        char getit;
        int j,x=7;
        gotoxy(54,1);          printf("ISSUED BOOKS");
        gotoxy(11,4);          printf("--------------------------------------------------------------------------------------------------");
        gotoxy(11,5);          printf("|    STUDENT NAME    | ENROLLMENT ID |  BOOK ID  |    BOOK NAME    | ISSUED  DATE | RETURN  DATE |");
        gotoxy(11,6);          printf("--------------------------------------------------------------------------------------------------");

        while(x<17)
        {
           gotoxy(11,x++);     printf("|                    |               |           |                 |              |              |");
        }
        gotoxy(11,17);       printf("--------------------------------------------------------------------------------------------------");
        gotoxy(19,18);   printf("--------------------------");
        gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
        gotoxy(19,20);   printf("--------------------------");

        gotoxy(75,18);   printf("--------------------------");
        gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
        gotoxy(75,20);   printf("--------------------------");
        gotoxy(57,19);   printf("->   <-");

        j=7,i=0;
        fs=fopen("Issue.dat","rb");
        while(fread(&b,sizeof(b),1,fs)==1)
        {

            gotoxy(14,j);    printf("%s",b.nam);
            gotoxy(35,j);    printf("%d",b.enrol);
            gotoxy(51,j);    printf("%d",b.bkid);
            gotoxy(63,j);    printf("%s",b.bknam);
            gotoxy(81,j);    printf("%d-%d-%d",b.issued.dd,b.issued.mm,b.issued.yy );
            gotoxy(96,j);    printf("%d-%d-%d",b.duedate.dd,b.duedate.mm,b.duedate.yy);
            gotoxy(50,25);
            j++;
            i++;
            if(i==10)
            {
              i=0;
              onc:
              gotoxy(60,19);
              fflush(stdin);
              getit=getch();
              switch(getit)
              {
              case '1':
                 MainMenu();
                 break;
              case '2':
              {
                system("cls");
                DisplayScr();   x=7;
                gotoxy(54,1);          printf("ISSUED BOOKS");
                gotoxy(11,4);          printf("--------------------------------------------------------------------------------------------------");
                gotoxy(11,5);          printf("|    STUDENT NAME    | ENROLLMENT ID |  BOOK ID  |    BOOK NAME    | ISSUED  DATE | RETURN  DATE |");
                gotoxy(11,6);          printf("--------------------------------------------------------------------------------------------------");

                while(x<17)
                {
                   gotoxy(11,x++);     printf("|                    |               |           |                 |              |              |");
                }
                gotoxy(11,17);       printf("--------------------------------------------------------------------------------------------------");
                gotoxy(19,18);   printf("--------------------------");
                gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
                gotoxy(19,20);   printf("--------------------------");

                gotoxy(75,18);   printf("--------------------------");
                gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
                gotoxy(75,20);   printf("--------------------------");
                gotoxy(57,19);   printf("->   <-");
                j=7;
                continue;
              }
              default:
              {
                gotoxy(53,21);   printf("Invalid  Choice");
                goto onc;
                break;
              }
              }
            }
        }
        getin:
        gotoxy(60,19);
        fflush(stdin);
        getit=getch();
        switch(getit)
        {
        case '1':
        {
            fclose(fs);        MainMenu();
            break;
        }
        case '2':
        {
            gotoxy(46,21);     printf("               ");
            gotoxy(54,21);     printf("No More Data");        goto getin;
            break;
        }
        default:
        {
            gotoxy(53,21);     printf("Invalid  Choice");     goto getin;
            break;
        }
       }
       break;
    }
    case '3':   //search issued books by id
    {
        int x=7,p; char getit;
        system("cls");
        DisplayScr();
        gotoxy(53,1);    printf("SEARCH  ISSUED");
        gotoxy(11,4);    printf("Enter Book ID : ");   scanf("%d",&p);
        gotoxy(11,4);         printf("--------------------------------------------------------------------------------------------------");
        gotoxy(11,5);         printf("|      STUDENT  NAME       |  ENROLLMENT ID  | BATCH | SEMESTER |   ISSUE DATE   |  RETURN DATE  |");
        gotoxy(11,6);         printf("--------------------------------------------------------------------------------------------------");

        while(x<17)
        {
          gotoxy(11,x++);     printf("|                          |                 |       |          |                |               |");
        }

        gotoxy(11,17);        printf("--------------------------------------------------------------------------------------------------");

        gotoxy(19,18);   printf("--------------------------");
        gotoxy(19,19);   printf("|        BACK : 1        |");
        gotoxy(19,20);   printf("--------------------------");

        gotoxy(75,18);   printf("--------------------------");
        gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
        gotoxy(75,20);   printf("--------------------------");
        gotoxy(57,19);   printf("->   <-");

        j=7,i=0;
        fs=fopen("Issue.dat","rb");
        while(fread(&b,sizeof(b),1,fs)==1)
        {
            if(b.bkid==p)
            {
              gotoxy(14,j);   printf("%s",b.nam);
              gotoxy(41,j);   printf("%d",b.enrol);
              gotoxy(59,j);   printf("%s",b.bt);
              gotoxy(67,j);   printf("%d",b.sem);
              gotoxy(78,j);   printf("%d-%d-%d",b.issued.dd,b.issued.mm,b.issued.yy);
              gotoxy(95,j);   printf("%d-%d-%d",b.duedate.dd,b.duedate.mm,b.duedate.yy);
              gotoxy(60,19);
              j++;
              i++;

              if(i==10)
              {
                i=0;
                one:
                gotoxy(60,19);
                fflush(stdin);
                getit=getch();
                switch(getit)
                {
                  case '1':
                     IssueSec();
                     break;
                  case '2':
                  {
                     system("cls");
                     DisplayScr();   x=7;
                     gotoxy(11,3);   printf("Enter Book ID : %d",p);
                     gotoxy(11,4);         printf("--------------------------------------------------------------------------------------------------");
                     gotoxy(11,5);         printf("|      STUDENT  NAME       |  ENROLLMENT ID  | BATCH | SEMESTER |   ISSUE DATE   |  RETURN DATE  |");
                     gotoxy(11,6);         printf("--------------------------------------------------------------------------------------------------");

                     while(x<17)
                     {
                       gotoxy(11,x++);     printf("|                          |                 |       |          |                |               |");
                     }

                     gotoxy(11,17);        printf("--------------------------------------------------------------------------------------------------");

                     gotoxy(19,18);   printf("--------------------------");
                     gotoxy(19,19);   printf("|        BACK : 1        |");
                     gotoxy(19,20);   printf("--------------------------");

                     gotoxy(19,20);   printf("--------------------------");
                     gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
                     gotoxy(75,20);   printf("--------------------------");
                     gotoxy(57,19);   printf("->   <-");
                     j=7;
                     continue;
                  }
                  default:
                  {
                     gotoxy(53,21);   printf("Invalid  Choice");
                     goto one;
                     break;
                  }
               }
             }
          }
        }
        geti:
        gotoxy(60,19);
        fflush(stdin);
        getit=getch();
        switch(getit)
        {
          case '1':
          {
            fclose(fp);        IssueSec();
            break;
          }
          case '2':
          {
            gotoxy(46,21);     printf("                   ");
            gotoxy(54,21);     printf("No More Data");        goto geti;
            break;
          }
          default:
          {
            gotoxy(53,21);     printf("Invalid  Choice");     goto geti;
            break;
          }
        }
        break;
    }
    case '4':                 //remove issued books from list
    {
        system("cls");
        DisplayScr();
        gotoxy(53,1);    printf("REMOVE SECTION");
        gotoxy(11,20);   printf("--------------------------------------------------------------------------------------------------");
        int bi,en;
        FILE *fg;             //declaration of temporary file for delete
        char another='y';
        while(another=='y')
        {
            gotoxy(11,4);     printf("Enter Student's Enrollment No : ");     scanf("%d",&en);
            gotoxy(89,4);     printf("Enter Book ID : ");     scanf("%d",&bi);
            fs=fopen("Issue.dat","rb+");
            while(fread(&b,sizeof(b),1,fs)==1)
            {
                if(b.bkid==bi && b.enrol==en)
                {
                    IssuedRec();
                    find='t';
                }
                if(find=='t')
                {
                    gotoxy(11,21);        printf("Confirm Remove(Y / N) : ");

                    if(getch()=='y')
                    {
                        fg=fopen("reco.dat","wb+");
                        rewind(fs);
                        while(fread(&b,sizeof(b),1,fs)==1)
                        {
                            if(b.bkid!=bi)
                            {
                            fseek(fs,0,SEEK_CUR);
                            fwrite(&b,sizeof(b),1,fg);
                            }
                        }
                        fclose(fs);
                        fclose(fg);
                        remove("Issue.dat");
                        rename("reco.dat","Issue.dat");
                        gotoxy(44,17);    printf("Issued Book Removed From The List");
                        gotoxy(43,18);    printf("-----------------------------------");
                       }

                }
                if(find!='t')
                {
                    gotoxy(50,15);        printf("No Record Found");
                    gotoxy(49,16);        printf("-----------------");
                }
            }
            gotoxy(11,21);      printf("Delete More Records(Y / N) : ");
            another=getch();
        }
        MainMenu();
        break;
    }
    case '5':
        MainMenu();
        break;
    case '6':
        LoginPortal();
        break;
    default:
        {
            gotoxy(10,18);      printf("\aWrong Entry!!");
            gotoxy(32,20);
            getch();
            IssueSec();
            break;
        }
    }
}

//show the list of book persist in library
void ViewSec(void)
{
    int x=7;
    char getit;
    system("cls");
    DisplayScr();
    gotoxy(55,1);         printf("BOOK  LIST");
    gotoxy(11,4);         printf("--------------------------------------------------------------------------------------------------");
    gotoxy(11,5);         printf("|    CATEGORY    |    ID    |      BOOK  NAME      |      AUTHOR      |  QTY  |   PRICE   | RACK |");
    gotoxy(11,6);         printf("|------------------------------------------------------------------------------------------------|");

    while(x<17)
    {
       gotoxy(11,x++);    printf("|                |          |                      |                  |       |           |      |");
    }

    gotoxy(11,17);        printf("--------------------------------------------------------------------------------------------------");

    gotoxy(19,18);   printf("--------------------------");
    gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
    gotoxy(19,20);   printf("--------------------------");

    gotoxy(75,18);   printf("--------------------------");
    gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
    gotoxy(75,20);   printf("--------------------------");
    gotoxy(57,19);   printf("->   <-");

    j=7,i=0;
    fp=fopen("Record.dat","rb");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
      gotoxy(14,j);   printf("%s",a.cat);
      gotoxy(31,j);   printf("%d",a.id);
      gotoxy(42,j);   printf("%s",a.name);
      gotoxy(65,j);   printf("%s",a.Author);
      gotoxy(84,j);   printf("%d",a.quantity);
      gotoxy(92,j);   printf("%.1f",a.Price);
      gotoxy(104,j);  printf("%d",a.rackno);
      gotoxy(60,19);
      j++;
      i++;

      if(i==10)
      {
         i=0;
         once:
         gotoxy(60,19);
         fflush(stdin);
         getit=getch();
         switch(getit)
         {
         case '1':
             MainMenu();
             break;
         case '2':
            {
                system("cls");
                DisplayScr();   x=7;
                gotoxy(55,1);         printf("BOOK  LIST");
                gotoxy(11,4);         printf("--------------------------------------------------------------------------------------------------");
                gotoxy(11,5);         printf("|    CATEGORY    |    ID    |      BOOK  NAME      |      AUTHOR      |  QTY  |   PRICE   | RACK |");
                gotoxy(11,6);         printf("--------------------------------------------------------------------------------------------------");

                while(x<17)
                {
                   gotoxy(11,x++);    printf("|                |          |                      |                  |       |           |      |");
                }

                gotoxy(11,17);        printf("--------------------------------------------------------------------------------------------------");

                gotoxy(19,18);   printf("--------------------------");
                gotoxy(19,19);   printf("|     MAIN  MENU : 1     |");
                gotoxy(19,20);   printf("--------------------------");

                gotoxy(75,18);   printf("--------------------------");
                gotoxy(75,19);   printf("|     NEXT  LIST : 2     |");
                gotoxy(75,20);   printf("--------------------------");
                gotoxy(57,19);   printf("->   <-");
                j=7;
                continue;
            }
         default:
           {
              gotoxy(53,21);   printf("Invalid  Choice");
              goto once;
              break;
           }
         }
      }
    }
    getinp:
    gotoxy(60,19);
    fflush(stdin);
    getit=getch();
    switch(getit)
    {
    case '1':
        {
        fclose(fp);        MainMenu();
        break;
        }
    case '2':
        {
            gotoxy(46,21);     printf("               ");
            gotoxy(54,21);     printf("No More Data");        goto getinp;
            break;
        }
    default:
        {
            gotoxy(53,21);     printf("Invalid  Choice");     goto getinp;
            break;
        }
    }

}

//edit book details (Edit Section)
void EditSec(void)
{
    reedit:
    system("cls");
    DisplayScr();
    char temp,temp1;
    int d;
    gotoxy(54,1);     printf("EDIT SECTION");
    gotoxy(11,20);    printf("--------------------------------------------------------------------------------------------------");
    char another='y';
    while(another=='y')
    {
        gotoxy(11,4);     printf("Enter Book Id : ");     scanf("%d",&d);

        fp=fopen("Record.dat","rb+");
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(CheckID(d)==0)
            {
                gotoxy(53,5);      printf("BOOK AVAILABLE");
                gotoxy(52,6);      printf("----------------");

                gotoxy(24,7);      printf("Present  Details");
                gotoxy(23,8);      printf("------------------");

                gotoxy(59,10);     printf("\xB2\xB2");
                gotoxy(59,11);     printf("\xB2\xB2");
                gotoxy(59,12);     printf("\xB2\xB2");
                gotoxy(59,13);     printf("\xB2\xB2");
                gotoxy(59,14);     printf("\xB2\xB2");
                gotoxy(59,15);     printf("\xB2\xB2");

                gotoxy(15,10);     printf("Book ID            : %d",a.id);
                gotoxy(15,11);     printf("Current Name       : %s",a.name);
                gotoxy(15,12);     printf("Current Author     : %s",a.Author);
                gotoxy(15,13);     printf("Current Quantity   : %d",a.quantity);
                gotoxy(15,14);     printf("Current Price      : %0.2f",a.Price);
                gotoxy(15,15);     printf("Current Rack No.   : %d",a.rackno);

                gotoxy(82,7);      printf("New  Details");
                gotoxy(79,8);      printf("------------------");

                gotoxy(65,10);     printf("Book ID            : %d",a.id);
                gotoxy(65,11);     printf("Enter New Name     : ");     scanf("%c",&temp); scanf("%[^\n]",a.name);
                gotoxy(65,12);     printf("Enter New Author   : ");     scanf("%c",&temp1); scanf("%[^\n]",a.Author);
                gotoxy(65,13);     printf("Enter New Quantity : ");     scanf("%d",&a.quantity);
                gotoxy(65,14);     printf("Enter New Price    : ");     scanf("%f",&a.Price);
                gotoxy(65,15);     printf("Enter New Rack No. : ");     scanf("%d",&a.rackno);
                gotoxy(52,17);     printf("Record  Modified");
                gotoxy(51,18);     printf("------------------");

                fseek(fp,ftell(fp)-sizeof(a),0);   // ftell is used to find position of the file pointer
                fwrite(&a,sizeof(a),1,fp);
                fclose(fp);
            }
            else
            {
                gotoxy(51,12);     printf("BOOK NOT AVAILABLE");
                gotoxy(50,13);     printf("--------------------");
            }
        }


        gotoxy(11,21);       printf("Modify Another Record(Y / N) : ");
        fflush(stdin);

        retype:
        gotoxy(42,21);
        another=getch();
        if(another=='y')
        {
            system("cls");
            DisplayScr();
            goto reedit;
        }
        else if(another=='n')
            MainMenu();
        else
        {
            goto retype;
        }
    }

}

// function to enter book details
int InputData()
{
    DisplayScr();
    int t; char temp,temp1;
    if(s>0 && s<7)
    {
    gotoxy(54,1);     printf("ADD  SECTION");

    a.cat=categories[s-1];
    gotoxy(11,4);     printf("Category  :  ");    printf("%s",categories[s-1]);

    gotoxy(53,7);     printf("Enter  Details");
    gotoxy(52,8);     printf("----------------");

    gotoxy(11,20);    printf("--------------------------------------------------------------------------------------------------");

    gotoxy(21,11);    printf("Book ID   :  ");
    scanf("%d",&t);

    if(CheckID(t)==0)
    {
        gotoxy(45,15);   printf("\aEntered Book ID Already Exists\a");
        gotoxy(44,16);   printf("--------------------------------");
        getch();
        MainMenu();
        return 0;
    }
    a.id=t;
    gotoxy(21,13);    printf("Book Name :  ");    scanf("%c",&temp); scanf("%[^\n]",a.name);
    gotoxy(21,15);    printf("Author    :  ");    scanf("%c",&temp1); scanf("%[^\n]",a.Author);

    gotoxy(59,11);    printf("\xB2\xB2");
    gotoxy(59,12);    printf("\xB2\xB2");
    gotoxy(59,13);    printf("\xB2\xB2");
    gotoxy(59,14);    printf("\xB2\xB2");
    gotoxy(59,15);    printf("\xB2\xB2");

    gotoxy(71,11);    printf("Quantity  :  ");    scanf("%d",&a.quantity);
    gotoxy(71,13);    printf("Price     :  ");    scanf("%f",&a.Price);
    gotoxy(71,15);    printf("Rack No   :  ");    scanf("%d",&a.rackno);

    return 1;
    }
    else
        return 0;
}

// function to check whether the book exists or not
int CheckID(int t)
{
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
    {
      if(a.id==t)
        return 0;    // 0 if book exists
    }
    return 1;        // 1 if book does not exists
}

// function for login portal
void LoginPortal(void)
{
   system("cls");
   DisplayScr();
   i=0; int flag=0;
   char choice,co,ch,ch1,pass[15],usrr[15];
   char d[25]="LOGIN PORTAL";
   char tx[18]="Credential Matched";
   gotoxy(54,1);   printf("%s",d);

   gotoxy(51,4);   printf("Password Protected");
   gotoxy(50,5);   printf("--------------------");
   gotoxy(11,7);   printf("User Name : ");
   gotoxy(85,7);   printf("Password  : ");

   gotoxy(11,20);  printf("--------------------------------------------------------------------------------------------------");
   gotoxy(97,7);

   gotoxy(23,7);
   while(ch!=13)       // input user name portion
   {
    fflush(stdin);
    ch=getch();
    if(ch!=13 && ch!=8)
    {
      putch('*');
      usrr[i] = ch;
      i++;
    }
   }
   usrr[i] = '\0';     // ending with NULL
   i=0;
   gotoxy(97,7);
   while(ch1!=13)       // input password portion
   {
    fflush(stdin);
    ch1=getch();
    if(ch1!=13 && ch1!=8)
    {
      putch('*');
      pass[i] = ch1;
      i++;
    }
   }
   pass[i] = '\0';     // ending with NULL

   gotoxy(10,9);
   fm=fopen("Member.dat","rb");
   while(fread(&me,sizeof(me),1,fm)==1)
   {
     if(((strcmp(usrr,me.usr)==0) && (strcmp(pass,me.pas)==0))==1)    // comparison of the inputted password with the legal password
     {
       gotoxy(51,9);
       for(i=0;i<18;i++)
       {
        delay(30);
        printf("%c",tx[i]);
       }

       gotoxy(50,12);
       printf("Hey ! %s",me.mnam);
       gotoxy(44,14);
       printf("Welcome To The Management System");
       gotoxy(43,15);
       printf("----------------------------------");

       if(cou==0)
       {
         gotoxy(11,21);    printf("Want To Continue(Y / N) : ");   scanf("%c",&choice);
         switch(choice)
         {
          case 'Y':
          case 'y':
           {
               LoadingBar();
               MainMenu();
               break;
           }
          case 'N':
          case 'n':
           {
               gotoxy(55,17);     printf("Thank  You");
               gotoxy(54,18);     printf("------------");
               gotoxy(1,25);      delay(1000);
               exit(0);
               break;
           }
          default :
           {
               gotoxy(93,21);     printf("Invalid Choice!!");
               exit(0);
           }
       }
      }
      else
      {
          LoadingBar();
          MainMenu();
      }
      flag=1;
    }
   }
   if(flag==0)
   {
       if(cou==0)
       {
           gotoxy(47,11);      printf("\aWarning!! Invalid Password\a\n");
           gotoxy(46,12);      printf("---------------------------\n");
           gotoxy(49,15);      printf("* One  Attempt  Left *\n");
           gotoxy(50,16);      printf("--------------------\n");
       }
       else
       {
           gotoxy(48,11);      printf("\a* Sorry! Attempt Fails *\a\n");
           gotoxy(49,12);      printf("----------------------\n");
           gotoxy(53,15);      printf("Wrong Password\n");
           gotoxy(52,16);      printf("----------------\n");
       }

       if(cou==0)
       {
           gotoxy(11,21);      printf("Want To Login Again(Y / N) : ");    scanf("%c",&co);
       }

       switch(co)
       {
         case 'Y':
         case 'y':
           {
               cou=1;
               LoginPortal();
               break;
           }
         case 'N':
         case 'n':
           {
               gotoxy(55,17);       printf("Thank  You");
               gotoxy(54,18);       printf("------------");
               gotoxy(1,25);
               exit(0);
               break;
           }
         default :
           {
               if(cou==0)
               {
                   gotoxy(93,21);   printf("Invalid Choice!!");
               }
               else
               {
                   gotoxy(1,25);
                   exit(0);
               }
           }
        }
   }
}

//function to display issued book's information
void IssuedRec()
{
    int fine = 0,day,month,year;
    gotoxy(54,6);    printf("RECORD FOUND");
    gotoxy(53,7);    printf("---------------");

    gotoxy(11,9);   printf("--------------------------------------------------------------------------------------------------");
    gotoxy(11,10);  printf("|                                               ||                                               |");
    gotoxy(11,11);  printf("|------------------------------------------------------------------------------------------------|");
    gotoxy(11,12);  printf("|                                               ||                                               |");
    gotoxy(11,13);  printf("|------------------------------------------------------------------------------------------------|");
    gotoxy(11,14);  printf("|                                               ||                                               |");
    gotoxy(11,15);  printf("--------------------------------------------------------------------------------------------------");
    gotoxy(13,10);   printf("Issued Book Name     : %s",b.bknam);
    gotoxy(13,12);   printf("Issued Date          : %d-%d-%d",b.issued.dd,b.issued.mm,b.issued.yy);
    gotoxy(13,14);   printf("Returning Date       : %d-%d-%d",b.duedate.dd,b.duedate.mm,b.duedate.yy);
    gotoxy(63,10);   printf("Student Name         : %s",b.nam);
    gotoxy(63,12);   printf("Student's Batch      : %s",b.bt);
    gotoxy(63,14);   printf("Student's Semester   : %d",b.sem);

    time_t now=time(NULL);
    struct tm *da = localtime(&now);
    day=da->tm_mday;
    month=da->tm_mon+1;
    year=da->tm_year+1900;

    // taking month of 30 days
    if((b.duedate.mm==month) && (day>b.duedate.dd))
    {
        fine = (day-b.duedate.dd)*10;
    }
    if(b.duedate.mm!=month && b.duedate.mm<month)
    {
        fine = (month-b.duedate.mm-1)*30*10 + (30-b.duedate.dd+day)*10;
    }
    if(fine==0)
    {
        gotoxy(57,18);   printf("NO FINE");
    }
    else
    {
        gotoxy(55,18);   printf("FINE : %d",fine);
    }
}

// function to display loading bar
void LoadingBar(void)
{
    gotoxy(48,17);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(48,18);   printf("\xDB\xDB                    \xDB\xDB");
    gotoxy(48,19);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(50,18);
    for(i=0;i<20;i++)
    {
        delay(100);
        printf("\xB2");
    }
}
//End of program
