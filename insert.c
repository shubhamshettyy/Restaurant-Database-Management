/*
gcc insert.c -I"F:\Shubham\PMDS Project\Project Final" -L"F:\Shubham\PMDS Project\Project Final" -lsqlite3
*/
#include<stdio.h>
#include "F:\Shubham\PMDS Project\Project Final\sqlite3.h"

sqlite3* db;
char* err_message=0;
int check;

void insert_customer();
void insert_employee();
void insert_menu();
void insert_bill();

int main()
{
	check=sqlite3_open("Restaurant.db",&db);
	if(check!=SQLITE_OK)
		printf("Cannot open database\n");
	else 
		printf("Database opened\n");
	insert_customer();
	insert_employee();
	insert_bill();
	insert_menu();
}

void insert_customer()
{
	char customer[][200]= {"INSERT INTO Customer VALUES (1,'Sarika Singh',9902696899,'sarika@abc.com','2000-07-24','2018-04-27');",
						"INSERT INTO Customer VALUES (2,'Supriya Singh',404333352,'surpiya@abc.com','1988-10-17','2016-01-20');",
						"INSERT INTO Customer VALUES (3,'Akshay Sheth',4046262504,'akshay@abc.com','1988-07-09','2016-01-20');",
						"INSERT INTO Customer VALUES (4,'Sunita Singh',9833350848,'sunita@abc.com','1963-08-11','1987-03-02');",
						"INSERT INTO Customer VALUES (5,'H.P Singh',9876543210,'hpsingh@abc.com','1957-07-01','1987-03-02');",
						"INSERT INTO Customer VALUES (6,'Roshni Batra',9876543210,'roshni@abc.com','2000-04-19','0000-00-00');",
						"INSERT INTO Customer VALUES (7,'Aakash Gedela',9876543210,'aakash@abc.com','2000-04-06','2017-01-01');",
						"INSERT INTO Customer VALUES (8,'Advait Panda',9876543210,'advait@abc.com','2000-05-23','0000-00-00');",
						"INSERT INTO Customer VALUES (9,'Soumia Gupta',9876543210,'soumia@abc.com','1999-12-24','29-08-2018');",
						"INSERT INTO Customer VALUES (10,'Shreyas Raman',9930116627,'shreyas@abc.com','2000-03-04','2018-04-27');"
						};
	printf("Inserting Customers\n");
	for(int i=0;i<10;i++)
	{
		check=sqlite3_exec(db,customer[i],0,0,&err_message);
		if(check!=SQLITE_OK)
			printf("Error\n");
		else 
			printf("Success %d\n",i+1);
	}
}

void insert_employee()
{
	char employee[][200]={"INSERT INTO Employee VALUES(1,'Shubham Shetty','Manager',100000,9875342514,'2000-09-15');",
						"INSERT INTO Employee VALUES(2,'Mark','Assistant Chef',20000,8796452316,'1996-10-23');",
						"INSERT INTO Employee VALUES(3,'Teddy','Cashier',10000,9976646523,'1987-01-17');",
						"INSERT INTO Employee VALUES(4,'Allen','Head Chef',200000,8796483526,'1987-02-01');",
						"INSERT INTO Employee VALUES(5,'Paul','Waiter',15000,9986596794,'1989-10-15');",
						"INSERT INTO Employee VALUES(6,'Mark','Waiter',10000,9978646577,'1978-11-07');",
						"INSERT INTO Employee VALUES(7,'David','Waiter',20000,8879689580,'1999-12-15');",
						"INSERT INTO Employee VALUES(8,'Kim','Receptionist',15000,8899786435,'1998-09-09');",
						"INSERT INTO Employee VALUES(9,'James','Assistant Chef',20000,8869504680,'1999-07-13');",
						"INSERT INTO Employee VALUES(10,'Ebrahim','Waiter',10000,8904638768,'2000-07-21');",
						"INSERT INTO Employee VALUES(11,'Viraj','Waiter',12000,9973424100,'1999-06-11');"
						};
	printf("Inserting Employees\n");
	for(int i=0;i<11;i++)
	{
		check=sqlite3_exec(db,employee[i],0,0,&err_message);
		if(check!=SQLITE_OK)
			printf("Error\n");
		else 
			printf("Success %d\n", i+1);
	}
	//printf("\n");
}

void insert_menu()
{
	char menu_data[][200]={"INSERT INTO Menu VALUES('Soups', 'Manchow', 150, 1);",
							"INSERT INTO Menu VALUES('Soups', 'Tomato', 100, 2);",
							"INSERT INTO Menu VALUES('Soups', 'Cream of onion', 150, 3);",
							"INSERT INTO Menu VALUES('Starters', 'Paneer Chilly', 210, 4);",
							"INSERT INTO Menu VALUES('Starters', 'Spring Roll', 190, 5);",
							"INSERT INTO Menu VALUES('Starters', 'Green Grilled Mushroom', 250, 6);",
							"INSERT INTO Menu VALUES('Starters', 'Hara Bhara Kabab', 200, 7);",
							"INSERT INTO Menu VALUES('Main Course(Italian)', 'Supreme Delight', 400, 8);",
							"INSERT INTO Menu VALUES('Main Course(Italian)', 'Margherita', 300, 9);",
							"INSERT INTO Menu VALUES('Main Course(Italian)', 'Arabita pink sauce pasta', 300, 10);",//10
							"INSERT INTO Menu VALUES('Main Course(Italian)', 'Cheese Fondue', 550, 11);",
							"INSERT INTO Menu VALUES('Main Course(Chinese)', 'Hakka Noodles', 300, 12) ;",
							"INSERT INTO Menu VALUES('Main Course(Chinese)', 'Burnt Chilly Garlic Rice', 320, 13) ;",
							"INSERT INTO Menu VALUES('Main Course(Indian)', 'Pav Bhaji Fondue', 450, 14) ;",
							"INSERT INTO Menu VALUES('Main Course(Indian)', 'Chopsey Dosa', 200, 15) ;",
							"INSERT INTO Menu VALUES('Main Course(Indian)', 'Chipotle Sandwich', 180, 16) ;",
							"INSERT INTO Menu VALUES('Main Course(Indian)', 'Chhole Bhature', 180, 17) ;",//17
							"INSERT INTO Menu VALUES('Main Course(Punjabi)', 'Shahi Paneer', 300, 18) ;",
							"INSERT INTO Menu VALUES('Main Course(Punjabi)', 'Malai Kofta', 300, 19) ;",
							"INSERT INTO Menu VALUES('Main Course(Punjabi)', 'Hyderabadi Kolhapuri', 300, 20) ;",
							"INSERT INTO Menu VALUES('Main Course(Punjabi)', 'Paneer Tikka Masala', 300, 21) ;",//21
							"INSERT INTO Menu VALUES('Main Course(Indian Breads)', 'Butter naan', 80, 22) ;",
							"INSERT INTO Menu VALUES('Main Course(Indian Breads)', 'Butter Roti', 60, 23) ;",
							"INSERT INTO Menu VALUES('Main Course(Indian Breads)', 'Kulcha ', 80, 24) ;",
							"INSERT INTO Menu VALUES('Main Course(Indian Breads)', 'Assorted bread basket', 200, 25) ;",
							"INSERT INTO Menu VALUES('Desserts', 'Chocolate Fondue ', 380, 26) ;",
							"INSERT INTO Menu VALUES('Desserts', 'Hot Sizzling Brownie', 250, 27) ;"
							"INSERT INTO Menu VALUES('Desserts', 'Italian Cappuccino Pudding ', 175, 28) ;",
							"INSERT INTO Menu VALUES('Desserts', 'Oreo Cream Shake', 140, 29) ;",//27
							"INSERT INTO Menu VALUES('Mocktails', 'Virgin Mojito ', 160, 30) ;",
							"INSERT INTO Menu VALUES('Hard Drinks', 'Tequila', 350, 31) ;",
							"INSERT INTO Menu VALUES('Hard Drinks', 'Black Dog', 200, 32) ;",
							"INSERT INTO Menu VALUES('Hard Drinks', 'Bira', 170, 33) ;",//32
							};
	printf("Inserting Menu\n");
	for(int i=0;i<33;i++)
	{
		check=sqlite3_exec(db,menu_data[i],0,0,&err_message);
		if(check!=SQLITE_OK)
			printf("Error\n");
		else 
			printf("Success %d\n",i+1);
	}
}

void insert_bill()
{
	char bill[][200]={"INSERT INTO Bill VALUES(1,1,4500,'2018-02-12','Card',1353966);",
                  "INSERT INTO Bill VALUES(2,2,6500,'2018-02-22','Card',1843631);",
                  "INSERT INTO Bill VALUES(3,3,3750,'2018-03-01','Card',2726955);",
                  "INSERT INTO Bill VALUES(4,4,3300,'2018-03-30','Cash',1353966);",
                  "INSERT INTO Bill VALUES(5,5,4000,'2018-04-04','Cash',4527433);",
                  "INSERT INTO Bill VALUES(6,6,8470,'2018-05-28','Card',1153789);",
                  "INSERT INTO Bill VALUES(7,7,5700,'2018-06-17','Cash',3410353);",
                  "INSERT INTO Bill VALUES(8,8,4100,'2018-07-19','Card',4383592);",
                  "INSERT INTO Bill VALUES(9,9,8100,'2018-07-26','Card',4986392);",
                  "INSERT INTO Bill VALUES(10,10,7300,'2018-08-06','Card',2385455);"
                 };

    printf("Inserting Bill\n");
    for( int i=0; i<10; i++)
    {
        check=sqlite3_exec(db,bill[i],0,0,&err_message);
        if(check!=SQLITE_OK)
            printf("Error\n");
		else
			printf("Success %d\n",i+1);
    }
}