#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==============================
   BANK ACCOUNT - LINKED LIST
   ============================== */

struct Account
{
    int accountNumber;
    char name[50];
    float balance;
    struct Account *next;
};

struct Account *head = NULL;


/* ==============================
   TRANSACTION - STACK
   ============================== */

struct Transaction
{
    char details[100];
    struct Transaction *next;
};

struct Transaction *top = NULL;


/* ==============================
   BINARY SEARCH TREE
   ============================== */

struct TreeNode
{
    int accountNumber;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *root = NULL;


/* ==============================
   SEARCH ACCOUNT IN LINKED LIST
   ============================== */

struct Account* searchAccount(int number)
{
    struct Account *temp = head;

    while (temp != NULL)
    {
        if (temp->accountNumber == number)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}


/* ==============================
   INSERT ACCOUNT INTO BST
   ============================== */

struct TreeNode* insertBST(struct TreeNode *root, int number)
{
    if (root == NULL)
    {
        struct TreeNode *newNode;

        newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));

        newNode->accountNumber = number;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    if (number < root->accountNumber)
    {
        root->left = insertBST(root->left, number);
    }
    else if (number > root->accountNumber)
    {
        root->right = insertBST(root->right, number);
    }

    return root;
}


/* ==============================
   SEARCH USING BST
   ============================== */

struct TreeNode* searchBST(struct TreeNode *root, int number)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->accountNumber == number)
    {
        return root;
    }

    if (number < root->accountNumber)
    {
        return searchBST(root->left, number);
    }

    return searchBST(root->right, number);
}


/* ==============================
   CREATE ACCOUNT
   ============================== */

void createAccount()
{
    struct Account *newAccount;
    struct Account *temp;

    newAccount = (struct Account*)malloc(sizeof(struct Account));

    printf("\nEnter Account Number: ");
    scanf("%d", &newAccount->accountNumber);

    /* Check duplicate account number */
    if (searchAccount(newAccount->accountNumber) != NULL)
    {
        printf("Account already exists!\n");
        free(newAccount);
        return;
    }

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", newAccount->name);

    printf("Enter Initial Balance: ");
    scanf("%f", &newAccount->balance);

    if (newAccount->balance < 0)
    {
        printf("Balance cannot be negative.\n");
        free(newAccount);
        return;
    }

    newAccount->next = NULL;

    /* Add account to linked list */
    if (head == NULL)
    {
        head = newAccount;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newAccount;
    }

    /* Add account number to BST */
    root = insertBST(root, newAccount->accountNumber);

    printf("\nAccount created successfully!\n");
}


/* ==============================
   DISPLAY ALL ACCOUNTS
   ============================== */

void displayAccounts()
{
    struct Account *temp = head;

    if (head == NULL)
    {
        printf("\nNo accounts available.\n");
        return;
    }

    printf("\n========== ALL ACCOUNTS ==========\n");

    while (temp != NULL)
    {
        printf("\nAccount Number : %d", temp->accountNumber);
        printf("\nAccount Holder : %s", temp->name);
        printf("\nBalance        : Rs. %.2f", temp->balance);
        printf("\n----------------------------------");

        temp = temp->next;
    }
}


/* ==============================
   SEARCH ACCOUNT
   ============================== */

void findAccount()
{
    int number;

    struct Account *account;
    struct TreeNode *result;

    printf("\nEnter Account Number: ");
    scanf("%d", &number);

    /* Search account number in BST */
    result = searchBST(root, number);

    if (result == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    /* Get complete account information */
    account = searchAccount(number);

    printf("\nAccount Found!\n");
    printf("Account Number : %d\n", account->accountNumber);
    printf("Account Holder : %s\n", account->name);
    printf("Balance        : Rs. %.2f\n", account->balance);
}


/* ==============================
   CHECK BALANCE
   ============================== */

void checkBalance()
{
    int number;

    struct Account *account;

    printf("\nEnter Account Number: ");
    scanf("%d", &number);

    account = searchAccount(number);

    if (account == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    printf("\nAccount Holder : %s", account->name);
    printf("\nAccount Number : %d", account->accountNumber);
    printf("\nCurrent Balance: Rs. %.2f\n", account->balance);
}


/* ==============================
   PUSH TRANSACTION INTO STACK
   ============================== */

void pushTransaction(char text[])
{
    struct Transaction *newTransaction;

    newTransaction =
        (struct Transaction*)malloc(sizeof(struct Transaction));

    strcpy(newTransaction->details, text);

    newTransaction->next = top;

    top = newTransaction;
}


/* ==============================
   DISPLAY RECENT TRANSACTIONS
   ============================== */

void displayTransactions()
{
    struct Transaction *temp = top;

    if (top == NULL)
    {
        printf("\nNo transactions available.\n");
        return;
    }

    printf("\n========== RECENT TRANSACTIONS ==========\n");

    while (temp != NULL)
    {
        printf("%s\n", temp->details);

        temp = temp->next;
    }
}


/* ==============================
   DEPOSIT MONEY
   ============================== */

void depositMoney()
{
    int number;

    float amount;

    char transaction[100];

    struct Account *account;

    printf("\nEnter Account Number: ");
    scanf("%d", &number);

    account = searchAccount(number);

    if (account == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("Enter a valid amount.\n");
        return;
    }

    account->balance = account->balance + amount;

    /* Add transaction to stack */
    sprintf(transaction,
            "Account %d : Deposited Rs. %.2f",
            number, amount);

    pushTransaction(transaction);

    printf("\nMoney deposited successfully.");
    printf("\nNew Balance: Rs. %.2f\n",
           account->balance);
}


/* ==============================
   WITHDRAW MONEY
   ============================== */

void withdrawMoney()
{
    int number;

    float amount;

    char transaction[100];

    struct Account *account;

    printf("\nEnter Account Number: ");
    scanf("%d", &number);

    account = searchAccount(number);

    if (account == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("Enter a valid amount.\n");
        return;
    }

    if (amount > account->balance)
    {
        printf("Insufficient balance.\n");
        return;
    }

    account->balance = account->balance - amount;

    /* Add transaction to stack */
    sprintf(transaction,
            "Account %d : Withdrawn Rs. %.2f",
            number, amount);

    pushTransaction(transaction);

    printf("\nMoney withdrawn successfully.");
    printf("\nRemaining Balance: Rs. %.2f\n",
           account->balance);
}


/* ==============================
   DELETE ACCOUNT
   ============================== */

void deleteAccount()
{
    int number;

    struct Account *temp;
    struct Account *previous;

    printf("\nEnter Account Number to Delete: ");
    scanf("%d", &number);

    if (head == NULL)
    {
        printf("No accounts available.\n");
        return;
    }

    /* Delete first account */
    if (head->accountNumber == number)
    {
        temp = head;

        head = head->next;

        free(temp);

        printf("Account deleted successfully.\n");

        return;
    }

    previous = head;

    /* Find account */
    while (previous->next != NULL &&
           previous->next->accountNumber != number)
    {
        previous = previous->next;
    }

    if (previous->next == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    temp = previous->next;

    previous->next = temp->next;

    free(temp);

    printf("Account deleted successfully.\n");
}


/* ==============================
   COUNT ACCOUNTS
   ============================== */

void countAccounts()
{
    int count = 0;

    struct Account *temp = head;

    while (temp != NULL)
    {
        count++;

        temp = temp->next;
    }

    printf("\nTotal Accounts: %d\n", count);
}


/* ==============================
   MAIN FUNCTION
   ============================== */

int main()
{
    int choice;

    do
    {
        printf("\n\n========================================");
        printf("\n     BANK ACCOUNT MANAGEMENT SYSTEM");
        printf("\n========================================");

        printf("\n1. Create Account");
        printf("\n2. Display All Accounts");
        printf("\n3. Search Account");
        printf("\n4. Check Balance");
        printf("\n5. Deposit Money");
        printf("\n6. Withdraw Money");
        printf("\n7. Delete Account");
        printf("\n8. Count Accounts");
        printf("\n9. View Recent Transactions");
        printf("\n10. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                displayAccounts();
                break;

            case 3:
                findAccount();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                depositMoney();
                break;

            case 6:
                withdrawMoney();
                break;

            case 7:
                deleteAccount();
                break;

            case 8:
                countAccounts();
                break;

            case 9:
                displayTransactions();
                break;

            case 10:
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while (choice != 10);


    /* Free linked list memory */
    while (head != NULL)
    {
        struct Account *temp = head;

        head = head->next;

        free(temp);
    }


    /* Free stack memory */
    while (top != NULL)
    {
        struct Transaction *temp = top;

        top = top->next;

        free(temp);
    }


    return 0;
}