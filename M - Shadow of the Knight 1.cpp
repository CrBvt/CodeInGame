#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

void WriteMovement(string bombDir);
void Up();
void Down ();
void Left ();
void Right ();
void CheckBomb();

long X;
long Y;

long X0;
long Y0;

double X_InnerBound;
double Y_InnerBound;
double X_OuterBound;
double Y_OuterBound;

long W; // width of the building.
long H; // height of the building.

long N; // maximum number of turns before game over.

bool flagU= false;
bool flagD= false;
bool flagL= false;
bool flagR= false;

string bombDir=""; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
string previousDir="";

int main()
{
    cin >> W >> H; cin.ignore();   
    cin >> N; cin.ignore(); 
    cin >> X >> Y; cin.ignore();

    X0=X;
    Y0=Y;

    X_InnerBound=0;
    Y_InnerBound=0;

    X_OuterBound=W-1;
    Y_OuterBound=H-1;

    string task= "Width : " + to_string(W) + " Height : " + to_string(H);

    cerr << task << endl;



    // game loop
    while (1) 
    {     
        cin >> bombDir; cin.ignore(); 
        
        cerr << "Current position " + to_string(X) + " " + to_string(Y) << endl;

        CheckBomb();
        WriteMovement(bombDir); 

        cerr << "Previous direction :" + previousDir  << endl;
        cerr << "Bomb direction : " + bombDir  << endl;

        

        previousDir = bombDir;  

        //if(flag) cerr << "Flag ON" << endl;
        //else     cerr << "Flag OFF" << endl;


        cerr << "X Inner Bound : " + to_string(X_InnerBound)  << endl;
        cerr << "X Outer Bound : " + to_string(X_OuterBound)  << endl;
        cerr << "Y Inner Bound : " + to_string(Y_InnerBound)  << endl;
        cerr << "Y Outer Bound : " + to_string(Y_OuterBound)  << endl;
        

        string movement = to_string(X) + " " + to_string(Y);

        // the location of the next window Batman should jump to.
        cout << movement << endl;
        
    }
}

void CheckBomb()
{
    flagU = false;
    flagD = false; 
    flagR = false;
    flagL = false;

    if((bombDir.find("U")!=-1) && (previousDir.find("D")!=-1)) flagU = true;
    if((bombDir.find("D")!=-1) && (previousDir.find("U")!=-1)) flagD = true;
    if((bombDir.find("R")!=-1) && (previousDir.find("L")!=-1)) flagR = true;
    if((bombDir.find("L")!=-1) && (previousDir.find("R")!=-1)) flagL = true;
}

 void WriteMovement(string bombDir)
 {

    double coordonate=0.0;

    if (bombDir.find("U")!=-1)
    {
        if (flagU) Y_InnerBound = Y0;
        Y0=Y;
        coordonate = (Y-Y_InnerBound)/2;
        Y-= ceil(coordonate);
    }
    else if (bombDir.find("D")!=-1)
    {
        if (flagD) Y_OuterBound = Y0;
        Y0=Y;
        coordonate = (Y_OuterBound-Y)/2;
        Y += ceil(coordonate); 

    }
    if (bombDir.find("R")!=-1)
    {
       if (flagR) X_OuterBound = X0;
       X0=X;
       coordonate = (X_OuterBound-X)/2;
       X += ceil(coordonate);

    }   
    else if (bombDir.find("L")!=-1)
    {
        if (flagL) X_InnerBound = X0;
        X0=X;
        coordonate = (X-X_InnerBound)/2;
        X -= ceil(coordonate);
    }
 }