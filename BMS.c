#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

struct Account {
    int account_number;
    char name[50];
    float balance;
};

struct Account accounts[MAX_ACCOUNTS];
int num_accounts = 0;

// Function prototypes
void create_account();
void display_account();
void update_account();
void delete_account();
void save_accounts_to_file();
void load_accounts_from_file();
void sort_accounts_by_account_number();
void create_account() {
    struct Account new_account;
    printf("Enter account number: ");
    scanf("%d", &new_account.account_number);
    printf("Enter name: ");
    scanf("%s", new_account.name);
    printf("Enter balance: ");
    scanf("%f", &new_account.balance);
    accounts[num_accounts++] = new_account;
    printf("Account created successfully.\n");
}

void display_account() {
    int account_number;
    printf("Enter account number: ");
    scanf("%d", &account_number);
    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].account_number == account_number) {
            printf("Account Number: %d\n", accounts[i].account_number);
            printf("Name: %s\n", accounts[i].name);
            printf("Balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

void update_account() {
    int account_number;
    printf("Enter account number: ");
    scanf("%d", &account_number);
    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].account_number == account_number) {
            printf("Enter new name: ");
            scanf("%s", accounts[i].name);
            printf("Enter new balance: ");
            scanf("%f", &accounts[i].balance);
            printf("Account updated successfully.\n");
            return;
        }
    }
    printf("Account not found.\n");
}

void delete_account() {
    int account_number;
    printf("Enter account number: ");
    scanf("%d", &account_number);
    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].account_number == account_number) {
            for (int j = i; j < num_accounts - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            num_accounts--;
            printf("Account deleted successfully.\n");
            return;
        }
    }
    printf("Account not found.\n");
}

void save_accounts_to_file() {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < num_accounts; i++) {
        fprintf(file, "%d %s %.2f\n", accounts[i].account_number, accounts[i].name, accounts[i].balance);
    }
    fclose(file);
    printf("Accounts saved to file.\n");
}

void load_accounts_from_file() {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("No existing accounts file found.\n");
        return;
    }
    while (!feof(file) && num_accounts < MAX_ACCOUNTS) {
        struct Account new_account;
        fscanf(file, "%d %s %f", &new_account.account_number, new_account.name, &new_account.balance);
        accounts[num_accounts++] = new_account;
    }
    fclose(file);
    printf("Accounts loaded from file.\n");
}

void sort_accounts_by_account_number() {
    // Bubble sort implementation
    for (int i = 0; i < num_accounts - 1; i++) {
        for (int j = 0; j < num_accounts - i - 1; j++) {
            if (accounts[j].account_number > accounts[j + 1].account_number) {
                struct Account temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }
}

int main() {
    load_accounts_from_file(); // Load accounts from file when the program starts

    int choice;
    do {
        printf("__________________(WELCOME)_________________");
        printf("\n__________(Bank Management System)__________\n");
        printf("********************************************\n");
        printf("1. Create Account\n");
        printf("2. Display Account\n");
        printf("3. Update Account\n");
        printf("4. Delete Account\n");
        printf("5. Save Accounts to File\n");
        printf("6. Exit...\n");
        printf("********************************************\n");
        printf("____________________________________________\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: create_account(); break;
            case 2: display_account(); break;
            case 3: update_account(); break;
            case 4: delete_account(); break;
            case 5: save_accounts_to_file(); break;
            case 6: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 6);

    return 0;
}

