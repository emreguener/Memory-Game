#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>
#include <windows.h>
using namespace std;

void Save_Game(int** board, bool** revealed, int row, int col, int moves);
void sleep(int milliseconds);
void intro();
void menu();
void InitializeBoard(int row, int col);
void AllCardsOpen(int row, int col); // oyuncunun konumlarý ve sayýlarý ezberlemesi için 
void PrintBoard(int row, int col);
bool IsGameOver(int row, int col);
void ClearScreen();
void WaitTime(int number);
void gotoxy(int x, int y); // Windows konsolunda sað üst köþeye metin yazdýran fonksiyon

int** board;
bool** revealed;

void sleep(int milliseconds) {
    Sleep(milliseconds);
}

void intro()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    cout << "Loading the Game..." << endl;
    sleep(1000);

    ClearScreen();
    cout << "*******************************************" << endl;
    sleep(500);
    cout << "*                                         *" << endl;
    sleep(500);
    cout << "*               WELCOME!                  *" << endl;
    sleep(500);
    cout << "*                                         *" << endl;
    sleep(500);
    cout << "*       *************************         *" << endl;
    sleep(500);
    cout << "*       *                       *         *" << endl;
    sleep(500);
    cout << "*       *      MEMORY GAME      *         *" << endl;
    sleep(500);
    cout << "*       *                       *         *" << endl;
    sleep(500);
    cout << "*       *************************         *" << endl;
    sleep(500);
    cout << "*                                         *" << endl;
    sleep(500);
    cout << "*       Developed by: Emre GUNER          *" << endl;
    sleep(500);
    cout << "*                                         *" << endl;
    sleep(500);
    cout << "*******************************************" << endl;
    sleep(2000);

    ClearScreen();
    cout << "Loading";
    for (int i = 0; i < 3; ++i) {
        sleep(500);
        cout << ".";
        cout.flush();
    }
    sleep(500);
    ClearScreen();

    cout << "Game Starting!" << endl;
    sleep(1500);
}


void Save_Game(int** board, bool** revealed, int row, int col, int moves) 
{
    ofstream save1("board.txt"); // tüm oyun alanýndaki sayýlar ve konumlarý
    ofstream save2("revealed.txt"); // sadece açýlan sayýlar ve konumlarý
    ofstream save3("row.txt"); // oyun alaný satýr ve sütun sayýsý
    ofstream save4("col.txt"); // sütun sayýsý
    ofstream save5("move.txt"); // hamle sayýsý
    if (!save1.is_open() || !save2.is_open() || !save3.is_open() ||!save4.is_open() || !save5.is_open())
    {
        cout << "File could not be created.";
    }
    else
    {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                save1 << board[i][j] << " ";
                save2 << revealed[i][j] << " ";
            }
            save1 << endl;
            save2 << endl;
        }
        save3 << row;
        save4 << col;
        save5 << moves;
    }
    save1.close(); // dosyayý kapatýyoruz.
    save2.close();
    save3.close();
    save4.close();
    cout << "The game save has been successfully saved!" << endl;
}

void menu()
{
    ClearScreen();
jump4:
    srand(time(NULL)); // Rastgelelik için tohumu ayarla
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "*******************************" << endl;
    cout << "*                             *" << endl;
    cout << "*         GAME MENU           *" << endl;
    cout << "*                             *" << endl;
    cout << "*******************************" << endl;
    cout << endl;
    cout << "1. Press 1 to Start New Game" << endl;
    cout << "2. Press 2 to Continue Saved Game" << endl;
    cout << "3. Press 3 to Rules" << endl;
    cout << "4. Press 4 to Quit" << endl;
    cout << endl;
jump3:
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
    {
        cout << "Please make a valid choice." << endl;
        WaitTime(1);
        goto jump3;
    }
    int moves = 0;
    ifstream inputFile1("board.txt");
    ifstream inputFile2("revealed.txt");
    ifstream inputFile3("row.txt");
    ifstream inputFile4("col.txt");
    ifstream inputFile5("move.txt");
    switch (choice)
    {
    case 1:
        ClearScreen();
        cout << "Starting a new game..." << endl;
        WaitTime(1);
        cout << "If you press the Shift key and enter your move during the game, the game will be saved." << endl;
        WaitTime(2);

        int row, col;

    jump:
        cout << "Please enter the number of rows in the game area: ";
        cin >> row;
        cout << "Please enter the number of columns in the game area: ";
        cin >> col;

        if (row * col % 2 != 0)
        {
            cout << "The game area should have an even number of rows and columns." << endl;
            cout << "Please enter the number of rows and columns for the game area again." << endl;
            WaitTime(3);
            goto jump;
        }

        InitializeBoard(row, col); // Oyun alanýnýn oluþturulmasý
        AllCardsOpen(row, col); // oyun alanýný 5 saniye göster
        WaitTime(5);

        int firstCardRow, firstCardCol, secondCardRow, secondCardCol;
        

        while (!IsGameOver(row, col))
        {
            gotoxy(70, 0);
            
            ClearScreen();
            PrintBoard(row, col);
            cout << "Number of moves: " << moves << endl << endl;
            WaitTime(1);
            int area = row * col;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            cout << "Please enter the position of the first card (row column): ";
            cin >> firstCardRow >> firstCardCol;
            if (GetAsyncKeyState(VK_SHIFT)) { // oyun esnasýnda oyunu kaydetmek için. SHIFT TUÞU ÝLE
                Save_Game(board, revealed, row, col, moves);
                ClearScreen();
                cout << "Your game has been successfully saved!" << endl;
                WaitTime(2);
                menu();
            }
            if (GetAsyncKeyState(VK_ESCAPE)) { // oyun esnasýnda doðrudan çýkýþ için. ESC ÝLE.
                ClearScreen();
                exit(0);
            }
            // Girilen konum geçerli deðilse veya kart zaten açýldýysa tekrar iste
            if (firstCardRow <= 0 || firstCardRow > row || firstCardCol <= 0 || firstCardCol > col || revealed[firstCardRow - 1][firstCardCol - 1])
            {
                cout << "Please make a valid move." << endl;
                WaitTime(1);
                continue;
            }
            ClearScreen();
            revealed[firstCardRow-1][firstCardCol-1] = true;
            PrintBoard(row, col);
            
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            cout << "\n\nPlease enter the position of the second card (row column): ";
            cin >> secondCardRow >> secondCardCol;
            moves++;
            // Girilen konum geçerli olsa veya kart zaten açýldýysa tekrar iste
            if (secondCardRow <= 0 || secondCardRow > row || secondCardCol <= 0 || secondCardCol > col || revealed[secondCardRow-1][secondCardCol-1])
            {
                cout << "Please make a valid move." << endl;
                WaitTime(1);
                // Ýlk kartý tekrar kapat
                revealed[firstCardRow-1][firstCardCol-1] = false;
                continue;
            }

            ClearScreen();
            revealed[secondCardRow-1][secondCardCol-1] = true;
            PrintBoard(row, col);

            // Kartlar eþleþmiþse
            if (board[firstCardRow-1][firstCardCol-1] == board[secondCardRow-1][secondCardCol-1])
            {
                cout << "Match found!" << endl;
                WaitTime(1);
            }
            else
            {
                cout << "No match found." << endl;
                WaitTime(1);
                // Kartlarý kapat
                revealed[firstCardRow-1][firstCardCol-1] = false;
                revealed[secondCardRow-1][secondCardCol-1] = false;
            }


        }

        cout << "Congratulations! You have completed the game." << endl;
        cout << "You won the game in " << moves << " moves" << endl;
        WaitTime(3);
        menu();
        // Bellekten dinamik olarak oluþturulan alanlarý temizleme
        for (int i = 0; i < row; i++)
        {
            delete[] board[i];
            delete[] revealed[i];
        }
        delete[] board;
        delete[] revealed;

        break;
    case 2:
        ClearScreen();
        cout << "Continuing the saved game..." << endl;
        WaitTime(2);

        if (!inputFile1.is_open() || !inputFile2.is_open() || !inputFile3.is_open() || !inputFile4.is_open() || !inputFile5.is_open())
        {
            cout << "File could not be opened." << endl;
        }
        else
        {
            int row, col;

            inputFile3 >> row; // Kaydedilen satýr sayýsýný oku
            inputFile4 >> col; // Kaydedilen sütun sayýsýný oku
            inputFile5 >> moves; // hamle sayýsý
            // Bellekten dinamik olarak oyun alaný ve revealed matrisini oluþtur
            board = new int* [row];
            revealed = new bool* [row];

            for (int i = 0; i < row; i++)
            {
                board[i] = new int[col];
                revealed[i] = new bool[col];

                for (int j = 0; j < col; j++)
                {
                    inputFile1 >> board[i][j]; // Kaydedilen board deðerlerini oku
                    inputFile2 >> revealed[i][j]; // Kaydedilen revealed deðerlerini oku
                }
            }

            inputFile1.close(); // Dosyalarý kapat
            inputFile2.close();
            inputFile3.close();
            inputFile4.close();
            inputFile5.close();
            cout << "Saved game successfully loaded!" << endl;
            WaitTime(2);

            // Oyunun devam ettiði noktaya gitmek için gereken deðiþiklikler
            int firstCardRow, firstCardCol, secondCardRow, secondCardCol;

            while (!IsGameOver(row, col))
            {
                ClearScreen();
                PrintBoard(row, col);
                gotoxy(70, 0);
                cout << "Number of moves: " << moves << endl << endl << endl << endl;
                WaitTime(1);
                int area = row * col;
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                cout << "Please enter the position of the first card (row column): ";
                cin >> firstCardRow >> firstCardCol;
                if (GetAsyncKeyState(VK_SHIFT)) { // oyun esnasýnda oyunu kaydetmek için. SHIFT TUÞU ÝLE
                    Save_Game(board, revealed, row, col, moves);
                    ClearScreen();
                    cout << "Your game has been successfully saved!" << endl;
                    WaitTime(2);
                    menu();
                }
                if (GetAsyncKeyState(VK_ESCAPE)) { // oyun esnasýnda doðrudan çýkýþ için. ESC ÝLE.
                    ClearScreen();
                    exit(0);
                }
                // Girilen konum geçerli deðilse veya kart zaten açýldýysa tekrar iste
                if (firstCardRow <= 0 || firstCardRow > row || firstCardCol <= 0 || firstCardCol > col || revealed[firstCardRow - 1][firstCardCol - 1])
                {
                    cout << "Please make a valid move." << endl;
                    WaitTime(1);
                    continue;
                }
                ClearScreen();
                revealed[firstCardRow-1][firstCardCol-1] = true;
                PrintBoard(row, col);
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                cout << "Please enter the position of the second card (row column): ";
                cin >> secondCardRow >> secondCardCol;
                moves++;
                // Girilen konum geçerli olsa veya kart zaten açýldýysa tekrar iste
                if (secondCardRow <= 0 || secondCardRow > row || secondCardCol <= 0 || secondCardCol > col || revealed[secondCardRow-1][secondCardCol-1])
                {
                    cout << "Please make a valid move." << endl;
                    WaitTime(1);
                    // Ýlk kartý tekrar kapat
                    revealed[firstCardRow-1][firstCardCol-1] = false;
                    continue;
                }

                ClearScreen();
                revealed[secondCardRow-1][secondCardCol-1] = true;
                PrintBoard(row, col);

                // Kartlar eþleþmiþse
                if (board[firstCardRow-1][firstCardCol-1] == board[secondCardRow-1][secondCardCol-1])
                {
                    cout << "Match found!" << endl;
                    WaitTime(1);
                }
                else
                {
                    cout << "No match found." << endl;
                    WaitTime(1);
                    // Kartlarý kapat
                    revealed[firstCardRow-1][firstCardCol-1] = false;
                    revealed[secondCardRow-1][secondCardCol-1] = false;
                }


            }

            cout << "Congratulations! You have completed the game." << endl;
            cout << "You won the game in " << moves << " moves" << endl;
            WaitTime(3);
            menu();
            // Bellekten dinamik olarak oluþturulan alanlarý temizleme
            for (int i = 0; i < row; i++)
            {
                delete[] board[i];
                delete[] revealed[i];
            }
            delete[] board;
            delete[] revealed;

            break;
    case 3:
        ClearScreen();
        cout << "Redirecting to the Rules menu..." << endl << endl;
        WaitTime(1);
        cout << "In each turn, a closed card is selected by the player and flipped to reveal its number," << endl;
        cout << "Once the game starts, you have 5 seconds to take a look at the numbers, and then they will all close." << endl;
        cout << "aiming to match cards with the same number." << endl;
        cout << "If you press the Shift key and enter your move during the game, the game will be saved." << endl;
        cout << "If you press the ESC key and enter your move during the game, you will exit the game directly." << endl;
        for (int i = 10; i > 0; i--) {
            cout << "You will be redirected to the main menu in " << i << " seconds.\r";
            cout.flush();
            WaitTime(1);
        }
        ClearScreen();
        goto jump4;

        break;
    case 4:
        ClearScreen();
        cout << "Exiting the game..." << endl;
        WaitTime(1);
        exit(0);
        break;
    default:
        cout << "Invalid choice! Please try again." << endl;
        sleep(1500);
        goto jump3;
        break;
        }

    }
}

void InitializeBoard(int rows, int columns)
{
    int area = rows * columns;
    int* numbers = new int[area];

    // Generating numbers from 0 to (area/2)-1
    for (int i = 0; i < area / 2; i++)
    {
        numbers[i] = i;
        numbers[i + area / 2] = i;
    }

    // Shuffling the numbers
    srand(time(0));
    for (int i = area - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(numbers[i], numbers[j]);
    }

    // Creating the game board and assigning the numbers
    board = new int* [rows];
    revealed = new bool* [rows];

    for (int i = 0; i < rows; i++)
    {
        board[i] = new int[columns];
        revealed[i] = new bool[columns];

        for (int j = 0; j < columns; j++)
        {
            board[i][j] = numbers[i * columns + j];
            revealed[i][j] = false;
        }
    }
    
    delete[] numbers;
}

void PrintBoard(int rows, int columns)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (revealed[i][j])
                cout << board[i][j] << " ";
            else
                cout << "* ";
        }
        cout << endl;
    }
}

void AllCardsOpen(int rows, int columns)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool IsGameOver(int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (!revealed[i][j])
                return false;
        }
    }
    return true;
}
void ClearScreen()
{
    // Ekraný temizlemek için platforma baðlý komutlarý kullan
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    //intro();
    menu();
   
}

void WaitTime(int x)
{
    this_thread::sleep_for(chrono::seconds(x));
}

// Windows konsolunda sað üst köþeye metin yazdýran fonksiyon
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}