#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

/////////////////////////STRUCT/////////////////

struct Card
{
    int owner;
    int cardId;
    int dx1;
    int dy1;
    int dx2;
    int dy2;
    int dx3;
    int dy3;
    int dx4;
    int dy4;
};

struct Action
{
    int cardID;
    string move;
};

struct Pawn
{
    int x,y;
    //int owner;
    int type;
};


///////////////////////DECLARATION//////////////////

int playerID;
int pID;
int pawnCount;

int owner;
int cardId;
int dx1;
int dy1;
int dx2;
int dy2;
int dx3;
int dy3;
int dx4;
int dy4;

int actionCount;
int choice;
int loggedActions;
string action="";

int commonBestMoveCardID;
int commonBestValue;
string commonBestMove;

string masterPosition="";

int Board[5][5];

//[Pawn][Move][Card]
string Results[10][4][5];
//[Pawn][Card]
int Best[5][5];
struct Card Cards[5];
struct Action Actions[100];
struct Pawn Pawns[10];

void ParseBoard (string board, int line);
void Reset();
void ParseCard(int cardNumber);
void ParseAction(int actionNumber);
void RegisterPawn(int pawnID,int pawnType,int x,int y);
void ComputeCard(int pawnID, int cardNumber);
void ComputeMove(int pawnID, int cardNumber, int move, int dy, int dx);

string RandomAction();
string Convert();
string ConvertX(int x);
string ConvertY(int y);

//=============================== DEFINITION///////////////////////////////

string ConvertX(int x)
{
    if(x==0) return "A";
    if(x==1) return "B";
    if(x==2) return "C";
    if(x==3) return "D";
    if(x==4) return "E";

    return "";
}

string ConvertY(int y)
{
    if(y==0) return "5";
    if(y==1) return "4";
    if(y==2) return "3";
    if(y==3) return "2";
    if(y==4) return "1";

    return "";
}

string Convert()
{
    if(commonBestValue>0) return to_string(commonBestMoveCardID) + " " + commonBestMove + " Value : " + to_string(commonBestValue);
    else return RandomAction();
}   

void RegisterPawn(int pawnType, int y,int x)
{    
    Pawns[pawnCount].y=y;
    Pawns[pawnCount].x=x;
    Pawns[pawnCount].type=pawnType;
    //Pawns[pawnID].owner=owner;

    if(pawnType * pID ==-2)
    {
        masterPosition= ConvertX(x) + ConvertY(y);
    }

    cerr << " Pawn " + to_string(pawnCount) + " : " + ConvertX(x) + ConvertY(y)  << endl;

    pawnCount++;

}

void ComputeMove(int pawnID, int cardNumber, int move, int dy, int dx)
{
    if(dx==0 && dy==0) return;

    cerr << "Computing move " + to_string(move)<< endl;

    int ry, rx, value;

    cerr << "Pawn at [" + to_string(Pawns[pawnID].y) + "][" + to_string(Pawns[pawnID].x) +"] / " 
        + ConvertX(Pawns[pawnID].x) + ConvertY(Pawns[pawnID].y)<< endl;
    cerr << "Y Movement :" + to_string(dy) + " X Movement :" + to_string(dx) << endl;

    ry = Pawns[pawnID].y + (dy *-1);
    rx = Pawns[pawnID].x + (dx);


    if(!(rx<5 && ry<5 && rx>=0 && ry>=0)) return;

    cerr << "Value at Board[" + to_string(ry)+ "][" + to_string(rx)  + "] / "
    +  ConvertX(rx) + ConvertY(ry) + " is " + to_string(Board[ry][rx]) << endl;

    value = Board[ry][rx]*pID;

    if (value>0)
    {
        Results[pawnID][move-1][cardNumber]=to_string(value) + " " +  ConvertX(Pawns[pawnID].x) + ConvertY(Pawns[pawnID].y) + ConvertX(rx) + ConvertY(ry);    
        cerr << "==========ADDING :" + Results[pawnID][move-1][cardNumber] << endl; 
    }

    
}

void ComputeCard(int pawnID, int cardNumber)
{

    cerr << "Computing Card " + to_string(Cards[cardNumber].cardId) + " for pawn n°" + to_string(pawnID) +
    " at " + ConvertX(Pawns[pawnID].x) +  ConvertY(Pawns[pawnID].y)  <<  endl;

    ComputeMove(pawnID,  cardNumber, 1, Cards[cardNumber].dy1, Cards[cardNumber].dx1);
    ComputeMove(pawnID,  cardNumber, 2, Cards[cardNumber].dy2, Cards[cardNumber].dx2);
    ComputeMove(pawnID,  cardNumber, 3, Cards[cardNumber].dy3, Cards[cardNumber].dy3);
    ComputeMove(pawnID,  cardNumber, 4, Cards[cardNumber].dy4, Cards[cardNumber].dx4);
}

string RandomAction()
{
    int choice = rand()/(RAND_MAX + 1u/loggedActions);
    return to_string(Actions[choice].cardID) + " " + Actions[choice].move + " Random choice";

}

void ParseAction(int actionNumber)
{
    Actions[actionNumber].cardID = cardId;
    Actions[actionNumber].move = action;
}

void ParseCard(int cardNumber)
{
    Cards[cardNumber].cardId = cardId;
    Cards[cardNumber].owner = owner;
    Cards[cardNumber].dx1 = dx1;
    Cards[cardNumber].dx2 = dx2;
    Cards[cardNumber].dx3 = dx3;
    Cards[cardNumber].dx4 = dx4;
    Cards[cardNumber].dy1 = dy1;
    Cards[cardNumber].dy2 = dy2;
    Cards[cardNumber].dy3 = dy3;
    Cards[cardNumber].dy4 = dy4;



    cerr << "CardID : " + to_string(cardId) << endl <<
        " X1 : " + to_string(dx1) + " Y1 : " + to_string(dy1) << endl <<
        " X2 : " + to_string(dx2) + " Y2 : " + to_string(dy2) << endl <<
        " X3 : " + to_string(dx3) + " Y3 : " + to_string(dy3) << endl <<
        " X4 : " + to_string(dx4) + " Y4 : " + to_string(dy4) << endl;
}

void ParseBoard (string board, int line)
{
    for (int j=0; j<5; j++)
    {

        if (board.substr(j,1).find('.')!=-1) Board[line][j] = 0;    
        else if (board.substr(j,1).find('W')!=-1)
        {
            Board[line][j] = -2;
            RegisterPawn(-2, line, j);
        } 
        else if (board.substr(j,1).find('w')!=-1)
        {
            Board[line][j] = -1; 
            RegisterPawn(-1, line,j); 
        }       
        else if (board.substr(j,1).find('B')!=-1)
        {
            Board[line][j] = 2; 
            RegisterPawn(2, line, j);  
        } 
        else if (board.substr(j,1).find('b')!=-1)
        {
            Board[line][j] = 1;
            RegisterPawn(1, line, j);
        } 
    }



}

void Reset()
{
    memset(Board, 0, sizeof(Board));
    memset(Cards, 0, sizeof(Cards));
    memset(Actions, 0, sizeof(Actions));
    memset(Best, 0, sizeof(Best)); 
    memset(Pawns, 0 , sizeof(Pawns));  


    for (int i=0; i<10 ; i++)
    {
        for (int j=0; j<4;j++)
        {
            for (int k=0 ; k<5;k++)
            {
                Results[i][j][k]="";
            }
        }
    }

    commonBestMoveCardID=-1;
    commonBestValue=0;
    commonBestMove="";
    pawnCount=0;
    loggedActions=0;

}


////////////////////////////////////MAIN////////////////////////////////////////////////

int main()
{  
    cin >> playerID; cin.ignore();

    if(playerID==0) pID = 1;
    else            pID = -1;

    cerr << "Player ID = " + to_string(playerID) << endl;

    //LOOP
    while (1) 
    {
        Reset();

        //==================================== GET BOARD
        for (int i = 0; i < 5; i++) 
        {
            string board;
            getline(cin, board);
            ParseBoard(board, i);

            //Display Board and Board matrix in error feed.
            //cerr << board << endl;
            //cerr << to_string(Board[i][0]) + to_string(Board[i][1]) + to_string(Board[i][2]) +
             //   to_string(Board[i][3]) + to_string(Board[i][4]) << endl;
        }

        //cerr << endl << "Master is at : " + masterPosition <<  endl << endl;

        //Shrines
        //Board[0][2]=2;
        //Board[4][2]=-2;


        cerr << "Pawn Count : " + to_string(pawnCount) << endl << endl;

        //================================================GET CARDS
        for (int i = 0; i < 5; i++) 
        {     
            cin >> owner >> cardId >> dx1 >> dy1 >> dx2 >> dy2 >> dx3 >> dy3 >> dx4 >> dy4; cin.ignore();
            ParseCard(i);
        }

        //=================================================LOG ALL POSSIBLE ACTIONS
        cin >> actionCount; cin.ignore();

        for (int i = 0; i < actionCount; i++) 
        {
            cin >> cardId >> action; cin.ignore();

            if(action.substr(0,2).compare(masterPosition)==0) continue;

            ParseAction(loggedActions);
            loggedActions++;
        }   

        //====================================================COMPUTE EVERY MOVE
        for (int i=0; i < 5; i++)
        {
            if (Cards[i].owner!=playerID) continue;     
           
            for (int j=0;j<pawnCount;j++)
            {
                if (Pawns[j].type*pID<0) ComputeCard(j,i);
            }         
        }   

        
        //===================================================FIND BEST MOVE
        //Cards
        for(int c=0; c<5;c++)
        {
            if (Cards[c].owner!=playerID) continue;   

            //Pawn
            for(int i=0; i<10;i++)
            {
            //int best=0;
            //int bestMove=0;

                if(Pawns[i].type*pID>0) continue;

                //Move
                for (int j=0; j<4;j++)
                {
                    if(Results[i][j][c].compare("")==0) continue;

                    cerr<< Results[i][j][c] << endl;

                    if(stoi(Results[i][j][c].substr(0,1)) > commonBestValue)
                    {
                        commonBestValue = stoi(Results[i][j][c].substr(0,1));
                        commonBestMoveCardID = Cards[c].cardId;
                        commonBestMove= Results[i][j][c].substr(2,4);
                    } 

                    /*if(stoi(Results[i][j][c].substr(0,1)) > best)
                    {
                        best = stoi(Results[i][j][c].substr(0,1));
                        bestMove = j;
                    } 

                    Best[i][c]=j;*/

                
                }
            }
        }

        cout << Convert() << endl;
    }
}