/*
gcc main.c -I"F:\Shubham\PMDS Project\Project Final" -L"F:\Shubham\PMDS Project\Project Final" -lsqlite3
*/
#include<stdio.h>
#include "F:\Shubham\PMDS Project\Project Final\sqlite3.h"
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

sqlite3* db;
char* err_message=0;
int check;
const char* data = "";
int item_price=0;
int EmpId;
int BillId;
char CustId[10];
int CustId_int=0;
char s_day[3],s_mon[3];
int bday_found=0;
int anni_found=0;

int display_menu();
char* main_course();
int display_employee();
int display_customer();
int order();
int place_order(int);
int print_bill(int *);
int add_bill_db();
int add_update_emp();
int add_emp();
int update_emp();
int validate(char*);
int validate_date(char*,char*,char*);
int check_member();
void CustomerID();
void Orderdate();
int searchbill();
int bday_anni(int);
int bday_anni_bill(int);
int add_update_customer();
int add_customer();
int update_customer();
void thankyou();
/*static int callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
   fprintf(stderr, "%s", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
  // printf("\n");
   return 0;
}
*/

static int callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
   for(i = 0; i<argc; i++)
   {
	  printf("%s",argv[i] ? argv[i] : "NULL");
	  if(i!=0)
	  {	
		for(int j=0;j<32-strlen(argv[i]);j++)
			printf(" ");
	  }
	  else
		printf("\t\t");
   }
   printf("\n");
   return 0;
}

static int callback_order(void *data, int argc, char **argv, char **azColName)
{
	int i;
	for(i = 0; i<argc; i++)
   {
	  sscanf(argv[i], "%d", &item_price); 
   }
}


static int callback_empid(void *data, int argc, char **argv, char **azColName)
{
	for(int i=0;i<argc;i++)
		sscanf(argv[i],"%d",&EmpId);
	return 0;
}

static int callback_bill_id(void *data, int argc, char **argv, char **azColName)
{
	for(int i=0;i<argc;i++)
		sscanf(argv[i],"%d",&BillId);
	return 0;
}

static int callback_dob(void *data, int argc, char **argv, char **azColName)
{
	int i;
	char * date= argv[0];
	if(strlen(s_day)==1)
	{
		strcat(s_day,"0");
		strrev(s_day);
	}
	if(strlen(s_mon)==1)
	{	
		strcat(s_mon,"0");
		strrev(s_mon);
	}
	strcpy(CustId,argv[1]);
   char q[200];
   for(i = 0; i<argc-1; i++)
   {
	   if((*(date+5)==s_mon[0] || *(date+5)==0)  && (*(date+6)==s_mon[1] || *(date+6)==0))
	   {
		   if((*(date+8)==s_day[0] || *(date+8)==0) && (*(date+9)==s_day[1] || *(date+9)==0))
		   {
			   //printf("entered if bday\n");
			   sprintf(q,"SELECT * FROM Customer WHERE CustomerId='%s';",CustId);
			   check= sqlite3_exec(db,q,callback,(void*) data,&err_message);
		   }
	   }		    
	    return 0;
   }
}
 
static int callback_dob_bill(void *data, int argc, char **argv, char **azColName)
{
	int i;
	char * date= argv[0];
	//printf("entered callbcak\n");
	if(strlen(s_day)==1)
	{
		strcat(s_day,"0");
		strrev(s_day);
	}
	if(strlen(s_mon)==1)
	{	
		strcat(s_mon,"0");
		strrev(s_mon);
	}
	//printf("%s %s %s\n",s_day,s_mon,date);
	//printf("%s\n",date);
   char q[200];
   for(i = 0; i<argc; i++)
   {
	   if((*(date+5)==s_mon[0] || *(date+5)==0)  && (*(date+6)==s_mon[1] || *(date+6)==0))
	   {
		   if((*(date+8)==s_day[0] || *(date+8)==0) && (*(date+9)==s_day[1] || *(date+9)==0))
		   {
			   bday_found=1;
		   }
	   }		   
	    return 0;
   }
}
 
static int callback_doa(void *data, int argc, char **argv, char **azColName)
{
	int i;
	char * date= argv[0];
	if(strlen(s_day)==1)
	{
		strcat(s_day,"0");
		strrev(s_day);
	}
	if(strlen(s_mon)==1)
	{	
		strcat(s_mon,"0");
		strrev(s_mon);
	}
	strcpy(CustId,argv[1]);
   if(strcmp(date,"0-0-0")!=0)
   {
   char q[200];
   for(i = 0; i<argc; i++)
   {
	   if((*(date+5)==s_mon[0] || *(date+5)==0)  && (*(date+6)==s_mon[1] || *(date+6)==0))
	   {
		   if((*(date+8)==s_day[0] || *(date+8)==0) && (*(date+9)==s_day[1] || *(date+9)==0))
		   {
			   //printf("entered if anni\n");
			   sprintf(q,"SELECT * FROM Customer WHERE CustomerId='%s';",CustId);
			   check= sqlite3_exec(db,q,callback,(void*) data,&err_message);
		   }
	   }		   
	    return 0;
   }
   }
}

static int callback_doa_bill(void *data, int argc, char **argv, char **azColName)
{
	int i;
	char * date= argv[0];
	//printf("entered callbcak doa\n");
	if(strlen(s_day)==1)
	{
		strcat(s_day,"0");
		strrev(s_day);
	}
	if(strlen(s_mon)==1)
	{	
		strcat(s_mon,"0");
		strrev(s_mon);
	}
	//printf("%s %s %s\n",s_day,s_mon,date);
   if(strcmp(date,"0-0-0")!=0)
   {
   char q[200];
   for(i = 0; i<argc; i++)
   {
	   if((*(date+5)==s_mon[0] || *(date+5)==0)  && (*(date+6)==s_mon[1] || *(date+6)==0))
	   {
		   if((*(date+8)==s_day[0] || *(date+8)==0) && (*(date+9)==s_day[1] || *(date+9)==0))
		   {
				anni_found=1;
		   }
	   }		   
	    return 0;
   }
   }
}

static int callback_custid(void *data, int argc, char **argv, char **azColName)
{
	for(int i=0;i<argc;i++)
		sscanf(argv[i],"%d",&CustId_int);
	return 0;
} 

int main()
{
	int ch;
	check=sqlite3_open("Restaurant.db",&db);
	if(check==SQLITE_OK)
	{
		do{
			printf("                             _               _            \n");
			printf("                            | |             | |           \n");
			printf("  _ __ ___  _   _ _ __   ___| |__   ___  ___| |_ ___ _ __ \n");
			printf(" | '_ ` _ \\| | | | '_ \\ / __| '_ \\ / _ \\/ __| __/ _ \\ '__|\n");
			printf(" | | | | | | |_| | | | | (__| | | |  __/\\__ \\ ||  __/ |   \n");
			printf(" |_| |_| |_|\\__,_|_| |_|\\___|_| |_|\\___||___/\\__\\___|_|   \n\n");
			printf("1. View Our Menu\n");
			printf("2. View Customer Information\n");
			printf("3. View Employee Information\n");
			printf("4. Add/Update Employee Information\n");
			printf("5. Add/Update Customer Information\n");//shubham
			printf("6. View Upcomming Birthdays/Anniversaries\n");//yug
			printf("7. Search for Bill\n");
			printf("8. Place an order\n");//sarika
			printf("9. Exit\n");
			printf("Enter your choice\n");
			scanf("%d",&ch);
			printf("\n");
			switch(ch)
			{
				case 1: display_menu(); //done
						break;
				case 2: display_customer(); //done
						break;
				case 3: display_employee(); //done
						break;
				case 4: add_update_emp();//done with validation
						break;
				case 5:add_update_customer();// do vali
						break;
				case 6:  printf("Enter number of days to check within \n");
						int n;
						scanf("%d",&n);
						bday_anni(n);// do vali
						break;
				case 7: searchbill();
						break;
				case 8: order(); //partially done, correct space
						break;
				case 9: thankyou();
						return 0;
						break;
						
				default: printf("Please enter a valid number (1-9)\n");
			}
		}while(1);	
	}
	else
		printf("Error opening database\n");
	return 0;
}

int display_customer()
{
	printf("Customer Id \tName \t\t\t\t Ph No \t\t\t\t Email \t\t\t\t\t DoB \t\t\t\tDoA\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	check= sqlite3_exec(db,"SELECT * FROM Customer",callback,(void*) data,&err_message);
	printf("\n");
}

int display_employee()
{
	printf("Employee Id \tName \t\t\t\t Post \t\t\t\t Salary \t\t\t\t Ph No \t\t\t\t DoB\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	check= sqlite3_exec(db,"SELECT * FROM Employee",callback,(void*) data,&err_message);
	printf("\n");
}

int display_menu()
{
	int ch;
	while(1)
	{
		printf("Select Category\n");
		printf("1. Soups\n");
		printf("2. Starters\n");
		printf("3. Main Course\n");
		printf("4. Desserts\n");
		printf("5. Mocktails\n");
		printf("6. Hard Drinks\n");
		printf("7. All Categories\n");
		printf("8. Go Back\n");
		printf("Enter choice\n");
		scanf("%d",&ch);
		char* category;
		char q[70]="SELECT SrNo,Item,Price FROM Menu WHERE Category=";
		switch(ch)
		{
			case 1: category="'Soups';";
					break;
			case 2: category="'Starters';";
					break;
			case 3: category=main_course();
					break;
			case 4: category="'Desserts';";
					break;
			case 5: category="'Mocktails';";
					break;
			case 6: category="'Hard Drinks';";
					break;
			case 7: strcpy(q,"SELECT SrNo,Item,Price FROM Menu;");
					category="";
					break;
			case 8: printf("\n");
					return 0;
					break;
			default: printf("Please enter a valid number (1-9)\n");
		}
		if(strcmp("",category)!=0)
			strcat(q,category);
			printf("Sr. No.\t\tItem\t\t\t\tPrice\n--------------------------------------------------------\n");
			check= sqlite3_exec(db,q,callback,(void*) data,&err_message);
			printf("\n");
	}
}
char* main_course()
{
	int ch;
	while(1)
	{
		printf("Select Sub-Category\n");
		printf("1. Italian\n");
		printf("2. Chinese\n");
		printf("3. Indian\n");
		printf("4. Punjabi\n");
		printf("5. Indian Breads\n");
		printf("6. Go back\n");
		printf("Enter choice\n");
		scanf("%d",&ch);
		char* category;
		switch(ch)
		{
			case 1: return"'Main Course(Italian)';";
					break;
			case 2: return"'Main Course(Chinese)';";
					break;
			case 3: return"'Main Course(Indian)';";
					break;
			case 4: return"'Main Course(Punjabi)';";
					break;
			case 5: return"'Main Course(Indian Breads)';";
					break;
			case 6: return "";
					break;
			default: printf("Enter a valid option\n");
		}
	}
}

int add_update_emp()
{
	int choice;
	printf("1. Add employee record.\n");
	printf("2. Update existing employee record.\n");
	printf("3. Go Back\n");
	printf("Enter choice\n");
	scanf("%d",&choice);
	while(1)
	{
		switch(choice)
		{
			case 1: add_emp();
					break;
			case 2: update_emp();
					break;
			case 3: return 1;
					break;
			default: printf("Please enter a valid number (1-9)\n");
		}
		break;
	}
	return 0;
}

int add_emp()
{
	int n;
	int check=1;
	printf("How many employees do you want to add?\n");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		char EmpName[20],Post[20],query[200],Phno[10],Salary[10],Month[3],Year[5],Date[3];
		char q[100]="SELECT EmpId FROM Employee ORDER BY EmpId DESC LIMIT 1";
		sqlite3_exec(db,q,callback_empid,(void*) data,&err_message);
		EmpId+=1;
		printf("Enter name of employee: ");
		scanf(" %[^\n]%*c",EmpName);
		printf("Enter post: ");
		scanf(" %[^\n]%*c",Post);
		while(check)
		{	
			printf("Enter salary: ");
			scanf("%s",&Salary);
			check=validate(Salary);
			if(check==1)
				printf("Only numbers accepted\n");
		}
		check=1;
		while(check)
		{
			printf("Enter Phone number(10 digits): ");
			scanf("%s",Phno);
			check=validate(Phno);
			if(check==1)
				printf("Only numbers accepted\n");
		}
		check=1;
		while(check)
		{
			printf("Enter DOB (DD MM YY): ");
			scanf("%s %s %s",&Date,&Month,&Year);
			check= validate_date(Date,Month,Year);
			if(check==1)
				printf("Invalid\n");
		}
		sprintf(query,"INSERT INTO Employee VALUES(%d,'%s','%s',%d,%s,'%s-%s-%s');",EmpId,EmpName,Post,Salary,Phno,Year,Month,Date);
		check=sqlite3_exec(db,query,0,0,&err_message);
		if(check!=SQLITE_OK)
				printf("Error\n");
			else 
			{
				printf("Employee successfully added.\n");
				printf("Employee Id= %d\n",EmpId);
			}
	}
	return 0;
}
int update_emp()
{
	char query[200],post[20],phno[10],salary[10];
	int n,id,choice;
	printf("Enter ID of the record you want to update: ");
	scanf("%d",&id);
	while(1)
	{
		printf("Which field do you want to update?\n");
		printf("1. Post\n");
		printf("2. Salary\n");
		printf("3. Phone Number\n");
		printf("4. Go back.\n");
		printf("Enter choice\n");
		scanf("%d",&choice);	
		int check=1;
		switch(choice)
		{
			case 1: printf("Enter New Post: ");			
					scanf(" %[^\n]%*c",post);
					sprintf(query,"UPDATE Employee SET Post ='%s' WHERE EmpId=%d;",post,id);
					check=sqlite3_exec(db,query,0,0,&err_message);
					if(check!=SQLITE_OK)
						printf("Error\n");
					else 
						printf("Updated successfully.\n");
					break;

			case 2: while(check)
					{	
						printf("Enter salary: ");
						scanf("%s",&salary);
						check=validate(salary);
						if(check==1)
						printf("Only numbers accepted\n");
					}
					check=1;
					sprintf(query,"UPDATE Employee SET Salary =%s WHERE EmpId=%d;",salary,id);
					check=sqlite3_exec(db,query,0,0,&err_message);						
					if(check!=SQLITE_OK)
						printf("Error\n");
					else 
						printf("Updated successfully.\n");
					break;
			case 3: while(check)
					{
						printf("Enter Phone number(10 digits): ");
						scanf("%s",phno);
						check=validate(phno);
						if(check==1)
						printf("Only numbers accepted\n");
					}
					sprintf(query,"UPDATE Employee SET PhNo =%s WHERE EmpId=%d;",phno,id);
					check=sqlite3_exec(db,query,0,0,&err_message);
					if(check!=SQLITE_OK)
						printf("Error\n");
					else 
						printf("Updated successfully.\n");
					break;
			case 4: return 0;

			default: printf("Please enter a valid number (1-9)\n");
			}		
		}
		
		return 0;
}

int validate(char* str)
{
	//printf("in validate\n");
	for(int i=0;i<strlen(str);i++)
	{
		if(!isdigit(*(str+i)))
			return 1;
	}
	return 0;
}

int validate_date(char *date, char* month, char* year)
{
	if(strlen(date)>2)
		return 1;
	if(strlen(month)>2)
		return 1;
	for(int i=0;i<strlen(date);i++)
	{
		if(!isdigit(*(date+i)))
			return 1;
	}
	for(int i=0;i<strlen(month);i++)
	{
		if(!isdigit(*(month+i)))
			return 1;
	}
		for(int i=0;i<strlen(year);i++)
	{
		if(!isdigit(*(year+i)))
			return 1;
	}
	int d=0,m=0;
	sscanf(date, "%d", &d); 
	sscanf(month, "%d", &m);
	if(d>31 || d<1)
		return 1;
	if(m> 12 || m<1)
		return 1;
	return 0;
}

int order()
{
	int ch;
	while(1)
	{
		printf("To place an order, enter the Sr. No. of the item in the menu\n");
		printf("Select an option\n1. View Menu\n2. Proceed to place order\n3. Go Back\nEnter Choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: display_menu();
					break;
			case 2: printf("Enter number of items\n");
					int n;
					scanf("%d",&n);
					place_order(n);
					break;
			case 3: return 0;
					break;
			default: printf("Enter a valid option\n");
		}
	}
	return 1;
}

int place_order(int n)
{
	int srno;
	int *order_count=(int *)calloc(33,sizeof(int));
	printf("Enter item Sr. No\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&srno);
		(*(order_count+srno-1))++;
	}
	char ch='\0';
	while(ch!='Y')
	{
		printf("Click 'Y' to proceed with bill or 'N' to add more items\n");
		int n1;
		scanf("%s",&ch);
		toupper(ch);
		switch(ch)
		{
			case 'Y': print_bill(order_count);
					  return 0;
					  break;
			case 'y': print_bill(order_count);
					  return 0;
					  break;
			case 'N': printf("Enter number of items to add\n");
					scanf("%d",&n1);
					printf("Enter item Sr. No\n");
					for(int i=0;i<n1;i++)
					{
						scanf("%d",&srno);
						(*(order_count+srno-1))++;
					}
					break;
			case 'n': printf("Enter number of items to add\n");
					scanf("%d",&n1);
					printf("Enter item Sr. No\n");
					for(int i=0;i<n1;i++)
					{
						scanf("%d",&srno);
						(*(order_count+srno-1))++;
					}
					break;
			default: printf("Enter a valid option\n");
		}
	}
	return 0;
}

int print_bill(int* order_count)
{
	char q[200]="";
	//char *q1= (char*)malloc (200*sizeof(char));
	float bill=0;
	float discount=0;
	char* pay_mode="";
	if (check_member()==1)
		discount=0.05;
	printf("Sr. No.\t\tQuantity\t\tItem\t\t\tPrice\n---------------------------------------------------------------------------------------\n");
		for(int i=0;i<33;i++) //printing bill
		{
			if(*(order_count+i)!=0)
			{
				sprintf(q,"SELECT Item, Price FROM Menu WHERE SrNo=%d",i+1);
				printf("%d\t\t%d\t\t\t",i+1,*(order_count+i));
				check= sqlite3_exec(db,q,callback,(void*) data,&err_message);
			}
		}
		for(int i=0;i<33;i++) //calculating total
		{
			if(*(order_count+i)!=0)
			{
				sprintf(q,"SELECT Price FROM Menu WHERE SrNo=%d",i+1);
				check= sqlite3_exec(db,q,callback_order,(void*) data,&err_message);
				bill+=(*(order_count+i)*item_price);
			}
		}
		printf("\n\t\t\t\t\t\t\t\tSub_total=%0.2f\n",bill);
		printf("\t\t\t\t\t\t\t\tCGST 2.5%%=%0.2f\n",0.025*bill);
		printf("\t\t\t\t\t\t\t\tSGST 2.5%%=%0.2f\n",0.025*bill);
		bill+=0.05*bill;
		if(discount==0)
			printf("\t\t\t\t\t\t\t\tGrand total=%0.2f\n",bill);
		else 
		{
			printf("\t\t\t\t\t\t\t\tTotal=%0.2f\n",bill);
			printf("\t\t\t\t\t\t\t\tDiscount applied!\n");
			bill=bill-(discount*bill);
			printf("\t\t\t\t\t\t\t\tGrand total=%0.2f\n",bill);
			
		}
		strcpy(q,"SELECT BillNo FROM Bill ORDER BY BillNo DESC LIMIT 1;");
		sqlite3_exec(db,q,callback_bill_id,(void*) data,&err_message);
		BillId++;
		int ch=0;
		while(ch!=1 && ch!=2)
		{
			printf("Enter payment mode-\n1.Cash\n2.Card\nEnter choice\n");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1: pay_mode="Cash";
						//printf("%d\n",ch);
						break;
				case 2: pay_mode="Card";
						break;
				default: printf("Enter valid choice\n");
			}
		}
		//printf("out of switch\n");
		time_t t=time(NULL);
        struct tm tm= *localtime(&t);
		tm.tm_year+=1900;
		tm.tm_mon+=1;
		//printf("after time\n");
		char q1[400];
		sprintf(q1,"INSERT INTO Bill VALUES(%d,'%s',%0.2f,'%d-%d-%d','%s');",BillId,CustId,bill,tm.tm_year,tm.tm_mon,tm.tm_mday,pay_mode);
		//printf("after sprintf%s\n",q1);
		int check=sqlite3_exec(db,q1,0,0,&err_message);
		if(check!=SQLITE_OK)
			printf("Error\n");
		else 
			printf("Bill added to database\n");
		return 1;
}

int check_member()
{
	printf("Are you a member? (Y/N)\n");
	char ch,ch1;
	scanf("%s",&ch);
	//printf("%c\n",ch);
	while(1)
	{
		if(ch=='Y'||ch=='y')
		{
			//printf("Entered if\n");
			int check=1;
			while(check)
			{
				//printf("Entered while\n");
				printf("Enter CustomerId\n");
				scanf("%s",CustId);
				check=validate(CustId);
				//printf("after validate\n");
				if(check==1)
					printf("Only Numbers accepted\n");
			}
			//printf("exit while\n");
			check=bday_anni_bill(0);			//check for bday
			//printf("from check bday %d\n",check);
			if(check==1)
				return 1;
			else 
				return 0;
		}
		else if(ch=='N'||ch=='n')
		{
			printf("Would you like to be a member?(Y for yes, any other key for no)\n");
			scanf("%s",&ch1);
			if(ch1=='Y'||ch1=='y')
			{	
				printf("Discounts apply from next visit\n");
				add_customer();
				return 0;
				//bday_anni();//check for bday
			}
			else
			{
				printf("Proceeding as Guest\n");
				strcpy(CustId,"0");
			return 0;
			}
		}
		else
			printf("Select Y or N\n");
	}
}

int bday_anni_bill(int n)
{
    time_t t=time(NULL);
	struct tm tm= *localtime(&t);
	char q[100];
	sprintf(q,"SELECT DoB FROM Customer WHERE CustomerId=%s;",CustId);
	char q1[100];
	sprintf(q1,"SELECT DoA FROM Customer WHERE CustomerId=%s;",CustId);
	sprintf(s_day,"%d",tm.tm_mday);
	sprintf(s_mon,"%d",tm.tm_mon+1);
    check= sqlite3_exec(db,q,callback_dob_bill,(void*) data, &err_message);
	check= sqlite3_exec(db,q1,callback_doa_bill,(void*) data, &err_message);
	if(bday_found==1 || anni_found==1)
	return 1;
}
	

int bday_anni(int n)
{
        time_t t=time(NULL);
        struct tm tm= *localtime(&t);
		char q[]="SELECT DoB, CustomerId FROM Customer;";
		char q1[]="SELECT DoA, CustomerId FROM Customer;";
        int i=0;
		printf("CustomerId \t\tName \t\tPhNo\t\t Email \t\tDoB  \t\tDoA  \n-------------------------------------------------------------------\n");                
        while(i!=n)
        {    
			sprintf(s_day,"%d",tm.tm_mday+i);
			sprintf(s_mon,"%d",tm.tm_mon+1);
            check= sqlite3_exec(db,q,callback_dob,(void*) data, &err_message);
			i++;
		}
		i=0;
		while(i!=n)
        {    
			sprintf(s_day,"%d",tm.tm_mday+i);
			sprintf(s_mon,"%d",tm.tm_mon+1);
            check= sqlite3_exec(db,q1,callback_doa,(void*) data, &err_message);
			i++;
		}
		
}

int searchbill()
{
    int choice=0;
    while(choice!=3)
    {
           printf("1. Search by Order date\n");
           printf("2. Search by CustomerID\n");
           printf("3. Go back\n");
           printf("Enter Choice:\n");
           //printf("\n");
		   scanf("%d",&choice);
           switch(choice)
           {
                case 1:Orderdate();
                        break;
                case 2:CustomerID();
                        break;
                case 3:return 1;
                        break;
                default:printf("Enter a valid number (1-3)\n");
           }
    }
}

void Orderdate()
{
	int check=1;
    char date[3], month[3], year[5];
	while(check)
	{
		printf("Enter Order Date (Year Month Date): ");
		scanf("%s%s%s", year, month, date);
		check=validate_date(date,month,year);
		if(check==1)
			printf("Enter valid date");
	}
    char query[100];
    sprintf(query,"SELECT * FROM Bill WHERE OrderDate = '%s-%s-%s';", year, month, date);
    printf("Bill No.\t\tCustomerID\t\tAmount\t\tOrderdate\t\tPaymode\t\tTransaction No.\n-----------------------------------------------------------------------------------------\n");
    check= sqlite3_exec(db,query,callback,(void*) data,&err_message);
}

void CustomerID()
{
    char ID[10];
	int check=1;
	while(check)
	{
		printf("Enter CustomerID: ");
		scanf("%s", ID);
		check=validate(ID);
		if(check==1)
			printf("Enter valid ID");
	}
    char query[100];
    sprintf(query,"SELECT * FROM Bill WHERE CustomerId = '%s';", ID);
    printf("Bill No.\t\tCustomerID\t\tAmount\t\tOrderdate\t\tPaymode\t\tTransaction No.\n-----------------------------------------------------------------------------------------\n");
    check= sqlite3_exec(db,query,callback,(void*) data,&err_message);
}

int add_update_customer()
{
	while(1)
	{
		int choice;
		printf("1. Add customer.\n");
		printf("2. Update existing customer record.\n");
		printf("3. Go Back.\n");
		printf("Enter choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: //printf("in case\n");
					add_customer();
					break;
			case 2: update_customer();
					break;
			case 3: return 1;
					break;
			default: printf("Enter Valid Choice (1-3)\n");
		}
		//printf("exit switch\n");
		return 0;
	}
}

int add_customer()
{
		//printf("enter func\n");
		int check=1,check1;
		char married;
		int choice;
		char query[200];
		char name[20],phno[10],email[30],Year_DoB[5],Year_DoA[5],Month_DoB[3],Month_DoA[3],Date_DoB[3],Date_DoA[3];
		char q[100]="SELECT CustomerId FROM Customer ORDER BY CustomerId DESC LIMIT 1;";
		check1=sqlite3_exec(db,q,callback_custid,(void*) data,&err_message);
		CustId_int+=1;
		sprintf(CustId,"%d",CustId_int);
		printf("Enter name of customer: ");
		scanf(" %[^\n]%*c",name);
		//printf("%s\n",name);
		while(check)
		{
			printf("Enter phone number: ");
			scanf(" %[^\n]%*c",phno);
			check=validate(phno);
			if(check==1)
				printf("Only numbers accepted.\n");
		}
		printf("Enter email: ");
		scanf("%s",email);
		check=1;
		while(check)
		{
			printf("Enter Date of Birth(DD MM YYYY): ");
			scanf("%s %s %s",Date_DoB,Month_DoB,Year_DoB);
			check=validate_date(Date_DoB,Month_DoB,Year_DoB);
			if(check==1)
				printf("Enter valid Date of Birth.\n");
		}

		check=1;
		printf("Are you married? (Y/N)\n");
		scanf("%s",&married);
		married=tolower(married);
		if(married=='y')
		{
			while(check)
			{
				printf("Enter Date of Anniversary(DD MM YYYY): ");
				scanf("%s %s %s",Date_DoA,Month_DoA,Year_DoA);
				check=validate_date(Date_DoA,Month_DoA,Year_DoA);
				if(check==1)
					printf("Enter valid Date of Anniversary.\n");
			}
		}
		if(married=='y')
			sprintf(query,"INSERT INTO Customer VALUES(%s,'%s',%s,'%s','%s-%s-%s','%s-%s-%s');",CustId,name,phno,email,Year_DoB,Month_DoB,Date_DoB,Year_DoA,Month_DoA,Date_DoA);
		else
			sprintf(query,"INSERT INTO Customer VALUES(%s,'%s',%s,'%s','%s-%s-%s','0-0-0');",CustId,name,phno,email,Year_DoB,Month_DoB,Date_DoB);
		check1=sqlite3_exec(db,query,0,0,&err_message);
		if(check1!=SQLITE_OK)
			printf("Error\n");
		else 
		{
			printf("Customer successfully added.\n");
			printf("Customer Id= %s\n",CustId);
		}
	return 0;
}

int update_customer()
{
	char phno[10],email[30],id[10];
	int check=1,choice,c;
	while(check)
	{
		printf("Enter Customer ID of the record: ");
		scanf("%s",&id);
		check=validate(id);
		if(check==1)
			printf("Enter valid Customer ID.\n");
	}
	check =1;
	while(1)
	{
		printf("Which field do you want to update?\n");
		printf("1. Phone Number.\n");
		printf("2. Email.\n");
		printf("3. Go back.\n");
		printf("Enter choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			 case 1: while(check)
			 		 {
			 		 	printf("Enter new Phone Number: ");
						scanf("%s",phno);
						check=validate(phno);
						if(check==1)
							printf("Enter valid mobile number.\n");
			 		 }
					 char q[200];
					 sprintf(q,"UPDATE Customer SET PhNo=%s WHERE CustomerId=%s;",phno,id);
					 //printf("%s",q);
					 c=sqlite3_exec(db,q,0,0,&err_message);
					 if(c!=SQLITE_OK)
						printf("Error\n");
					 else 
						printf("Customer successfully updated.\n");
					break;
			 case 2: printf("Enter new Email ID: ");
					scanf("%s",email);
					char q1[200];
					sprintf(q1,"UPDATE Customer SET Email='%s' WHERE CustomerId=%s;",email,id);
					//printf("%s\n",q1);
					c=sqlite3_exec(db,q1,0,0,&err_message);
					if(c!=SQLITE_OK)
						printf("Error\n");
					else 
						printf("Customer successfully updated.\n");
					break;
			case 3: return 0;
			default: printf("Please enter a valid number.\n");			
		}
	}
}

void thankyou()
{
	printf(" _______ _                 _     __     __         _ \n");
	printf("|__   __| |               | |    \\ \\   / /        | |\n");
	printf("   | |  | |__   __ _ _ __ | | __  \\ \\_/ /__  _   _| |\n");
	printf("   | |  | '_ \\ / _` | '_ \\| |/ /   \\   / _ \\| | | | |\n");
	printf("   | |  | | | | (_| | | | |   <     | | (_) | |_| |_|\n");
	printf("   |_|  |_| |_|\\__,_|_| |_|_|\\_\\    |_|\\___/ \\__,_(_)\n\n\n");
	printf("A Project by-\nSarika Singh\nShubham Shetty\nYug Vajani\nYash Shah");
}