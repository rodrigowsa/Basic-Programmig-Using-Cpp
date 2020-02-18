#include<conio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

    class product
    {
        int pno;
        char name[50];
        float price, qty, tax, dis;

        public:
            void create_product()
            {
                cout<< "\nPlease Enter The Product No. of The Product ";
                cin >> pno;
                fflush(stdin);
                cout << "\n\nPlease Enter The Name of The Product ";
                gets(name);
                cout << "\nPlease Enter The Price of The Product ";
                cin >> price;
                cout << "\nPlease Enter The Discount (%) ";
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
};

// function to write in file
void write_product()
{
    fstream fp;
    product pr;
    fp.open("Shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();
    cout << "\n\nThe Product Has Been Added";
}

// function to delete record of file
void delete_product()
{
    fstream fp;
    product pr;
    int no;
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        if (pr.retpno() != no)
        {
            fp2.write((char * ) & pr, sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat", "Shop.dat");
    cout << "\n\n\tRecord Deleted ..";
}
// function to display all products price list

void menu()
{
    fstream fp;
    product pr;
    fp.open("Shop.dat", ios:: in );
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File ";
        cout << "\n\n\n Program is closing ....";
        exit(0);
    }
    cout << "\n\n\t\tProduct MENU\n\n";
    cout << "====================================================\n";
    cout << "P.NO.\t\tNAME\t\tPRICE\n";
    cout << "====================================================\n";

    while (fp.read((char * ) & pr, sizeof(product)))
    {
        cout << pr.retpno() << "\t\t" << pr.retname() << "\t\t" << pr.retprice() << endl;
    }
    fp.close();
}
// function to place order and generating bill for Products

void place_order()
{
    fstream fp;
    product pr;
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
    cout << "\n\nThank You For Placing The Order";
    system("cls");
    cout << "\n\n\n\n******************************** INVOICE ************************\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n ";
    for (int x = 0; x <= c; x++)
    {
        fp.open("Shop.dat", ios:: in );
        fp.read((char * ) & pr, sizeof(product));
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
            fp.read((char * ) & pr, sizeof(product));
        }
        fp.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;

}
// ADMINSTRATOR MENU FUNCTION

void admin_menu()
{
    char ch2;
    cout << "\n\n\n\tADMIN MENU";
    cout << "\n\n\t1.ADD PRODUCT";
    cout << "\n\n\t2.DELETE PRODUCT";
    cout << "\n\n\t3.VIEW PRODUCT MENU";
    cout << "\n\n\t4.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-4) :";
    cin >> ch2;
    switch (ch2)
    {
    case '1':
        write_product();
        break;
    case '2':
        delete_product();
        break;
    case '3':
        menu();
        break;
    case '4':
         break;
    default:
        cout << "\a";
        admin_menu();
    }
}
// THE MAIN FUNCTION OF PROGRAM

int main()
{
    char ch;
    do
    {
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. CUSTOMER";
        cout << "\n\n\t02. ADMINISTRATOR";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        ch = getche();
        switch (ch)
        {
        case '1':
            place_order();
            getch();
            system("cls");
            break;
        case '2':
            admin_menu();
            break;
        case '3':
            exit(0);
        default:
            cout << "\a";
            system("cls");
        }
    } while (ch != '3');
    return 0;
}
