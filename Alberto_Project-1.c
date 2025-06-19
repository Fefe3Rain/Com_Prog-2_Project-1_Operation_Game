/*
    Written by: Rain Sidney G. Alberto
    Course & Section: Bachelor of Science in Information Technology - 1A
    Starting Date: March 4, 2025 (Time: 12:00 PM)
    End Date: March 30, 2025 (Time: 2:00 PM)
*/
// Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constant Variable
#define MAX 50

// Global Variables

// Parallel Arrays
char username[MAX][31], password[MAX][11];
int score[MAX] = {0}, ascore[MAX] = {0}, sscore[MAX] = {0}, mscore[MAX] = {0}, dscore[MAX] = {0};

// Array counters
int last, currentuser = 0;

// Function Declarations

// Basic Functions
int init(); // Initialize last to -1
int isfull(); //Returns 1 if full
int isempty(); // Returns 1 if empty

// Account Functions
int signin(); // Add new account
int login(); // Retrieves existing account

// Registration Functions Menu
int regmenu(); // Displays registration menu
int regcase(); // switch case for registration menu

// Data management functions
void upload(); // saves the data to a file
void download(); // retrieves the data from a file

// Games per operation
int addition(int items); // Randomizes the addition
int subtraction(int items); // Randomizes the subtraction
int multiplication(int items); // Randomizes the multiplication
int division(int items); // Randomizes the division

// Calculate the scores function
void calculate();

// Play function menu
int playmenu(); // Displays play menu
int playcase(); // switch case for play menu

// Functions for displaying leaderboards
int displaymenu(); // Displays display menu
void displayall(); // Displays all leaderboards
void displayadd(); // Displays addition leaderboards
void displaysub(); // Displays subtraction leaderboards
void displaymulti(); // Displays multiplication leaderboards
void displaydiv(); // Displays division leaderboards
int displaycase(); // switch case for display menu

// Main menu functions
int mainmenu(); // Displays main menu
int maincase(); // switch case for main menu

// Main Function
int main (){
    init();
    download();
    int reg = regcase(); // Flagger variable for the return value of regcase()
    if (reg == 1) { // if the user signed in successfully
        system("cls");
        maincase();
    } else { // if the user logged in successfully
        system("cls");
        printf("Welcome back!\n\n");
        displayall();
        maincase();
    }
    return 0;
}

// Function Definitions
int init(){
    last = -1;
}
int isfull(){
    return (last == MAX - 1);
}
int isempty(){
    return (last == -1);
}
int signin(){
    system("cls");
    if (isfull()){ // If statement for the system is full
        printf("The system is full!\n");
        system("pause");
        regcase();
    } else { // If statement for the system is not full
        printf("     Sign in\n\n");
        printf("Enter your username: ");
        scanf(" %[^\n]", username[last + 1]); // Using last + 1 to add a new account
        for (int i = 0; i <= last; i++){ // Duplicate checker
            if (strcmp(username[last + 1], username[i]) == 0){
                printf("Duplicate username is not allowed!\n");
                system("pause");
                signin();
                return 1;
            }
        }
        last++; // Increment last to add a new account
        printf("Enter your password: ");
        scanf(" %[^\n]", password[last]);
        getchar();
        printf("\nAccount successfully created!\n");
        system("pause");
        currentuser = last; // Set the current user to the last account created
        return 1;
    }
}
int login(){
    system("cls");
    if (isempty()){ // If statement for the system is empty
        printf("The system is empty!\n");
        system("pause");
        regcase();
    } else {
        int i;
        char un[31], pw[11]; // entry string  variables for login
        printf("      Log in\n\n");
        printf("Enter your username: ");
        scanf(" %[^\n]", un);
        printf("Enter your password: ");
        scanf(" %[^\n]", pw);
        getchar();

        for (i = 0; i <= last; i++){ // locates the index of the account
            if (strcmp(un, username[i]) == 0 && strcmp(pw, password[i]) == 0){
                printf("\nLogin successful!\n");
                currentuser = i;
                return 2;
            }
        }
        if (strcmp(un, username[i]) != 0 || strcmp(pw, password[i]) != 0){ // if the username and password do not match
            printf("Invalid username or password!\n");
            system("pause");
            regcase();
        }
        return 2;
    }
}
int regmenu(){
    int op;
    printf("Register an account first!\n\n");
    printf("1. Log in (Existing Players)\n");
    printf("2. Sign in (For new Players)\n");
    printf("3. Exit\n");
    printf("\nSelect an option(1-3): ");
    scanf("%d", &op);
    return op; // return the value of op
}
int regcase(){ // corresponds the returned value of regmenu()
    system("cls");
    switch(regmenu()){
        case 1:
            login();
            break;
        case 2:
            signin();
            break;
        case 3:
            system("cls");
            printf("Thank you for using my progarm.\n\n");
            exit(0);
            break;
        default:
            printf("Try again!\n");
            system("pause");
            regcase();
    }
}
void upload(){
    FILE *fp = fopen("accounts.txt", "w+");
    if (fp == NULL){ // If the file does not exist
        printf("File Error\\Error 404\n");
        system("pause");
    } else { // prints in a text file
        for (int i = 0; i <= last; i++)
            fprintf(fp, "%s\n%s\n%d %d %d %d %d\n", username[i], password[i], score[i], ascore[i], sscore[i], mscore[i], dscore[i]);
    }
    fclose(fp);
}
void download(){
    FILE *fp = fopen("accounts.txt", "r+");
    if (fp == NULL){ // If the file does not exist
        printf("File Error\\Error 404\n");
        system("pause");
    } else { // reads the text file
        while (fscanf(fp, " %[^\n]\n %[^\n]\n%d %d %d %d %d\n", username[last + 1], password[last + 1], &score[last + 1], &ascore[last + 1], &sscore[last + 1], &mscore[last + 1], &dscore[last + 1]) == 7)
            last++; // increments the last variable for the current index of the array
    }
    fclose(fp);
}
int addition(int items){
    int a, b, ans, i, ctr = 0;
    srand(time(NULL)); // seeding the random number generator
    for (i = 1; i <= items; i++){
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        printf("%d.) What is %d + %d = ", i, a, b);
        scanf("%d", &ans);
        if (ans == a + b){
            printf("Correct!\n");
            ctr++;
        } else
            printf("Wrong! The correct answer is %d.\n", a + b);
    }
    return ctr;
}
int subtraction(int items){
    int a, b, ans, i, ctr = 0;
    srand(time(NULL));
    for (i = 1; i <= items; i++){
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        printf("%d.) What is %d - %d = ", i, a, b);
        scanf("%d", &ans);
        if (ans == a - b){
            printf("Correct!\n");
            ctr++;
        } else
            printf("Wrong! The correct answer is %d.\n", a - b);
    }
    return ctr;
}
int multiplication(int items){
    int a, b, ans, i, ctr = 0;
    srand(time(NULL));
    for (i = 1; i <= items; i++){
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        printf("%d.) What is %d * %d = ", i, a, b);
        scanf("%d", &ans);
        if (ans == a * b){
            printf("Correct!\n");
            ctr++;
        } else
            printf("Wrong! The correct answer is %d.\n", a * b);
    }
    return ctr;
}
int division(int items){
    int i, ctr = 0;
    float a, b, ans;
    srand(time(NULL));
    for (i = 1; i <= items; i++){
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        printf("%d.) What is %.0f / %.0f = ", i, a, b);
        scanf("%f", &ans);
        if (ans >= a / b){
            printf("Correct!\n");
            ctr++;
        } else {
            printf("Wrong! The correct answer is %.2f.\n", a / b);
        }
    }
    return ctr;
}
void calculate(){
    for (int i = 0; i <= last; i++) // sums up the scores of each operation
        score[i] = ascore[i] + sscore[i] + mscore[i] + dscore[i];
}
int playmenu(){
    int op;
    system("cls");
    printf("      Game Menu\n\n");
    printf("1. Play Addition\n");
    printf("2. Play Subtraction\n");
    printf("3. Play Multiplication\n");
    printf("4. Play Division\n");
    printf("5. Back to Main Menu\n");
    printf("\nSelect an option(1-5): ");
    scanf("%d", &op);
    return op; // returns the value of op
}
int playcase(){ // switch case for the play menu and for score organization
    system("cls");
    int n = 5, as, ss, ms, ds;
    switch(playmenu()){
        case 1:
            system("cls");
            as = addition(n);
            ascore[currentuser] += as;
            printf("You got %d out of %d.\n", as, n);
            calculate();
            system("pause");
            break;
        case 2:
            system("cls");
            ss = subtraction(n);
            sscore[currentuser] += ss;
            printf("You got %d out of %d.\n", ss, n);
            calculate();
            system("pause");
            break;
        case 3:
            system("cls");
            ms = multiplication(n);
            mscore[currentuser] += ms;
            printf("You got %d ou t of %d.\n", ms, n);
            calculate();
            system("pause");
            break;
        case 4:
            system("cls");
            ds = division(n);
            dscore[currentuser] += ds;
            printf("You got %d out of %d.\n", ds, n);
            calculate();
            system("pause");
            break;
        case 5:
            system("cls");
            maincase();
            break;
        default:
            printf("Invalid input! Please try again\n");
            system("pause");
            playcase();
    }
}
int displaymenu(){
    int op;
    printf("    Display Leaderboards\n\n");
    printf("1. Overall Leaderboards\n");
    printf("2. Addition Leaderboards\n");
    printf("3. Subtraction Leaderboards\n");
    printf("4. Multiplication Leaderboards\n");
    printf("5. Division Leaderboards\n");
    printf("6. Back to Main Menu\n");
    printf("\nSelect an option (1-6): ");
    scanf("%d", &op);
    return op; // returns the value of op
}
void displayall(){
    if (isempty()){
        printf("The system is empty!\n");
        system("pause");
    } else {
        int temp_score[MAX]; // Temporary array for sorting and displaying the scores
        char temp_username[MAX][31];

        for (int i = 0; i <= last; i++){ // Copying the scores and usernames to temporary arrays
            temp_score[i]  = score[i];
            strcpy(temp_username[i], username[i]);
        }

        for (int i = 0; i <= last; i++){ // Sorting the scores in descending order
            for (int j = 0; j <= last; j++){
                if (temp_score[i] > temp_score[j]){
                    int temp = temp_score[i];
                    temp_score[i] = temp_score[j];
                    temp_score[j] = temp;

                    char tempstr[31];
                    strcpy(tempstr, temp_username[i]);
                    strcpy(temp_username[i], temp_username[j]);
                    strcpy(temp_username[j], tempstr);
                }
            }
        }

        printf("     Overall Leaderboards:\n\n"); // prints the sorted scores
        printf("RANK\tNAME\t\tSCORE\n");
        for (int i = 0; i <= last; i++)
            printf("%d.)\t%s\t\t%d\n", i + 1, temp_username[i], temp_score[i]);
        system("pause");
    }
}
void displayadd(){
    if (isempty()){
        printf("The system is empty!\n");
        system("pause");
    } else {
        int temp_ascore[MAX];
        char temp_username[MAX][31];

        for (int i = 0; i <= last; i++){
            temp_ascore[i]  = ascore[i];
            strcpy(temp_username[i], username[i]);
        }

        for (int i = 0; i <= last; i++){
            for (int j = 0; j <= last; j++){
                if (temp_ascore[i] > temp_ascore[j]){
                    int temp = temp_ascore[i];
                    temp_ascore[i] = temp_ascore[j];
                    temp_ascore[j] = temp;

                    char tempstr[31];
                    strcpy(tempstr, temp_username[i]);
                    strcpy(temp_username[i], temp_username[j]);
                    strcpy(temp_username[j], tempstr);
                }
            }
        }

        printf("     Addition Leaderboards:\n\n");
        printf("RANK\tNAME\t\tSCORE\n");
        for (int i = 0; i <= last; i++)
            printf("%d.)\t%s\t\t%d\n", i + 1, temp_username[i], temp_ascore[i]);
        system("pause");
    }
}
void displaysub(){
    if (isempty()){
        printf("The system is empty!\n");
        system("pause");
    } else {
        int temp_sscore[MAX];
        char temp_username[MAX][31];

        for (int i = 0; i <= last; i++) {
            temp_sscore[i]  = sscore[i];
            strcpy(temp_username[i], username[i]);
        }

        for (int i = 0; i <= last; i++){
            for (int j = 0; j <= last; j++){
                if (temp_sscore[i] > temp_sscore[j]){
                    int temp = temp_sscore[i];
                    temp_sscore[i] = temp_sscore[j];
                    temp_sscore[j] = temp;

                    char tempstr[31];
                    strcpy(tempstr, temp_username[i]);
                    strcpy(temp_username[i], temp_username[j]);
                    strcpy(temp_username[j], tempstr);
                }
            }
        }

        printf("     Subtraction Leaderboards:\n\n");
        printf("RANK\tNAME\t\tSCORE\n");
        for (int i = 0; i <= last; i++)
            printf("%d.)\t%s\t\t%d\n", i + 1, temp_username[i], temp_sscore[i]);
        system("pause");
    }
}
void displaymulti(){
    if (isempty()){
        printf("The system is empty!\n");
        system("pause");
    } else {
        int temp_mscore[MAX];
        char temp_username[MAX][31];

        for (int i = 0; i <= last; i++){
            temp_mscore[i]  = mscore[i];
            strcpy(temp_username[i], username[i]);
        }

        for (int i = 0; i <= last; i++){
            for (int j = 0; j <= last; j++){
                if (temp_mscore[i] > temp_mscore[j]){
                    int temp = temp_mscore[i];
                    temp_mscore[i] = temp_mscore[j];
                    temp_mscore[j] = temp;

                    char tempstr[31];
                    strcpy(tempstr, temp_username[i]);
                    strcpy(temp_username[i], temp_username[j]);
                    strcpy(temp_username[j], tempstr);
                }
            }
        }

        printf("     Multiplication Leaderboards:\n\n");
        printf("RANK\tNAME\t\tSCORE\n");
        for (int i = 0; i <= last; i++)
            printf("%d.)\t%s\t\t%d\n", i + 1, temp_username[i], temp_mscore[i]);
        system("pause");
    }
}
void displaydiv(){
    if (isempty()){
        printf("The system is empty!\n");
        system("pause");
    } else {
        int temp_dscore[MAX];
        char temp_username[MAX][31];

        for (int i = 0; i <= last; i++){
            temp_dscore[i]  = dscore[i];
            strcpy(temp_username[i], username[i]);
        }

        for (int i = 0; i <= last; i++){
            for (int j = 0; j <= last; j++){
                if (temp_dscore[i] > temp_dscore[j]){
                    int temp = temp_dscore[i];
                    temp_dscore[i] = temp_dscore[j];
                    temp_dscore[j] = temp;

                    char tempstr[31];
                    strcpy(tempstr, temp_username[i]);
                    strcpy(temp_username[i], temp_username[j]);
                    strcpy(temp_username[j], tempstr);
                }
            }
        }

        printf("     Division Leaderboards:\n\n");
        printf("RANK\tNAME\t\tSCORE\n");
        for (int i = 0; i <= last; i++)
            printf("%d.)\t%s\t\t%d\n", i + 1, temp_username[i], temp_dscore[i]);
        system("pause");
    }
}
int displaycase(){
    while (1){
        system("cls");
        switch (displaymenu()){
            case 1:
                system("cls");
                displayall();
                break;
            case 2:
                system("cls");
                displayadd();
                break;
            case 3:
                system("cls");
                displaysub();
                break;
            case 4:
                system("cls");
                displaymulti();
                break;
            case 5:
                system("cls");
                displaydiv();
                break;
            case 6:
                system("cls");
                maincase();
                break;
            default:
                printf("Invalid output! Please try again\n");
                system("pause");
                displaycase();
        }
    }
}
int mainmenu(){
    int op;
    printf("   Welcome to the Game!\n\n");
    printf("       Main Menu\n\n");
    printf("1. Play a game\n");
    printf("2. Display Leaderboards\n");
    printf("3. Save and Exit\n");
    printf("\nSelect an option (1-3): ");
    scanf("%d", &op);
    return op;
}
int maincase(){
    while (1){
        system("cls");
        switch(mainmenu()){
            case 1:
                system("cls");
                playcase();
                break;
            case 2:
                system("cls");
                displaycase();
                break;
            case 3:
                system("cls");
                upload();
                printf("Thank you for using my program\n\n");
                exit(0);
                break;
            default:
                printf("Try again!\n");
                system("pause");
                maincase();
        }
    }
}
