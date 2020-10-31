
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include<iostream>
#include<dos.h>


    class SUPERMARKET
    {
	int pno;
	char name[50];
	float price, qty, tax, dis;
	public:
	    void create_product()
	    {
		cout << "\nPlease Enter The Product No. of The Product : ";
		cin >> pno;
		cout << "\n\nPlease Enter The Name of The Product : ";
		gets(name);
		cout << "\nPlease Enter The Price of The Product : ";
		cin >> price;
		cout << "\nPlease Enter The Discount(%) : ";
		cin >> dis;
	    }

	void show_product()
	{
	    cout << "\nThe Product No. of The Product : " << pno;
	    cout << "\nThe Name of The Product : ";
	    puts(name);
	    cout << "\nThe Price of The Product : " << price;
	    cout << "\nDiscount : " << dis;
	}

	int retpno()
	{
	    return pno;
	}

	float retprice()
	{
	    return price;
	}

	char * retname()
	{
	    return name;
	}

	int retdis()
	{
	    return dis;
	}

    }; //class ends here

//***************************************************************
// global declaration for stream object, object
//****************************************************************

fstream fp;
SUPERMARKET pr;
//***************************************************************
// function to write in file
//****************************************************************

void write_product()
{
    fp.open("Shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(SUPERMARKET));
    fp.close();
    cout << "\n\nThe Product Has Been Created. ";
    getch();
}
//***************************************************************
// function to read all records from file
//****************************************************************
void display_all()
{
    clrscr();
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(SUPERMARKET)))
    {
	pr.show_product();
	cout << "\n\n====================================\n";
	getch();
    }
    fp.close();
    getch();
}
//***************************************************************
// function to read specific record from file
//****************************************************************
void display_sp(int n)
{
    int flag = 0;
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(SUPERMARKET)))
    {
	if (pr.retpno() == n)
	{
	    clrscr();
	    pr.show_product();
	    flag = 1;
	}
    }
    fp.close();
    if (flag == 0)
	cout << "\n\nRecord Not Exist ! ! !";
    getch();
}
//***************************************************************
// function to modify record of file
//****************************************************************
void modify_product()
{
    int no,pos, found = 0;
    clrscr();
    cout << "\n\n\t\t\tTO MODIFY ";
    cout << "\n\n\tPlease Enter The Product No. of The Product : ";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    while (fp.read((char * ) & pr, sizeof(SUPERMARKET)) && found == 0)
    {
	if (pr.retpno() == no)
	{
	    pr.show_product();
	    cout << "\nPlease Enter The New Details of Product : " << endl;
	    pr.create_product();
	    pos = -1 * sizeof(pr);
	    fp.seekp(pos, ios::cur);
	    fp.write((char * ) & pr, sizeof(SUPERMARKET));
	    cout << "\n\n\t Record Updated.";
	    found = 1;
	}
    }
    fp.close();
    if (found == 0)
	cout << "\n\n Record Not Found ! ! !";
    getch();
}
//***************************************************************
// function to delete record of file
//****************************************************************
void delete_product()
{
    int no;
    clrscr();
    cout << "\n\n\n\t\t\tDelete Record.";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete : ";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(SUPERMARKET)))
    {
	if (pr.retpno() != no)
	{
	    fp2.write((char * ) & pr, sizeof(SUPERMARKET));
	}
    }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat", "Shop.dat");
    cout << "\n\n\t\t\tRecord Deleted ..";
    getch();
}
//****************************************************************

void menu()
{
    clrscr();
    fp.open("Shop.dat", ios:: in );
    if (!fp)
    {
	cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to createFile . . . ";
	cout << "\n\n\n Program is closing . . . .";
	getch();
	exit(0);
    }

    cout << "\n\n\t\tProduct MENU\n\n";
    cout << "====================================================\n";
    cout << "P.NO.\t\tNAME\t\t\tM.R.P\n";
    cout << "====================================================\n";

    while (fp.read((char * ) & pr, sizeof(SUPERMARKET)))
    {
	cout << pr.retpno() << "\t\t" << pr.retname() << "\t\t\t" << pr.retprice() << endl;
    }
    fp.close();
}

//***************************************************************
// function to place order and generating bill for Products
//****************************************************************

void place_order()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do
    {
	cout << "\n\nEnter The Product No. Of The Product : ";
	cin >> order_arr[c];
	cout << "\nQuantity in number : ";
	cin >> quan[c];
	c++;
	cout << "\nDo You Want To Order Another Product ? (y/n)";
	cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order. . .";
    getch();
    clrscr();
    cout << "\n\n******************************** INVOICE ************************\n";
    cout << "\nPr No.\t\tPr Name\t\tQuantity \t\tM.R.P \t\tAmount \t\tAmount after discount\ n ";
    for (int x = 0; x <= c; x++)
    {
	fp.open("Shop.dat", ios:: in );
	fp.read((char * ) & pr, sizeof(SUPERMARKET));
	while (!fp.eof())
	{
	    if (pr.retpno() == order_arr[x])
	    {
		amt = pr.retprice() * quan[x];
		damt = amt - (amt * pr.retdis() / 100);
		cout << "\n" << order_arr[x] << "\t" << pr.retname() <<
		    "\t" << quan[x] << "\t\t" << pr.retprice() << "\t" << amt << "\t\t" << damt;
		total += damt;
	    }
	    fp.read((char * ) & pr, sizeof(SUPERMARKET));
	}

	fp.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
    getch();
}

//***************************************************************
// INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
    clrscr();
    gotoxy(25, 10);
    cout << "SHOP BILLING MANAGEMENT SYSTEM";
    gotoxy(27, 20);
    cout << "Press Any key to Proceed: ";
    getch();

}

//***************************************************************
// ADMINSTRATOR MENU FUNCTION
//****************************************************************
void admin_menu()
{
    clrscr();
    char ch2;
    cout << "\n\n\n----------------------------:ADMIN MENU:---------------------";
    cout << "\n\n\t1.CREATE PRODUCT";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.QUERY ";
    cout << "\n\n\t4.MODIFY PRODUCT";
    cout << "\n\n\t5.DELETE PRODUCT";
    cout << "\n\n\t6.VIEW PRODUCT MENU";
    cout << "\n\n\t7.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-7) : ";
    ch2 = getche();
    switch (ch2)
    {
    case '1':
	clrscr();
	write_product();
	break;
    case '2':
	display_all();
	break;
    case '3':
	int num;
	clrscr();
	cout << "\n\n\tPlease Enter The Product No. ";
	cin >> num;
	display_sp(num);
	break;
    case '4':
	modify_product();
	break;
    case '5':
	delete_product();
	break;
    case '6':
	menu();
	getch();
    case '7':
	break;
    default:
	cout << "\a";
	admin_menu();
    }
}

void main()
{
    char ch;
    intro();
    do
    {
	clrscr();
	cout << "\n\n\n--------------------------------:MAIN MENU:----------------------------";

	cout << "\n\n\t01. CUSTOMER";
	cout << "\n\n\t02. ADMINISTRATOR";
	cout << "\n\n\t03. EXIT";
	cout << "\n\n\tPlease Select Your Option (1-3) : ";
	ch = getche();
	switch (ch)
	{
	case '1':
	    clrscr();
	    place_order();
	    getch();
	    break;
	case '2':
	    admin_menu();
	    break;
	case '3':
	    cout<<"\n\n\n\n\n\n\n\n\t\t\t\tExiting Program . . .";
	    sleep(4);
	    exit(0);
	default:
	    cout << "\n\n\tInvalid Entry ! ! !";
	}
    } while (ch != '3');
}
// END OF PROJECT
// Developed by Subhranta Panda 
