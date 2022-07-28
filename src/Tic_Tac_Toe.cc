/*Tic-Tac-Toe Game using C++*/
/*User Vs Computer*/
/**
 *author: Suraj Kumar Giri.
 *Date: 21-06-2022
 *Time: 23:54:27
 */

/***ADDITION OF NEW FEATURE ANNOUNCED****
 *author: Suraj Kumar Giri.
 *Date: 23-07-2022
 *Time: 20:53:30
 *Purpose:
 *1) To add feature of playing one times user, 2nd times computer iteratively (By default).
 *   But the configuration can be changed in 'sudo' mode to desired configuration (like only user will start the game OR only computer will start the game).
 *2) Feature of 2 players mode without any interfere of computer.
 *   There may be changed in the current configuration of program because some functions are compulsory to used in newly created class. So, we use inheritance in a better way. (Instead of inheriting the all things while some of them are only required.)
 */

/**Tic-Tac-Toe playing board
 **For user
  1 2 3
  4 5 6
  7 8 9
 *user can enter 1,2,3... for select the the respective cell
 **For Developer
  00 01 02
  10 11 12
  20 21 22
 */

/*MORE:
 *1) see 'COMMENT BLOCK 1200' for know about access rights of nested class to parent class and vice versa.
 */

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;
int numberOfTimesGamePlayed;                            /*Global variable to count the number of times game played by user in the current session*/
int userWonCounter;                                     /*Global variable to count the number of times user won the game in current session*/
int computerWonCounter;                                 /*Global variable to count the number of times computer won the game in current session*/
int drawCounter;                                        /*Global variable to count the number of times games draw in current session*/
char traceCellFillingInGame[10];                        // Global String for developers only. It stores the the cell filled by user and computer in as it is sequence to analyses the win/loss and logics (for developers only.). Developers can see this string by calling the function "TraceCellFillingInGameFunction()" just after typing '~' in any input buffer accepting input after win/loss of game.
short globalTracingIndex;                               // for index of string 'traceCellFillingInGame'
bool restartNextNewGameWithNewGameConfiguration = true; // global variable if contains true then it helps in continuing to next game without asking the user about configuration in every new game else continue to next game with a new game configuration and displaying the first menu again.. (by default in first game : true).

/*global function to display the game statics of current session*/
void displayTheGameStatistics()
{
    printf("\n\n\033[38;5;190m**********GAME STATICS OF CURRENT SESSION***********\n");
    printf("\033[38;5;190m* \033[38;5;45;3mTotal number of times game played           : %02d\033[38;5;190m *\n", numberOfTimesGamePlayed - 1);
    printf("\033[38;5;190m* \033[38;5;45;3mTotal number of times you won the game      : %02d\033[38;5;190m *\n", userWonCounter);
    printf("\033[38;5;190m* \033[38;5;45;3mTotal number of times computer won the game : %02d\033[38;5;190m *\n", computerWonCounter);
    printf("\033[38;5;190m* \033[38;5;45;3mTotal number of times game draw             : %02d\033[38;5;190m *\n", drawCounter);
    printf("\033[38;5;190m****************************************************\n");
}

void traceCellFillingInGameFunction()
{
    cout << "\n*******TRACE CELL FILLING*******\033[38;5;154;1m" << endl;
    for (short i = 0; traceCellFillingInGame[i] != '\0'; i++)
        cout << "[" << traceCellFillingInGame[i] << "] -> ";
    cout << "\033[0mGame Ended!" << endl;
}

class general
{
public:
    /*for taking feedback/bug report/suggestions/others from user*/
    void feedback()
    {
        system("start https://docs.google.com/forms/d/e/1FAIpQLSdkvMXOsVFF7A9kiyCfpwG-dEKcmgBagZJ9szcGKBeu-VJTTw/viewform?usp=pp_url");
    }

    /*returns random number. Changes every second.*/
    int randomNumber()
    {
        time_t seed = time(NULL);
        srand(seed);
        return rand();
    }

    /*take argument of row and column i.e, position of a cell and the 3x3 matrix base address. Returns true if cell is empty else false.*/
    bool isCellEmpty(short row, short col, char matrix[][3])
    {
        if (matrix[row][col] == ' ') // if cell filled with space then it will be empty
            return true;
        return false;
    }

    /*take argument of row and column i.e, position of a cell and the 3x3 matrix base address. Returns true if cell is filled else false.*/
    bool isCellFilled(short row, short col, char matrix[][3])
    {
        return !isCellEmpty(row, col, matrix); /*isCellEmpty() returns false if cell is filled else true*/
    }

    /**
     *Take arguments of desired element which need to be searched in the series (exist or not) && first 3 elements of series(SumSeries) to get the logic for series traversal till desired position.
     * && range of elements till which you want to find your desiredElement (by default it is 100 means only till 100th element of series, your desired element will be searched).
     * returns true if element found in series in provided/default range else false.
     * e.g. of using this function:
     * Let a series 2,5,8..... and we have to check 21 is present in this series or not.
     */
    bool isInSumSeriesOfIt(int elementToBeCheckInThisSeries, int element1, int element2, int element3, short range = 100)
    {
        bool correctSeries = false; /*If series received in argument is correct series of sum then it will become true else false*/
        short difference = element2 - element1;
        if (difference == element3 - element2) /*if received sequence is correct then it will process to next*/
            correctSeries = true;

        int currentElement = element1;
        short i = 0;
        while (correctSeries)
        {
            if (currentElement == elementToBeCheckInThisSeries)
                return true;
            currentElement += difference; /*incrementing to next element of the series*/
            if (++i == range)             /*if desiredElement doesn't found then the loop of series break after the provided range of checking (by default it is till 100th element of the series).*/
                break;
        }
        return false; /*if series is not correct OR desiredElement doesn't found in default/provided range.*/
    }

    /*this function takes argument of a number and if number is in range of 1 to 9 then it returns true else false*/
    bool isInRangeOf1to9(int number)
    {
        if (number >= 1 && number <= 9)
            return true;
        return false;
    }
};

class allMenu
{
    // static int userSelectedDefaultGameLevel;//we can't use static int as data member of class
public:
    /*welcome menu with and without ASCII art of logo. By default 'false' for printing ASCII art. Pass 'true' to print ASCII art*/
    void welcomeMenu(bool withAsciiArt = false)
    {
        cout << "\e[2J\e[H";
        if (!withAsciiArt)
            cout << "\e[1;31m************WELCOME TO TIC-TAC-TOE GAME.************" << endl;
        else
        {
            cout << "\033[1;31m";
            cout << " _____  _         _____              _____            " << endl;
            cout << "|_   _|(_)  ___  |_   _|__ _   ___  |_   _|___    ___ " << endl;
            cout << "  | |  | | / __|   | | / _` | / __|   | | / _ \\  / _ \\" << endl;
            cout << "  | |  | || (__    | || (_| || (__    | || (_) ||  __/" << endl;
            cout << "  |_|  |_| \\___|   |_| \\__,_| \\___|   |_| \\___/  \\___|" << endl;
            cout << "                                                      " << endl;
        }
        cout.width(63);
        cout << "\e[1;36mDeveloper: Suraj Kumar Giri\e[0m" << endl
             << endl;
        ;
    }

    /*top block of gameRestartMenu which need to print repeatedly if user clear the screen*/
    void gameRestartMenuBlock()
    {
        cout << "\n\n\033[38;5;208m+++++++++++++++++++GAME RESTART MENU++++++++++++++++++++\033[0m" << endl;
        cout << "\033[38;5;190mDo you want to start a new game?" << endl
             << "\033[38;5;201;1;3m=> Press '1' or 'enter' to start a new game.\033[0m" << endl
             << "\033[28;5;190m=> Press '#' to exit the game." << endl
             << "=> Press '@' to clear the display.\033[0m" << endl
             << "\033[38;5;159mWrite your choice:\033[0m" << endl;
        //  cout<<"write '~' to trace how the cell filled."<< endl;//for developers
        cout << "$ ";
    }

    /*display the requires command to user to restart the game. returns true if user wants to restart the game else false*/
    bool gameRestartMenu()
    {
        while (true)
        {
            gameRestartMenuBlock();
            fflush(stdin); // flushing the standard input stream's buffer
            char choice = cin.get();
            short choiceInInt = choice - 48; // converting character to integer using ASCII
            if (choice == '~')
            {
                traceCellFillingInGameFunction();
                system("pause");
                continue;
            }
            if (choiceInInt == 1 || choice == '\n')
                return true; // means user want to restart the game
            else if (choice == '@')
            {
                system("cls");
                continue;
            }
            else if (choice == '#')
                return false; // if user exits the game
            else
            {
                cout << "\033[1;31mFatal Error: Invalid choice." << endl;
                cout << "\033[2mPlease select a choice again.\033[0m" << endl;
            }
        }
    }

    /*take argument of of last selected game level of user (if first then by default 0) and display the menu on the basis of that level*/
    void gameLevelMenuBlock(int userSelectedDefaultGameLevel)
    {
        cout << "\033[1;34m===============GAME LEVEL MENU================\033[0m" << endl;
        cout << "\033[38;5;82;3m=> Press '1' for Easy Level." << endl;
        cout << "=> Press '2' for Medium Level." << endl;
        cout << "=> Press '3' for Impossible Level." << endl;

        if (userSelectedDefaultGameLevel == 0) // by default static int is 0 and when user selected once 1 for easy then userSelectedDefaultGameLevel will become 1. If user has selected by default from beginning then it will not change and still 0. So, I have used 0 & 1 in OR in condition of if().
            cout << "=> Press 'enter' for default level (easy)." << endl;
        else if (userSelectedDefaultGameLevel == 1)
            cout << "\033[38;5;201;3;1m=> Press 'enter' for your last selected level (EASY)." << endl;
        else if (userSelectedDefaultGameLevel == 2)
            cout << "\033[38;5;201;3;1m=> Press 'enter' for your last selected level (MEDIUM)." << endl;
        else // for gameLevel==3 for impossibleLevel
            cout << "\033[38;5;201;3;1m=> Press 'enter' for your last selected level (IMPOSSIBLE)." << endl;

        cout << "\033[38;5;82;3m=> Press '#' for exit game." << endl;
        cout << "=> Press '@' for clear the display." << endl;
        cout << "=> Press '&' for feedback/suggestion/bug report/others.\033[0m" << endl;
        cout << "\033[38;5;123mWrite your choice:\033[0m" << endl;
    }

    // /*take user input for menu displayed by called function. Returns userChoiceInInt if choice is correct and -1 if user wants to exit. I have defined this function user interaction in many menus are similar and it cold be defined in a function at one place*/
    // short interactWithUserInMenu()
    // {
    // }

    /*Menu to ask user for level of game he/she wants to play. returns the selected level (1-easy,2-medium,3-impossible) and returns -1 if user exits the game*/
    short
    gameLevelMenu()
    {
        while (true)
        {
            /*we have to stores the current session selectedLevel of user. So, that from next game of current session user don't need to retype the option to select level. My aim is to provide feature to press enter and select the last selected level. It only possible via static variable or global var.*/
            static int userSelectedDefaultGameLevel; /*To store the last selected game level of user in current session. So, whenever user press enter then last selected game level will be selected*/
            gameLevelMenuBlock(userSelectedDefaultGameLevel);

            cout << "$ ";
            fflush(stdin); // flushing the standard input stream's buffer
            char choice = cin.get();
            short choiceInInt = choice - 48; // converting character to integer using ASCII
            if (choiceInInt >= 1 && choiceInInt <= 3)
            {
                userSelectedDefaultGameLevel = choiceInInt;

                if (userSelectedDefaultGameLevel == 1)
                    cout << "\033[1;3;32mNice, EASY Level Selected......" << endl;
                else if (userSelectedDefaultGameLevel == 2)
                    cout << "\033[1;3;32mWow, MEDIUM Level Selected......" << endl;
                else
                    cout << "\033[1;3;32mGreat, IMPOSSIBLE Level Selected......" << endl;

                return choiceInInt;
            }
            else if (choice == '\n') // if user press enter for by default level and it's is easy level in beginning or previous selected level of current user session.
            {
                if (userSelectedDefaultGameLevel == 0)
                {
                    cout << "\033[1;3;32mNice, EASY Level Selected......" << endl;
                    return 1; // for easy
                }

                if (userSelectedDefaultGameLevel == 1)
                    cout << "\033[1;3;32mNice, EASY Level Selected......" << endl;
                else if (userSelectedDefaultGameLevel == 2)
                    cout << "\033[1;3;32mWow, MEDIUM Level Selected......" << endl;
                else
                    cout << "\033[1;3;32mGreat, IMPOSSIBLE Level Selected......" << endl;

                return userSelectedDefaultGameLevel; // by default easy level which is 1
            }
            else if (choice == '@')
            {
                system("cls");
                welcomeMenu(true); // because this is 2nd menu after welcome menu. So, welcome menu should be visible along with it.
                continue;
            }
            else if (choice == '#')
                return -1; // if user exits the game
            else if (choice == '&')
            {
                general obj;
                obj.feedback();
                cout << "\033[38;5;154mThanks for submitting your feedback/bug report/suggestion. :)" << endl;
                cout << "It will help us to improve your experience with the application. \033[38;5;190m:)\033[0m" << endl;
                system("pause");
                system("cls");
                welcomeMenu(true); // again displaying the welcome menu after clear of display
                continue;
            }
            else
            {
                cout << "\033[1;31mFatal Error: Invalid choice." << endl;
                cout << "\033[2mPlease select a choice again.\033[0m" << endl;
            }
        }
    }
};

class ticTacToe : private allMenu
{
    /*****data members start*****/
    char matrix[3][3]; // for matrix of Tic-Tac-Toe
    char computerChar; // for computer playing character like 'X' or 'O'. By default 'O'
    char userChar;     // for user playing character like 'X' or 'O'. By default 'X'
    short filledCells; // stores number of cells filled (by user & computer characters 'X'/'O). By default it is 0
    enum gameLevel
    {
        easy,
        medium,
        impossible
    } level;

    /*class as a data member of class 'ticTacToe'. (Nested Class).*/
    /*CLASS FOR THE LOGIC OF MEDIUM LEVEL OF TIC-TAC-TOE (logic for, how the computer will restrict user to win + try to win by filling the appropriate cells of matrix of ticTacToe).
     *use this class member function only after at least 3 cells of matrix filled (2 by user and 1 by computer (by default, user will start the game in this program)) &
     *because win/loss only possible if at least 3 cells are filled by one participants.
     */
    class mediumLevel
    {
        /******************************NOTE FOR NESTED CLASS************************************** COMMENT BLOCK 1200
         **INSIDE NESTED CLASS (a class as data member of another class).
         *we can only access any data member or member function of parent class by an object/instance of the parent class.
         *But we have an additional facility than general is that, in nested class we can access all private/public/protected data members/ member functions of parent class using an object of the parent class without any restriction.
         *Nested Class is only accessible inside it's parent class.
         *There is no scope of nested class outside of the parent class in which it is defined.
         *FOCUS:: Here, we can only access the parent class data member/member function by creating a new object of parentClass. So, we can't access the data member value in current object of parentClass.
         *Below 2 lines are from book of c++ by BJARNE STROUSTRUP (the developer of c++)
         *1.) A C++ nested class does not have access to an object of the enclosing class. (myEdit: here 'an object' means 'current object' of enclosing class. See below line for more clear explanation by STROUSTRUP)
         *2.) A nested class has access to members of its enclosing class, even to private members (just as a member function has), but has no notion of a current object of the enclosing class.
         *So, it is clear that, nested class has to create new object of the enclosing class and that new object will not have any data of current class.
         *KEEP IN MIND, each object of a class is different. Different objects of same class have same template but having different values. Each object of a class has different block of allocated memory and holds different values. Class is a blueprint and multiple different objects are created using this blueprint.
         *FOCUS: I have solved the above limitation, by passing the required value (dataMember) from current object of enclosing class to the nested class object via parametrized constructor of nested class while creating instance of nested class in enclosing class. And In this way, I have used the dataMembers of current object of enclosing class in nested class without any access issue. (This is due to power of constructor)
         * (We can eliminate this limitation by FRIEND function. Friend function can access the all private/public/protected data members & member functions of a class by the object of that class. It can also work with multiple class at same time and can be used to operate on objects of different classes at same time.). But we will not use it here.
         *
         **INSIDE THE PARENT CLASS,
         *accessing the nested class (child class) from parent class is like accessing the class dataMember or memberFunction from outside the class (let say from main() function).
         *Parent class can access the memberFunction or dataMember of it's child class (nested class) only by an object of the child class (nested class)
         *But parent class has access like outsider. That is, parent class can only access public memberFunctions and dataMember of the child class with the help of an object of child class.
         *Parent class can't access any private & protected dataMember or memberFunction of the child class
         *
         *******************************************************************************************/

        /*-------------------------------------LOGIC FOR MEDIUM LEVEL---------------------------------------------*/
        /*WHAT'S TO DO:
         *If condition satisfied for winning in next filling by user then computer has to restrict it.
         *If condition satisfied for winning in next filling by computer then computer has to fill it.
         */
        /*CONDITION TO WIN IN NEXT FILLING BY USER OR COMPUTER. (Total 8 winning lines we have check i.e., 3 rows + 3 columns + 2 diagonals).
         *1) 2 cells must be filled in single row/column/diagonal with 'X' or 'O' and left one cell should be empty.
         */
        /*PROGRAM LOGIC:
         *1) 1st check, is two cells filled? If yes then check 3rd cell if it is empty then check character in both filled cell. If both character is same then fill computer character.
            If both character belongs to computer then 'computer will win' else both characters belongs to user and computer will restrict the user to win by filling computerChar.
         *2) we have check the above logic1 for all 8 lines of winning i.e, 3 rows + 3 columns + 2 diagonals.
            all 8 lines will be check in worst case otherwise if condition of filling fulfilled anywhere the function will returns the cellNumber to fill.
         */

        // now starting programming for mediumLevel
        char matrix[3][3];        // gamePad of ticTacToe
        short filledCellsCounter; // count the filled cells in current row or column (by default it is 0)
        char playingCharacter1;   // to store the character filled in filledCell 1
        char playingCharacter2;   // to store the character filled in filledCell 2
        short flag = 0;           // flag to indicate no. of playingCharacter stored for checking
        char userChar;            // to store the playing character selected by user (any of 'X' Or 'O')
        char computerChar;        // to store the playing character filled by computer (any of 'X' Or 'O')

        /*Takes arguments of position of cell (row,col) and count the filled cells in matrix/gamePad and assign in data member 'filledCellsCounter'*/
        void filledCellsCounterFunction(short row, short col)
        {
            general generalObj;

            if (generalObj.isCellFilled(row, col, matrix)) // we can't use "parentInstance.isCellFilled(i, j)" because 'parentInstance' is new object containing garbage values. And we need to access the matrix of current object of enclosing class which is not accessible by nested class. So, we have used parametrized constructor.
                filledCellsCounter++;
            // else
            // emptyCellsCounter++; //No need of it. /*we can also use (3-filledCellsCounter) outside this loop to find the number of empty cells*/
        }

        /**
         *Take arguments current row and column of loop in i and j respectively. And also take 'rows' and 'columns' by reference which are received from computerTurn() of of current object of enclosing class..
         *This function will called only if it is confirmed that 2 cells are filled and 1 cell is empty (by default if 2 cells are filled.) in current row/column.
         *This function assign both filled characters in data member 'playingCharacter1' and 'playingCharacter2' respectively which will be used in calling function to check the winning condition and return condition of calling function.
         *if empty cell postion received in i,j then this function will assign this position to the referenced 'row' and 'column' which will reflect in computerTurn() of of current object of enclosing class.
         *Main reason to make this function is to avoid repetition of approx same LOC for rows/columns/diagonals (with little change in position).
         *It's name is so because .... (see line no.3 of this comment block)
         */
        void assignFilledCellsCharacterInDataMember(short i, short j, short &row, short &column)
        {
            general generalObj; /*creating instance of the class 'general'*/

            /*now we have to store 2 characters of 2 filledCell in two variable declared above (playingCharacter1 & playingCharacter2). But in one iteration, we have to store only one character. So, we use flag to indicate iteration & perform the desired operation*/
            if (generalObj.isCellFilled(i, j, matrix))
            {
                if (flag == 0)
                {
                    playingCharacter1 = matrix[i][j];
                    flag++;
                }
                else if (flag == 1) // after storing one I have stores the 2nd playingCharacter
                    playingCharacter2 = matrix[i][j];
            }
            else if (matrix[i][j] == ' ') // empty. means if both filled cell have same playingCharacter then we have to send position of this blank cell.
            {
                /*we have to pass position of cell to fill (empty) via reference received in row, column*/
                row = i;
                column = j;
                /*there is no use of above 2 lines of assigning if playingCharacter1!=playingCharacter2*/
            }
        }

    public:
        /***WHY THIS FUNCTION ?. COMMENT BLOCK 2122
         *This function is a copy (with some enhancement) of the function 'whichCellShouldFilled()' of 'mediumLevel' class.
         *Only little changes have been added in it for checking the winning condition of solemnly for computer only.
         *Initially, The function 'whichCellShouldFilled()' is used to restrict the user to win and also used to make computer to won the game.
         *But there was a huge limitation of that function (whichCellShouldFilled()) which are following:
         *1) It checks the condition winning the computer or restricting the user in sequence.
         *   The sequence is: It checks rows first (top to down) -> then column (left to right) -> then diagonals (1 then 2).
         *2) It returns the function after selecting the empty cell of that row/column/diagonal which comes first in sequence and satisfies the conditions (2 cells must be filled with same playingCharacter (either 'X' or 'O') and the rest 1 cell should be empty.).
         *The cause of limitation is that the function returns whenever any line line (row, column,diagonal) encounters in the pre-programmed sequence satisfying the condition.
         *Below is the effect (on game) of this 'sequenced checking and returning of the function':
         **Such condition created in which user has done some mistake or two winning condition of computer created.
         * -> Let 3 cells are filled by user and 2 cells are filled by computer. See below (Let use playingChar is 'X'):
         *    X | X |  |
                | X |  |
              O | O |  |
         *Above is the situation,, and now it's computer turn to fill.
         *As per the function 'whichCellShouldFilled()'. the control started checking in sequence and whenever first row checks then it satisfies the condition (2 cells should be filled with same playingCharacter (either 'X' or 'O')).
         *So, control will return by selecting the cell(0,2) to fill.
         *But this is the main problem, it's chance to fill the cell (0,2) and win the game by computer.
         *But due to in sequence and return of function the control hadn't reached in that row.

         **So, main problem is that, that function primarily focusing on restricting the user to win (if computer winning condition satisfies in sequence before restricting the user then only computer winning preferred else user restriction are more prioritized.)
         *But we must need to check the winning possibility of computer before restricting the user. If computer winning possible then that cell will be filled and computer will win the game and user will not receive any change to fill in next turn and win.
         *So, it is compulsory to check the winning possibility of computer before restricting the user.
         **This problem is with all level either easy,  medium or hard. In easy level also, computer can win the match due to user mistake but computer don't fill the required cell. In medium level also, when sometimes, user restriction condition satisfied and in next computer condition is also satisfied.
         * Then also due to sequence, the user restriction was used to preferred instead making computer win. It's make the game worst.
         *
         * ********ADVANTAGES OF THIS FUNCTION********
         * It will called to check the possibility of winning by computer if computer can win from current fill then it will select the required row and column to make computer win.
         * It will called before the function 'whichCellShouldFilled()' which restrict user from winning (if one row/column/diagonal) are making user win in next fill. But this function called before the same and check the winning condition for computer. If computer can win then no issue it will make computer win.
         * One of the main advantage of this function is that it is independent and only work to make computer win if simple winning condition satisfied. It doesn't implement any logic to restrict user. So, It can also be used in easyLevel(No logic to restrict user) and if user has done any mistake and computer can win by next filling.
         * And it can also be used before restricting the user in mediumLevel as well as impossibleLevel to make computer win if possible.
         * -----------------------------------------
         * take arguments of row and column and assign the desired position in passed row and column by reference. Returns true if winning of computer condition found else false.
         * If returns true means winning of computer condition found and row,column contains desired position of cell to fill.
         * If false returns then passed row and column doesn't contains desired position of cell to fill. And to fill this you have to use any logic like to restrict the user if possible or fill by some powerful logic to defeat user badly.😂
         */
        bool whichCellShouldFilledToMakeComputerWin(short &row, short &column)
        {
            /*for rows (in first iteration) and column (in 2nd iteration). */
            short forIteration = 0;                              /*for counting the iteration in while loop*/
            for (forIteration; forIteration < 2; forIteration++) /* forIteration=0 for rows (3 rows) and forIteration=1 for columns (3 columns)*/
            {
                /*I am trying to perform both rows and columns operations in a loop because cells index reversed in column in comparision to rows and vice versa).
                 *In 'isWonTheGame()' function I have written the code of rows and columns separately. You can see it.
                 *But we can automate it in loop because only index are reversing and our lines of code become half. Edit: I have tried it below. LOC decreases drastically.¯\_(ツ)_/¯
                 *We have to use conditional for rows and column and call the same function with reversed row and column index from each other.
                 */
                for (short i = 0; i < 3; i++)
                {
                    filledCellsCounter = 0; // assigning 0 in each new row or column
                    for (short j = 0; j < 3; j++)
                    {
                        /*for rows*/
                        if (forIteration == 0) /*Means for rows*/
                            filledCellsCounterFunction(i, j);
                        /*for columns*/
                        else /* if (forIteration == 1)*/      /*Means for column*/
                            filledCellsCounterFunction(j, i); // reversed for column
                    }                                         /*end of inner for loop*/

                    if (filledCellsCounter == 2) /*2 cells must be filled for winning possibility. Confirmation of winning only if both filled cell have same playingCharacter*/
                    {
                        /*-----------------FOR ROWS AND COLUMNS----------------------*/
                        /*
                         *in current line (row/column),
                         *one cell will definitely empty (contains space).
                         *both filled cell may contains 'X'(next winning condition of player having 'X') OR 'O'(next winning condition of player having 'O') OR both (no winning condition)
                         */

                        flag = 0; // reset to zero for every new row/column

                        if (forIteration == 0) /****** for rows*******/
                        {
                            /*we have to access all cells of current row again to check what's filled in it.*/
                            for (short j = 0; j < 3; j++)
                            {
                                /*COMMENT BLOCK 1201
                                 *In this situation, we have 3 cells in 2 cells are filled and 1 cell is empty
                                 *if both filled cells have same playingCharacter (any one of 'X' and 'O')
                                 *then we have to return the postion of empty cell to fill and win/restrict the game (if playingCharacter is of computer) or restrict winning the user (if playingCharacter is of user).
                                 */
                                assignFilledCellsCharacterInDataMember(i, j, row, column);
                            }
                        }
                        else // if(forIteration==1)/*****for columns******/
                        {
                            /*we have to access all cells of current column again to check what's filled in it.*/
                            for (short j = 0; j < 3; j++)
                            {
                                /*see above comment -> COMMENT BLOCK 1201*/
                                assignFilledCellsCharacterInDataMember(j, i, row, column); // reversed for column
                            }
                        }

                        if (playingCharacter1 == playingCharacter2 && playingCharacter2 == computerChar) // if both playingCharacter are same then it is winning condition and 'row' and 'column' contains the desired position.
                            return true;
                    }
                    else
                        continue; /*for next row/column*/
                }                 /*end of 1st for loop*/
            }                     /*end of outer most for loop*/

            /*-----------------FOR DIAGONALS----------------------*/
            /*
             *1) 00,11,22 (logic to use loop for automation: row==column)
             *2) 02,11,20 (logic to use loop for automation: row is increasing by 1 and column is decreasing by 1)
             */
            /*for diagonal 1*/
            filledCellsCounter = 0; // reset to filledCellsCounter to 0 to restart
            for (short i = 0; i < 3; i++)
                filledCellsCounterFunction(i, i); // counting the filled cells of the diagonal1
            if (filledCellsCounter == 2)
            {
                flag = 0; // reset the flag to 0. It indicates the number of filled cells assigned in respective data members. So, for this diagonal, we have to reset it.
                for (int i = 0; i < 3; i++)
                    assignFilledCellsCharacterInDataMember(i, i, row, column);                   /*assign the filled cell's value in data member 'playingCharacter1' and 'playingCharacter2'*/
                if (playingCharacter1 == playingCharacter2 && playingCharacter2 == computerChar) /*checking the condition for winning of computer or restricting the user to win*/
                    return true;
            }

            /*for diagonal 2*/
            filledCellsCounter = 0; // reset to filledCellsCounter to 0 to restart
            for (short i = 0, j = 2; i < 3; i++, j--)
                filledCellsCounterFunction(i, j); // counting the filled cells of the diagonal2
            if (filledCellsCounter == 2)
            {
                flag = 0; // reset the flag to 0. It indicates the number of filled cells assigned in respective data members. So, for this diagonal, we have to reset it.
                for (short i = 0, j = 2; i < 3; i++, j--)
                    assignFilledCellsCharacterInDataMember(i, j, row, column);                   /*assign the filled cell's value in data member 'playingCharacter1' and 'playingCharacter2'*/
                if (playingCharacter1 == playingCharacter2 && playingCharacter2 == computerChar) /*checking the condition for winning of computer or restricting the user to win*/
                    return true;
            }

            /*if none of above return execute means there is no condition of either winning of user or computer.
             *So, we return false to indicate that don't use passed referenced 'row' & 'column'. Use any other logic to fill the cell (because currently there is no winning situation).
             */
            return false;
        }

        /*take arguments of row and column and assign the desired position in passed row and column. Returns true if winning of computer/restricting of user condition found else false.
         *If returns true means winning/restring condition found and row,column contains desired position of cell to fill.
         *If false returns then passed row and column doesn't contains desired position of cell to fill. And to fill this you have to use another logic or easyLevel method. (Recommended to use another logic, which leads to win)
         */
        bool whichCellShouldFilled(short &row, short &column)
        {
            /*Edit...start*/
            /*Checking the possibility of computer before restricting the user. If there is any possibility to make computer win by single filling of cell. Then there is no need to restrict user, just fill that cell and won the match. That's enough*/
            /*see 'COMMENT BLOCK 2122' for more about this edit.*/
            if (whichCellShouldFilledToMakeComputerWin(row, column))
                return true;
            /*if there is no winning condition satisfied for computer then only below code of this function will execute.*/
            /*Edit...end*/

            /*for rows (in first iteration) and column (in 2nd iteration). */
            short forIteration = 0;                              /*for counting the iteration in while loop*/
            for (forIteration; forIteration < 2; forIteration++) /* forIteration=0 for rows (3 rows) and forIteration=1 for columns (3 columns)*/
            {
                /*I am trying to perform both rows and columns operations in a loop because cells index reversed in column in comparision to rows and vice versa).
                 *In 'isWonTheGame()' function I have written the code of rows and columns separately. You can see it.
                 *But we can automate it in loop because only index are reversing and our lines of code become half. Edit: I have tried it below. LOC decreases drastically.¯\_(ツ)_/¯
                 *We have to use conditional for rows and column and call the same function with reversed row and column index from each other.
                 */
                for (short i = 0; i < 3; i++)
                {
                    filledCellsCounter = 0; // assigning 0 in each new row or column
                    for (short j = 0; j < 3; j++)
                    {
                        /*for rows*/
                        if (forIteration == 0) /*Means for rows*/
                            filledCellsCounterFunction(i, j);
                        /*for columns*/
                        else /* if (forIteration == 1)*/      /*Means for column*/
                            filledCellsCounterFunction(j, i); // reversed for column
                    }                                         /*end of inner for loop*/

                    if (filledCellsCounter == 2) /*2 cells must be filled for winning possibility. Confirmation of winning only if both filled cell have same playingCharacter*/
                    {
                        /*-----------------FOR ROWS AND COLUMNS----------------------*/
                        /*
                         *in current line (row/column),
                         *one cell will definitely empty (contains space).
                         *both filled cell may contains 'X'(next winning condition of player having 'X') OR 'O'(next winning condition of player having 'O') OR both (no winning condition)
                         */

                        flag = 0; // reset to zero for every new row/column

                        if (forIteration == 0) /****** for rows*******/
                        {
                            /*we have to access all cells of current row again to check what's filled in it.*/
                            for (short j = 0; j < 3; j++)
                            {
                                /*COMMENT BLOCK 1201
                                 *In this situation, we have 3 cells in 2 cells are filled and 1 cell is empty
                                 *if both filled cells have same playingCharacter (any one of 'X' and 'O')
                                 *then we have to return the postion of empty cell to fill and win/restrict the game (if playingCharacter is of computer) or restrict winning the user (if playingCharacter is of user).
                                 */
                                assignFilledCellsCharacterInDataMember(i, j, row, column);
                            }
                        }
                        else // if(forIteration==1)/*****for columns******/
                        {
                            /*we have to access all cells of current column again to check what's filled in it.*/
                            for (short j = 0; j < 3; j++)
                            {
                                /*see above comment -> COMMENT BLOCK 1201*/
                                assignFilledCellsCharacterInDataMember(j, i, row, column); // reversed for column
                            }
                        }

                        if (playingCharacter1 == playingCharacter2) // if both playingCharacter are same then it is winning condition and 'row' and 'column' contains the desired position.
                            return true;
                    }
                    else
                        continue; /*for next row/column*/
                }                 /*end of 1st for loop*/
            }                     /*end of outer most for loop*/

            /*-----------------FOR DIAGONALS----------------------*/
            /*
             *1) 00,11,22 (logic to use loop for automation: row==column)
             *2) 02,11,20 (logic to use loop for automation: row is increasing by 1 and column is decreasing by 1)
             */
            /*for diagonal 1*/
            filledCellsCounter = 0; // reset to filledCellsCounter to 0 to restart
            for (short i = 0; i < 3; i++)
                filledCellsCounterFunction(i, i); // counting the filled cells of the diagonal1
            if (filledCellsCounter == 2)
            {
                flag = 0; // reset the flag to 0. It indicates the number of filled cells assigned in respective data members. So, for this diagonal, we have to reset it.
                for (int i = 0; i < 3; i++)
                    assignFilledCellsCharacterInDataMember(i, i, row, column); /*assign the filled cell's value in data member 'playingCharacter1' and 'playingCharacter2'*/
                if (playingCharacter1 == playingCharacter2)                    /*checking the condition for winning of computer or restricting the user to win*/
                    return true;
            }

            /*for diagonal 2*/
            filledCellsCounter = 0; // reset to filledCellsCounter to 0 to restart
            for (short i = 0, j = 2; i < 3; i++, j--)
                filledCellsCounterFunction(i, j); // counting the filled cells of the diagonal2
            if (filledCellsCounter == 2)
            {
                flag = 0; // reset the flag to 0. It indicates the number of filled cells assigned in respective data members. So, for this diagonal, we have to reset it.
                for (short i = 0, j = 2; i < 3; i++, j--)
                    assignFilledCellsCharacterInDataMember(i, j, row, column); /*assign the filled cell's value in data member 'playingCharacter1' and 'playingCharacter2'*/
                if (playingCharacter1 == playingCharacter2)                    /*checking the condition for winning of computer or restricting the user to win*/
                    return true;
            }

            /*if none of above return execute means there is no condition of either winning of user or computer.
             *So, we return false to indicate that don't use passed referenced 'row' & 'column'. Use any other logic to fill the cell (because currently there is no winning situation).
             */
            return false;
        }

        /*parametrized constructor. We don't have access to the values current object of enclosing class. To solve this, I have used parametrized constructor and passed the matrix and save in this nested class's current object*/
        mediumLevel(char matrix[][3], char computerChar) /*Edit: Added additional argument of 'computerChar' to check the winning condition of computer before restricting the user. And to check the winning condition of any particular playingChar, we need that one in our function/class*/
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                    this->matrix[i][j] = matrix[i][j];
            }
            filledCellsCounter = 0; // assigning by default value of filled cells i.e., 0

            /*assigning the computerChar and userChar below*/
            this->computerChar = computerChar;
            if (computerChar == 'O')
                userChar = 'X';
            else
                userChar = 'O';
        }

        /*destructor*/
        ~mediumLevel() {}
    };

    /*class for logic easyLevel of ticTacToe*/
    class easyLevel
    {
        char matrix[3][3]; // gamePad of ticTacToe. It is required because we don't have access to the matrix(gamePad) of current object of the enclosing class.

    public:
        /*take arguments of row and column and assign the position of any random empty cell in passed row and column.*/
        void whichCellShouldFilled(short &row, short &column)
        {
            /*We will not use any advanced logic here. We will simple use random number b/w 1-9 and fill the cell. */
            general generalObj;       // instance of general class
            ticTacToe parentInstance; /*creating instance of the parent class*/
            int modifier = 21;        // taking any random number (let 21) to modify cellNumber (because randomNumber() changes value every second. But loop may be go in next iteration within a second. If we don't modify the value then we will get same result) //no effect on logic
            while (true)
            {
                short cellNumber = (modifier + generalObj.randomNumber()) % 10; //%10 because if a number divided by x then remainder will be from 0 to x-1. And here we need value from 1 to 9
                /*now we have to interpret the command (cellNumber) to it's proper index to insert the playingCharacter in the matrix/GamePad*/
                parentInstance.commandInterpreter(cellNumber, row, column);
                if (generalObj.isCellEmpty(row, column, matrix)) // returns true if cell is empty else false
                    break;
                else
                {
                    modifier *= 3; // multiplying by random number, let 3
                    continue;
                }
            }
        }

        /*parametrized constructor. We don't have access to the values current object of enclosing class. To solve this, I have used parametrized constructor and passed the matrix and save in this nested class's current object*/
        easyLevel(char matrix[][3])
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                    this->matrix[i][j] = matrix[i][j];
            }
        }

        /*destructor*/
        ~easyLevel() {}
    };

    /*we need the position of all 3 cells (because only 3 cell are used to win) which are responsible for winning the game. We can it to do things like show 'strikethrough' in winningCell during display of gamePad after winning of game*/
    /*if user/computer won the game then the position of all three cells which are responsible for winning are following:*/
    short positionOfWinningCells[6]; /*initially it will {0,0,0,0,0,0}
                                      *let it is {0,0,1,1,2,2} after assigned by isWonTheGame() function then
                                      *position of first cell = (0,0)
                                      *position of second cell = (1,1)
                                      *position of third cell = (2,2)
                                      *We can see that these three cells are responsible for winning.
                                      *So, we will check continuous value in array to get position of winningCell where each 2 value is position of one winningCell.
                                      */
    /****data members end ****/

    /****member function starts ****/

    /*interact with user to select the playing character and also assign the respective character to variables 'computerChar' & 'userChar' on the basis of user input*/
    void playingCharacterSelector()
    {
        while (true)
        {
            cout << "\033[38;5;225m\nSelect your playing character." << endl;
            cout << "\033[38;5;214m=> Press '1' for 'X' " << endl;
            cout << "=> Press '2' for 'O' " << endl;
            /*modifying the code for changing the default playerChar from fixed 'X' to "default playChar = user Last selected character". And for first time the default is 'X'*/
            if (numberOfTimesGamePlayed == 1) /*for game 1 of current session*/
                cout << "=> Press 'enter' for default ('X').\033[0m" << endl;
            else
            {
                cout << "\033[38;5;201;1;3m=> Press 'enter' for your default ('" << userChar << "')."
                     << "\033[0m" << endl;
            }
            char choice;
            cout << "$ ";
            fflush(stdin); // flushing the standard input stream's buffer
            choice = cin.get();

            if (choice == '\n') // if user has pressed 'enter' for default
            {
                // if (numberOfTimesGamePlayed != 1) // for !=1. Because for gameNumber1 the default constructor assign userChar to 'X' and computerChar to 'O'. And if user press enter for default in gameNumber1 then the default assignment by constructor will followed and no need to modify.
                /*so in any gameNumber if user press enter for default then we don't need to assign anything to user/computerChar because if it's first game then by default assigned by constructor else preassigned by user in below else block of while()*/
                cout << "\033[1;3;32mNice, Playing Character '" << userChar << "' Selected......" << endl;
                break;
            }
            else
            {
                if (choice == '1') // means userChar='X' and by default it is same
                {
                    userChar = 'X';
                    computerChar = 'O';
                    cout << "\033[1;3;32mNice, Playing Character 'X' Selected......" << endl;
                    break;
                }
                else if (choice == '2')
                {
                    userChar = 'O';
                    computerChar = 'X';
                    cout << "\033[1;3;32mNice, Playing Character 'O' Selected......" << endl;
                    break;
                }
                else
                {
                    cout << "\033[1;31mFatal Error: Invalid Choice." << endl;
                    cout << "\033[1;32mPlease select your choice again.\033[0m" << endl;
                }
            }
        }
    }

    /*to display the instructions for input in cell of matrix/gamePad of ticTacToe*/
    void displayCellInputInstructions()
    {
        cout << "\n\033[38;5;200m=================READ BELOW CAREFULLY=================" << endl;
        cout << "\033[38;5;190m:: Enter the number filled below in cells to select your choice for that cell in game." << endl;
        cout << ":: Any other input rather than 1-9 is invalid." << endl;
        cout << ":: You can't select the filled cell again in the same game.\033[0m" << endl
             << endl;

        short number = 1; // for display the number that user will select in game to select the respective cell
        for (int i = 0; i < 3; i++)
        {
            cout << "\t";
            for (int j = 0; j < 3; j++)
            {
                if (j == 1)
                    cout << "\e[1;32m |   \e[1;0m";
                cout << number++ << "  ";
                // cout << matrix[i][j] << ends;
                if (j == 1)
                    cout << "\e[1;32m |  \e[1;0m";
            }
            cout << endl;
            if (i == 0 || i == 1)
                cout << "\e[1;32m--------------------------------\e[0m" << endl;
        }
    }

    /*returns true if cell is empty else false. Takes argument of rows and column*/
    bool isCellEmpty(short row, short col)
    {
        if (matrix[row][col] == ' ') // if cell filled with space then it will be empty
            return true;
        return false;
    }

    /*returns true if cell is filled else false. Takes argument of rows and column*/
    bool isCellFilled(short row, short col)
    {
        return !isCellEmpty(row, col); /*isCellEmpty() returns false if cell is filled else true*/
    }

    /*check if user/computer won the game or not
     *Call this function if at least total 5 cells are filled by user & computer. 3 cells by user & 2 by computer and vice versa (depends upon who started first)
     *At least 3 cells with same playingCharacter requires for fulfill the winning condition for the player of that playingCharacter
     **About this function:
     *Take argument of playingCharacter 'X' or 'O' and check all possible conditions (8 conditions) for winning the game.
     *If received playing character fulfill the winning conditions. Then it returns true else false.
     *If won then the one of user/computer won the game whose playingCharacter==received playingCharacter
     */
    bool isWonTheGame(char playingCharacter) // playingCharacter of player
    {
        /*at least 5 cells must be filled by user & computer to be in probability of winning (see above comment for details). We will first check the condition of filled cells and if it true as per desired then we will go forward else return false*/
        if (filledCells < 5)
            return false;

        /************************if(filledCells>=5)*****************************/
        /*total 8 conditions are winning conditions*/
        /**WINNING CONDITIONS
         **Row-Wise
         *1. 00,01,02
         *2. 10,11,12
         *3. 20,21,22
         **Column-Wise (just opposite index of Row-Wise)
         *4. 00,10,20
         *5. 01,11,21
         *6. 02,12,22
         **Diagonal
         *7. 00,11,22
         *8. 20,11,02
         */

        /*FIXING HUGE BUG
         *we must need to verify that the cell which are checking currently must have filled.
         *If any of the cell in 'winning condition' is empty then there will no option to win. If cell contains 'space' then it will empty And we will check the condition for empty
         *If we don't do so, there will always spaces which fulfill the winning conditions and user will win the match without fulfilling the winning conditions.
         *
         *
         */

        /**Row-Wise. for 1,2,3*/
        for (short i = 0; i < 3; i++) /* i changed from 'int' to 'short' type because of error in Clang++. See COMMENT BLOCK 1220*/
        {
            /*we are checking the empty cell. If any of the cell in current row is empty then there will no any possibility of winning & we will continue the loop to next iteration.*/
            if (isCellEmpty(i, 0) || isCellEmpty(i, 1) || isCellEmpty(i, 2))
                continue;                                                          // if cell is empty then there is no any possibility of winning. So, continue the loop
            else if (matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2]) // it is like "if(a==b && b==c)"
            {
                /*if above condition satisfied then above 3 cells are winning cells and we need to store it's position for use it later*/
                short tempCellPosition[] = {i, 0, i, 1, i, 2}; // all 3 cells position one by one respectively
                /*COMMENT BLOCK 1220
                 *in above line of code 'i' must be short type if compiler is clang++. In G++, it may be int or short no issue.
                 *If 'i' is of 'int' type then 'Clang++' show error "error: non-constant-expression cannot be narrowed from type 'int' to 'short' in initializer list [-Wc++11-narrowing]"
                 *clang++ shows error because 'tempCellPosition' is of type 'short' and we are initializing it with 'i' which is of 'int' type and it's a variable not constant and we used to initialize any array etc by literals/constant.
                 */

                for (int j = 0; j < 6; j++) // condition<6 because total number of cells for winning = 3 and each one have position(x,y). So, total required size = 3x2 = 6
                    positionOfWinningCells[j] = tempCellPosition[j];

                return true;
            }
        }

        /**Column-Wise. for 4,5,6*/
        for (short i = 0; i < 3; i++) /* i changed from 'int' to 'short' type because of error in Clang++. See COMMENT BLOCK 1220*/
        {
            /*we are checking the empty cell. If any of the cell in current column is empty then there will no any possibility of winning & we will continue the loop to next iteration.*/
            if (isCellEmpty(0, i) || isCellEmpty(1, i) || isCellEmpty(2, i))
                continue;                                                          // if cell is empty then there is no any possibility of winning. So, continue the loop
            else if (matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i]) // it is like "if(a==b && b==c)"
            {
                /*if above condition satisfied then above 3 cells are winning cells and we need to store it's position for use it later*/
                short tempCellPosition[] = {0, i, 1, i, 2, i}; // all 3 cells position one by one respectively. See COMMENT BLOCK 1220 for details regarding data type should be used during initialization.
                for (int j = 0; j < 6; j++)                    // condition<6 because total number of cells for winning = 3 and each one have position(x,y). So, total required size = 3x2 = 6
                    positionOfWinningCells[j] = tempCellPosition[j];

                return true;
            }
        }

        /**Diagonal-Wise. for 7,8*/
        // we can simply write if(conditions) to do here. Because size is known 3x3. But if there will custom size of matrix then we must need to use loop. Currently, we are not using loop here. But we will use it later for further extension if required.
        /*we are checking the empty cell. If any of the cell in current diagonal is empty then there will no any possibility of winning & we will continue the loop to next iteration.*/
        if (isCellEmpty(0, 0) || isCellEmpty(1, 1) || isCellEmpty(2, 2))
        {
        } /*do nothing. Just we have to execute this block if condition satisfied that any of cell is empty. And it's not possible to win via this winning condition */ // we can't return false here because it may be possible that any below winning condition will satisfy.
        else if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2])                                                                                          // it is like "if(a==b && b==c)"
        {
            /*if above condition satisfied then above 3 cells are winning cells and we need to store it's position for use it later*/
            short tempCellPosition[] = {0, 0, 1, 1, 2, 2}; // all 3 cells position one by one respectively
            for (int j = 0; j < 6; j++)                    // condition<6 because total number of cells for winning = 3 and each one have position(x,y). So, total required size = 3x2 = 6
                positionOfWinningCells[j] = tempCellPosition[j];
            return true;
        }

        /*we are checking the empty cell. If any of the cell in current diagonal is empty then there will no any possibility of winning & we will continue the loop to next iteration.*/
        if (isCellEmpty(0, 2) || isCellEmpty(1, 1) || isCellEmpty(2, 0))
        {
            // empty
            /*see above 2nd comment for details*/
        }
        else if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0]) // it is like "if(a==b && b==c)"
        {
            /*if above condition satisfied then above 3 cells are winning cells and we need to store it's position for use it later*/
            short tempCellPosition[] = {0, 2, 1, 1, 2, 0}; // all 3 cells position one by one respectively
            for (int j = 0; j < 6; j++)                    // condition<6 because total number of cells for winning = 3 and each one have position(x,y). So, total required size = 3x2 = 6
                positionOfWinningCells[j] = tempCellPosition[j];
            return true;
        }

        /*if all conditions fails means no any of 8 winning conditions satisfied. So, No winning & as expected we will return false*/
        return false;
    }

    /*when user input command 1...9 to select a cell then this function will take that cellNumber (number from 1-9) and give the real postion of the cell by giving row index in 'i' and column index in 'j'*/
    void commandInterpreter(short cellNumber, short &i, short &j)
    {
        switch (cellNumber)
        {
        case 1:
            i = 0;
            j = 0;
            break;
        case 2:
            i = 0;
            j = 1;
            break;
        case 3:
            i = 0;
            j = 2;
            break;
        case 4:
            i = 1;
            j = 0;
            break;
        case 5:
            i = 1;
            j = 1;
            break;
        case 6:
            i = 1;
            j = 2;
            break;
        case 7:
            i = 2;
            j = 0;
            break;
        case 8:
            i = 2;
            j = 1;
            break;
        case 9:
            i = 2;
            j = 2;
            break;
        }
    }

    /*It's reverse working function of function commandInterpreter. Take arguments of rows and columns and returns the respective command i.e., cellNumber. If not found returns -1*/
    short reverseCommandInterpreter(short row, short column)
    {
        short cellNumber = 1;
        for (short i = 0; i < 3; i++)
        {
            for (short j = 0; j < 3; j++)
            {
                if (row == i && column == j)
                    return cellNumber;
                cellNumber++;
            }
        }
        return -1;
    }

    /*to input 'X' or 'O' from user in game. On success returns true else false */
    bool userTurn()
    {
        char cellNumber;      // store cell number (command)
        short tempCellNumber; // store cell number in integer (by subtracting 48 from character)
        short loopCounter = 0;
        bool isDisplayCleared = false; /*if screen get cleared due to any reason then this will be true else false*/
        while (true)
        {
            loopCounter++;
            if (loopCounter == 1 || isDisplayCleared) // this if() for user only and below 2 lines of code for both (user & developer as player)
            {
                if (isDisplayCleared) /*if display is cleared then we need to show menu, gamePad etc again*/
                {
                    displayCurrentGameInfoBlockMenu();
                    displayGamePad();
                }
                cout << "\033[38;5;51;3m\nWrite you cell choice: \033[38;5;99m(Press '#' to exit).\033[0m" << endl;
                // cout << "&'@' to clear the screen.)\033[0m" << endl;//for developers
                cout << "$ ";
                isDisplayCleared = false;
            }
            fflush(stdin);

            char cellNumber = getch();
            tempCellNumber = cellNumber - 48;
            general generalObj;
            /*now checking the conditions*/

            if (cellNumber == '#') /*if user wants to exit*/
            {
                cout << "#";
                return false;
            }
            else if (generalObj.isInRangeOf1to9(tempCellNumber))
            {
                cout << cellNumber;
                short i, j; // for row and column of cell selected by user
                commandInterpreter(tempCellNumber, i, j);
                /*we will first check that if the given cell is empty or not. If cell is empty then good and If already filled then it will error and user need to re-input the cellNumber*/
                if (!isCellEmpty(i, j)) // returns true if empty else false
                {
                    system("cls");
                    isDisplayCleared = true;
                    continue;
                }
                traceCellFillingInGame[globalTracingIndex++] = cellNumber; // global cell filling tracer for developers ease
                matrix[i][j] = userChar;                                   // assigning the userChar/playingCharacter in the selected cell
                break;
            }
            else
                continue; // if user select any random character/string/press enter which is not from any of command.

            // START OF 'CODE FOR PROGRAMMERS' (MEANS IF USER IS A PROGRAMMER)//
            //  for developers and execute only if need because it display error message if any invalid input entered. But in case of user, there will no error will be shown. If correct input given then only shown else input will discarded.//
            //   cellNumber = cin.get();
            //   tempCellNumber = cellNumber - 48; // converting character to respective integer for testing. (typeCasting not working. why?)

            // /*now checking the conditions*/
            // if (cellNumber == '\n') // if user pressed enter
            //     continue;
            // else if (cellNumber == '#')
            //     return false;
            // else if (cellNumber == '@')
            // {
            //     system("cls");
            //     displayGamePad();
            //     continue;
            // }
            // else if (tempCellNumber < 1 || tempCellNumber > 9) // cell number must be between 1 and 9
            // {
            //     cout << "\033[1;31m\nFatal Error: Invalid Cell Choice." << endl;
            //     cout << "\033[1;32mPlease select your choice again.\033[0m" << endl;
            // }
            // else
            // {
            //     /*now we have to interpret the command (cellNumber) to it's proper index to insert the playingCharacter in the matrix/GamePad*/
            //     short i, j; // for row and column of cell selected by user
            //     commandInterpreter(tempCellNumber, i, j);
            //     /*we will first check that if the given cell is empty or not. If cell is empty then good and If already filled then it will error and user need to re-input the cellNumber*/
            //     if (!isCellEmpty(i, j)) // returns true if empty else false
            //     {
            //         cout << "\033[1;31m\nFatal Error: Invalid Cell Choice." << endl;
            //         cout << "Selected cell '" << tempCellNumber << "' is already filled." << endl;
            //         cout << "\033[1;32mPlease select your choice again.\033[0m" << endl;
            //         continue;
            //     }
            //     matrix[i][j] = userChar; // assigning the userChar/playingCharacter in the selected cell
            //     break;
            // }
            // END OF CODE OF PROGRAMMERS FOR INPUT//
        }

        /**Fixed bug. fixed abnormal termination of game when user select any empty cell to fill (particularly for cell number 9)". I have found that control auto send false only incase of cell number 9 input by user else it returns true. But it's wrong. We have to explicitly mention the return statement.
         *this 'return true' is compulsory otherwise function return anything either true/false if programmer hasn't mentioned explicitly
         *and if function returns false then as coded in called function the program will be terminate by understanding that user want's to exit the game.
         */
        return true;
    }

    /*This function is for computerTurn. It take argument of 'row' and 'column' and assign the position of a random cell of matrix of Tic-Tac-Toe in the same.*/
    void easyLevelFunction(short &row, short &column)
    {
        easyLevel objEasy(matrix); // creating instance of nested class easyLevel and passing the address of matrix of this object as parameter of constructor because we don't have access to this object in nested function but we need to use the dataMember values (matrix/gamePad) in the nested class.
        objEasy.whichCellShouldFilled(row, column);
    }
    /*take argument of position(row, column) of cell and if the cell is filled by computer then returns true else false*/
    bool isCellFilledByComputer(short row, short column)
    {
        if (isCellFilled(row, column)) // if cell will filled then after we will check is it filled by computer or not.
        {
            if (matrix[row][column] == computerChar)
                return true;
            return false;
        }
    }

    /*take argument of position(row, column) of cell and if the cell is filled by user then returns true else false*/
    bool isCellFilledByUser(short row, short column)
    {
        if (isCellFilled(row, column)) // if cell will filled then after we will check is it filled by computer or not.
        {
            if (matrix[row][column] == userChar)
                return true;
            return false;
        }
    }

    /*returns random corner cellNumber on the basis number of times user played the game in current session. It does't check cell is filled or empty.
     *returns 1,7,3,9 on newGameNumber 1,2,3,4 respectively and repeat the same result till next 4 newGame.
     *If this function get called multiple times in same game then the same cellNumber will be returned.
     *See comment block "COMMENT BLOCK 4432" for more info.....
     */
    short randomCornerNumber()
    {
        general generalObj;
        if (generalObj.isInSumSeriesOfIt(numberOfTimesGamePlayed, 1, 5, 9))
            return 1;
        else if (generalObj.isInSumSeriesOfIt(numberOfTimesGamePlayed, 2, 6, 10))
            return 7;
        else if (generalObj.isInSumSeriesOfIt(numberOfTimesGamePlayed, 3, 7, 11))
            return 3;
        else if (generalObj.isInSumSeriesOfIt(numberOfTimesGamePlayed, 4, 8, 12))
            return 9;

        /*QUESTION: why 1,5,9 or 2,6,10 or 3,7,11 or 4,8,12 in above LOC of this function ?
         *Because we have only 4 corners i.e., 1,3,7,9 but user can play the game any number of times in current session.
         *And we have to send different corner cellNumber in starting of each new game in current session for better user experience. See "COMMENT BLOCK 4432" to know more about the same.
         *So, we have to repeat the return value from every 5th new game.
         *So, I have used the below logic to send different corner cellNumber in every new game. (repetition from every fifth new game)
         *new game 1 -> corner cell 1
         *new game 2 -> corner cell 7
         *new game 3 -> corner cell 3
         *new game 4 -> corner cell 9
         *new game 5 -> repetition as like newGame 1 again and so on........
         *As per repetition logic, the same cornerCell will be repeat on every 5th newGame.
         *So, 5th new game from current game = currentGameNumber + 4 = numberOfTimesGamePlayed + 4.
         *So, on above discussed basis,
         *cornerNumber 1 will be returned in game number 1,5(1+4),9(5+4),13(9+4) and so on...
         *cornerNumber 7 will be returned in game number 2,6(2+4),10(6+4),14(10+4) and so on...
         *cornerNumber 3 will be returned in game number 3,7(3+4),11(7+4),15(11+4) and so on...
         *cornerNumber 9 will be returned in game number 4,8(4+4),12(8+4),16(12+4) and so on...
         */
    }

    /*this function is used in Impossible level to restrict user to win the game.
     *If user already filled the mid position of matrix (1,1) then we need to fill corner as soon as possible to restrict the user to win.
     *There are four corners are in matrix.
     *1) cellNumber1 (0,0)
     *2) cellNumber3 (0,2)
     *3) cellNumber7 (1,0)
     *4) cellNumber9 (1,2)
     *this function try to fill any random corner of matrix if any of it is empty.
     *Takes argument of row and column for modifying the it's value to make it for corner filling.
     *returns true if corner filling is possible and row,column is modified to make it for corner filling else false.
     */
    bool fillAnyCornerOfMatrix(short &row, short &column)
    {

        /*Edit..........Start*/
        /**WHY THIS EDIT REQUIRED: COMMENT BLOCK 4432
         *Actually it's coded for better user experience if user play the game multiple times in the same session and selected the impossibleLevel.
         *Actually what was happening that, when user selected the cell(1,1) i.e., mid-mid cell in impossibleLevel then computer fills always the corner(0,0) as per the program in below for loop block.
         *The repetition of same cell filled by computer makes the game a little rubbish.
         *If we fill random corner cell i.e., any of cell 1,3,7 and 9 then there will no any effect on the restricting logic of impossibleLevel.
         *Then why not, write a new function or modify the function fillAnyCornerOfMatrix() to fill the random corner cell in at least starting of a new game by user in current session.
         *So, I have defined a function randomCornerNumber() which returns random corner cell on the basis number of times user played the game in current session.
         *this function is only for first time corner filling in every new game in current session. If called multiple time in same game then same cellNumber will return. and we have called it in every call of below function.
         */
        /*we have to use any logic to restrict execution of below 4 LOC after 1st call of this function because from 2nd call the randomCornerNumber() function returns same cell number and it will already filled and then we have to go to for() loop block to fill the corner which is empty.
         *It will increase the time complexity without any need. We have to restrict it by any good logic.
         */
        short corner = randomCornerNumber(); /*It will return same cellNumber if called more that once in same game. So, below 4 lines are useful only in first call of fillAnyCornerOfMatrix() in new game.*/
        commandInterpreter(corner, row, column);
        if (isCellEmpty(row, column))
            return true;
        /*Edit......End*/
        /*if returned cell by randomCornerNumber() is not empty means from the 2nd call of current function the below code will execute every times till end of the current game of this session*/

        /*we can use loop to automate the working for above 4 cell checking (1,3,7,9)*/
        for (short i = 0; i < 2; i++)
        {
            short j = 0;
            while (j <= 2)
            {
                if (isCellEmpty(i, j))
                {
                    row = i;
                    column = j;
                    return true;
                }
                j += 2; /*because we need only 0 and 2 in column*/
            }
        }
        return false;
    }

    /*returns true if any two diagonally opposite corners filled by user else false*/
    bool isDiagonallyOppositeCornersFilledByUser()
    {
        /*
         *Diagonally opposite of corner 1 is 9 and vice versa.
         *Diagonally opposite of corner 3 is 7 and vice versa.
         */
        /*
         *position of cellNumber1 = (0,0) && cell9 = (2,2)
         *position of cellNumber3 = (0,2) && cell7 = (2,0)
         */

        if (isCellFilledByUser(0, 0)) /*for cellNumber 1*/
        {
            if (isCellFilledByUser(2, 2)) /*for cellNumber 9 (diagonally opp. of 1)*/
                return true;
        }
        else if (isCellFilledByUser(0, 2)) /*for cellNumber 3*/
            if (isCellFilledByUser(2, 0))  /*for cellNumber 7 (diagonally opp. of 3)*/
                return true;
        return false; // if no condition satisfied
    }

    /*this function is related to special condition (double winning condition) named L-Shaped-2nd.
     *It returns true if both left and right cells of an empty corner is filled by user else false.
     *Takes argument of cornerCellNumber as reference and if returns true then cornerCellNumber contains required empty cornerCellNumber else no changes in it.
     */
    bool isLeftRightCellsOfAnyEmptyCornerFilledByUser(short &cornerCellNumber)
    {
        /*cornerCells are 1(0,0), 3(0,2),7(2,0) & 9(2,2)*/
        if (isCellEmpty(0, 0))
        {
            // left cell = 2(0,1)
            // right cell = 4(1,0)
            if (isCellFilledByUser(0, 1) && isCellFilledByUser(1, 0))
            {
                cornerCellNumber = reverseCommandInterpreter(0, 0);
                return true;
            }
        }
        if (isCellEmpty(0, 2))
        {
            // left cell = 2(0,1)
            // right cell = 4(1,2)
            if (isCellFilledByUser(0, 1) && isCellFilledByUser(1, 2))
            {
                cornerCellNumber = reverseCommandInterpreter(0, 2);
                return true;
            }
        }
        if (isCellEmpty(2, 0))
        {
            // left cell = 2(1,0)
            // right cell = 4(2,1)
            if (isCellFilledByUser(1, 0) && isCellFilledByUser(2, 1))
            {
                cornerCellNumber = reverseCommandInterpreter(2, 0);
                return true;
            }
        }
        if (isCellEmpty(2, 2))
        {
            // left cell = 2(2,1)
            // right cell = 4(1,2)
            if (isCellFilledByUser(2, 1) && isCellFilledByUser(1, 2))
            {
                cornerCellNumber = reverseCommandInterpreter(2, 2);
                return true;
            }
        }
        else
            return false;
    }

    /**This function list out the cells filled by user (by default) and see below for more info and changes possibles...
     *Take argument of an array (int*) and fill that cellNumber in it which is filled by user. And returns the total number of cells filled by user.
     *Take another argument named as 'limitCounter' (by default it is -1) and not in use. It is used if you want to limit counting of number of cells filled by user.
     *Means if you want to list only 3 filled user cellNumber then you can pass 3 in 'limitCounter' and whenever 3 cells found filled by user then the function returns with that 'limitCounter' and list contains number of cells = limitCounter.
     *If you don't pass anything to 'limitCounter' then by default all cells of matrix will be checked (till maxCellsCanFilledByUser) and list them out and returns the total cells filled by user.
     *if callingFunction passes limitCounter then ther is no need to store the returned number because it will same as passed value of limitCounter.
     */
    short listTheCellsFilledByUser(int *list, int limitCounter = -1)
    {
        short maxCellsCanFilledByUser = 5; /*maximum 5 cells can be filled by user if game draw else less*/
        short indexOfList = 0;
        for (short i = 0; i < 3; i++)
        {
            for (short j = 0; j < 3; j++)
            {
                if (isCellFilledByUser(i, j))
                {
                    list[indexOfList++] = reverseCommandInterpreter(i, j);
                    if (limitCounter > 0 && indexOfList == limitCounter) /*if calling function passed any limit to count the cell filled by user then we will count only those number of cells else traversal will be till maxCellCanFilledByUser or till end*/
                        break;
                    else if (indexOfList == maxCellsCanFilledByUser) // user can't fill cell greater than 5
                        break;
                }
            }
        }
        return indexOfList; // index of list = total number of cells filled.
    }

    /*returns true if passed cellNumber is a corner cell else false*/
    bool isACornerCell(short cellNumber)
    {
        /*(1/3/7/9) are the corner cells.*/
        if (cellNumber == 1 || cellNumber == 3 || cellNumber == 7 || cellNumber == 9)
            return true;
        return false;
    }

    /*returns true if passed cellNumber is a mid cell except cell(1,1) i.e., center else false*/
    bool isAMidCellExceptTheCenter(short cellNumber)
    {
        /*2/4/6/8 are the mid cells. (except cell(1,1))*/
        if (cellNumber == 2 || cellNumber == 4 || cellNumber == 6 || cellNumber == 8)
            return true;
        return false;
    }

    /*returns true if both received cellNumbers are of different rows and different columns else false.*/
    bool areBothCellsInDifferentRowsAndColumns(short cellNumber1, short cellNumber2)
    {
        short row1, column1, row2, column2; // to stores the position of received both. Indexing is proper as received.
        commandInterpreter(cellNumber1, row1, column1);
        commandInterpreter(cellNumber2, row2, column2);

        /*now we have the position of both received cells. If position doesn't match then both cells have different positions i.e., different row and column.*/
        if (row1 != row2)
        {
            if (column1 != column2)
                return true;
        }
        return false;

        /*keep in mind: different positions means different rows & different columns OR different rows & same columns OR same rows & different columns.
         *But in this function, it is explicitly said that different rows as well as different columns means completely different position. No common row or column is applicable.
         */
    }

    /*returns true if either row or column or both of cellNumber2 match with same of cellNumber1 then it returns true else false.*/
    bool isCellNumber2InSameRowOrColumnOfCellNumber1(short cellNumber1, short cellNumber2)
    {
        short row1, column1, row2, column2; // to stores the position of received both. Indexing is proper as received.
        commandInterpreter(cellNumber1, row1, column1);
        commandInterpreter(cellNumber2, row2, column2);

        /*now we have the position of both received cellNumbers. If either row or column or both match then cellNumber2 will in same row or column of cellNumber1 and we wil return true else false.*/
        if (row1 == row2 || column1 == column2)
            return true;
        return false;
    }

    /*take argument of 'midCellNumber' and returns any one cellNumber of 2 of it's adjacent cells.
     *It also takes an argument of exceptCellNumber and if user passes a cellNumber in it and
     *it will adjacent of passed midCell then it will not return and control will go for returning the 2nd one.
     *It will also not work for returning adjacent of center cell(1,1).
     *It will return only adjacent cells of mid cell (2,4,6,8).
     *returns -1 on any error or invalid midCellNumber.
     */
    short adjacentCellOfMidCellExceptCenter(short midCellNumber, short exceptCellNumber = -1)
    {
        /*ADJACENT CELLS OF MID CELLS:
         *for midCell = 2 --> 1 & 3
         *for midCell = 4 --> 1 & 7
         *for midCell = 6 --> 3 & 9
         *for midCell = 8 --> 7 & 9
         */
        if (midCellNumber == 2)
        {
            if (exceptCellNumber != 1)
                return 1;
            else
                return 3;
        }
        else if (midCellNumber == 4)
        {
            if (exceptCellNumber != 1)
                return 1;
            else
                return 7;
        }
        else if (midCellNumber == 6)
        {
            if (exceptCellNumber != 3)
                return 3;
            else
                return 9;
        }
        else if (midCellNumber == 8)
        {
            if (exceptCellNumber != 7)
                return 7;
            else
                return 9;
        }
        return -1; /*on error or invalid midCellNumber*/
    }

    /*if lShaped possible then returns true else false. If true then the desired cellNumber is assigned to received argument 'desiredCellNumber' by reference..*/
    bool isL_ShapedPossible(short &desiredCellNumber)
    {
        /*to create l_shaped possible 1st 2 cells must be filled as follow:
         *One should be on any corner.
         *And 2nd one should be in mid of row/column (not diagonal) but that cell should not be row and column of 1st selected corner.
         **The above 2 steps is compulsory but not mandatory to follow the sequence. User is independent to choose step 2 first then step 1 and vice versa also applicable. But The condition must be satisfied as written.
         *Above both 2 satisfies, then user need to fill, that corner cell which is adjacent to filled mid-cell but it must be in same row/column of the previously filled corner cell (here which is in 1st step).
         */
        int listOfUserFilledCells[2];                       // Here in l-shaped we will check only when 3 cells are filled in which 2 cells are filled by user and 1 by computer.
        listTheCellsFilledByUser(listOfUserFilledCells, 2); // we will not store the returned data because it will equal to passed 'limitCounter' which is 2 in this case.

        /*now we need to check the condition for l_shaped using both filledCells*/
        /*1. One cell must be a corner. (1/3/7/9).
          2. 2nd one must be a mid (not 1,1). (2/4/6/8).
          --> And both must not be in same row or same column.
         */
        /*if above condition satisfies, then we need to find that one cell (on the basis of both cells) which will be filled by user to create double winning condition and fill that cell before user to restrict him to create such condition.😂.
         *REQUIRED CELL: A corner Cell which is adjacent to midCell (means in same row or column of midCell) && in same row/column of 1stSelectedCornerCell (opposite corner of 1stCornerCell but not in diagonally opposite).
         */
        if (isACornerCell(listOfUserFilledCells[0])) /*cornerCell*/
        {
            if (isAMidCellExceptTheCenter(listOfUserFilledCells[1])) /*midCell*/
            {
                /*2 conditions satisfied then now we need to check that both cells (1 corner & 1 mid) must be at different rows as well as different columns.*/
                if (areBothCellsInDifferentRowsAndColumns(listOfUserFilledCells[0], listOfUserFilledCells[1]))
                {
                    short tempDesiredCellNumber = adjacentCellOfMidCellExceptCenter(listOfUserFilledCells[1]);
                    /*1. now one condition for desired cellNumber has been fulfilled that it should be adjacent of midCell.
                     *2. Now we will check 2nd conditions that the desiredCell should be in same row OR same column of the cornerFilledCell.*/
                    if (isCellNumber2InSameRowOrColumnOfCellNumber1(tempDesiredCellNumber, listOfUserFilledCells[0]))
                    {
                        desiredCellNumber = tempDesiredCellNumber;
                        return true;
                    }
                    else
                    {
                        /*this block executes means previous cellNumber which was one of 2 cells adjacent to midCell but it doesn't satisfied the 2nd condition which is it should be in same row or column of cornerFilledCell of user.*/
                        // now only one cell left which is adjacent to midCell. So, we will also receive it by below way:
                        tempDesiredCellNumber = adjacentCellOfMidCellExceptCenter(listOfUserFilledCells[1], tempDesiredCellNumber); // in this time we have except the previous received cell number which hasn't satisfied the 2nd condition. (And we have only 2 cells adjacent to mid one. So, It's last checking.)
                        /*current desiredCellNumber is only and only adjacent cell which is left and previous received cellNumber fails to satisfy the condition then it's 100% sure that it will satisfy the condition. So, I will not check it (because no other cell left adjacent to midCell) and return it to be filled by computer to restrict user.*/
                        desiredCellNumber = tempDesiredCellNumber;
                        return true;
                    }
                }
            }
        }
        else if (isAMidCellExceptTheCenter(listOfUserFilledCells[0])) /*midCell*/
        {
            if (isACornerCell(listOfUserFilledCells[1])) /*cornerCell*/
            {
                /*2 conditions satisfied then now we need to check that both cells (1 corner & 1 mid) must be at different rows as well as different columns.*/
                if (areBothCellsInDifferentRowsAndColumns(listOfUserFilledCells[1], listOfUserFilledCells[0]))
                {
                    short tempDesiredCellNumber = adjacentCellOfMidCellExceptCenter(listOfUserFilledCells[0]);
                    /*1. now one condition for desired cellNumber has been fulfilled that it should be adjacent of midCell.
                     *2. Now we will check 2nd conditions that the desiredCell should be in same row OR same column of the cornerFilledCell.*/
                    if (isCellNumber2InSameRowOrColumnOfCellNumber1(tempDesiredCellNumber, listOfUserFilledCells[1]))
                    {
                        desiredCellNumber = tempDesiredCellNumber;
                        return true;
                    }
                    else
                    {
                        /*this block executes means previous cellNumber which was one of 2 cells adjacent to midCell but it doesn't satisfied the 2nd condition which is it should be in same row or column of cornerFilledCell of user.*/
                        // now only one cell left which is adjacent to midCell. So, we will also receive it by below way:
                        tempDesiredCellNumber = adjacentCellOfMidCellExceptCenter(listOfUserFilledCells[0], tempDesiredCellNumber); // in this time we have except the previous received cell number which hasn't satisfied the 2nd condition. (And we have only 2 cells adjacent to mid one. So, It's last checking.)
                        /*current desiredCellNumber is only and only adjacent cell which is left and previous received cellNumber fails to satisfy the condition then it's 100% sure that it will satisfy the condition. So, I will not check it (because no other cell left adjacent to midCell) and return it to be filled by computer to restrict user.*/
                        desiredCellNumber = tempDesiredCellNumber;
                        return true;
                    }
                }
            }
        }
        return false; // no l_shaped possible.
    }

    /*to input 'X' or 'O' from computer in game. On success returns true else false*/
    bool computerTurn()
    {
        short row, column; // for row and column of selected cell

        /*Three levels of game 1. easy, 2. Medium, 3. Impossible*/
        /************EASY LEVEL*************/
        if (level == easy)
        {
            if (filledCells >= 4)
            {
                mediumLevel objMedium(matrix, computerChar);
                if (!objMedium.whichCellShouldFilledToMakeComputerWin(row, column))
                    easyLevelFunction(row, column);
            }
            else
                easyLevelFunction(row, column);
        }
        /************MEDIUM LEVEL*************/
        else if (level == medium)
        {
            if (filledCells >= 3) // because next winning condition only possible if 3 cells are filled (2 by user and 1 by computer because user has started the game.)
            {
                mediumLevel objMedium(matrix, computerChar); // creating instance of nested class mediumLevel and passing the address of matrix of this object as parameter of constructor because we don't have access to this object in nested function but we need to use the dataMember values (matrix/gamePad) in the nested class.
                /*we are taking temporarily 'i' and 'j' variables because we can't pass the reference of original 'row' & 'column'.
                 *If we pass the original 'row' and 'column' of this function to 'whichCellShouldFilled' function then if desired position not found,
                 *then 'row' and 'column' will contains (assigned by) wrong position. So, it's necessary to use temporary variables and if functions returns true then assign them to original 'row' and 'column'.
                 */
                short i;                                   // for temporary row
                short j;                                   // for temporary column
                if (objMedium.whichCellShouldFilled(i, j)) /*'whichCellShouldFilled() returns true if desired position found else false*/
                {
                    row = i;
                    column = j;
                }
                else
                    easyLevelFunction(row, column);
            }
            else
                easyLevelFunction(row, column);
        }
        /************IMPOSSIBLE LEVEL*************/
        else // if(level == impossible)
        {
            // cout << "Code not written for impossible level" << endl;
            // return false; // code not written yet

            mediumLevel objMedium(matrix, computerChar);
            bool isComputerVShapedPossible = false;

            if (filledCells < 3)
            {
                if (matrix[1][1] == userChar)
                {
                    fillAnyCornerOfMatrix(row, column);
                    /*it is guaranteed that above called function returns true because
                     *this block can only execute if filledCells<3 and
                     * if it is so then in worst scenario also 2 corners will be empty and it satisfy our requirements.
                     */
                }
                else
                {
                    /*if user has not filled the mid cell (1,1) then user will not able to create V shape in this game.
                     *And if V shaped not created then two winning conditions will never form. And user will never win the game.
                     *So, we are taking this opportunity to make computer char at mid position (1,1) and write the logic to make V shaped by computer and making computer to win the game.
                     */
                    row = 1;
                    column = 1;
                    isComputerVShapedPossible = true;
                }
            }
            /*we are checking most case in condition "filledCells=3" because when user filled 2 cells then user intension is visible about making 2 winning condition from any of 4 (v-shaped, expanded-l-shaped or l-shaped or l-shaped-2nd.). So, we are restring user on the basis of his filled 2 cells*/
            /*below is one special condition when only 3 cells are filled(2 by user and 1 by computer) in which user has filled the 2 diagonally opposite corners and computer has filled one mid(1,1) cell.*/
            else if (filledCells == 3 && matrix[1][1] == computerChar) // means mid-mid-Cell(1,1) is not filled by user. Means v-shaped not possible for user. So, he can use any of rest 2 double winning condition maker.
            {
                short desiredCellNumber; // used to store the desired cell number to fill in special condition 3 (l-shaped). L-shaped is very important & powerful.

                /*In this block, FilledCells is fixed i.e., 3 (2 by user and 1 by computer).
                 *And we have manipulate the 2 cells filled by user to estimate the user intention of making 2 winning conditions from any of rest 3 (expanded-l-shaped, l-shaped, l-shaped-2nd) (rest because in this block v-shape is not possible because cell(1,1) is filled by computer not by user. So, computer can use V-shape. We will think on it later.).
                 *And we have restrict user to making 2 winning conditions.
                 *If we don't restrict user just after filling 2 cells then whenever user will 3rd cell the 2 winning condition may create and computer lost the game.
                 *So, It's compulsory to restrict user and check all double winning condition and how to restrict the user to create it, only during 2 cells are filled by user.
                 */
                short cornerCellNumber; /* for special condition 3 to store cornerCellNumber modified by function isLeft....FilledByUser() if required conditions satisfied*/
                /*special condition(double winning condition) 2 (1 is v-shaped) if user has filled 2 diagonally opposite corners (Expanded-L-Shaped Logic). Expanded-L-shaped has 2 conditions: any of opposite corner should be filled (either in same row/column or in diagonal. But here we are same diagonal only because if userChar will filled in 2 cells then it will auto-restricted by whichCellShouldFill() function of medium level which is implement in else block of this if(filledCells==3).*/
                if (isDiagonallyOppositeCornersFilledByUser())
                {
                    /*why this special condition
                     *1) if 1st cell is filled by user is any of corner (1,3,7,9)
                     *2) And by default I have added in impossible level that if user don't select mid then computer will select mid. So, computerChar will be at cell(1,1) i.e., mid.
                     *3) this condition is only for if 3rd cell is filled by user is the diagonally opposite corner cell of 1st selected corner cell filled by user. (and as per 1st step of this comment one of corner is filled by user).
                     *if this block doesn't exist then by default as computer will fill any of rest corner cell as programmed in below 'elseif' block.
                     *and if done so, then computer will lost the game because of becoming 2 winning condition of user..
                     *and in this block we will restrict to make two winning condition of user by creating a winning condition of computer.
                     *
                     * THE EXAMPLE OF ABOVE IS FOLLOWING:
                     *1) user selected any of 1,3,7,9
                     *2) by default if user hasn't selected mid(1,1) then computer will select the cell(1,1) i.e., mid
                     *3) user select any of 9/7/3/1 which is diagonally opposite of the corner cell that user has selected any of 1/3/7/9 respectively in 1st step. (means in this step if user has selected diagonally opposite corner of the corner cell selected by user in 1st step.)
                     **if we don't restrict user to fill any corner cell in 5th filling then computer will lost the game because of becoming 2 winning conditions.
                     *So, we have to restrict user in this step (this is 4th cell filling step (2nd turn of computer)) in such a way that user will not fill any corner cell in next step(5th cell filling).
                     *And to restrict user to fill any corner in next step, we have to create winning situation of computer.
                     *And now we have to make winning condition for computer to restrict user to create 2 winning conditions for him/her.
                     **
                     *Now let's think about how to create winning situation of computer.
                     *We know that one computerChar is present in overall mid cell(1,1). So, we have many condition to create winning situation of computer.
                     *1. fill cell 2 to create winning situation 2,5,8 and user need to fill 8 to restrict computer and in this way, user unable to fill any corner and if done so then there will no any possibility of creating any 2 winning situation of userChar.
                     *2. fill cell 8 to create winning situation 2,5,8 and user need to fill 8 to restrict computer and in this way, user unable to fill any corner and if done so then there will no any possibility of creating any 2 winning situation of userChar.
                     *3. fill cell 4 to create winning situation 4,5,6 and user need to fill 8 to restrict computer and in this way, user unable to fill any corner and if done so then there will no any possibility of creating any 2 winning situation of userChar.
                     *4. fill cell 6 to create winning situation 4,5,6 and user need to fill 8 to restrict computer and in this way, user unable to fill any corner and if done so then there will no any possibility of creating any 2 winning situation of userChar.
                     *We can fill any of 2,8,4,6 because We know that all these 4 cells are empty till this case because only 3 cells are filled only (2 by user & 1 by computer) in which 2 cells filled by user will at any of 2 diagonally opposite corners (1&9 OR 3&7) and 1 cell is filled by computer which is cellNumber 5 i.e, mid cell(1,1).
                     */

                    /*Now on the basis of above discussed conditions, we(computer) will fill any of 2,8,4,6 cell.
                     *But we will use static int here, so that we trace the user who create this situation in current session of program and give different taste to user by filling different cell from 2,8,4,6 in each such situation. If user crates such situation more that 4 times then we again start from filling the 2nd cell.
                     */

                    static int traceUserVisit; /*Counter for current user creating such situation so it's necessary to use the codes of this block. It will always from 0 to 3 for 2,8,4 and 6 cellNumber respectively*/

                    if (traceUserVisit == 4)
                        traceUserVisit = 0;

                    if (traceUserVisit == 0)
                    {
                        commandInterpreter(2, row, column);
                        traceUserVisit++;
                    }
                    else if (traceUserVisit == 1)
                    {
                        commandInterpreter(8, row, column);
                        traceUserVisit++;
                    }
                    else if (traceUserVisit == 2)
                    {
                        commandInterpreter(4, row, column);
                        traceUserVisit++;
                    }
                    else if (traceUserVisit == 3)
                    {
                        commandInterpreter(6, row, column);
                        traceUserVisit++;
                    }
                }
                // /*special condition(double winning condition) 3 if user has filled one corner & one left/right of that corner. (L-Shaped). L-shaped has 2 conditions: */
                else if (isL_ShapedPossible(desiredCellNumber))
                {
                    commandInterpreter(desiredCellNumber, row, column);
                } // done
                /*special condition(double winning condition) 4 if user has filled left and right of a corner but that corner is empty. (L-Shaped-2nd)*/
                else if (isLeftRightCellsOfAnyEmptyCornerFilledByUser(cornerCellNumber))
                {
                    commandInterpreter(cornerCellNumber, row, column);
                }
                else
                {
                    if (!objMedium.whichCellShouldFilled(row, column)) // returns false if no winning/restricting condition found else true.
                    {
                        if (fillAnyCornerOfMatrix(row, column)) /*to restrict user to win the game because userChar is at mid position (1,1)*/
                        {
                            /*no need to write any code here. because row and column is already modified in 'fillCornerOfMatrix' function and in last 2nd line of this function the same is assign to the matrix.*/
                        }
                        else
                            easyLevelFunction(row, column);
                    }
                }
            }
            else if (!objMedium.whichCellShouldFilled(row, column)) // it returns false when no winning condition found else true if winning condition found and also make correct position of row & column to win computer or restrict user. It is recommended to call whichCellShouldFilled() function only if 3 cell are filled (2 by user and 1 by computer).
            {
                // if (isComputerVShapedPossible) /*to make computer to win the game because computerChar is at mid position (1,1)*/;

                //     tryToMakeVShapeForComputer(row, column);
                // else
                if (fillAnyCornerOfMatrix(row, column)) /*to restrict user to win the game because userChar is at mid position (1,1)*/
                {
                    /*no need to write any code here. because row and column is already modified in 'fillCornerOfMatrix' function and in last 2nd line of this function the same is assign to the matrix.*/
                }
                else
                    easyLevelFunction(row, column);
            }
        }

        /*============For All Levels==============*/
        traceCellFillingInGame[globalTracingIndex++] = 48 + reverseCommandInterpreter(row, column); // global cell filling tracer for developers ease. //+48 to convert the number to character to store in string.
        matrix[row][column] = computerChar;
        return true;
    }

    /*returns true if passed position(i,j) is the position of any one of 3 cells used in winning the game else returns false*/
    bool isPositionOfWinningCell(int i, int j)
    {
        /*Total 3 winning cells are possible and we have stored the position of all winning cells in array positionOfWinningCells[] in function isWonTheGame()
         *positionOfWinningCells[] = {x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5};
         */
        if (positionOfWinningCells[0] == i && positionOfWinningCells[1] == j)
            return true;
        else if (positionOfWinningCells[2] == i && positionOfWinningCells[3] == j)
            return true;
        else if (positionOfWinningCells[4] == i && positionOfWinningCells[5] == j)
            return true;
        return false;
    }

    /*To display the matrix/GamePad of Tic-Tac-Toe. This function can be used to display while playing and after won the game also. Pass 'true' in argument if you want to display after won else default argument is 'false' and no need to pass it.*/
    void displayGamePad(bool isWon = false)
    {
        short command = 1;
        for (int i = 0; i < 3; i++)
        {
            cout << "\t";
            for (int j = 0; j < 3; j++)
            {
                if (j == 1)
                    cout << "\e[1;32m |   \e[1;0m";

                /****cell character printing starts*/
                if (isCellEmpty(i, j))
                    cout << "\033[0m\033[38;5;236m\e[2m\e[3m" << command++ << "  \033[0m"; // initially 234m
                // cout << matrix[i][j] << "\033[0m\e[2m" << command++ << "  \033[0m";//initially, this code is used above but it prints extra space which hamper the cells uniform area
                else if (isWon == true && isPositionOfWinningCell(i, j)) // only execute when user/computer won the game.
                {
                    /*control will come inside this block only if user / computer won the game and the current cell position in loop = position of any one of the three winning cells*/
                    /*we already have the position of all 3 winning cells in the data member (array) positionOfWinningCells[]*/
                    /*adding different color for 'X' and 'O' along strikethrough because these cells are winning cells*/
                    if (matrix[i][j] == 'X')
                        cout << "\033[38;5;202m\033[9m\033[3m\033[4m\033[48;5;165m\033[38;5;232m" << matrix[i][j] << "\033[0m  ";
                    else if (matrix[i][j] == 'O')
                        cout << "\033[1;36m\033[9m\033[3m\033[4m\033[48;5;165m\033[38;5;232m" << matrix[i][j] << "  \033[0m";
                    command++; // as cell traversal increases the command for user 1...9 will increases
                }
                else // means cell is filled by user/computer input
                {
                    /*adding different color for 'X' and 'O'*/
                    if (matrix[i][j] == 'X')
                        cout << "\033[38;5;202m" << matrix[i][j] << "  \033[0m";
                    else if (matrix[i][j] == 'O')
                        cout << "\033[1;36m" << matrix[i][j] << "  \033[0m";
                    command++; // as cell traversal increases the command for user 1...9 will increases
                }
                /****cell character printing ends*/

                // cout << matrix[i][j] << ends;
                if (j == 1)
                    cout
                        << "\e[1;32m |  \e[1;0m";
            }
            cout << endl;
            if (i == 0 || i == 1)
                cout << "\e[1;32m--------------------------------\e[0m" << endl;
        }
    }

    /*returns the current game level in string object and all strings have same precision */
    string whatIsCurrentGameLevel()
    {
        string gameLevelInString;
        if (level == easy)
            gameLevelInString = "Easy      ";
        else if (level == medium)
            gameLevelInString = "Medium    ";
        else // if (level== impossible)
            gameLevelInString = "Impossible";
        return gameLevelInString;
    }

    /*Display the current game info like playing character of user, computer & game number, game level etc to user for ease in playing.
     *Edit: added argument named as 'isNeedToDisplayUserComputerTurn'. Means calling function can send false to hide the statics of computer-user turns in game else it will display.
     *Default value is true.
     */
    void displayCurrentGameInfoBlockMenu(bool isNeedToDisplayUserComputerTurn = true)
    {
        cout << "\033[38;5;238m******************************************************************" << endl;
        cout << "\033[38;5;238m*                  \033[38;5;101;3mYour Playing Character : " << userChar << "                    \033[38;5;238m*" << endl;
        cout << "\033[38;5;238m*                  \033[38;5;101;3mComputer Playing Character : " << computerChar << "                \033[38;5;238m*" << endl;
        cout << "\033[38;5;238m*                  \033[38;5;101;3mCurrent Game Level : " << whatIsCurrentGameLevel() << "               \033[38;5;238m*" << endl;
        if (numberOfTimesGamePlayed > 9) // if game played will be in 2 digits then design of square hamper. We can use printf("%02d",var) but I haven't use it because I don't want include whole stdio.h file in this program. So, I am managing spaces by checking this condition.
            cout << "\033[38;5;238m*                  \033[38;5;101;3mCurrent Game Number: " << numberOfTimesGamePlayed << "                       \033[38;5;238m*" << endl;
        else
            cout << "\033[38;5;238m*                  \033[38;5;101;3mCurrent Game Number: " << numberOfTimesGamePlayed << "                        \033[38;5;238m*" << endl;
        printf("\033[38;5;238m*                  \033[38;5;101;3mGame Played : %02d Times                        \033[38;5;238m*\n", numberOfTimesGamePlayed - 1);
        printf("\033[38;5;238m*                  \033[38;5;101;3mYou Won : %02d Times                            \033[38;5;238m*\n", userWonCounter);
        printf("\033[38;5;238m*                  \033[38;5;101;3mComputer Won : %02d Times                       \033[38;5;238m*\n", computerWonCounter);
        printf("\033[38;5;238m*                  \033[38;5;101;3mGame Draw : %02d Times                          \033[38;5;238m*\n", drawCounter);
        cout << "\033[38;5;238m******************************************************************";
        if (isNeedToDisplayUserComputerTurn)
        {
            cout << "\n\033[38;5;238m*********\033[38;5;149m\033[1m\033[3mGamePad After '" << filledCells / 2 << "' User Turn"
                 << " && '" << filledCells / 2 << "' Computer Turn\033[0m\033[38;5;238m*********\033[0m" << endl
                 << endl;
        }
    }

    /*supreme function to control all activities in the game. returns true on success else false on failure or exit without completion of game*/
    bool startGame()
    {
        /*0. first we need to ask the level of game user wants to play*/
        static int returnedValue; // static int because we don't want to take gameLevel from user in every newGame in current session. This will only execute if user will want else only once i.e., first time.
        if (restartNextNewGameWithNewGameConfiguration)
            returnedValue = gameLevelMenu(); // gameLevelMenu() returns -1 if user exits
        if (returnedValue == -1)
            return false;
        else if (returnedValue == 1)
            level = easy;
        else if (returnedValue == 2)
            level = medium;
        else // if(returnedValue==3)
            level = impossible;

        /*1. Now, we will ask user to select the playingCharacter 'X' or 'O'*/
        static char userCharStatic;                     /*to store the last time userSelectedChar in static way.*/
        if (restartNextNewGameWithNewGameConfiguration) /*for firs time or if user want to modify the game configuration*/
        {
            playingCharacterSelector();
            userCharStatic = userChar; /*If user has changes then we need to modify it*/
        }
        else
        {
            if (userCharStatic == 'O') // if userChar is 'O' then it will work else by default userChar is 'X' after creating every new object of ticTacToe(by default constructor)
            {
                userChar = 'O';
                computerChar = 'X';
            }
        }
        /*2. we need to display the command that will be used by user to select his/her cell to play*/
        if (restartNextNewGameWithNewGameConfiguration) /*The instruction menu will be displayed only once in one session or if user want.*/
        {
            displayCellInputInstructions();
            cout << "\033[38;5;159;1;3m" << endl;
            system("pause"); // pause the screen until user press any key
        }
        // cout << "\e[2J\e[H"; // clear the display and placed to cursor to position (0,0)
        system("cls"); // clear the display

        /*now game started*/
        bool wonFlag = false; // this is a flag to mark if any one won the game or not. By default it is false
        while (filledCells <= 9)
        {
            displayCurrentGameInfoBlockMenu(); /*to display the current game info like game number, playing character, gameLevel etc to user for him/her ease*/
            displayGamePad();
            if (userTurn())
            {
                filledCells++;
                if (filledCells > 4)
                    if (isWonTheGame(userChar))
                    {
                        system("cls");                     // clear the display
                        displayCurrentGameInfoBlockMenu(); /*to display the current game info like game number, playing character, gameLevel etc to user for him/her ease. User can share screenshot to any one also*/
                        displayGamePad(true);
                        cout << "\n\033[38;5;154m+=+=+=+=+=+=+=+=>>\033[38;5;201;3mCONGRATULATION, YOU WON THE GAME!\033[38;5;154m<<=+=+=+=+=+=+=+=+\033[0m" << endl;
                        wonFlag = true;
                        userWonCounter++;
                        traceCellFillingInGame[globalTracingIndex] = '\0'; /*Added Null Character to terminate the string if any one won the game*/
                        break;
                    }
                    /*COMMENT CODE 1021
                     *actually the person who started the game will end the game. Means here user will end the game by selecting the last empty cell.
                     *So, when last cell is filled by user then there is no cell left for computer turn.
                     *So, when filledCells==9 we have to break the loop.
                     *Control will come in below elif only if neither user nor computer won the game. Means when DRAW condition occurs.
                     */
                    else if (filledCells == 9)
                    {
                        system("cls");                          /*clearing the display after 1 round (1 turn for user and 1 turn for computer)*/
                        displayCurrentGameInfoBlockMenu(false); /*to display the current game info like game number, playing character, gameLevel etc to user for him/her ease. User can share screenshot to any one also*/
                        cout << "\n\033[38;5;238m*********\033[38;5;149m\033[1m\033[3mGamePad After '" << (filledCells / 2) + 1 << "' User Turn"
                             << " && '" << filledCells / 2 << "' Computer Turn\033[0m\033[38;5;238m*********\033[0m\033[0m" << endl
                             << endl;
                        displayGamePad(); // displaying the draw gamePad
                        break;            // breaking the loop because all cells are filled and no one won. (DRAW)
                    }
            }
            else
                return false; // user exit the game without completion

            // cout << "\n\033[38;5;190m******************************\033[38;5;201m\033[1m\033[3mGamePad After User Turn\033[0m\033[38;5;190m******************************\033[0m" << endl;
            if (computerTurn())
            {
                filledCells++;
                if (filledCells > 4)
                    if (isWonTheGame(computerChar))
                    {
                        system("cls");
                        displayCurrentGameInfoBlockMenu(); /*to display the current game info like game number, playing character, gameLevel etc to user for him/her ease. User can share screenshot to any one also*/
                        displayGamePad(true);
                        cout << "\n\033[38;5;154m+=+=+=+=+=>>\033[38;5;201;3mCOMPUTER WON THE GAME!\033[38;5;129m(Better Luck Next Time)\033[38;5;154m<<=+=+=+=+=+\033[0m" << endl;
                        computerWonCounter++;
                        wonFlag = true;
                        traceCellFillingInGame[globalTracingIndex] = '\0'; /*Added Null Character to terminate the string if any one won the game*/
                        break;
                    }
            }
            else
                return false; // computer exit the game without completion (written to execute only when codes of medium or impossible level are not completed (temporarily))
            // displayGamePad();
            system("cls"); /*clearing the display after 1 round (1 turn for user and 1 turn for computer)*/
        }                  /*end of while*/
        if (!wonFlag)      // if no one won the game then 'wonFlag' will be false and we have display the 'DRAW' status of the game
        {
            cout << "\n\033[38;5;154m=+=+=+=+=+=+=+=+=+=>>\033[38;5;201;3mDRAW!\033[38;5;129;3m(No One Won The Game)\033[38;5;154m<<=+=+=+=+=+=+=+=+=+=\033[0m" << endl;
            drawCounter++;
            traceCellFillingInGame[globalTracingIndex] = '\0'; /*Added Null Character to terminate the string if any one won the game*/
        }
        return true;
    }

public:
    /*constructor*/
    ticTacToe()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                matrix[i][j] = ' '; // adding space in each cell
        }

        computerChar = 'O'; // assigning by default value
        userChar = 'X';     // assigning by default value
        filledCells = 0;    // Initially, number of cells filled with 'X' or 'O' will by zero.

        /*assigning base value to the array positionOfWinningCells*/
        for (short i = 0; i < 6; i++)
            positionOfWinningCells[i] = 0;
    }

    /*destructor*/
    ~ticTacToe() {}

    bool start()
    {
        return startGame();
    }
};

/*main() function*/
int main()
{
    while (true)
    {
        globalTracingIndex = 0;    // assigned the index of global string object traceCellFillingINGame to 0 in every new game.
        numberOfTimesGamePlayed++; // increasing the counter which stores the number of times the game was played
        system("cls");
        {
            /*using block because after returning of control then object will be destroyed by destructor*/
            if (restartNextNewGameWithNewGameConfiguration) // can..continue.. variable returns true if continue the game with last game configuration else false.
            {
                allMenu menuObject;
                menuObject.welcomeMenu(true);
            }
            ticTacToe obj;
            if (!obj.start()) // start returns true after successful completion of game one times
                break;        // if start returns false means user want to exit the game.
            else
            {
                cout << "\n\033[38;5;154m--------------------------------------------------------------------\033[0m" << endl;
                cout << "\033[38;5;202;3;1m=> Press any key to continue to a new game with same configurations.\033[0m" << endl;
                cout << "\033[38;5;177m=> Press '@' to change configurations." << endl;
                cout << "\033[38;5;177m=> Press '#' to exit." << endl;
                cout << "\033[38;5;154m---------------------------------------------------------------------\033[0m" << endl;
                cout << "Write your choice:" << endl;
                cout << "$ ";
                // char choice = cin.get();
                char choice = getch(); // so user don't need to press enter. getch() is unbuffered and exit after reading single char.
                if (choice == '#')
                    break;
                else if (choice == '@')
                    restartNextNewGameWithNewGameConfiguration = true;
                else
                {
                    if (choice == '~') // to trace the cellFilling pattern For developers
                    {
                        traceCellFillingInGameFunction();
                        system("pause");
                    }
                    restartNextNewGameWithNewGameConfiguration = false;
                }
            }
        }
        if (restartNextNewGameWithNewGameConfiguration)
        {
            allMenu menuObject;
            if (menuObject.gameRestartMenu())
                continue;
            else
                break;
        }
    }
    displayTheGameStatistics();
    cout << "\n\033[38;5;51mTHANKS FOR USING TIC-TAC-TOE." << endl
         << "\033[38;5;128mSee you soon!" << endl
         << "Bye Bye........." << endl;
    cout << "\033[1;32mExited from main() successfully.\e[0m" << endl;
    system("pause");
}