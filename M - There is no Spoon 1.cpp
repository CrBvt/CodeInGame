#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/

int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();

    int size = width*height;
    string line ="";
    
    cerr << "Width : " + to_string(width) + " Height : " + to_string(height) << endl;

    int matrix[height][width] ;
    string output[size];

    cerr << "Création de la matrice" << endl;

    //Création de la matrice
    for(int h=0 ; h<height ; h++)
    {
        getline(cin, line); // width characters, each either 0 or .

        cerr << "Height : " + to_string(h) + " = " + line << endl;

        for(int w=0 ; w<width ; w++)
        {
            string unit = line.substr(w,1);

            if(unit.find('0')!=-1) matrix[h][w]=1;
            else matrix[h][w]=0;
        }

    }

    cerr << "Envoie des données" << endl;

    int i=0;

    for(int h=0 ; h<height ; h++)
    {
        for(int w=0 ; w<width ; w++)
        {
            if (matrix[h][w]==1)
            {
                output[i]+=to_string(w) + " " + to_string(h);

                int wSearch = w;
                int hSearch = h;
                bool found;


                found = false;
                while(wSearch<width-1)
                {
                    wSearch++;

                    if(matrix[h][wSearch]==1) 
                    {
                        output[i]+=" " + to_string(wSearch) + " " + to_string(h);
                        found =true;
                        break;
                    }
                }

                if(!found) output[i]+=" -1 -1";
                
                found = false;
                while(hSearch<height-1)
                {
                    hSearch++;

                    if(matrix[hSearch][w]==1) 
                    {
                        output[i]+=" " + to_string(w) + " " + to_string(hSearch);
                        found =true;
                        break;
                    }
                }

                if(!found) output[i]+=" -1 -1";

                i++;
            }  
        }
    }

    for (int j=0 ; j<i+1 ; j++)
    {
       cout << output[j] << endl;
    } 
      
}