/*  Written by: Rain Sidney G. Alberto
    Course & Section: Bachelor of Science in Information Technology - 1A
    Starting Date: April 7, 2025 (Time: 7:00 AM)
    End Date: April 13, 2025 (Time: 6:10 PM) */

// Header Files
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAX 50 // Constant variable

// Struct variables
struct Player{
    string Player_name;
    string Password;
    int Total_score = 0;
    int Addition_score = 0;
    int Subtraction_score = 0;
    int Multiplication_score = 0;
    int Division_score = 0;
};

// Classes
// Encapsulation, Abstraction, and Base class for the Inheritance and Polymorphism
class Game{
    private:
        Player Account[MAX];
        int Last, Current_player, Number = 5, Addition_points, Subtraction_points, Multiplication_points, Division_points;
        int Locate(string Username, string Passcode);
    public:
        void Initialization();
        bool Is_Full();
        bool Is_Empty();
        void Login(string Username, string Passcode);
        string Anti_Duplicate(string Username);
        void Signin(Player Information);
        void Save();
        void Retrieve();
        void Registration_mode();
        void Game_mode();
        void Display_mode();
        void Display_All();
        void Display_Addition();
        void Display_Subtraction();
        void Display_Multiplication();
        void Display_Division();
};

// Derived class for the inheritance of menus
class Menu: public Game{
    public:
    int Registration_menu();
    int Main_menu();
    int Game_menu();
    int Display_menu();
};

// Derived classes for the polymorphism of the game mode
class Addition: public Game{
    public:
        int Addition_Game(int Items){
            int a, b, Answer, Counter = 0;
            srand(time(NULL));
            for (int i = 1; i <= Items; i++){
                a = rand() % 10 + 1;
                b = rand() % 10 + 1;
                cout << i << ".) What is " << a << " + " << b << " = ";
                cin >> Answer;
                if (Answer == a + b){
                    cout << "Correct!\n";
                    Counter++;
                } else
                    cout << "Wrong! The correct answer is " << a + b << ".\n";
            }
            return Counter;
        }
};

class Subtraction: public Game{
    public:
        int Subtraction_Game(int Items){
            int a, b, Answer, Counter = 0;
            srand(time(NULL));
            for (int i = 1; i <= Items; i++){
                a = rand() % 10 + 1;
                b = rand() % 10 + 1;
                cout << i << ".) What is " << a << " - " << b << " = ";
                cin >> Answer;
                if (Answer == a - b){
                    cout << "Correct!\n";
                    Counter++;
                } else
                    cout << "Wrong! The correct answer is " << a - b << ".\n";
            }
            return Counter;
        }
};

class Multiplication: public Game{
    public:
        int Multiplication_Game(int Items){
            int a, b, Answer, Counter = 0;
            srand(time(NULL));
            for (int i = 1; i <= Items; i++){
                a = rand() % 10 + 1;
                b = rand() % 10 + 1;
                cout << i << ".) What is " << a << " * " << b << " = ";
                cin >> Answer;
                if (Answer == a * b){
                    cout << "Correct!\n";
                    Counter++;
                } else
                    cout << "Wrong! The correct answer is " << a * b << ".\n";
            }
            return Counter;
        }
};

class Division: public Game{
    public:
        int Division_Game(int Items){
            float a, b, Answer;
            int Counter = 0;
            srand(time(NULL));
            for (int i = 1; i <= Items; i++){
                a = rand() % 10 + 1;
                b = rand() % 10 + 1;
                cout << i << ".) What is " << a << " / " << b << " = ";
                cin >> Answer;
                if (Answer == a / b){
                    cout << "Correct!\n";
                    Counter++;
                } else
                    cout << "Wrong! The correct answer is " << a / b << ".\n";
            }
            return Counter;
        }
};

// Main Function
int main(){
    Game Manager;
    Menu Menus;
    Manager.Initialization();
    Manager.Retrieve();
    Manager.Registration_mode();
    while (true){
        switch(Menus.Main_menu()){
            case 1:
                system("cls");
                Manager.Game_mode();
                break;
            case 2:
                system("cls");
                Manager.Display_mode();
                break;
            case 3:
                system("cls");
                Manager.Save();
                cout << "Saving your progress...\n";
                cout << "Exiting the program...\n";
                cout << "Thank you for using the program!\n";
                exit (0);
            default:
                cout << "Invalid input! Please try again.\n";
                system("pause");
                break;
        }
    }
    return 0;
}

// Function Definitions
int Game::Locate(string Username, string Passcode){
    for (int i = 0; i <= Last; i++)
        if (Username == Account[i].Player_name && Passcode == Account[i].Password)
            return i;
    return -1;
}
void Game::Initialization(){
    Last = -1;
}
bool Game::Is_Full(){
    return (Last == MAX - 1);
}
bool Game::Is_Empty(){
    return (Last == -1);
}
void Game::Login(string Username, string Passcode){
    system("cls");
    int Position = Locate(Username, Passcode);
    if (Position < 0){
        cout << "Record of " << Username << " not found.\n";
        system("pause");
        Registration_mode();
    } else {
        cout << "Login Successful!\n";
        cout << "Welcome back " << Username << "!\n";
        Current_player = Position;
        Display_All();
    }
}
string Game::Anti_Duplicate(string Username){
    bool Duplicate;
    do {
        Duplicate = false;
        for (int i = 0; i <= Last; i++){
            if (Username == Account[i].Player_name){
                cout << "Username already exists! Please try again.\n";
                cout << "Enter a new username: ";
                getline(cin, Username);
                Duplicate = true;
                break;
            }
        }
    } while (Duplicate);
    return Username;
}
void Game::Signin(Player Information){
    system("cls");
    Last++;
    Account[Last] = Information;
    Current_player = Last;
    cout << "Account Successfully Created!\n";
    cout << "Welcome " << Account[Last].Player_name << "!\n";
    system("pause");
}
void Game::Save(){
    ofstream fp("accounts.txt");
    if (!fp){
        system("cls");
        cout << "File Error\\Error 404\n";
        system("pause");
    } else {
        for (int i = 0; i <= Last; i++){
            fp << Account[i].Player_name << endl << Account [i].Password << endl
                << Account[i].Total_score << " " << Account[i].Addition_score << " "
                << Account[i].Subtraction_score << " " << Account[i].Multiplication_score << " "
                << Account[i].Division_score << endl;
        }
    }
    fp.close();
}
void Game::Retrieve(){
    ifstream fp("accounts.txt");
    if (!fp){
        system("cls");
        cout << "File Error\\Error 404\n";
        system("pause");
    } else {
        Player sr;
        while(getline(fp, sr.Player_name) && getline(fp, sr.Password) && 
        fp >> sr.Total_score >> sr.Addition_score >> sr.Subtraction_score
        >> sr.Multiplication_score >> sr.Division_score){
            fp.ignore();
            Last++;
            Account[Last] = sr;
            Current_player = Last;
        }
    }
}
int Menu::Registration_menu(){
    int options;
    system("cls");
    cout << "Register an Account!\n";
    cout << "1. Log in your account.\n";
    cout << "2. Sign in an account.\n";
    cout << "3. Save and Exit\n";
    cout << "Select an option (1-3): ";
    cin >> options;
    return options;
}
int Menu::Main_menu(){
    int options;
    system("cls");
    cout << "Welcome to the Arithmetic Game!\n";
    cout << "Main Menu\n";
    cout << "1. Play the Game\n";
    cout << "2. Leaderboards\n";
    cout << "3. Save and Exit\n";
    cout << "Select an option (1-3): ";
    cin >> options;
    return options;
}
int Menu::Game_menu(){
    int options;
    system("cls");
    cout << "Game Menu\n";
    cout << "1. Play Addition\n";
    cout << "2. Play Subtraction\n";
    cout << "3. Play Multiplication\n";
    cout << "4. Play Division\n";
    cout << "5. Back to Main Menu\n";
    cout << "Select an option (1 - 5): ";
    cin >> options;
    return options;
}
int Menu::Display_menu(){
    int options;
    cout << "Display Menu\n";
    cout << "1. Overall Leaderboards\n";
    cout << "2. Addition Leaderboards\n";
    cout << "3. Subtraction Leaderboards\n";
    cout << "4. Multiplication Leaderboards\n";
    cout << "5. Division Leaderboards\n";
    cout << "6. Back to Main Menu\n";
    cout << "Select an option (1 - 6): ";
    cin >> options;
    return options;
}
void Game::Registration_mode(){
    Menu Menus;
    Player Data;
    bool Flag = false;
    do {
        switch (Menus.Registration_menu()){
            case 1:
                if (Is_Empty()){
                    cout << "The system is empty!\n";
                    system("pause");
                } else {
                    system("cls");
                    cout << "Log in your account.\n";
                    cin.ignore();
                    cout << "Enter your username: ";
                    getline(cin, Data.Player_name);
                    cout << "Enter your password: ";
                    getline(cin, Data.Password);
                    Login(Data.Player_name, Data.Password);
                    Flag = true;
                }
                break;
            case 2:
                if (Is_Full()){
                    cout << "The system is full!\n";
                    system("pause");
                } else {
                    system("cls");
                    cout << "Sign in an account.\n";
                    cin.ignore();
                    cout << "Enter a username: ";
                    getline(cin, Data.Player_name);
                    Data.Player_name = Anti_Duplicate(Data.Player_name);
                    cout << "Enter a password: ";
                    getline(cin, Data.Password);
                    Signin(Data);
                    Flag = true;
                }
                break;
            case 3:
                system("cls");
                cout << "Exiting the program...\n";
                cout << "Thank you for using the program!\n";
                exit(0);
            default:
                cout << "Invalid input! Please try again.\n";
                system("pause");
                break;
        }
    } while (!Flag);
}
void Game::Game_mode(){
    Addition Game1;
    Subtraction Game2;
    Multiplication Game3;
    Division Game4;
    Menu Menus;
    while (true){
        switch(Menus.Game_menu()){
            case 1:
                system("cls");
                Addition_points = Game1.Addition_Game(Number);
                Account[Current_player].Addition_score += Addition_points;
                Account[Current_player].Total_score += Addition_points;
                cout << "You got " << Addition_points << " out of " << Number << ".\n";
                system("pause");
                break;
            case 2:
                system("cls");
                Subtraction_points = Game2.Subtraction_Game(Number);
                Account[Current_player].Subtraction_score += Subtraction_points;
                Account[Current_player].Total_score += Subtraction_points;
                cout << "You got " << Subtraction_points << " out of " << Number << ".\n";
                system("pause");
                break;
            case 3:
                system("cls");
                Multiplication_points = Game3.Multiplication_Game(Number);
                Account[Current_player].Multiplication_score += Multiplication_points;
                Account[Current_player].Total_score += Multiplication_points;
                cout << "You got " << Multiplication_points << " out of " << Number << ".\n";
                system("pause");
                break;
            case 4:
                system("cls");
                Division_points = Game4.Division_Game(Number);
                Account[Current_player].Division_score += Division_points;
                Account[Current_player].Total_score += Division_points;
                cout << "You got " << Division_points << " out of " << Number << ".\n";
                system("pause");
                break;
            case 5:
                return;
            default:
                cout << "Invalid input! Please try again.\n";
                system("pause");
                break;
        }
    }
}
void Game::Display_mode(){
    Menu Menus;
    while (true){
        switch(Menus.Display_menu()){
            case 1:
                system("cls");
                Display_All();
                break;
            case 2:
                system("cls");
                Display_Addition();
                break;
            case 3:
                system("cls");
                Display_Subtraction();
                break;
            case 4:
                system("cls");
                Display_Multiplication();
                break;
            case 5:
                system("cls");
                Display_Division();
                break;
            case 6:
                return;
            default:
                cout << "Invalid input! Please try again.\n";
                system("pause");
                break;
        }
    }
}
void Game::Display_All(){
    int Temp_score[MAX];
    string Temp_name[MAX];

    for (int i = 0; i <= Last; i++){
        Temp_score[i] = Account[i].Total_score;
        Temp_name[i] = Account[i].Player_name;
    }

    for (int i = 0; i <= Last; i++){
        for (int j = 0; j <= Last; j++){
            if (Temp_score[i] > Temp_score[j]){
                int temp = Temp_score[i];
                Temp_score[i] = Temp_score[j];
                Temp_score[j] = temp;

                string tempstr = Temp_name[i];
                Temp_name[i] = Temp_name[j];
                Temp_name[j] = tempstr;
            }
        }
    }
    cout << "Overall Leaderboards\n";
    cout << "Rank\tName\t\tScore\n";
    for (int i = 0; i <= Last; i++)
        cout << i + 1 << ".)\t" << Temp_name[i] << "\t\t" << Temp_score[i] << endl;
    system("pause");
}
void Game::Display_Addition(){
    int Temp_score[MAX];
    string Temp_name[MAX];

    for (int i = 0; i <= Last; i++){
        Temp_score[i] = Account[i].Addition_score;
        Temp_name[i] = Account[i].Player_name;
    }

    for (int i = 0; i <= Last; i++){
        for (int j = 0; j <= Last; j++){
            if (Temp_score[i] > Temp_score[j]){
                int temp = Temp_score[i];
                Temp_score[i] = Temp_score[j];
                Temp_score[j] = temp;

                string tempstr = Temp_name[i];
                Temp_name[i] = Temp_name[j];
                Temp_name[j] = tempstr;
            }
        }
    }
    cout << "Addition Leaderboards\n";
    cout << "Rank\tName\t\tScore\n";
    for (int i = 0; i <= Last; i++)
        cout << i + 1 << ".)\t" << Temp_name[i] << "\t\t" << Temp_score[i] << endl;
    system("pause");
}
void Game::Display_Subtraction(){
    int Temp_score[MAX];
    string Temp_name[MAX];

    for (int i = 0; i <= Last; i++){
        Temp_score[i] = Account[i].Subtraction_score;
        Temp_name[i] = Account[i].Player_name;
    }

    for(int i = 0; i <= Last; i++){
        for (int j = 0; j <= Last; j++){
            if (Temp_score[i] > Temp_score[j]){
                int temp = Temp_score[i];
                Temp_score[i] = Temp_score[j];
                Temp_score[j] = temp;

                string tempstr = Temp_name[i];
                Temp_name[i] = Temp_name[j];
                Temp_name[j] = tempstr;
            }
        }
    }

    cout << "Subtraction Leaderboards\n";
    cout << "Rank\tName\t\tScore\n";
    for (int i = 0; i <= Last; i++)
        cout << i + 1 << ".)\t" << Temp_name[i] << "\t\t" << Temp_score[i] << endl;
    system("pause");
}
void Game::Display_Multiplication(){
    int Temp_score[MAX];
    string Temp_name[MAX];

    for (int i = 0; i <= Last; i++){
        Temp_score[i] = Account[i].Multiplication_score;
        Temp_name[i] = Account[i].Player_name;
    }

    for (int i = 0; i <= Last; i++){
        for (int j = 0; j <= Last; j++){
            if (Temp_score[i] > Temp_score[j]){
                int temp = Temp_score[i];
                Temp_score[i] = Temp_score[j];
                Temp_score[j] = temp;

                string tempstr = Temp_name[i];
                Temp_name[i] = Temp_name[j];
                Temp_name[j] = tempstr;
            }
        }
    }

    cout << "Multiplication Leaderboards\n";
    cout << "Rank\tName\t\tScore\n";
    for (int i = 0; i <= Last; i++)
        cout << i + 1 << ".)\t" << Temp_name[i] << "\t\t" << Temp_score[i] << endl;
    system("pause");
}
void Game::Display_Division(){
    int Temp_score[MAX];
    string Temp_name[MAX];

    for (int i = 0; i <= Last; i++){
        Temp_score[i] = Account[i].Division_score;
        Temp_name[i] = Account[i].Player_name;
    }

    for (int i = 0; i <= Last; i++){
        for (int j = 0; j <= Last; j++){
            if (Temp_score[i] > Temp_score[j]){
                int temp = Temp_score[i];
                Temp_score[i] = Temp_score[j];
                Temp_score[j] = temp;

                string tempstr = Temp_name[i];
                Temp_name[i] = Temp_name[j];
                Temp_name[j] = tempstr;
            }
        }
    }

    cout << "Division Leaderboards\n";
    cout << "Rank\tName\t\tScore\n";
    for (int i = 0; i <= Last; i++)
        cout << i + 1 << ".)\t" << Temp_name[i] << "\t\t" << Temp_score[i] << endl;
    system("pause");
}