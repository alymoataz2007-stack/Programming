#ifndef BANK_H
#define BANK_H
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"
typedef struct
{
    int day;
    int month;
    int year;
}date;
typedef struct
{
    char account_num[20];
    char name[200];
    char mobile[20];
    char email[200];
    float balance;
    date date_opened;
    char status[9];
    float dailyWithdraw;
    date withdrawDate;
    date statusdate;
}account;



extern account accounts[1000];
extern int size;

void load();

void Query( );
void AdvancedSearch();
void AddAccount();
void DeleteAccount();
void ModifyAccount();

// Ali
void load();
void Login();
void menu(int login);
int samedate(date response,int i);
 void deleteByDate();
void deletemultiple();
void deleteInactive90Days(void);


date getToday(void);
void CHANGE_STATUS(void);

void WITHDRAW(void);
void DEPOSIT(void);
void TRANSFER(void);
void REPORT(void);
void PrintSortedAccount(void);



void save();




// Helper Functions
void UpdateFile(account accounts[],int AccountsCount);
date getToday(void);
int daysBetween(date from,date to);
int FindAccountIndex(char accnumber[]);
void toLowerCase(char *str);
char* MonthIntToStr(int month);


// Validation Functions
int validateAccountNumber(char* accountNumber);
int validateName(char* name);
int validateEmail(char* email);
int validateMobile(char* mobile);
int validateBalance(char*balanceStr);

#endif
