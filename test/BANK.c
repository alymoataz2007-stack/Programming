#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "BANK.h"
#define CYAN    "\033[1;36m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

// ALI'S FUNCTIONS. LOAD
// every function should have the option to return back to main

//Helper Functions
void toLowerCase(char *str)
{
    int i;
    for(i=0; str[i]!='\0'; i++)
    {
        str[i]=tolower(str[i]);
    }
}

int FindAccountIndex(char accnumber[])
{
    int acc_ind=-1,i;

    for(i=0; i<size; i++)
    {

        if(!strcmp(accounts[i].account_num,accnumber))
        {
            acc_ind=i;
            break;
        }
    }
    if(acc_ind==-1)
        return -1;
    else return acc_ind;

}


int daysBetween(date from,date to)
{
    return(to.year-from.year)*365 +(to.month-from.month)*30+(to.day-from.day);
}


date getToday(void)
{
    date today;
    time_t currentTime=time(NULL);
    struct tm *localT=localtime(&currentTime);
    today.day= localT->tm_mday;
    today.month= localT->tm_mon+1;
    today.year= localT->tm_year+1900;

    return today;
}

char* MonthIntToStr(int month)
{
    const char *months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    if(month < 1 || month > 12)
        return "Invalid month";

    return months[month - 1];
}



account accounts[1000];


int size = 0;

// VALIDATION FUNCTIONS
int validateAccountNumber(char *accountNumber)
{

    if (strlen(accountNumber)!=10)
    {

        printf(RED "Error: Account number must be 10 digits\n" RESET);

        return 0;
    }

    for (int i=0; i<strlen(accountNumber); i++)
    {
        if (!isdigit(accountNumber[i]))
        {

            printf(RED "Error: Account number must contain only digits\n" RESET);

            return 0;
        }
    }
    if (strlen(accountNumber)== 0)
    {
        printf(RED "Error: Account number cant be empty\n" RESET);

        return 0;
    }

    return 1;
}
int validateMobile(char*mobile)
{
    if (strlen(mobile)!= 11)
    {

        printf(RED "Mobile number must be 11 digits\n" RESET);

        return 0;
    }

    for (int i=0; i<strlen(mobile); i++)
    {
        if (!isdigit(mobile[i]))
        {

            printf(RED "Error: Mobile number must contain only digits\n" RESET);

            return 0;
        }
    }
    if (strlen(mobile)==0)
    {

        printf(RED "Error: Mobile number cant be empty\n" RESET);

        return 0;
    }

    return 1;
}

int validateName(char*name)
{

    if (strlen(name)==0)
    {

        printf(RED "Error: Name cant be empty. \n" RESET);

        return 0;
    }
    if (strlen(name)<2)
    {

        printf(YELLOW "Error, Enter name again: \n" RESET);
        return 0;
    }
    if (strlen(name)>100)
    {

        printf(RED "Error: Name is too long.\n" RESET);
        return 0;
    }
    for (int i=0; i<strlen(name); i++)
    {
        if (!isalpha(name[i])&&name[i]!=' ')
        {
            printf(RED "Error: Name must be made up of letters only.\n" RESET);
            return 0;
        }
    }
    return 1;

}

int validateBalance(char*balanceStr)
{

    int i;
    int dotCount=0;
    int len=strlen(balanceStr);

    if (len==0)
    {
        printf(RED "Error: Balance cannot be empty.\n" RESET);
        return 0;
    }

    for (i=0; i<len; i++)
    {
        if (isdigit(balanceStr[i]))
        {
            continue;
        }
        else if (balanceStr[i]=='.')
        {
            dotCount++;
            if (dotCount > 1)
            {
                printf(RED "Error: Invalid format (too many decimals).\n" RESET);
                return 0;
            }
        }
        else
        {
            printf(RED "Error: Balance must contain only positive digits.\n" RESET);
            return 0;
        }
    }

    float valu=atof(balanceStr);

    if (valu<=0.0)
    {
        printf(RED "Error: Balance must be greater than 0.\n" RESET);
        return 0;
    }

    if (valu>1000000.00)
    {
        printf(RED "Error: Deposit limit exceeded (Max: 1,000,000).\n" RESET);
        return 0;
    }

    return 1;
}

int validateEmail(char*email)
{
    int atcount=0;
    int atIndex=-1;
    int dotIndex=-1;
    int dotCount=0;
    int i;

    if(email==NULL)
    {
        printf(RED "Error: Empty\n" RESET);
        return 0;
    }
    for(i=0;i<strlen(email);i++)
    {
        if(isspace(email[i]))
        {
            printf(RED "Error: Email cant contain spaces\n" RESET);
            return 0;
        }
        if(email[i]=='@')
        {
            atcount++;
            atIndex=i;
        }
    }
    if(atcount!=1)
    {
        printf(RED "Error: Email must contain only 1 @\n" RESET);
        return 0;
    }
    if(atIndex==0)
    {
        printf(RED "Error: Email cant begin with @\n" RESET);
        return 0;
    }
    for(i=atIndex+1;i<strlen(email);i++)
    {
        if(email[i]=='.')
        {
            dotCount++;
            dotIndex=i;
        }
    }
    if(dotCount!=1)
    {
        printf(RED "Error: Email must contain exactly one . after @\n" RESET);
        return 0;
    }
    if(dotIndex==atIndex+1)
    {
        printf(RED "Error: Wrong email format\n" RESET);
        return 0;
    }
    if(dotIndex==strlen(email)-1)
    {
        printf(RED "Error: email cant end with .\n" RESET);
        return 0;
    }
    return 1;
}



void save() //aly
{

    FILE*f=fopen("accounts.txt","w");
    if(f==NULL)
    {
        printf("file not found\n");
        exit(0);
    }
    for(int i=0;i<size;i++)
    {
        fprintf(f,"%s,%s,%s,%f,%s,%d-%d,%s\n",accounts[i].account_num,accounts[i].name,accounts[i].email,accounts[i].balance,accounts[i].mobile,accounts[i].date_opened.month,accounts[i].date_opened.year,accounts[i].status);
    }
    fclose(f);
}


//Aly
void load()
{
    FILE*f=fopen("accounts.txt","r");
    if(f==NULL)
    {
        printf(RED "FILE NOT FOUND\n" RESET);
        exit(0);
    }
    char*p;
    char line[500];
    while(!feof(f))
    {
        if(fgets(line,500,f)==NULL)
            break;
            line[strcspn(line, "\n")]='\0';
        p=strtok(line,",");
        if(p==NULL)
            break;
        strcpy(accounts[(size)].account_num,p);
        p=strtok(NULL,",");
        strcpy(accounts[(size)].name,p);
        p=strtok(NULL,",");
        strcpy(accounts[(size)].email,p);
        p=strtok(NULL,",");
        accounts[(size)].balance=atof(p);
        p=strtok(NULL,",");
        strcpy(accounts[(size)].mobile,p);
        p=strtok(NULL,",");
        sscanf(p,"%d-%d",&accounts[size].date_opened.month,&accounts[size].date_opened.year);
        p=strtok(NULL," ");
        strcpy(accounts[(size)].status,p);
        accounts[(size)].withdrawDate.day=-1;
        accounts[(size)].dailyWithdraw=0;
        accounts[(size)].statusdate=accounts[(size)].date_opened;
          size++;

    }
    menu(1);
    fclose(f);
}

void Login() //aly
{
    int login=0;
    int attempts=0;
    FILE *user=fopen("users.txt","r");
    if(user==NULL)
    {
        printf(RED "FILE NOT FOUND\n" RESET);
        exit(0);
    }
    char user_username[100];
    char user_password[100];
    char file_username[100];
    char file_password[100];
    int found=0;
    getchar();
    printf("please enter username\n");
    scanf("%s",user_username);
    printf("please enter password\n");
    scanf("%s",user_password);
    getchar();
    do
    {
        while(!feof(user))
        {
            fscanf(user,"%s",file_username);
            fscanf(user,"%s",file_password);

            if(strcmp(user_username, file_username) == 0 && strcmp(user_password, file_password) == 0)
            {
                found=1;
                fclose(user);
                load();
                return;
            }

        }
        attempts++;
        rewind(user);
        if(attempts>2)
        {
            printf(RED "Please try again later\n" RESET);
            menu(0);
        }
        else
        {
            printf(RED "INCORRECT USERNAME OR PASSWORD PLEASE RENTER\n" RESET);
            printf("enter username\n");
            scanf("%s",user_username);
            printf("enter password\n");
            scanf("%s",user_password);
        }
    }
    while(found==0);
    fclose(user);
}

// Ibrahim
void Query()
{
    getchar();
    printf(BLUE "\n----------Search----------\n" RESET);
    int found=0;
    int i;
    char accNumber[11];
    printf("Please enter account number: ");
    scanf("%s", accNumber);
    getchar();
    while (!validateAccountNumber(accNumber))
    {
        printf(YELLOW "\nplease enter agaim: " RESET);
        scanf("%s", accNumber);
        getchar();
    }

    for (i=0; i<size; i++)
    {

        if (strcmp(accounts[i].account_num,accNumber)==0)
        {
            found = 1;
            printf(GREEN "Account Found!\n" RESET);
            printf("\nAccount Number: %s",accounts[i].account_num);
            printf("\nName: %s",accounts[i].name);
            printf("\nE-Mail: %s", accounts[i].email);
            printf("\nBalance: %.3f $", accounts[i].balance);
            printf("\nMobile Number: %s", accounts[i].mobile);
            printf("\nDate Opened: %s %d", MonthIntToStr(accounts[i].date_opened.month), accounts[i].date_opened.year);
            printf("\nStatus: %s", accounts[i].status);
            break;
        }
    }
    if (!found)
    {
        printf(RED "Error: Account number %s does not exist\n" RESET, accNumber);

    }
    menu(1);
}
void AdvancedSearch()
{

    char keyword[100];
    int NumOfMatch = 0;
    int i;
    getchar();
    printf(BLUE "\n--------------Advanced Search--------------\n" RESET);
    printf("Please enter the keyword to search for: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")]='\0';
    while (!validateName(keyword))
    {
        printf(YELLOW "\nPlease enter valid keyword: " RESET);
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = '\0';
    }

    for (i=0; i<size; i++)
    {
        if (strstr(accounts[i].name, keyword)!=NULL)
        {
            printf("\nAccount Number: %s", accounts[i].account_num);
            printf("\nName: %s", accounts[i].name);
            printf("\nE-Mail: %s", accounts[i].email);
            printf("\nBalance: %.3f $", accounts[i].balance);
            printf("\nMobile Number: %s", accounts[i].mobile);
            printf("\nDate Opened: %s %d", MonthIntToStr(accounts[i].date_opened.month), accounts[i].date_opened.year);
            printf("\nStatus: %s\n\n", accounts[i].status);
            NumOfMatch++;
        }
    }
    if (NumOfMatch==0)
    {
        printf(YELLOW "0 matches were found for %s\n" RESET, keyword);
    }
    else
    {
        printf(GREEN "Total number of matches found are ---> %d\n" RESET, NumOfMatch);
    }
    menu(1);
}

void AddAccount()
{
    getchar();
    printf(BLUE "\n----------Add Account-----------\n" RESET);
    account newAccount;
    int dupe=0;
    int i;
    do
    {
        if (size>=1000)
        {

            printf(RED "Account storage is full\n" RESET);

            return;
        }
        printf("\nEnter new account number: ");
        fgets(newAccount.account_num, sizeof(newAccount.account_num), stdin);
        newAccount.account_num[strcspn(newAccount.account_num, "\n")]='\0';
        while (!validateAccountNumber(newAccount.account_num))
        {


            printf(YELLOW "Account number is invalid please enter again: " RESET);

            fgets(newAccount.account_num, sizeof(newAccount.account_num), stdin);
            newAccount.account_num[strcspn(newAccount.account_num, "\n")] = '\0';
        }
        for (i=0; i<size; i++)
        {
            dupe = 0;
            if (strcmp(accounts[i].account_num, newAccount.account_num)==0)
            {
                dupe = 1;

                printf(RED "An account with this account number already exists\n" RESET);

                break;
            }
        }
    }
    while (dupe);

    printf("\nEnter name: ");
    fgets(newAccount.name, sizeof(newAccount.name), stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = '\0';
    while (!validateName(newAccount.name))
    {

        printf(YELLOW "Please enter valid name again: " RESET);

        fgets(newAccount.name, sizeof(newAccount.name), stdin);
        newAccount.name[strcspn(newAccount.name, "\n")] = '\0';
    }

    printf("Enter mobile number: ");
    fgets(newAccount.mobile, sizeof(newAccount.mobile), stdin);
    newAccount.mobile[strcspn(newAccount.mobile, "\n")] = '\0';
    while (!validateMobile(newAccount.mobile))
    {

        printf(YELLOW "Please enter valid mobile number again: " RESET);

        fgets(newAccount.mobile, sizeof(newAccount.mobile), stdin);
        newAccount.mobile[strcspn(newAccount.mobile, "\n")] = '\0';
    }

    printf("Enter email: ");
    fgets(newAccount.email, sizeof(newAccount.email), stdin);
    newAccount.email[strcspn(newAccount.email, "\n")] = '\0';
    while(!validateEmail(newAccount.email))
    {

        printf(YELLOW "Please enter valid email again: " RESET);

        fgets(newAccount.email, sizeof(newAccount.email),stdin);
        newAccount.email[strcspn(newAccount.email, "\n")] ='\0';

    }
    char balanceBuffer[50];
    printf("Enter opening balance: ");
    fgets(balanceBuffer, sizeof(balanceBuffer),stdin);
    balanceBuffer[strcspn(balanceBuffer, "\n")]='\0';

    while (!validateBalance(balanceBuffer))
    {
        printf(YELLOW "Please enter a valid balance: " RESET);
        fgets(balanceBuffer, sizeof(balanceBuffer), stdin);
        balanceBuffer[strcspn(balanceBuffer,"\n")]='\0';
    }
    newAccount.balance = atof(balanceBuffer);

    newAccount.date_opened=getToday();

    strcpy(newAccount.status, "active");

    accounts[size] = newAccount;
    (size)++;
    char newFileName[15];
    snprintf(newFileName,sizeof(newFileName),"%s.txt", newAccount.account_num);

    FILE*newFile=fopen(newFileName,"w");


    printf(GREEN "Account created successfully.!\n" RESET);
    save();
    menu(1);

    return;
}

void DeleteAccount()
{
    getchar();
    printf(BLUE "\n----------Delete Account-----------\n" RESET);
    char accNum[20];
    int i;
    int index =-1;
    int found=0;


    printf("\nPlease enter account number of the account you wish to delete: ");
    fgets(accNum, sizeof(accNum), stdin);
    accNum[strcspn(accNum, "\n")] = '\0';
    while(!validateAccountNumber(accNum)){
        printf(YELLOW"Please enter again: "RESET);
         fgets(accNum, sizeof(accNum), stdin);
    accNum[strcspn(accNum, "\n")] = '\0';
    }

    for (i = 0; i <size; i++)
    {
        if (strcmp(accounts[i].account_num, accNum) == 0)
        {
            index = i;
            found=1;
            break;
        }
    }
    if (!found||index==-1)
    {
        printf(RED "\nCant find an account with the given account number. \n" RESET);
        menu(1);
    }

    if (accounts[i].balance > 0)
    {
        printf(RED "\naccount %s cant be deleted as balance is not 0.00$\n" RESET, accNum);
    }
    else
    {
        for (i = index; i < size; i++)
        {
            accounts[i] = accounts[i + 1];
        }
        (size)--;
        printf(GREEN "\nAccount deleted successfully!\n" RESET);
    }
    save();
    menu(1);
}

void ModifyAccount()
{

    printf(BLUE "\n----------Modify Account-----------\n" RESET);
    char accNum[20];
    int index =-1;
    int i;
    int found = 0;
getchar();
    printf("\nPlease enter account number of the account you wish to modify: ");
    fgets(accNum, sizeof(accNum), stdin);
    accNum[strcspn(accNum, "\n")] = '\0';
     while (!validateAccountNumber(accNum))
        {


            printf(YELLOW "Account number is invalid please enter again: " RESET);

            fgets(accNum, sizeof(accNum), stdin);
            accNum[strcspn(accNum, "\n")] = '\0';
        }

    for (i = 0; i < size; i++)
    {
        if (strcmp(accounts[i].account_num, accNum) == 0)
        {
            index = i;
            found = 1;
            break;
        }
    }

    if (found!=1||index==-1)
    {
        printf(RED "\nCan't find an account with the given account number.\n" YELLOW"Going back to menu!\n" RESET);
        menu(1);
    }

    printf(GREEN "Account found. Press enter to continue\n" RESET);
    getchar();
    printf("Enter new name: ");
    fgets(accounts[index].name, sizeof(accounts[index].name),stdin);
    accounts[index].name[strcspn(accounts[index].name, "\n")] = '\0';
    while (!validateName(accounts[index].name))
    {
        printf(YELLOW "Please enter valid name again: " RESET);
        fgets(accounts[index].name, sizeof(accounts[index].name), stdin);
        accounts[index].name[strcspn(accounts[index].name, "\n")]= '\0';
    }

    printf("\nEnter mobile: ");
    fgets(accounts[index].mobile, sizeof(accounts[index].mobile),stdin);
    accounts[index].mobile[strcspn(accounts[index].mobile, "\n")]='\0';
    while (!validateMobile(accounts[index].mobile))
    {
        printf(YELLOW "Please enter valid mobile number again: " RESET);
        fgets(accounts[index].mobile, sizeof(accounts[index].mobile), stdin);
        accounts[index].mobile[strcspn(accounts[index].mobile, "\n")] = '\0';
    }

    printf("\nEnter email: ");
    fgets(accounts[index].email, sizeof(accounts[index].email),stdin);
    accounts[index].email[strcspn(accounts[index].email, "\n")]='\0';
    while(!validateEmail(accounts[index].email))
    {
        printf(YELLOW "Please enter valid email again: " RESET);
        fgets(accounts[index].email, sizeof(accounts[index].email),stdin);
        accounts[index].email[strcspn(accounts[index].email, "\n")] ='\0';

    }
    save();

    printf(GREEN "Account number: %s has been modified successfully!\n" RESET, accNum);
    menu(1);
}

void CHANGE_STATUS(void)
{
    getchar();
    printf(BLUE "\n--------------Change Status--------------\n" RESET);
    int acc_ind,i;
    char accnumber[20];
    printf("Enter account number:\n");
    scanf("%19s",accnumber);
     while(!validateAccountNumber(accnumber)){
        printf(YELLOW "Account number is invalid please enter again: " RESET);

            fgets(accnumber, sizeof(accnumber), stdin);
            accnumber[strcspn(accnumber, "\n")]='\0';

    }
    acc_ind=FindAccountIndex(accnumber);
    if(acc_ind==-1)
    {
        printf(RED "Account doesn't exist\n" RESET);
        menu(1);
    }

    char new_status[10];
    do
    {

        printf("Enter new status (active/inactive)\n");

        scanf("%9s",new_status);
        toLowerCase(new_status);
        if(strcmp(new_status,"active")!=0 && strcmp(new_status,"inactive")!=0)
        {
            printf(YELLOW "Invalid status, please re-enter status\n" RESET);
        }
    }
    while(strcmp(new_status,"active")!=0 && strcmp(new_status,"inactive")!=0);

    printf("Your current status is %s\n",accounts[acc_ind].status);
    printf("Are you sure you want to change your status to %s (yes/no)\n",new_status);
    char response[5];
    do
    {
        scanf("%4s",response);
        toLowerCase(response);
        if(strcmp(response,"yes")!=0 &&strcmp(response,"no")!=0 )
        {
            printf(YELLOW "Invalid response, please try again\n" RESET);
        }

    }
    while(strcmp(response,"yes")!=0 && strcmp(response,"no")!=0 );

    if(!strcmp(response,"yes") && strcmp(accounts[acc_ind].status,new_status))
    {
        strcpy(accounts[acc_ind].status,new_status);
        accounts[acc_ind].statusdate=getToday();
        printf(GREEN "Status has been changed to %s\n" RESET,new_status);
    }
    else if(!strcmp(response,"no"))
    {
        printf(YELLOW "Status will remain as %s\n" RESET,accounts[acc_ind].status);
    }
    else
    {
        printf(RED "Status is already %s" RESET,&new_status);
    }
    save();
     menu(1);

}

void WITHDRAW(void)
{
    getchar();
    printf(BLUE "\n--------------Withdraw--------------\n" RESET);
    float amount;
    date today;
    int acc_ind;
    char accnumber[20];
    printf("Enter account number:\n");
    scanf("%19s",accnumber);
    getchar();

    while(!validateAccountNumber(accnumber)){
        printf(YELLOW "Account number is invalid please enter again: " RESET);

            fgets(accnumber, sizeof(accnumber), stdin);
            accnumber[strcspn(accnumber, "\n")]='\0';

    }
    acc_ind=FindAccountIndex(accnumber);
    if(acc_ind==-1)
    {
        printf(RED "Account doesn't exist\n" RESET);
        menu(1);
    }
    if(!strcmp(accounts[acc_ind].status, "inactive"))
    {
        printf(RED "Account is inactive, Withdrawal denied\n" RESET);
        menu(1);
    }

    printf("Enter amount:\n");
    while(scanf("%f",&amount)!=1|| amount<=0)
    {
        printf(RED "Invalid input, Enter a positive number.\n" RESET);
        while(getchar()!= '\n');

    }
    if(amount>10000)
    {
        printf(RED "Max withdrawal per transaction is 10,000\n" RESET);
        menu(1);
    }

    if(amount>accounts[acc_ind].balance)
    {
        printf(RED "Insufficient balance\n" RESET);
        menu(1);

    }


    today=getToday();
    if(accounts[acc_ind].withdrawDate.day!=today.day || accounts[acc_ind].withdrawDate.month!=today.month || accounts[acc_ind].withdrawDate.year!=today.year)
    {
        accounts[acc_ind].dailyWithdraw=0;
        accounts[acc_ind].withdrawDate=today;

    }

    if(accounts[acc_ind].dailyWithdraw +amount>50000)
    {
        printf(RED "Daily limit exceeded\n" RESET);
        menu(1);
    }




    char filename[30];
    snprintf(filename, sizeof(filename), "%s.txt", accnumber);
    FILE *transaction=fopen(filename,"a");
    if(transaction==NULL)
    {
        printf(RED "Error opening transaction file\n" RESET);
        menu(1);
    }
    fprintf(transaction,"Withdraw %.2f\n",amount);
    fclose(transaction);

    accounts[acc_ind].balance=accounts[acc_ind].balance-amount;
    accounts[acc_ind].dailyWithdraw=accounts[acc_ind].dailyWithdraw+amount;
    printf(GREEN "Withdrawal successful\n" RESET);
save();
 menu(1);

}

void DEPOSIT(void)
{
    getchar();
    printf(BLUE "\n--------------Deposit--------------\n" RESET);
    float amount;
    int acc_ind;
    char accnumber[20];
    printf("Enter account number:\n");
    scanf("%19s",accnumber);
    getchar();
     while(!validateAccountNumber(accnumber)){
        printf(YELLOW "Account number is invalid please enter again: " RESET);

            fgets(accnumber, sizeof(accnumber), stdin);
            accnumber[strcspn(accnumber, "\n")]='\0';

    }
    acc_ind=FindAccountIndex(accnumber);
    if(acc_ind==-1)
    {
        printf(RED "Account doesn't exist\n" RESET);
       menu(1);
    }
    if(!strcmp(accounts[acc_ind].status, "inactive"))
    {
        printf(RED "Account is inactive, Deposit denied\n" RESET);
       menu(1);
    }

    printf("Enter amount:\n");
    while(scanf("%f",&amount)!=1|| amount<=0)
    {
        printf(RED "Invalid input, Enter a positive number.\n" RESET);
        while(getchar()!= '\n');

    }

    if(amount>10000)
    {
        printf(RED "Max deposit per transaction is 10,000\n" RESET);
       menu(1);
    }



    char filename[30];
    snprintf(filename, sizeof(filename), "%s.txt", accnumber);
    FILE *transaction=fopen(filename,"a");
    if(transaction==NULL)
    {
        printf(RED "Error opening transaction file\n" RESET);
     menu(1);
    }
    fprintf(transaction,"Deposit %f\n",amount);
    fclose(transaction);
    accounts[acc_ind].balance=accounts[acc_ind].balance+amount;
    printf(GREEN "Deposit successful\n" RESET);
    save();
     menu(1);
}

void TRANSFER(void)
{
    getchar();
    printf(BLUE "\n--------------Transfer--------------\n" RESET);
    float amount;
    int sender_ind,receiver_ind;
    char sender_num[20],receiver_num[20];
    printf("Enter your account number\n");
    scanf("%19s",sender_num);
    getchar();
     while(!validateAccountNumber(sender_num)){
        printf(YELLOW "Account number is invalid please enter again: " RESET);

            fgets(sender_num, sizeof(sender_num), stdin);
            sender_num[strcspn(sender_num, "\n")]='\0';

    }
    sender_ind=FindAccountIndex(sender_num);
    if(sender_ind==-1)
    {
        printf(RED "Account doesn't exist\n" RESET);
       menu(1);
    }
    printf("Enter receiver account number\n");
    scanf("%19s",receiver_num);
     while(!validateAccountNumber(receiver_num)){
        printf(YELLOW "Account number is invalid please enter again: " RESET);

            fgets(receiver_num, sizeof(receiver_num), stdin);
            receiver_num[strcspn(receiver_num, "\n")]='\0';

    }
    receiver_ind=FindAccountIndex(receiver_num);
    if(receiver_ind==-1)
    {
        printf(RED "Account doesn't exist\n" RESET);
      menu(1);
    }

    if(!strcmp(accounts[sender_ind].status, "inactive"))
    {
        printf(RED "Your account is inactive, Transfer denied\n" RESET);
       menu(1);
    }
    else if(!strcmp(accounts[receiver_ind].status, "inactive"))
    {
        printf(RED "Receiver's account is inactive, Transfer denied\n" RESET);
       menu(1);
    }

    printf("Enter amount to transfer:\n");

    while(scanf("%f",&amount)!=1|| amount<=0)
    {
        printf(RED "Invalid input, Enter a positive number.\n" RESET);
        while(getchar()!= '\n');

    }
    if(amount>accounts[sender_ind].balance)
    {
        printf(RED "Insufficient balance\n" RESET);
        menu(1);
    }




    char filesender[30],filereceiver[30];
    FILE *transaction;

    snprintf(filesender, sizeof(filesender), "%s.txt", sender_num);
    transaction=fopen(filesender,"a");
    if(transaction==NULL)
    {
        printf(RED "Error opening transaction file\n" RESET);
        menu(1);
    }
    fprintf(transaction,"TransferOut %f\n",amount);
    fclose(transaction);


    snprintf(filereceiver, sizeof(filereceiver), "%s.txt", receiver_num);
    transaction=fopen(filereceiver,"a");
    if(transaction==NULL)
    {
        printf(RED "Error opening transaction file\n" RESET);
        menu(1);
    }
    fprintf(transaction,"TransferIn %f\n",amount);
    fclose(transaction);

    accounts[sender_ind].balance=accounts[sender_ind].balance-amount;
    accounts[receiver_ind].balance=accounts[receiver_ind].balance+amount;

    printf(GREEN "Transfer successful\n" RESET);
    save();
    menu(1);

}



void REPORT(void)
{
    getchar();
    printf(BLUE "\n--------------Report--------------\n" RESET);
    int acc_ind;
    char accnumber[20];
    printf("Enter account number:\n");
    scanf("%19s",accnumber);
     getchar();
     while(!validateAccountNumber(accnumber)){
        printf(YELLOW "Account number is invalid please enter again: " RESET);

            fgets(accnumber, sizeof(accnumber), stdin);
            accnumber[strcspn(accnumber, "\n")]='\0';

    }
    acc_ind=FindAccountIndex(accnumber);
    if(acc_ind==-1)
    {
        printf(RED "Account doesn't exist\n" RESET);
        menu(1);
    }
    char filename[30];
    char lines[100][100];
    int count=0;
    snprintf(filename, sizeof(filename), "%s.txt", accnumber);
    FILE *transaction=fopen(filename,"r");
    if(transaction==NULL)
    {
        printf(YELLOW "No transaction history for this account\n" RESET);
        menu(1);
    }
    while (count<100 && fgets(lines[count], 100, transaction)!=NULL)
    {
        count++;
    }

    fclose(transaction);
    if(count==0)
    {
        printf(YELLOW "No transactions found\n" RESET);
        menu(1);
    }
    printf(BLUE "Transaction report for account %s\n" RESET,accnumber);
    int start=count-5,i;
    if(start<0)
        start=0;
    for(i=start; i<count; i++)
    {
        printf("%s",lines[i]);
    }
 menu(1);
}

void sortbyname() // ascending in names
{
    int swap=1;
    account temp;
    while(swap)
    {
        swap=0;
        for(int i=0;i<size-1;i++)
        {
          if(strcmp(accounts[i].name,accounts[i+1].name)>0)
          {
              swap=1;
              temp=accounts[i];
              accounts[i]=accounts[i+1];
              accounts[i+1]=temp;
          }
        }
    }
}
void sortbydate() // newest account el awel
{
    int swap=1;
    account temp;
    while(swap)
    {
        swap=0;
        for(int i=0;i<size-1;i++)
        {
            if(accounts[i].date_opened.year<accounts[i+1].date_opened.year||(accounts[i].date_opened.year==accounts[i+1].date_opened.year&&accounts[i].date_opened.month<accounts[i+1].date_opened.month))
            {
                swap=1;
                temp=accounts[i];
                accounts[i]=accounts[i+1];
                accounts[i+1]=temp;
            }
        }
    }
}
void sortbybalance() //ascending balance
{
    int swap=1;
    account temp;
    while(swap)
    {
        swap=0;
        for(int i=0;i<size-1;i++)
        {
            if(accounts[i].balance>accounts[i+1].balance)
            {
                swap=1;
                temp=accounts[i];
                accounts[i]=accounts[i+1];
                accounts[i+1]=temp;
            }
        }
    }
}
void sortbystatus()// prints active accounts first b3dein inactive
{
    int swap=1;
    account temp;
    while(swap)
    {
        swap=0;
        for(int i=0;i<size-1;i++)
        {
            if(strcmp(accounts[i].status,"inactive")==0&&strcmp(accounts[i+1].status,"active")==0)
            {
                swap=1;
                temp=accounts[i];
                accounts[i]=accounts[i+1];
                accounts[i+1]=temp;
            }
        }
    }
}
void PrintSortedAccount(void)

{
    int correct=0;
    int response;
    int word=1;
    int ch;
    getchar();
    do
    {

        printf(BLUE"\n----------Print Accounts----------\n");
        printf(CYAN"1.SORT BY NAME\n");
        printf("2.SORT BY DATE\n");
        printf("3.SORT BY BALANCE\n");
        printf("4.SORT BY STATUS\n"RESET);
        do
         {
           if(scanf("%d",&response)!=1)
                {
                printf("\nPlease enter a number: ");
                word=1;
                while((ch=getchar())!='\n'&&ch!=EOF);
           }
           else
            word=0;
         }while(word==1);
         switch(response)
         {
           case 1:
            correct=1;
           sortbyname();
            break;
           case 2:
            correct=1;
            sortbydate();
            break;
           case 3:
            correct=1;
            sortbybalance();
           break;
           case 4:
            correct=1;
            sortbystatus();
            break;
           default:
            printf(RED"Please enter a valid option\n"RESET);
         }

    }while(correct==0);
    for(int i=0;i<size;i++)
    {
        printf("%s,%s,%s,%f,%s,%s %d,%s\n",accounts[i].account_num,accounts[i].name,accounts[i].email,accounts[i].balance,accounts[i].mobile,MonthIntToStr(accounts[i].date_opened.month),accounts[i].date_opened.year,accounts[i].status);
    }
    menu(1);
}



int samedate(date response,int i)
{
    if(accounts[i].date_opened.month==response.month&&accounts[i].date_opened.year==response.year)
        return 1;

    return 0;
}
void deleteByDate()
{
    date response;
    printf("please enter month\n");
    scanf("%d",&response.month);
    printf("please enter year\n");
    scanf("%d",&response.year);
    for(int i=0; i<size; i++)
    {
        if(samedate(response,i))
        {
            for(int j=i; j<size-1; j++)
                accounts[j]=accounts[j+1];
            size--;
            i--;
        }

    }
    printf(GREEN "Deleted accounts successfully\n" RESET);
    save();
}

void deleteInactive90Days(void)
{
    date today=getToday();
    account temp[100];
    int newSize=0;
    int deleted=0;

    for(int i=0; i<size; i++)
    {
        if(strcmp(accounts[i].status,"inactive")==0 &&
                accounts[i].balance==0 &&
                daysBetween(accounts[i].statusdate,today)>90)
        {
            deleted++;
        }
        else
        {
            temp[newSize++]=accounts[i];
        }
    }

    size=newSize;
    for(int i=0; i<size; i++)
    {
        accounts[i]=temp[i];
    }

    save();

    if(deleted==0)
    {
        printf(YELLOW "No inactive accounts eligible for deletion.\n" RESET);
    }
    else
    {
        printf(GREEN "Operation completed successfully.\n" RESET);
        printf(GREEN "Number of accounts deleted: %d\n" RESET, deleted);
    }
}


void deletemultiple()
{
    printf(BLUE "\n--------------Delete Multible--------------\n" RESET);
    int choice;
    int correct=0;
    int word=0;
    int ch;

    do
    {
        printf("1.Delete by creation date\n");
        printf("2.Delete inactive accounts\n");
        do
        {
            if(scanf("%d",&choice)!=1)
            {
                printf("Please enter a number: ");
                word=1;
                while((ch=getchar())!='\n'&&ch!=EOF);
            }
            else
                word=0;
        }
        while(word==1);
        switch (choice)
        {
        case 1:
            deleteByDate();
            correct=1;
            break;
        case 2:
            deleteInactive90Days();
            correct=1;
            break;

            printf(RED "Error: Please enter valid option\n" RESET);

        }
    }
    while(correct==0);
    menu(1);
}









void menu(int login)
{
    int response;
    int correct=0;
    int word=1;
    int ch;
    if(login==0)
    {
        do
        {
            printf(BLUE "--------WELCOME TO ZOR BANK---------\n" RESET);
            printf("Choose what you would like to do\n");
            printf(CYAN"0.QUIT\n");
            printf("1.LOGIN\n"RESET);
            do
            {
                if(scanf("%d",&response)!=1)

                {
                    printf(YELLOW "Please enter a number\n" RESET);
                    word=1;
                    while((ch=getchar())!='\n'&&ch!=EOF);
                }
                else
                    word=0;
            }
            while(word==1);
            if(response==1)
            {
                correct=1;
                Login();
                return;
            }
            else if(response==0)
            {
                correct=1;
                printf(GREEN "Exiting Bank!" RESET);
                exit(0);
            }
            printf("");
            printf(RED "INCORRECT CHOICE PLEASE CHOOSE FROM OPTIONS\n" RESET);
        }
        while(correct==0);
    }
    else
    {
        do
        {
            printf("\nChoose what you would like to do\n");
            printf(CYAN"0.QUIT\n");
            printf("1.LOGIN\n");
            printf("2.ADD\n");
            printf("3.DELETE\n");
            printf("4.MODIFY\n");
            printf("5.SEARCH\n");
            printf("6.ADVANCED SEARCH\n");
            printf("7.CHANGE STATUS\n");
            printf("8.WITHDRAW\n");
            printf("9.DEPOSIT\n");
            printf("10.TRANSFER\n");
            printf("11.REPORT\n");
            printf("12.PRINT\n");
            printf("13.DELETE MULTIBLE\n"RESET);
            do
            {
                if(scanf("%d",&response)!=1)
                {
                    printf(YELLOW "Please enter a number\n" RESET);
                    word=1;
                    while((ch=getchar())!='\n'&&ch!=EOF);
                }
                else
                    word=0;
            }
            while(word==1);
            switch(response)
            {
            case 0:
                printf(BLUE "\n-Exiting Bank! See you soon-\n" RESET);
                correct=1;
                exit(0);
            case 1:
                correct=1;
                Login();
                break;
            case 2:
                correct=1;
                AddAccount();
                break;
            case 3:
                correct=1;
                DeleteAccount();
                break;
            case 4:
                correct=1;
                ModifyAccount();
                break;
            case 5:
                correct=1;
                Query();
                break ;
            case 6:
                correct=1;
                AdvancedSearch();
                break ;
            case 7:
                correct=1;
                CHANGE_STATUS();
                break;
            case 8:
                correct=1;
                WITHDRAW();
                break;
            case 9:
                correct=1;
                DEPOSIT();
                break;
            case 10:
                correct=1;
                TRANSFER();
                break;
            case 11:
                correct=1;
                REPORT();
                break;
            case 12:
                correct=1;
                PrintSortedAccount();
                break;
            case 13:
                correct=1;
                deletemultiple();
                break;
            default:
                printf(RED "\nINCORRECT CHOICE PLEASE CHOOSE FROM OPTIONS\n" RESET);
            }
        }
        while(correct==0);
    }


}
