/*
    MANALILI, SEAN DAIKI M.
    BSIT - 1A
    ARITHMETIC GAME IN OOP
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

#define MAX 10
#define MAX_QUESTIONS 5

struct Player {
    string name;
    string password;
    int Overall_Score = 0;
    int Addition_Score = 0;
    int Subtraction_Score = 0;
    int Multiplication_Score = 0;
    int Division_Score = 0;
};

class PlayerManager {
private:
    Player players[MAX];
    int last;

public:
    PlayerManager() : last(-1) {}

    bool IsEmpty() const {
        return last == -1;
    }

    int GetPlayerCount() const {
        return last + 1;
    }

    int AddPlayer(const string& name, const string& password) {
        if (last + 1 >= MAX) return -1;
        last++;
        players[last].name = name;
        players[last].password = password;
        return last;
    }

    int FindPlayer(const string& name) const {
        for (int i = 0; i <= last; i++) {
            if (players[i].name == name) return i;
        }
        return -1;
    }

    Player* GetPlayer(int index) {
        if (index < 0 || index > last) return nullptr;
        return &players[index];
    }

    Player* GetLastPlayer() {
        if (last < 0) return nullptr;
        return &players[last];
    }
};

class Leaderboard {
public:
    void DisplayLeaderboard(Player players[], int count, const string& title, function<int(const Player&)> scoreGetter) {
        system("cls");

        if (count == 0) {
            cout << "No players to display in the leaderboard." << endl;
            system("pause");
            return;
        }

        sort(players, players + count, [&](Player a, Player b) {
            return scoreGetter(a) > scoreGetter(b);
        });

        cout << title << " Leaderboard" << endl;
        cout << "----------------------------------------" << endl;
        cout << left << setw(10) << "Rank"
             << setw(15) << "Name"
             << setw(15) << "Score" << endl;

        for (int i = 0; i < count; i++) {
            cout << left << setw(10) << (i + 1)
                 << setw(15) << players[i].name
                 << setw(15) << scoreGetter(players[i]) << endl;
        }

        cout << "----------------------------------------" << endl;
        system("pause");
    }
};

//Inheritance
class Game {
protected:
    Player* currentPlayer;
    int maxQuestions;

public:
    Game(Player* player, int maxQuestions = MAX_QUESTIONS) : currentPlayer(player), maxQuestions(maxQuestions) {}
    virtual void play() = 0;
};

class AdditionGame : public Game {
public:
    AdditionGame(Player* player) : Game(player) {}

    void play() override {
        system("cls");
        int a, b, answer, score = 0;
        srand(time(0));
        for (int i = 0; i < maxQuestions; i++) {
            a = rand() % 100 + 1;
            b = rand() % 100 + 1;
            cout << "Question " << (i + 1) << ": " << a << " + " << b << " = ? ";
            cin >> answer;
            if (answer == (a + b)) {
                cout << "Correct!" << endl;
                score++;
            } else {
                cout << "Wrong! The correct answer is " << (a + b) << endl;
            }
        }
        currentPlayer->Addition_Score += score;
        currentPlayer->Overall_Score += score;
        cout << "Your score: " << score << "/" << maxQuestions << endl;
        system("pause");
    }
};

class SubtractionGame : public Game {
    public:
        SubtractionGame(Player* player) : Game(player) {}
    
        void play() override {
            system("cls");
            int a, b, answer, score = 0;
            srand(time(0));
            for (int i = 0; i < maxQuestions; i++) {
                a = rand() % 100 + 1;
                b = rand() % 100 + 1;
                cout << "Question " << (i + 1) << ": " << a << " - " << b << " = ? ";
                cin >> answer;
                if (answer == (a - b)) {
                    cout << "Correct!" << endl;
                    score++;
                } else {
                    cout << "Wrong! The correct answer is " << (a - b) << endl;
                }
            }
            currentPlayer->Subtraction_Score += score;
            currentPlayer->Overall_Score += score;
            cout << "Your score: " << score << "/" << maxQuestions << endl;
            system("pause");
        }
};

class MultiplicationGame : public Game {
    public:
        MultiplicationGame(Player* player) : Game(player) {}
    
        void play() override {
            system("cls");
            int a, b, answer, score = 0;
            srand(time(0)); 
            for (int i = 0; i < maxQuestions; i++) {
                a = rand() % 100 + 1;
                b = rand() % 100 + 1;
                cout << "Question " << (i + 1) << ": " << a << " x " << b << " = ? ";
                cin >> answer;
                if (answer == (a * b)) {
                    cout << "Correct!" << endl;
                    score++;
                } else {
                    cout << "Wrong! The correct answer is " << (a * b) << endl;
                }
            }
            currentPlayer->Multiplication_Score += score;
            currentPlayer->Overall_Score += score;
            cout << "Your score: " << score << "/" << maxQuestions << endl;
            system("pause");
        }
};

class DivisionGame : public Game {
    public:
        DivisionGame(Player* player) : Game(player) {}
    
        void play() override {
            system("cls");
            float a, b, answer;
            int score = 0;
            srand(time(0)); 
            for (int i = 0; i < maxQuestions; i++) {
                a = rand() % 100 + 1;
                b = rand() % 10 + 1;
                cout << "Question " << (i + 1) << ": " << a << " / " << b << " = ? ";
                cin >> answer;
                if (answer == (a / b)) {
                    cout << "Correct!" << endl;
                    score++;
                } else {
                    cout << "Wrong! The correct answer is " << (a / b) << endl;
                }
            }
            currentPlayer->Division_Score += score;
            currentPlayer->Overall_Score += score;
            cout << "Your score: " << score << "/" << maxQuestions << endl;
            system("pause");
        }
};

class GameController {
private:
    PlayerManager playerManager;
    Leaderboard leaderboard;
    int currentPlayerIndex = -1;

public:
    void Initialize() {
        playerManager = PlayerManager();
    }

    void SaveData() {
        ofstream file("Arithmetic_Data.txt");
        if (!file) {
            cout << "Unable to open file" << endl;
            return;
        }

        for (int i = 0; i < playerManager.GetPlayerCount(); i++) {
            Player* p = playerManager.GetPlayer(i);
            if (p) {
                file << p->name << endl
                     << p->password << endl
                     << p->Overall_Score << endl
                     << p->Addition_Score << endl
                     << p->Subtraction_Score << endl
                     << p->Multiplication_Score << endl
                     << p->Division_Score << endl;
            }
        }
        file.close();
        cout << "Data saved successfully!" << endl;
    }

    void LoadData() {
        ifstream file("Arithmetic_Data.txt");
        if (!file) {
            cout << "Unable to open file" << endl;
            return;
        }

        string name, password;
        int overallScore, additionScore, subtractionScore, multiplicationScore, divisionScore;

        while (getline(file, name)) {
            getline(file, password);
            file >> overallScore >> additionScore >> subtractionScore >> multiplicationScore >> divisionScore;
            file.ignore();

            int index = playerManager.AddPlayer(name, password);
            Player* p = playerManager.GetPlayer(index);
            if (p) {
                p->Overall_Score = overallScore;
                p->Addition_Score = additionScore;
                p->Subtraction_Score = subtractionScore;
                p->Multiplication_Score = multiplicationScore;
                p->Division_Score = divisionScore;
            }
        }
        file.close();
        cout << "Data loaded successfully!" << endl;
    }

    void LogInMenu() {
        system("cls");
        cout << "Welcome to the Arithmetic Game!" << endl;
        cout << "1. Log In" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            LogIn();
            break;
        case 2:
            SignUp();
            break;
        case 3:
            SaveData();
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
            LogInMenu();
        }
    }

    void LogIn() {
        system("cls");
        string name, password;
        cout << "Log In" << endl;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your password: ";
        getline(cin, password);

        int index = playerManager.FindPlayer(name);
        if (index == -1) {
            cout << "Player not found. Please sign up." << endl;
            system("pause");
            LogInMenu();
        } else {
            Player* p = playerManager.GetPlayer(index);
            if (p->password == password) {
                currentPlayerIndex = index;
                cout << "Welcome back, " << p->name << "!" << endl;
                system("pause");
                leaderboard.DisplayLeaderboard(playerManager.GetPlayer(0), playerManager.GetPlayerCount(), "Overall", [](const Player& p) { return p.Overall_Score; });
                MainMenu();
            } else {
                cout << "Incorrect password. Please try again." << endl;
                system("pause");
                LogInMenu();
            }
        }
    }

    void SignUp() {
        system("cls");
        string name, password;
        cout << "Sign Up" << endl;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your password: ";
        getline(cin, password);

        if (playerManager.FindPlayer(name) != -1) {
            cout << "Player already exists. Please log in." << endl;
            system("pause");
            LogInMenu();
        } else {
            if (playerManager.AddPlayer(name, password) == -1) {
                cout << "Unable to add player. Maximum players reached." << endl;
            } else {
                cout << "Sign up successful! Welcome, " << name << "!" << endl;
            }
            system("pause");
            LogInMenu();
        }
    }

    void MainMenu() {
        system("cls");
        cout << "Main Menu" << endl;
        cout << "1. Play" << endl;
        cout << "2. Leaderboard" << endl;
        cout << "3. Log Out" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            PlayMenu();
            break;
        case 2:
            LeaderboardMenu();
            break;
        case 3:
            LogInMenu();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            MainMenu();
        }
    }

    void PlayMenu() {
        system("cls");
        cout << "Play Menu" << endl;
        cout << "1. Addition" << endl;
        cout << "2. Subtraction" << endl;
        cout << "3. Multiplication" << endl;
        cout << "4. Division" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        Game* game = nullptr;
        Player* currentPlayer = playerManager.GetPlayer(currentPlayerIndex);

        switch (choice) {
        case 1:
            game = new AdditionGame(currentPlayer);
            break;
        case 2:
            game = new SubtractionGame(currentPlayer);
            break;
        case 3:
            game = new MultiplicationGame(currentPlayer);
            break;
        case 4:
            game = new DivisionGame(currentPlayer);
            break;
        case 5:
            MainMenu();
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            PlayMenu();
            return;
        }

        if (game) {
            game->play();
            delete game;
        }

        PlayMenu();
    }

    void LeaderboardMenu() {
        while (true) {
            system("cls");
            cout << "Leaderboard Menu" << endl;
            cout << "1. Overall Leaderboard" << endl;
            cout << "2. Addition Leaderboard" << endl;
            cout << "3. Subtraction Leaderboard" << endl;
            cout << "4. Multiplication Leaderboard" << endl;
            cout << "5. Division Leaderboard" << endl;
            cout << "6. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                leaderboard.DisplayLeaderboard(playerManager.GetPlayer(0), playerManager.GetPlayerCount(), "Overall", [](const Player& p) { return p.Overall_Score; });
                break;
            case 2:
                leaderboard.DisplayLeaderboard(playerManager.GetPlayer(0), playerManager.GetPlayerCount(), "Addition", [](const Player& p) { return p.Addition_Score; });
                break;
            case 3:
                leaderboard.DisplayLeaderboard(playerManager.GetPlayer(0), playerManager.GetPlayerCount(), "Subtraction", [](const Player& p) { return p.Subtraction_Score; });
                break;
            case 4:
                leaderboard.DisplayLeaderboard(playerManager.GetPlayer(0), playerManager.GetPlayerCount(), "Multiplication", [](const Player& p) { return p.Multiplication_Score; });
                break;
            case 5:
                leaderboard.DisplayLeaderboard(playerManager.GetPlayer(0), playerManager.GetPlayerCount(), "Division", [](const Player& p) { return p.Division_Score; });
                break;
            case 6:
                MainMenu();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                LeaderboardMenu();
            }
        }
    }
};

int main() {
    GameController gameController;
    gameController.Initialize();
    gameController.LoadData();
    gameController.LogInMenu();
    return 0;
}