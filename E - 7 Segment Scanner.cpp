using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Solution
{
    static void Main(string[] args)
    {
        string line1 = Console.ReadLine();
        string line2 = Console.ReadLine();
        string line3 = Console.ReadLine();

        string upperDigit=" _     _  _     _  _  _  _  _ ";
        string midDigit  ="| |  | _| _||_||_ |_   ||_||_|";
        string lowerDigit="|_|  ||_  _|  | _||_|  ||_| _|";

        string output ="";

        int iLength= line1.Length/3;

        //Console.Error.WriteLine(iLength);

        for (int i=0; i<iLength;i++)
        {
            for(int j=0; j<10;j++)
            {
                if(
                    String.Equals(upperDigit.Substring(j*3,3), line1.Substring(i*3,3)) &&
                    String.Equals(midDigit.Substring(j*3,3), line2.Substring(i*3,3)) &&
                    String.Equals(lowerDigit.Substring(j*3,3), line3.Substring(i*3,3))      
                ) 
                {

                    //Console.Error.WriteLine("Found number :" + j);
                    output+=j;
                    break;
                }
            }
        }
        
        Console.WriteLine(output);
    }
}