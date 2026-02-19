#include <iostream>
#include <fstream>
#include "BIO.h"
using namespace std;
int main(){
    string sequence1;//creates two string elements
    string sequence2;
    ifstream inFile("input.txt");
    if(inFile.is_open()){//checks if input file exists
        cout << "Reading sequences from input.txt..." << endl;
     string line;//uses this string to read from input file
     string current = "";

    while (getline(inFile, line)){//read file line by line
          if(!line.empty() && line.back() == '\r')//solves the windows /r that counts as a character which kept adding another row to the input file
        line.pop_back();
       if(line.empty())continue; //checks for empty lines in th input file
    if(line[0] == '>') continue; //input file should have >seq1 then the >seq1 on next line thn line 3 is >seq2 and then the sequence
    if(sequence1.empty())
        sequence1 += line;//first sequence goes into sequence 1
    else
        sequence2 += line;//second sequence goes into sequence 2
    }
        if(sequence1.empty() || sequence2.empty()){//if one sequence is missing print an error message
            cout << "Error: input.txt must contain two sequences." << endl;
            return 1;
        }
        inFile.close();
    }
    else{//if file doesn't exist
        cout << "No input file found.\n";//prompt user if no input file is found
        cout << "Enter first sequence: ";//displays for user to put in first sequence
        cin >> sequence1;
        cout << "Enter second sequence: ";//displays for second sequence
        cin >> sequence2;
    }
    ofstream outFile("output.txt");//creates output file
    if(!outFile.is_open()){//makes sre output.txt is opened
        cout << "Error: Could not create output.txt" << endl;
        return 1;
    }
    BIO alignment(sequence1, sequence2);//creates an object of alignment in the BIO constructor this allows
    //it to score the matrix and allow for penalties of gaps and mismatches
    alignment.initializeMatrix();//runs the algorithm
    alignment.fillMatrix();//calls the fillmatrix
    alignment.traceback(outFile);//reconstructs ther best alignment and writes it into the output.txt
    alignment.displayMatrix();//calls the displaymatrix
    cout << endl <<"Alignment Score: " << alignment.getAlignmentScore() << endl;//prints the final score
    cout << "Results written to output.txt" << endl;//inform the user where the results are stored at
    outFile.close();//closes outputfile
    return 0;//ends program
}