/*
gcc create.c -I"F:\Shubham\PMDS Project\Project Final" -L"F:\Shubham\PMDS Project\Project Final" -lsqlite3
*/
#include<stdio.h>
#include "F:\Shubham\PMDS Project\Project Final\sqlite3.h"
int main()
{
	 //printf("%s\n", sqlite3_libversion()); 
	sqlite3* db;
	char* err_message=0;
	int check=sqlite3_open("Restaurant.db",&db);
	if(check!=SQLITE_OK)
		printf("Cannot open database\n");
	else 
		printf("Database opened\n");
	
	char* create_customer="DROP TABLE IF EXISTS Customer; CREATE TABLE Customer(CustomerId int primary key,Name varchar(20),PhNo int(10),Email varchar(30),DoB date,DoA Date);";
	check=sqlite3_exec(db,create_customer,0,0,&err_message);
	if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Table Customer created\n");
	
	char* create_employee="DROP TABLE IF EXISTS Employee; CREATE TABLE Employee(EmpId int primary key,EmpName VARCHAR(20),Post VARCHAR(20),Salary int,PhNo int(10),DoB DATE);";
	check=sqlite3_exec(db,create_employee,0,0,&err_message);
	if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Table Employee created\n");
	
	char* create_bill="DROP TABLE IF EXISTS Bill; CREATE table Bill(BillNo int primary key,CustomerId int,Amount int,OrderDate TIMESTAMP,PayMode varchar(10),TrxnNo int,foreign key(CustomerId) references Customer(CustomerId));";
	check=sqlite3_exec(db,create_bill,0,0,&err_message);
	if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Table Bill created\n");
	
	char* create_menu="DROP TABLE IF EXISTS Menu; CREATE table Menu(Category varchar(20),Item varchar(20),Price int,SrNo int primary key);";
	check=sqlite3_exec(db,create_menu,0,0,&err_message);
	if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Table Menu created\n");
    return 0;
}

/*
Database opened
Table Customer created
Table Employee created
Table Bill created
Table Menu created
*/



			