#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include "queue1.h"
#include "stackme.h"

using namespace std;

int search(int);
int display();
void customer_portal();
//      string check(int); // for checking quantity   //

////////////////////////////////////////////////////////////////////
struct node
{
    int ID;
    string proName;
    double prePrice;
    int quantity;
    struct node *next;
};

struct node *head = NULL;

////////////////////////////////////////////////////////////////////
void beg()
{
    system("cls");
    int id, quant; // quant for quantity
    string name;
    double pre; // pre for price
    struct node *t = new node;
    struct node *p = head;

    cout << "\t\t\tEnter product ID:-";
    cin >> id;
    t->ID = id;
    cout << "\t\t\tEnter product Name:-";
    cin >> name;
    t->proName = name;
    cout << "\t\t\tEnter product price:-";
    cin >> pre;
    t->prePrice = pre;
    cout << "\t\t\tEnter product quantity:-";
    cin >> quant;
    t->quantity = quant;
    if (head == NULL)
    {
        t->next = head;
        head = t;
    }
    else
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = t;
        t->next = NULL;
    }
    system("cls");
    cout << "\n\n\t\t\t\tThis product is Inserted!\n\n\n";
}

///////////////////////////////////////////////////////////////////////////////////////////
int search(int id) // for search item in list
{
    int count = 1;
    struct node *p = head;
    while (p != NULL)
    {
        if (p->ID == id)
            break;
        else
            count++;
        p = p->next;
    }
    return count;
}
///////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
void delPro()
{
    system("cls");
    display();
    int id;
    struct node *cur = head;
    struct node *pre = head;
    cout << "\n\nEnter ID to delete that product:\n\n";
    cin >> id;
    if (head == NULL)
    {
        system("cls");
        cout << "List is empty" << endl;
    }
    int pos = 0;
    int count = display(); // for load no of nodes
    pos = search(id);       // for check whether desired node exists or not
    if (pos <= count)
    {
        while (cur->ID != id)
        { // for delete middle area products
            pre = cur;
            cur = cur->next;
        }
        pre->next = cur->next;
        system("cls");
        cout << "\n<<item is deleted>>\n";
    }
    else
    {
        cout << "\n<<<Not found>>\n\n";
    }
}

//////////////////////////////////////////////////////////////////////////////////
void modify()
{
    int id;
    double pre; // pre for price
    string pName;
    int nid;
    int nq; // pName for new name
    if (head == NULL)
    {
        system("cls");
        cout << "List is empty" << endl;
    }
    else
    {
        display();
        cout << "\n\nEnter ID to modify product Name and its price:\n";
        cin >> id;
        struct node *cur = head;
        int pos = 0;
        int count = display(); // for load no of nodes
        pos = search(id);      // for check whether desired node exists or not
        if (pos <= count)
        {
            while (cur->ID != id)
            {
                cur = cur->next;
            }
            cout << "\nOld ID : " << cur->ID << endl;
            cout << "\nOld Name : " << cur->proName << endl;
            cout << "\nOld Price : " << cur->prePrice << endl;
            cout << "\nOld Quantity : " << cur->quantity << endl;

            cout << endl
                 << endl;
            cout << "Enter new ID:";
            cin >> nid;
            cur->ID = nid;
            cout << "Enter new Name:";
            cin >> pName;
            cur->proName = pName;
            cout << "Enter new Price:";
            cin >> pre;
            cur->prePrice = pre;
            cout << "Enter new Quantity:";
            cin >> nq;
            cur->quantity = nq;
        }
        else
        {
            cout << id << " is <<<Not found>>\n\n";
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////
int display()
{
    system("cls");
    int c = 0; // c for count products
    struct node *p = head;
    cout << "Existing products are:\n";
    cout << "ID\t\tProduct Name\t\t Price\t\tQuantity\n";
    cout << "=================================================================|\n";
    while (p != NULL)
    {
        cout << p->ID << "\t\t" << p->proName << "\t\t" << p->prePrice << "\t\t" <<p->quantity << "\n"; // call check func and pass quantity
        p = p->next;
        c = c + 1;
    }
    cout << "\nTotal products in our store is : " << c << "\n\n\n";
    return c;
}
////////////////////////////////////////////////////////////////////////////////////////
/*  string check(int quant)
    { 
        // check function;
    int a = quant;
    stringstream ss;
    ss << a;
    string quantity = ss.str();

    if (quant <= 0)
        return "out of stock!";
    else
        return quantity;
}   
*/
///////////////////////////////////////////////////////////////////////
void buy()
{
    system("cls");
    display();
    
    string products[20];
    int pay = 0, no, c = 0, price, id, i = 1;

    if (head == NULL)
    {
        cout << "\n<<<<There are no items to buy>>>>\n\n";
        return;
    }

    cout << "How many items do you want to buy? ";
    cin >> no;

    int count = display(); // For storing the number of nodes

    while (i <= no)
    {
        struct node *cur = head;
        int quant, cho;
    a:
        cout << "Enter the ID of the item you want to buy: ";
        cin >> id;

        if (id == -1)
        {
            system("cls");
            return;
        }

        int pos = search(id);
        if (pos <= count)
        {
            while (cur->ID != id)
            {
                cur = cur->next;
            }

            cout << "How many quantities do you want: ";
            cin >> quant;

            if (cur->quantity < quant)
            {
                cout << "\n\n\t\t\t----The Quantity You Entered is not available---" << endl;
                cout << "\n\t\t\t-----(Press -1 to return to the Main Menu)------" << endl;
                goto a;
            }

            products[c] = cur->proName; // This will contain the names of the bought items
            c++;

            pay = pay + (cur->prePrice * quant); // Calculate the bill
            cur->quantity = cur->quantity - quant; // Update quantity
            i++;
        }
        else
        {
            cout << "\n<<<<<<<<<This item is not available in our store at this time>>>>\n\n";
        }
    }
     
    cout << "\n\n\n\n\t\t\tYou have bought: ";
    for (int i = 0; i < no; i++)
    {
        cout << products[i] << ",";
    }

    price = pay * 0.90; // Applying 10% discount
    cout << "\n\nOriginal price: " << pay;
    cout << "\nWith 10% discount: " << price << "\nThank you for shopping!\n\n";
    string customer;

    cout << "\n\t\t Enter Your Name: ";
    cin >> customer;

    // Assuming enqueue function is correctly defined elsewhere
    enqueue(customer);
}


///////////////////////////////////////////////////////////////////////////////////////
void administrator()
{
    system("cls");
    int ch;

    do
    {
        // choice for below message
        cout << "\t\t============================================" << endl;
        cout << "\t\t|          Administrator Portal              |" << endl;
        cout << "\t\t============================================" << endl;

        cout << "\t\t     Enter 1 to ADD a new product    " << endl;
        cout << "\t\t     Enter 2 to display all products   " << endl;
        cout << "\t\t     Enter 3 to MODIFY an Existing product" << endl;
        cout << "\t\t     Enter 4 to Delete a particular product item" << endl;
        cout << "\t\t     Enter 5 to view Customers List " << endl;
        cout << "\t\t     Enter 6 to Dequeue a customer" << endl;
        cout << "\t\t     Enter 7 to View sold items" << endl;
     //   cout << "\t\t     Enter 8 to Check out" << endl;   //
        cout << "\t\t     Enter 0 to Exit" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            beg();
            break;
        case 2:
            display();
            break;
        case 3:
            modify();
            break;
        case 4:
            delPro();
            break;
        case 5:
             displayQueue(); // Placeholder for displayQueue function
            break;
        case 6:
             dequeue(); // Placeholder for dequeue function
            break;
        case 7:
             display(); // Placeholder for display function
            break;
       /* case 8:
             //check(); // Placeholder for check function
            break;    */
        case 0:
        customer_portal();
            exit(0);
            break;
        default:
            cout << "Invalid input";
        }
    } while (ch != 0);
}

void customer_portal(){
     int ch = -1;
 do
    {
        system("cls");
        cout << "\t\t============================================" << endl;
        cout << "\t\t|                WELCOME!                   |" << endl;
        cout << "\t\t============================================" << endl;

        cout << "\t\t      Enter 1 for Admin Portal           " << endl;
        cout << "\t\t      Enter 2 for Customer Portal       " << endl;
        cout << "\t\t      Enter 0 to exit system" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            administrator();
            break;
        case 2:
            buy();
            break;
        case 0:
            exit(0);
            break;
        default:
            cout << "Invalid input";
        }
    } while (ch != 0);

    }

////////////////////////////////////////////////////////////////////////////////////////
int main()
{
   customer_portal();
   
    return 0;
}