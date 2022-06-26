/*Tic-Tac-Toe Game using C++*/
/*User Vs Computer*/
/**
 *author: Suraj Kumar Giri.
 *Date: 21-06-2022
 *Time: 23:54:27
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
using namespace std;
int numberOfTimesGamePlayed; /*Global variable to count the number of times game played by user in the current session*/
class general
{
public:
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
};

class allMenu
{
    // static int userSelectedDefaultGameLevel;//we can't use static int as data member of class
public:
    /*welcome menu*/
    void welcomeMenu()
    {
        cout << "\e[2J\e[H";
        cout << "\e[1;31m************WELCOME TO TIC-TAC-TOE GAME.************" << endl;
        cout.width(63);
        cout << "\e[1;36mDeveloper: Suraj Kumar Giri\e[0m" << endl;
    }

    /*top block of gameRestartMenu which need to print repeatedly if user clear the screen*/
    void gameRestartMenuBlock()
    {
        cout << "\n\n\033[38;5;208m+++++++++++++++++++GAME RESTART MENU++++++++++++++++++++\033[0m" << endl;
        cout << "\033[38;5;201mDo you want to restart the game?" << endl
             << "\033[38;5;190m=> Press '1' or 'enter' to restart the game." << endl
             << "=> Press '#' to exit the game." << endl
             << "=> Press '@' to clear the display.\033[0m" << endl
             << "\033[38;5;159mWrite your choice:\033[0m" << endl;
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
            cout << "=> Press 'enter' for your last selected level (EASY)." << endl;
        else if (userSelectedDefaultGameLevel == 2)
            cout << "=> Press 'enter' for your last selected level (MEDIUM)." << endl;
        else // for gameLevel==3 for impossibleLevel
            cout << "=> Press 'enter' for your last selected level (IMPOSSIBLE)." << endl;

        cout << "=> Press '#' for exit game." << endl;
        cout << "=> Press '@' for clear the display.\033[0m" << endl;
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
                welcomeMenu(); // because this is 2nd menu after welcome menu. So, welcome menu should be visible along with it.
                continue;
            }
            else if (choice == '#')
                return -1; // if user exits the game
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
        /*take arguments of row and column and assign the desired position in passed row and column. Returns true if winning of computer/restricting of user condition found else false.
         *If returns true means winning/restring condition found and row,column contains desired position of cell to fill.
         *If false returns then passed row and column doesn't contains desired position of cell to fill. And to fill this you have to use another logic or easyLevel method. (Recommended to use another logic, which leads to win)
         */
        bool whichCellShouldFilled(short &row, short &column)
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
        mediumLevel(char matrix[][3])
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                    this->matrix[i][j] = matrix[i][j];
            }
            filledCellsCounter = 0; // assigning by default value of filled cells i.e., 0
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
            cout << "=> Press 'enter' for default ('X').\033[0m" << endl;
            char choice;
            cout << "$ ";
            fflush(stdin); // flushing the standard input stream's buffer
            choice = cin.get();

            if (choice == '\n') // if user has pressed 'enter' for default
                break;
            else
            {
                if (choice == '1') // means userChar='X' and by default it is same
                    break;
                else if (choice == '2')
                {
                    userChar = 'O';
                    computerChar = 'X';
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

    /*to input 'X' or 'O' from user in game. On success returns true else false */
    bool userTurn()
    {
        char cellNumber;      // store cell number (command)
        short tempCellNumber; // store cell number in integer (by subtracting 48 from character)
        while (true)
        {
            cout << "\033[38;5;51;3m\nWrite you cell choice: \033[38;5;99m(Press '#' to exit & '@' to clear the screen.)\033[0m" << endl;
            cout << "$ ";
            fflush(stdin);
            cellNumber = cin.get();
            tempCellNumber = cellNumber - 48; // converting character to respective integer for testing. (typeCasting not working. why?)

            /*now checking the conditions*/
            if (cellNumber == '\n') // if user pressed enter
                continue;
            else if (cellNumber == '#')
                return false;
            else if (cellNumber == '@')
            {
                system("cls");
                displayGamePad();
                continue;
            }
            else if (tempCellNumber < 1 || tempCellNumber > 9) // cell number must be between 1 and 9
            {
                cout << "\033[1;31m\nFatal Error: Invalid Cell Choice." << endl;
                cout << "\033[1;32mPlease select your choice again.\033[0m" << endl;
            }
            else
            {
                /*now we have to interpret the command (cellNumber) to it's proper index to insert the playingCharacter in the matrix/GamePad*/
                short i, j; // for row and column of cell selected by user
                commandInterpreter(tempCellNumber, i, j);
                /*we will first check that if the given cell is empty or not. If cell is empty then good and If already filled then it will error and user need to re-input the cellNumber*/
                if (!isCellEmpty(i, j)) // returns true if empty else false
                {
                    cout << "\033[1;31m\nFatal Error: Invalid Cell Choice." << endl;
                    cout << "Selected cell '" << tempCellNumber << "' is already filled." << endl;
                    cout << "\033[1;32mPlease select your choice again.\033[0m" << endl;
                    continue;
                }
                matrix[i][j] = userChar; // assigning the userChar/playingCharacter in the selected cell
                break;
            }
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

    /*to input 'X' or 'O' from computer in game. On success returns true else false*/
    bool computerTurn()
    {
        short row, column; // for row and column of selected cell

        /*Three levels of game 1. easy, 2. Medium, 3. Impossible*/
        /************EASY LEVEL*************/
        if (level == easy)
        {
            easyLevelFunction(row, column);
        }
        /************MEDIUM LEVEL*************/
        else if (level == medium)
        {
            if (filledCells >= 3) // because next winning condition only possible if 3 cells are filled (2 by user and 1 by computer because user has started the game.)
            {
                mediumLevel objMedium(matrix); // creating instance of nested class mediumLevel and passing the address of matrix of this object as parameter of constructor because we don't have access to this object in nested function but we need to use the dataMember values (matrix/gamePad) in the nested class.
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

            mediumLevel objMedium(matrix);
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
            /*below is one special condition when only 3 cells are filled(2 by user and 1 by computer) in which user has filled the 2 diagonally opposite corners and computer has filled one mid(1,1) cell.*/
            else if (filledCells == 3 && matrix[1][1] == computerChar && isDiagonallyOppositeCornersFilledByUser())
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
            else if (!objMedium.whichCellShouldFilled(row, column)) // it returns false when no winning condition found else true if winning condition found and also make correct position of row & column to win computer or restrict user.
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

    /*supreme function to control all activities in the game. returns true on success else false on failure or exit without completion of game*/
    bool startGame()
    {
        /*0. first we need to ask the level of game user wants to play*/
        short returnedValue = gameLevelMenu(); // gameLevelMenu() returns -1 if user exits
        if (returnedValue == -1)
            return false;
        else if (returnedValue == 1)
            level = easy;
        else if (returnedValue == 2)
            level = medium;
        else // if(returnedValue==3)
            level = impossible;

        /*1. Now, we will ask user to select the playingCharacter 'X' or 'O'*/
        playingCharacterSelector();
        /*2. we need to display the command that will be used by user to select his/her cell to play*/
        displayCellInputInstructions();
        cout << endl;
        system("pause"); // pause the screen until user press any key
        // cout << "\e[2J\e[H"; // clear the display and placed to cursor to position (0,0)
        system("cls"); // clear the display

        /*now game started*/
        bool wonFlag = false; // this is a flag to mark if any one won the game or not. By default it is false
        while (filledCells <= 9)
        {
            displayGamePad();
            if (userTurn())
            {
                filledCells++;
                if (filledCells > 4)
                    if (isWonTheGame(userChar))
                    {
                        system("cls"); // clear the display
                        displayGamePad(true);
                        cout << "\n\033[38;5;154m=+=+=+=+=+=+=+=+=+=+=+=+=>>\033[38;5;201;3mCONGRATULATION, YOU WON THE GAME!\033[38;5;154m<<=+=+=+=+=+=+=+=+=+=+=+=+=\033[0m" << endl;
                        wonFlag = true;
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
                        system("cls"); /*clearing the display after 1 round (1 turn for user and 1 turn for computer)*/
                        cout << "\n\033[38;5;190m********************\033[38;5;201m\033[1m\033[3mGamePad After '" << (filledCells / 2) + 1 << "' User Turn"
                             << " && '" << filledCells / 2 << "' Computer Turn\033[0m\033[38;5;190m*****************\033[0m" << endl;
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
                        displayGamePad(true);
                        cout << "\n\033[38;5;154m=+=+=+=+=+=+=+=+=>>\033[38;5;201;3mCOMPUTER WON THE GAME!\033[38;5;129m(Better Luck Next Time)\033[38;5;154m<<=+=+=+=+=+=+=+=+=\033[0m" << endl;
                        wonFlag = true;
                        break;
                    }
            }
            else
                return false; // computer exit the game without completion (written to execute only when codes of medium or impossible level are not completed (temporarily))
            // displayGamePad();
            system("cls"); /*clearing the display after 1 round (1 turn for user and 1 turn for computer)*/
            cout << "\n\033[38;5;190m********************\033[38;5;201m\033[1m\033[3mGamePad After '" << filledCells / 2 << "' User Turn"
                 << " && '" << filledCells / 2 << "' Computer Turn\033[0m\033[38;5;190m*****************\033[0m" << endl;
        }             /*end of while*/
        if (!wonFlag) // if no one won the game then 'wonFlag' will be false and we have display the 'DRAW' status of the game
            cout << "\n\033[38;5;154m=+=+=+=+=+=+=+=+=>>\033[38;5;201;3mDRAW!\033[38;5;129;3m(No One Won The Game)\033[38;5;154m<<=+=+=+=+=+=+=+=+=\033[0m" << endl;
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
        numberOfTimesGamePlayed++; // increasing the counter which stores the number of times the game was played
        system("cls");
        {
            /*using block because after returning of control then object will be destroyed by destructor*/
            allMenu menuObject;
            menuObject.welcomeMenu();
            ticTacToe obj;
            if (!obj.start()) // start returns true after successful completion of game one times
                break;        // if start returns false means user want to exit the game.
        }
        allMenu menuObject;
        if (menuObject.gameRestartMenu())
            continue;
        else
            break;
    }
    cout << "\n\033[38;5;51mTHANKS FOR USING TIC-TAC-TOE." << endl
         << "\033[38;5;128mSee you soon!" << endl
         << "Bye Bye........." << endl;
    cout << "\033[1;32mExited from main() successfully.\e[0m" << endl;
    system("pause");
}