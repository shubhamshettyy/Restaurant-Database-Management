void insert employee()
{
char* employee1="INSERT INTO Employee VALUES(1,'Shubham','Manager',100000,9875342514,'2000-09-15');";
char* employee2="INSERT INTO Employee VALUES(2,'Mark','Assistant Chef',20000,8796452316,'1996-10-23');";
char* employee3="INSERT INTO Employee VALUES(3,'Teddy','Cashier',10000,9976646523,'1987-01-17');";
char* employee4="INSERT INTO Employee VALUES(4,'Allen','Head Chef',200000,8796483526,'1987-02-01');";
char* employee5="INSERT INTO Employee VALUES(5,'Paul','Waiter',15000,9986596794,'1989-10-15');";
char* employee6="INSERT INTO Employee VALUES(6,'Mark','Waiter',10000,9978646577,'1978-11-07');";
char* employee7="INSERT INTO Employee VALUES(7,'David','Waiter',20000,8879689580,'1999-12-15');";
char* employee8="INSERT INTO Employee VALUES(8,'Kim','Receptionist',15000,8899786435,'1998-09-09');";
char* employee9="INSERT INTO Employee VALUES(9,'James','Assistant Chef',20000,8869504680,'1999-07-13');";
char* employee10="INSERT INTO Employee VALUES(10,'Ebrahim','Waiter',10000,8904638768,'2000-07-21');";
char* employee11="INSERT INTO Employee VALUES(11,'Viraj','Waiter',12000,9973424100,'1999-06-11');";
		
check=sqlite3_exec(db,employee1,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
check=sqlite3_exec(db,employee2,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
check=sqlite3_exec(db,employee3,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
check=sqlite3_exec(db,employee4,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
check=sqlite3_exec(db,employee5,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
check=sqlite3_exec(db,employee6,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
check=sqlite3_exec(db,employee7,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
check=sqlite3_exec(db,employee8,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
check=sqlite3_exec(db,employee9,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
check=sqlite3_exec(db,employee10,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
check=sqlite3_exec(db,employee11,0,0,&err_message);
if(check!=SQLITE_OK)
		printf("Error\n");
	else 
		printf("Success");
}
