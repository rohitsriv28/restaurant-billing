#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#define MAX_ITEMS 50
#define MAX_NAME_LENGTH 50
#define MAX_DATE_LENGTH 30
#define FILENAME "SpiceSymphony.dat"

// Color codes for terminal
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

// Structures
typedef struct {
    char name[20];
    float price;
    int quantity;
} Item;

typedef struct {
    char customer[MAX_NAME_LENGTH];
    char date[MAX_DATE_LENGTH];
    int itemCount;
    Item items[MAX_ITEMS];
} Order;

// Function Prototypes
void clearInputBuffer();
void clearScreen();
void colorPrintf(int color, const char* format, ...);
void printBillHeader(const char* name, const char* date);
void printBillBody(const char* item, int quantity, float price);
void printBillFooter(float total);
void saveOrder(const Order* order);
void displayAllOrders();
void searchOrderByCustomer();
void createNewOrder();
void displayMenu();

// Utility function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Screen Clearing Function
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Color Printf Function
void colorPrintf(int color, const char* format, ...) {
    va_list args;
    va_start(args, format);
    switch(color) {
        case 1: printf(COLOR_RED); break;
        case 2: printf(COLOR_GREEN); break;
        case 3: printf(COLOR_YELLOW); break;
        case 4: printf(COLOR_BLUE); break;
        default: break;
    }
    vprintf(format, args);
    printf(COLOR_RESET);
    va_end(args);
}

// Bill Header Printing
void printBillHeader(const char* name, const char* date) {
    char dateStr[20], timeStr[20];
    sscanf(date, "%s %s", dateStr, timeStr);
    printf("\n\n\t Spice Symphony");
    printf("\n\t -----------------");
    printf("\nDate: %s\tTime: %s", dateStr, timeStr);
    printf("\nInvoice To: %s", name);
    printf("\n---------------------------------------\n");
    printf("Items\t\tQty\t\tTotal\t\t");
    printf("\n---------------------------------------\n\n");
}

// Bill Body Printing
void printBillBody(const char* item, int quantity, float price) {
    printf("%-15s\t%d\t\t%.2f\n", item, quantity, quantity * price);
}

// Bill Footer Printing with Tax Calculations
void printBillFooter(float total) {
    float discount = 0.1 * total;
    float netTotal = total - discount;
    float vat = 0.13 * netTotal;
    float grandTotal = netTotal + vat;
    
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f\n", total);
    printf("Discount @10%%\t\t\t%.2f\n", discount);
    printf("\t\t\t\t-------\n");
    printf("Net Total\t\t\t%.2f\n", netTotal);
    printf("VAT @13%%\t\t\t%.2f\n", vat);
    printf("---------------------------------------\n");
    printf("Grand Total\t\t\t%.2f\n", grandTotal);
    printf("---------------------------------------\n");
}

// Save Order to File
void saveOrder(const Order* order) {
    FILE* fp = fopen(FILENAME, "ab");
    
    if (fp == NULL) {
        colorPrintf(1, "Error opening file for saving.\n");
        return;
    }
    
    if (fwrite(order, sizeof(Order), 1, fp) == 1) {
        colorPrintf(2, "Successfully saved invoice.\n");
    } else {
        colorPrintf(1, "Error saving invoice.\n");
    }
    
    fclose(fp);
}

// Display All Orders
void displayAllOrders() {
    FILE* fp = fopen(FILENAME, "rb");
    
    if (fp == NULL) {
        colorPrintf(3, "No previous invoices found.\n");
        return;
    }
    
    Order order;
    
    colorPrintf(4, "\n *****Your Previous Invoices*****\n");
    
    rewind(fp);
    
    while (fread(&order, sizeof(Order), 1, fp) == 1) {
        float total = 0;
        printBillHeader(order.customer, order.date);
        
        for (int i = 0; i < order.itemCount; i++) {
            printBillBody(order.items[i].name, order.items[i].quantity, order.items[i].price);
            total += order.items[i].quantity * order.items[i].price;
        }
        
        printBillFooter(total);
    }
    
    fclose(fp);
}

// Search Order by Customer Name
void searchOrderByCustomer() {
    char name[MAX_NAME_LENGTH];
    
    int invoiceFound = 0;
    
    printf("Enter the customer name: ");
    
    clearInputBuffer();
    
    fgets(name, sizeof(name), stdin);
    
    name[strcspn(name, "\n")] = 0; // Remove newline character
    
    FILE* fp = fopen(FILENAME, "rb");
    
    if (fp == NULL) {
        colorPrintf(3, "No invoices found.\n");
        return;
    }
    
    Order order;
    
    rewind(fp);
    
    colorPrintf(4, "\t*****Invoice of %s*****\n", name);
    
    while (fread(&order, sizeof(Order), 1, fp) == 1) {
        if (strcasecmp(order.customer, name) == 0) {
            float total = 0;
            printBillHeader(order.customer, order.date);
            
            for (int i = 0; i < order.itemCount; i++) {
                printBillBody(order.items[i].name, order.items[i].quantity, order.items[i].price);
                total += order.items[i].quantity * order.items[i].price;
            }
            
            printBillFooter(total);
            invoiceFound = 1;
        }
    }
    
   if (!invoiceFound) {
       colorPrintf(3,"Sorry, no invoice found for %s\n", name);
   }
   
   fclose(fp);
}

// Create New Order
void createNewOrder() {
   Order order;
   float total = 0;
   int itemCount;

   // Get current date and time
   time_t now;
   struct tm *timeinfo;

   time(&now);
   timeinfo = localtime(&now);

   // Format date and time
   strftime(order.date,sizeof(order.date),"%Y-%m-%d %H:%M:%S",timeinfo);

   printf("Enter customer name: ");
   clearInputBuffer();
   fgets(order.customer,sizeof(order.customer),stdin);
   order.customer[strcspn(order.customer,"\n")] = 0;

   printf("Enter number of items: ");
   scanf("%d",&itemCount);

   order.itemCount = (itemCount > MAX_ITEMS) ? MAX_ITEMS : itemCount;

   for(int i=0; i<order.itemCount; i++) {
       clearInputBuffer();
       printf("\nEnter item %d name: ", i + 1);
       fgets(order.items[i].name,sizeof(order.items[i].name),stdin);
       order.items[i].name[strcspn(order.items[i].name,"\n")] = 0;

       printf("Enter quantity: ");
       scanf("%d",&order.items[i].quantity);

       printf("Enter unit price: ");
       scanf("%f",&order.items[i].price);

       total += order.items[i].quantity * order.items[i].price;
   }

   printBillHeader(order.customer ,order.date);

   for(int i=0; i<order.itemCount; i++) {
       printBillBody(order.items[i].name ,order.items[i].quantity ,order.items[i].price );
   }

   printBillFooter(total);

   char saveBill;

   printf("Save invoice? (y/n): ");
   scanf(" %c",&saveBill);

   if(saveBill == 'y' || saveBill == 'Y') {
       saveOrder(&order);
   }
}

// Display Menu
void displayMenu() {
   clearScreen();
   
   colorPrintf(4,"\n\t====== SPICE SYMPHONY ======\n");

   printf("\nSelect Operation:\n");
   printf("1. Create New Invoice\n");
   printf("2. View All Invoices\n");
   printf("3. Search Invoice\n");
   printf("4. Exit System\n");
}

// Main Function
int main() {
   int choice;
   
   char continueOperation = 'y';

   while (continueOperation == 'y' || continueOperation == 'Y') {
       displayMenu();

       printf("\nYour Choice: ");
       scanf("%d", &choice);

       switch (choice) {
           case 1:
               createNewOrder();
               break;
           case 2:
               displayAllOrders();
               break;
           case 3:
               searchOrderByCustomer();
               break;
           case 4:
               colorPrintf(2,"\n\t Culinary Journey Ends Here! 🍽️\n\n");
               return 0;
           default:
               colorPrintf(1,"Invalid option. Please try again.\n");
       }

       printf("\nContinue? (y/n): ");
       scanf(" %c", &continueOperation);
   }

   colorPrintf(2,"\n\t Culinary Journey Ends Here! 🍽️\n\n");

   return 0;
}