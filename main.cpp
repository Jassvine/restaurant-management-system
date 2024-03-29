#include<iostream>
#include <iomanip>
#include<string>
#include<conio.h>
#include<mysql.h>

using namespace std;

// Global Variable
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res; //result data

string UserID, EquipmentID; //user session //store user ID
// Global Variable End

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
          cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;
            //(void)getchar();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        conn = mysql_real_connect(conn, "localhost", "root", "", "restaurant", 3306, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl; 
            _getch();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
};



void Register();
void Login();
void AdminMenu();
void CustomerMenu();
void InsertNewMenu();
void ListofMenu();
void UpdateDelMenu();
void SearchMenu();
void ListofMenu();
void InsertNewOrder();
void ListofOrders();
void UpdateDelOrder();
void SearchOrder();
void InsertCustomerRate();
void ViewCustomerRate();
void report();
void MenuOrder();
void SearchRate();
void MinRate();
void MaxRate();

int main()
{
    system("cls");
    system("title RESTAURANT MANAGEMENT SYSTEM");
    system("color 0f");
    db_response::ConnectionFunction();

    int chooseOneFromMenu = 0;

    

    cout << setw(10) << "******************************************************************************************** \n\n\n" << endl;
    cout << setw(5)<< "                    WELCOME TO M&M COLLAB RESTAURANT \n\n" << endl;
    cout << setw(5) << "        WE HOPE YOU HAVE A GOOD EXPERIENCE DINING IN OUR RESTAURANT\n\n\n";
    cout << "                   PLEASE FOLLOW SOP MEASURES AND STAY SAFE! \n\n\n";
    cout << setw(10)<< "        1. LOG INTO YOUR ACCOUNT \n\n";
    cout << setw(5) << "        2. RESGISTER A NEW ACCOUNT \n\n";
    cout << setw(5) << "        3. EXIT .\n\n\n";
   
    cout <<setw(10) << "*********************************************************************************************\n\n" << endl;
    cout << "Please enter your choice. What would you like to do?  : ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        Login();
        break;
    case 2:
        Register();
        break;
    case 3:
        cout << "Program will exit now...bye!" << endl;
        exit(0);
    default:
        cout << "Please choose between 1 - 3. Press Enter To Continue...";
        _getch(); // get char // pause console // 
        system("cls"); // clear console
        main(); //
        break;
    }
            return 0;
        }
void Register()
{
    system("cls");
    string name, phone, address, username, password, CustID;
    cout << setw(10) << "******************************************************************************************** \n\n\n" << endl;
    cout << setw(5) << "                    WELCOME TO M&M COLLAB RESTAURANT \n\n" << endl;
    cout << setw(5) << "        WE HOPE YOU HAVE A GOOD EXPERIENCE DINING IN OUR RESTAURANT\n\n\n";
    cout << "                            PLEASE FOLLOW SOP MEASURES AND STAY SAFE! \n\n\n";
    cout << setw(10) << "        THIS IS YOUR E-REGISTRATION FORM. PLEASE FILL IT IN WITH YOUR DETAILS  \n\n";
    cout << setw(5) << "                             thank you!  \n\n";
    cout << setw(10) << "*********************************************************************************************\n\n" << endl;
    cout << "NAME :  ";
    cin.ignore(1, '\n');
    getline(cin, name );
    cout << "CONTACT NUMBER: ";
    getline(cin, phone);
    cout << "ADDRESS : ";
    getline(cin, address);
    cout << "USERNAME : ";
    getline(cin, username);
    cout << "create your unique CUSTOMER ID : ";
    getline(cin, CustID);
    cout << "ENTER YOUR PASSWORD  : ";
        char ch;
    while ((ch = _getch()) != 13)
    {
        password += ch;
        cout << '*';
    }

    string checkUser_query = "select * from Customer where CustUsername = '" + username + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            cout << "Username is already exist. Press Enter to Try Again...";
            _getch();
            Register();
        }
        else
        {
            string insertCustomer_query = "insert into Customer (CustName, CustPhone, CustAddress, CustUsername, CustPw, CustID) values ('" + name + "', '" + phone + "', '" + address + "', '" + username + "', '" + password + "', '" + CustID + "')";
            const char* q = insertCustomer_query.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate)
            {
                cout << endl << "You have been registered. Press Enter to Continue...";
                _getch();
                main();
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}
void Login()
{
    system("cls");
    string username, password, CustID;
    int role = 0; //Admin role = 1 //Customer role = 2

    cout << "Please enter your USERNAME : ";
    cin >> username;
    cout << "Please input your ID : ";
    cin >> CustID;
    cout << "Please enter your PASSWORD : ";
    
    char ch;
    while ((ch = _getch()) != 13)
    {
        password += ch;
        cout << '*';
    }

    do
    {
        cout << "\n\n\n 1. ADMIN  ";
        cout << "- Strictly only for admin of m&m collab  ";
        cout << "\n\n\n 2. CUSTOMER  ";
        cout << "- If you are a customer who would like to enjoy our services, please log in here. ENJOY :) ";
        cout << "\n\n\n Please enter your choice :  ";
        cin >> role;
    } while (role != 1 && role != 2); //else 1 & 2 //keep looping

    if (role == 1) //admin
    {
        //check username & password 
        string checkUser_query = "select * from Admin where AdminUsername = '" + username + "' and AdminPw = '" + password + "'";
        const char* cu = checkUser_query.c_str();//convert
        qstate = mysql_query(conn, cu);//executee

        if (!qstate) //query boleh jalan
        {
            res = mysql_store_result(conn); //store result
            if (res->row_count == 1) //jumpa user
            {
                while (row = mysql_fetch_row(res)) //loop each of row dalam result
                    UserID = row[0]; //store  in variable

                AdminMenu();
            }
            else //wrong pw
            {
                char c;
                cout << "Invalid username or password. Would you want to try again? (y/n): ";
                cin >> c;
                if (c == 'y' || c == 'Y')
                    Login();
                else
                    main();
            }
        }
    }

    else if (role == 2)
    {
        string checkUser_query = "select * from Customer where CustUsername = '" + username + "' and CustPw = '" + password + "'";
        const char* cu = checkUser_query.c_str();//convert
        qstate = mysql_query(conn, cu);//executee

        if (!qstate) //query boleh jalan
        {
            res = mysql_store_result(conn); //store result
            if (res->row_count == 1) //jumpa user
            {
                while (row = mysql_fetch_row(res)) //loop each of row dalam result
                    UserID = row[0]; //store ID in variable

                CustomerMenu();
            }
            else //wrong username and pw
            {
                char c;
                cout << "Invalid username or password. Want to try again? (y/n): ";
                cin >> c;
                if (c == 'y' || c == 'Y')
                    Login();
                else
                    main();
            }
        }
    }
}
void AdminMenu()
{
    system("cls");
    int choose;

    cout << setw(10) << "******************************************************************************************** \n\n\n" << endl;
    cout << setw(5) << "                   HI ADMIN \n\n" << endl;
    cout << setw(5) << "        THIS IS THE MENU SECTION OF M&M COLLAB RESTAURANT T\n\n\n";
    cout << "                      YOU MAY CHOOSE YOUR TASK \n";
    cout << setw(10) << "            1. INSERT A NEW M&M MENU \n";
    cout << setw(5) << "            2. LIST OFTHE AVAILABLE M&M MENU !  \n";
    cout << setw(10) << "            3. VIEW RATINGS FROM CUSTOMER \n";
    cout << setw(5) << "            4. REPORTING \n";
    cout << setw(5) << "            5. Exit to MAIN MENU \n";
    cout << setw(10) << "*********************************************************************************************\n\n" << endl;

    cout << " Please enter your choice : ";
    cin >> choose;
    switch (choose)
    {
    case 1:
        InsertNewMenu(); //function to insert new data
        break;
    case 2:
        ListofMenu();
        break;
    case 3:
        ViewCustomerRate();
        break;
    case 4:
        report();
        break;
    case 5:
        main();
        break;
    default:
        cout << "Please choose between 1 -5. Press Enter To Continue...";
        _getch(); // get char // pause console // 
        system("cls"); // clear console
        AdminMenu(); //
        break;
    }
}
void InsertNewMenu()
{
    system("cls");
    string name, description, price;

    cout << "====> Insert New Menu" << endl;
    cin.ignore(1, '\n');
    cout << "Name of Menu : ";
    getline(cin, name);
    cout << "Price of Menu : ";
    getline(cin, price);
    cout << "Description of Menu :";
    getline(cin, description);
    

    //YYYY-MM-DD //default date format - MySQL

    string insert_query = "insert into Menu (MenuName,MenuDescription,MenuPrice) values ('" + name + "','" + description + "','" + price + "')";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate) //query boleh jalan
    {
        cout << endl << "Menu is successful added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    char choose;
    do
    {
        cout << "Do you want add another menu? (y/n): ";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
        {
            InsertNewMenu();
        }
        else if (choose == 'n' || choose == 'N')
        {
            AdminMenu();
        }
    } while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
}
void ListofMenu()
{
    system("cls");
    qstate = mysql_query(conn, "select MenuID, MenuName, MenuDescription, MenuPrice from Menu");

    //set width //header
    cout << setw(11) << "MenuID" << setw(20) << "Name" << setw(11) << " " << setw(22) << "Description" << setw(30) << " " << setw(8) << "Price" << endl;
    if (!qstate)
    {
        //body table
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) //fetch every row until the end of data
        {
            cout << setw(8) << row[0] << setw(27) << row[1] << setw(27) << row[2] << setw(30) << "RM" << setw(9) << row[3] << endl;
        }
    }

    char choose;
    cout << "\n =====> Choose (e) (E) to edit Menu <====== \n";
    cout << "\n =====> Choose (s) (S) to search Menu <====== \n";
    cout << "\n =====> Choose (m) (M) to head back to Main Menu <====== \n";
    cin >> choose;
    if (choose == 'e' || choose == 'E')
        UpdateDelMenu();
    else if (choose == 's' || choose == 'S')
        SearchMenu();
    else if (choose == 'm' || choose == 'M')
        AdminMenu();

}
void UpdateDelMenu()
{
    
   // int description;
    char choose;

    string name, description, price, MenuID;
    do
    {
        cout << "\n***** Choose (u) (U) to update Menu ******\n";
        cout << "\n ****** Choose (d) (D) to delete Menu *****\n";
      
        cin >> choose;
    } while (choose != 'u' && choose != 'U' && choose != 'd' && choose != 'D');

    cout << "Enter Menu ID: ";
    cin >> MenuID;
    if (choose == 'u' || choose == 'U')
    {
        int chooseUpdate = 0;
        system("cls");
        do
        {
            
            string search_query = "select MenuID, MenuName, MenuDescription, MenuPrice from Menu where MenuID = '" + MenuID + "'";
            const char* q = search_query.c_str();
            qstate = mysql_query(conn, q);
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) //looping to retreive the data
            {

                cout<< "\t\t\t\t    ---------------------------\n";
                cout << "\t\t\t\t          |   M&M MENU  |\n" ;
                cout << "\t\t\t\t    ---------------------------\n";
              
                cout << "MENU ID: " << row[0] << " ============> Uneditable"
                    << "\n\n1. ===> MENU NAME : " << row[1] << "\n\n"
                    << "\n2. ===> MENU DESCRIPTION: " << row[2] << "\n\n"
                    << "\n3. ===> MENU PRICE: RM " << row[3] << "\n\n"
                    << "\n4. ===> SAVE YOUR UPDATES " << "\n\n\n";
               
            }
            cout << "\n Choose to update ->  1. update the Menu Name  2. update the Menu Description  3. update the Menu Price : ";
            cin >> chooseUpdate;
            cin.ignore(1, '\n');
            if (chooseUpdate == 1)
            {
               
                cout << "Insert New Menu Name: ";
                getline(cin, name);
                string update_query = "update Menu set MenuName = '" + name + "' where MenuID = '" + MenuID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
            }
            else if (chooseUpdate == 2)
            {
                cout << "Insert New Menu Description : ";
                getline(cin, description);
                string update_query = "update Menu set MenuDescription = '" + description + "' where MenuID = '" + MenuID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
            }
            else if (chooseUpdate == 3)
            {
                cout << "Insert New Price : RM ";
                getline(cin, price);
                string update_query = "update Menu set MenuPrice = '" + price + "' where MenuID = '" + MenuID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);

            }
            else if (chooseUpdate == 4)
            {
                ListofMenu();
            }
        } while (true);
    }

    else if (choose == 'd' || choose == 'D')
    {
        char choose2;
        do
        {
            cout << "Are you sure want to remove this Menu? (y/n): ";
            cin >> choose2;
            if (choose2 == 'y' || choose2 == 'Y')
            {
                string delete_query = "delete from Menu where MenuID = '" + MenuID + "'";
                const char* q = delete_query.c_str();
                qstate = mysql_query(conn, q);
                if (!qstate)
                {
                    cout << "The Menu has been removed. Press Enter to Continue...";
                    _getch();
                    ListofMenu();
                }
                else
                {
                    cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                }
            }

        } while (choose2 != 'y' && choose2 != 'Y' && choose2 != 'n' && choose2 != 'N');

    }
}
void SearchMenu()
{
    system("cls");
    char choose;
    string MenuName;
    cin.ignore(1, '\n');
    cout << "Search Menu by name: ";
    getline(cin, MenuName);

    cout << "\t\t\t\t    -------------------------------------------------\n";
    cout << "\t\t\t\t          |   LIST OF SEARCHED M&M MENU  |\n";
    cout << "\t\t\t\t    ---------------------------------------------------\n";

    string search_query = "select MenuID, MenuName, MenuDescription, MenuPrice from Menu where MenuName like '%" + MenuName + "%'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << setw(11) << "MenuID" << setw(17) << "MenuName"  << setw(25) <<  "MenuPrice" << setw(25) << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(6) << row[0] << setw(25) << row[1] << setw(17) << "RM" << setw(5) << row[3] << setw(23) << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "\n ======> Choose (e) (E) to edit Menu <======: ";
    cout << "\n ======> Choose (s) (S) to search Menu <======: ";
    cout << "\n ======> Choose (m) (M) to go back to Main Menu <======: ";
    cin >> choose;
    if (choose == 'e' || choose == 'E')
        UpdateDelMenu();
    else if (choose == 's' || choose == 'S')
        SearchMenu();
    else if (choose == 'm' || choose == 'M')
        AdminMenu();
} 



 
void CustomerMenu()
{
    system("cls");
    int choose;
    cout << setw(10) << "********************************************************************************************************************** \n\n\n" << endl;
    cout << setw(5) << "                    WELCOME TO M&M COLLAB RESTAURANT \n\n" << endl;
    cout << setw(5) << "        WE HOPE YOU HAVE A GOOD EXPERIENCE DINING IN OUR RESTAURANT\n\n\n";
    cout << "                   PLEASE FOLLOW SOP MEASURES AND STAY SAFE! \n\n";
    cout << setw(10) << "                 ..  YOU CAN MAKE YOUR ORDERS HERE .. \n\n";
    cout << setw(10) << "*********************************************************************************************************************** \n\n\n" << endl;
    cout << setw(5) << "                   1. TO INSERT A NEW ORDER \n\n" << endl;
    cout << setw(5) << "                   2. TO VIEW ORDERS\n\n" << endl;
    cout << setw(5) << "                   3. RATE & SUGGEST\n\n" << endl;
    cout << setw(5) << "                   4. MAIN MENU \n\n";
    cout << setw(10) << "************************************************************************************************************************\n\n" << endl;
    cout << "Please input your choice : ";
    cin >> choose;
    switch (choose)

    {
    case 1:
        InsertNewOrder(); //function to insert new data
        break;
    case 2:
        ListofOrders();
        break;
    case 3:
        InsertCustomerRate();
        break;
    case 4:
        main();
        break;
    default:
        cout << "Please choose between 1 -3. Press Enter To Continue...";
        _getch(); // get char // pause console // 
        system("cls"); // clear console
        CustomerMenu(); //
        break;

    }
} 
void InsertNewOrder()
{
    system("cls");
    qstate = mysql_query(conn, "select MenuID, MenuName, MenuDescription, MenuPrice from Menu");

    //set width //header
    cout << setw(11) << "MenuID" << setw(20) << "Name" << setw(11) << " " << setw(22) << "Description" << setw(25) << " " << setw(8) << "Price" << endl;
    if (!qstate)
    {
        //body table
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) //fetch every row until the end of data
        {
            cout << setw(8) << row[0] << setw(27) << row[1] << setw(27) << row[2] << setw(30) << "RM" << setw(9) << row[3] << endl;
        }
    }

    
    string CustID, MenuID, Quantity, OrderDate;
    cout << "Insert New Order\n" << endl;
    cin.ignore(1, '\n');
    cout << "CUST ID: ";
    getline(cin, CustID);
    cout << "MENU ID : ";
    getline(cin, MenuID);
    cout << "Quantity of Order : ";
    getline(cin, Quantity);
    cout << "Date of Order (yyyy/mm/dd) : ";
    getline(cin, OrderDate);


    //YYYY-MM-DD //default date format - MySQL

    string insert_query = "insert into `Ordering` (CustID,MenuID,Quantity, `OrderDate`) values ('" + CustID + "','" + MenuID + "','" + Quantity + "','" + OrderDate + "')";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate) //query boleh jalan
    {
        cout << endl << "Your ORDER has been successfully made and added to database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    char choose;
    do
    {
        cout << "Do you want add another order? (y/n): ";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
        {
            InsertNewOrder();
        }
        else if (choose == 'n' || choose == 'N')
        {
            CustomerMenu();
        }
    } while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
}
void ListofOrders() 
{
    system("cls");

    //qstate = mysql_query(conn, "SELECT CustID, OrderDate (quantity*menuprice)as totalprice FROM Menu Right JOIN `Ordering` USING (menuId) "); //here add calculation
    qstate = mysql_query(conn, "SELECT S.CustID, SUM(M.MenuPrice * S.Quantity) as totalPrice FROM menu as M INNER JOIN ordering as S ON M.MenuID = S.MenuID Group by S.CustID ");
   // qstate = mysql_query(conn, "SELECT OrderID, MenuID, Quantity FROM menuorder");
        
    //set width //header

   
    //cout << "Your unique CUSTOMER ID is : "; 
    cout << "You Have Ordered :\n\n"; 
    cout << "=====================================================================================================================================================\n";
    cout << left << setw(18) << " Customer ID" << right << setw(60) << "Your total for all orders" << right << setw(23) << endl;
    cout << "======================================================================================================================================================\n";

    //cout << setw(11) << "OrderID" << setw(20) << "OrderDate(yyyy/mm/dd)" << setw(23) << "MenuID" << setw(15) << "CustID"  << setw(20) << "OrderQuantity" << endl;
    if (!qstate)
    {
        //body table
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) //fetch every row until the end of data
        {
            cout << setw(8) << "ID -" << setw(3) << row[0] << setw(50) << "RM" << setw(8) << row[1] << endl; // setw(20) << row[3] << setw(20) << row[4] << setw(20) << row[5] << endl; //still gotta fix spacing
        }
        
    } //listing available
  

    char choose;
    cout << "\n\n\n =====> Choose (e) (E) to edit Order <====== \n";
    cout << "\n =====> Choose (s) (S) to search Order <====== \n";
    cout << "\n =====> Choose (m) (M) to head back to Customer Menu <====== \n";
    cout << "\n PLEASE INPUT YOUR CHOICE : ";
    cin >> choose;
    if (choose == 'e' || choose == 'E')
        UpdateDelOrder();
    else if (choose == 's' || choose == 'S')
        SearchOrder();
    else if (choose == 'm' || choose == 'M')
        CustomerMenu();

} 
void UpdateDelOrder()
{
    system("cls");
  
        qstate = mysql_query(conn,"SELECT menuId, OrderDate, (quantity * menuprice)as totalprice, (Select custid from customer where custid = Ordering.custid) as custid, ordering.orderid FROM Menu Right JOIN Ordering USING(menuId )");

        //set width //header
        cout << setw(11) << "MenuID" << setw(28) << "Date " << setw(44) << " (Sub) Total Price " << setw(32) << "Cust ID" << setw(34) << " Order ID " << setw(8) << endl;
        if (!qstate)
        {
            //body table
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) //fetch every row until the end of data
            {
                cout << setw(8) << row[0] << setw(33) << row[1] << setw(30) << "RM" << setw(9) << row[2] << setw(32) << row[3] << setw(32) << row[4] << row[5] << endl;
            }

        }
            char choose;
            string OrderID, MenuID, quantity, date, CustID;

            do
            {

                cout << "\n ****** Choose (u) (U) to edit Order ***** \n";
                cout << "\n ****** Choose (d) (D) to delete Order ****** \n";
                cin >> choose;

            } while (choose != 'u' && choose != 'U' && choose != 'd' && choose != 'D');
        

            cout << "Enter Order ID: ";
            cin >> OrderID;

            if (choose == 'u' || choose == 'U')
            {
                int chooseUpdate = 0;
                system("cls");
                do
                {

                    string search_query = " SELECT `OrderID`, `OrderDate`, `MenuID`, `CustID`, `Quantity` from ordering where `OrderID` = '" + OrderID + "'";
                    const char* q = search_query.c_str();
                    qstate = mysql_query(conn, q);
                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res)) //looping to retreive the data
                    {
                        cout << "\t\t\t\t    ---------------------------------------------\n";
                        cout << "\t\t\t\t          |   CUSTOMER ORDER DETAILS  |\n";
                        cout << "\t\t\t\t    -----------------------------------------------\n";
                        cout << "ORDER ID: " << row[0] << " =========> Uneditable"
                            << "\n\n1. MENU ID: " << row[2]
                            << "\n2. QUANTITY of Order : " << row[4]
                            << "\n3. CUST ID :" << row[3] << " =========> Uneditable"
                            << "\n4. ORDER DATE :" << row[1]
                            << "\n5. SAVE YOUR ORDER ";

                    }
                    cout << "\n Choose to update ->  1. update the MENU ID  2. update the Order QUANTITY  3. update the Order DATE\n\n ";
                    cout << " PLEASE INPUT YOUR CHOICE : ";

                    cin >> chooseUpdate;
                    cin.ignore(1, '\n');
                    if (chooseUpdate == 1)
                    {
                        qstate = mysql_query(conn, "select MenuID, MenuName, MenuDescription, MenuPrice from Menu");

                        //set width //header
                        cout << setw(11) << "MenuID" << setw(20) << "Name" << setw(11) << " " << setw(22) << "Description" << setw(30) << " " << setw(8) << "Price" << endl;
                        if (!qstate)
                        {
                            //body table
                            res = mysql_store_result(conn);
                            while (row = mysql_fetch_row(res)) //fetch every row until the end of data
                            {
                                cout << setw(8) << row[0] << setw(27) << row[1] << setw(27) << row[2] << setw(30) << "RM" << setw(9) << row[3] << endl;
                            }
                        }
                        cout << "Insert New MenuID : ";
                        getline(cin, MenuID);
                        string update_query = "update `ordering` set `MenuID` = '" + MenuID + "' where `OrderID` = '" + OrderID + "'"; //updating menu id 
                        const char* q = update_query.c_str();
                        qstate = mysql_query(conn, q);
                    }
                    else if (chooseUpdate == 2)
                    {
                        cout << "Insert New Quantity of Order :";
                        getline(cin, quantity);
                        string update_query = "update `ordering` set `Quantity` = '" + quantity + "' where `OrderID` = '" + OrderID + "'"; //change order qty
                        const char* q = update_query.c_str();
                        qstate = mysql_query(conn, q);

                    }
                    else if (chooseUpdate == 4)
                    {
                        cout << "Insert New date of Order (yyyy/mm/dd) :";
                        getline(cin, date);
                        string update_query = "update `ordering` set `OrderDate` = '" + date + "' where `OrderID` = '" + OrderID + "'"; //change date
                        const char* q = update_query.c_str();
                        qstate = mysql_query(conn, q);

                    }
                    else if (chooseUpdate == 5)
                    {
                        ListofOrders();
                    }
                } while (true);
            }


            else if (choose == 'd' || choose == 'D')
            {
                char choose2;
                do
                {
                    cout << "Are you sure want to remove your Order? (y/n): ";
                    cin >> choose2;
                    if (choose2 == 'y' || choose2 == 'Y')
                    {
                        string delete_query = "delete from `ordering` where `OrderID` = '" + OrderID + "'";
                        const char* q = delete_query.c_str();
                        qstate = mysql_query(conn, q);
                        if (!qstate)
                        {
                            cout << "The Order has been removed. Press Enter to Continue...";
                            _getch();
                            ListofOrders();
                        }
                        else
                        {
                            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                        }
                    }

                } while (choose2 != 'y' && choose2 != 'Y' && choose2 != 'n' && choose2 != 'N');
            }
        }

    
      


void SearchOrder()
{
    system("cls");
    char choose;
    string CustID;
    cin.ignore(1, '\n');
    cout << "Search your orders by your CUSTOMER ID: ";
    getline(cin, CustID);


    cout << "\t\t\t\t    ---------------------------------------------\n";
    cout << "\t\t\t\t          |  LIST OF SEARCHED ORDERS |\n";
    cout << "\t\t\t\t    -----------------------------------------------\n";

    string search_query = "select OrderID, OrderDate, MenuID, Quantity from ordering where CustID like '%" + CustID + "%'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << setw(11) << "OrderID" << setw(30) << "Date" << setw(30) << "MenuID"  << setw(33) << "Quantity\n" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(6)<< "Order ID - " << setw(3) <<  row[0] << setw(30) << row[1] << setw(30) << "Menu ID - " << setw(3) << row[2] << setw(23) << row[3] << setw(23) << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }


    cout << "\n ======> Choose (e) (E) to edit Menu <======: ";
    cout << "\n ======> Choose (s) (S) to search Menu <======: ";
    cout << "\n ======> Choose (m) (M) to go back to Main Menu <======: ";
    cin >> choose;
    if (choose == 'e' || choose == 'E')
        UpdateDelOrder();
    else if (choose == 's' || choose == 'S')
        SearchOrder();
    else if (choose == 'm' || choose == 'M')
        CustomerMenu();
    else
        ListofOrders();
}

//analysis table
void InsertCustomerRate()
{
    system("cls");
    string rating, comments, CustID, AdminID;

    cout << "Insert your rate" << endl;
    cin.ignore(1, '\n');
    cout << "RATE YOUR EXPERIENCE OUR OF 5: ";
    getline(cin, rating);
    cout << "COMMENTS: ";
    getline(cin, comments);
    cout << "WHAT IS YOUR UNIQUE CUSTOMER ID: ";
    getline(cin, CustID);
    cout << "ADMIN ID (INPUT VALUE 1): ";
    getline(cin, AdminID);
    //cout << "Expired Date (dd/mm/yyyy): ";
   // getline(cin, expdate);

    //YYYY-MM-DD //default date format - MySQL INSERT INTO `rate` (`ID`, `rating`, `comments`, `CustID`, `AdminID`) VALUES (NULL, '3', 'good. fast.', '10', '1')


    string insert_query = "INSERT INTO `rate` (`rating`, `comments`, `CustID`, `AdminID`) VALUES ('" + rating + "','" + comments + "','" + CustID + "', '" + AdminID + "')";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate) 
    {
        cout << endl << "Rating is successfully added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    char choose;
    do
    {
        cout << "Do you want add another rate? (y/n): ";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
        {
            InsertCustomerRate();
        }
        else if (choose == 'n' || choose == 'N')
        {
            CustomerMenu();
        }
    } while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
}

void ViewCustomerRate()
{
    system("cls");
    qstate = mysql_query(conn, "select ID, rating, comments, CustID, AdminID from rate");

    //set width //header
    cout << setw(9) << "ID" << setw(30) << "Ratings" << setw(31) << " Comments" << setw(32) << "CustID" << setw(17) <<  endl;
    if (!qstate)
    {
        //body table
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) //fetch every row until the end of data
        {
            cout << setw(9) << row[0] << setw(27) << row[1] << setw(33) << row[2] << setw(31)  << row[3] << endl;
        }
    }

    char choose;
    cout << "\n (s) to search ratings : ";
    cin >> choose;
    if (choose == 's' || choose == 'S')
        SearchRate();
    else 
        AdminMenu();
   
}
void SearchRate()
{
    system("cls");
    char choose;
    string rating;
    cin.ignore(1, '\n');
    cout << "Search your ratings: ";
    getline(cin, rating);

    cout << "\t\t\t\t--- List of Searched ratings ---\n\n" << endl;

    string search_query = "select ID, AdminID, comments, CustID from rate where rating like '%" + rating  + "%'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << setw(9) << "Rate ID" << setw(30) << "Admin ID" << setw(30) << "Comments"  << setw(30) << "CustID" << setw(25) << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(6) << row[0] << setw(29) << row[1] << setw(33) << row[2]  << setw(30) << row[3] << setw(23) << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "\n\n\n =====> Choose (s) (S) to Search Rate <====== \n";
    cout << "\n =====> Choose (m) (M) to exit to Admin Menu <====== \n";
    cin >> choose;
    if (choose == 's' || choose == 'S')
        SearchRate();
    else if (choose == 'm' || choose == 'M');
    AdminMenu();
    
}


void report()
{
    system("cls");
    int choose;

    cout << setw(10) << "******************************************************************************************** \n\n\n" << endl;
    cout << setw(5) << "                   HI ADMIN \n\n" << endl;
    cout << setw(5) << "        THIS IS THE RATE SECTION OF M&M COLLAB RESTAURANT \n\n\n";
    cout << "                       YOU MAY CHOOSE YOUR TASK \n\n\n";
    cout << setw(10) << "             1. VIEW MAXIMUM RATING \n\n";
    cout << setw(5) << "               2. VIEW MINIMUM RATING \n\n";
    cout << setw(10) << "*********************************************************************************************\n\n" << endl;
    cout << "\n\n PLEASE INPUT YOUR CHOICE : \n";
    cin >> choose;
    switch (choose)
    {
    case 1:
        MaxRate(); //function to insert new data
        break;
    case 2:
        MinRate();
        break;
    case 3:
        AdminMenu();
        break;
    }
}

void MinRate()
{
    qstate = mysql_query(conn, "SELECT MIN(rating) AS LowestRate FROM rate");

    if (!qstate)
    {
        cout << endl << endl << "   Minimum ratings \t: ";

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(3) << " " << row[0] << endl;
        }
    }
    char choose;
    cout << "\n *******  INPUT (p) (P) TO CHECK MAXIMUM RATE  ******** : ";
    cout << "\n *******  Select a random key to head back to the ADMIN MENU  ******** : ";
    cin >> choose;
    if (choose == 'p' || choose == 'P')
        MaxRate();
    else
        AdminMenu();
}

    
void MaxRate()
{
    qstate = mysql_query(conn, "SELECT MAX(rating) AS HighestRate FROM rate");

    if (!qstate)
    {
        cout << endl << endl << "   Max ratings \t: ";

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(3) << " " << row[0] << endl;
        }
    }
    char choose;
    cout << "\n ******* INPUT (p) (P) TO CHECK MINIMUM RATE******** : ";
    cout << "\n ******* Select a random key to head back to the ADMIN MENU ******** : ";
    cin >> choose;
    if (choose == 'p' || choose == 'P')
        MinRate();
    else
        AdminMenu();
}


//AS LowestRate FROM rate
//sql for max SELECT MAX(rating) AS HighestRate FROM rate