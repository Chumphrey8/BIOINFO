#include "Bio.h"//includes header file
#include <iostream>//cout //cin
#include <iomanip>//setw
#include <algorithm>//max()
using namespace std;
//constructor
BIO::BIO(const string& s1, const string& s2,int matchScore, int mismatchScore, int gapPenalty)//initializes default values
    {//default values set
    seq1 = s1;
    seq2 = s2;
    match = matchScore;
    mismatch = mismatchScore;
    gap = gapPenalty;
    matrix.resize(seq1.length() + 1,vector<int>(seq2.length() + 1, 0));//creates a resizable 2d matrix//plus 1 stores initialize gap penalites
    direction.resize(seq1.length() + 1,vector<char>(seq2.length() + 1, ' '));//storess the direction of where each value came from in the matrix
    path.resize(seq1.length() + 1,vector<bool>(seq2.length() + 1, false));//uses a boolean to determine which value to highlight for traceback path
}

void BIO::initializeMatrix(){//Fills the first row and column of the matrix with gap penalties
    matrix[0][0] = 0;//top left corner formatting
    direction[0][0] = '0';
    for (size_t i = 1; i <= seq1.length(); ++i){//first column
        matrix[i][0] = i * gap;//multiply the row index by gap penalty
        direction[i][0] = 'U';
    }
    for (size_t j = 1; j <= seq2.length(); ++j){//first row
        matrix[0][j] = j * gap;//multiply the row index by gap penalty
        direction[0][j] = 'L';
    }
}
void BIO::fillMatrix(){
    for (size_t i = 1; i <= seq1.length(); ++i){
        for (size_t j = 1; j <= seq2.length(); ++j){
           int scoreDiag = matrix[i - 1][j - 1];
if (seq1[i - 1] == seq2[j - 1]){
    scoreDiag += match;//add match score if characters match
}
else{
    scoreDiag += mismatch;//add mismatch penalty
}//add match score when letters are the same
            int scoreUp = matrix[i - 1][j] + gap;//scoreup aligns seq1 i-1 with gap in seq2
            int scoreLeft = matrix[i][j - 1] + gap;//scoreleft aligns seq2 i-1 with gap in seq1
            int best = max({scoreDiag, scoreUp, scoreLeft});//determines best possible score for each cell
            matrix[i][j] = best;//stores the movements of the matrix in order to allow for easier traceback later.
            if(best == scoreDiag)
                direction[i][j] = 'D';
            else if(best == scoreUp)
                direction[i][j] = 'U';
            else
                direction[i][j] = 'L';
        }
    }
}//diagonal scoring is ScoreDiag Aligns seq1 i-1 and seq2 i-2
//if matches add match score. if not add mismatch score
//matrix[i][j] = max({scoreDiag, scoreUp, scoreLeft}); chooses best score
int BIO::getAlignmentScore()const{
    return matrix[seq1.length()][seq2.length()];//returns the score at the bottom right of the matrix
}
void BIO::traceback(ofstream& outFile){//starts from th bottom right and starts the traceback process
    string aligned1 = "";//create empty strings
    string aligned2 = "";
    int matchCount = 0;//match counter
    int mismatchCount = 0;//mismatch counter
    int gapCount = 0;//gap counter
    int i = seq1.length();//start at bottom right then traceback
    int j = seq2.length();
    while (i > 0 || j > 0){//while not at position 0,0
        path[i][j] = true;//mark traceback path
        if(direction[i][j] == 'D'){
            char c1 = seq1[i - 1];
            char c2 = seq2[j - 1];
            aligned1 = c1 + aligned1;
            aligned2 = c2 + aligned2;
        if (c1 == c2)//if match
             matchCount++;//add to match counter
        else//if not match
            mismatchCount++;//add to mismatch counter
        i--;
        j--;
        }
        else if(direction[i][j] == 'U'){//gap in sequence 2
            aligned1 = seq1[i - 1] + aligned1;
        aligned2 = "-" + aligned2;
         gapCount++;//add to gap counter
        i--;
        }
        else{//gap in sequence 1
           aligned1 = "-" + aligned1;
        aligned2 = seq2[j - 1] + aligned2;
        gapCount++;//add to gap counter
        j--;
        }
    }
    path[0][0] = true;//each cell is marked in order to color it red to demostrate the traceback to the user
    outFile << "Alignment Score: " << getAlignmentScore() << endl << endl;//formatting for the output file
    outFile << "Best Possible Alignment:" << endl;
    outFile << "Matches: " << matchCount << endl;//displays matches
    outFile << "Mismatches: " << mismatchCount << endl;//displays mismatches
    outFile << "Gaps: " << gapCount << endl;//displays gaps
    outFile << aligned1 << endl;//outputs the best possible sequence
    outFile << aligned2 << endl;
}
void BIO::displayMatrix()const{//Prints the score matrix in a readable table.
     if(seq1.length() > 50 || seq2.length() > 50){//checks for matrices that are too large
    cout << "The Matrix is too large to display." << endl;
    return;
}
    cout << endl << "Needleman-Wunsch Matrix (Red = Traceback Path)" << endl << endl;//title of graph
    cout << setw(4) << " ";//aligns columns and prints column headers
    cout << setw(4) << "-";
    for(size_t j = 0; j < seq2.length(); ++j)//prints sequence 2 across the top
        cout << setw(4) << seq2[j];
    cout << endl;
    for(size_t i = 0; i <= seq1.length(); ++i){//loops through each row of the matrix
        if(i == 0)
            cout << setw(4) << "-";
        else
            cout << setw(4) << seq1[i - 1];//prints first sequence to label the rows
        for(size_t j = 0; j <= seq2.length(); ++j){// inner loop that goes through the columns
            if(path[i][j])
                cout << "\033[31m";//highlights traceback red
            char arrow;
            if(direction[i][j] == 'D') arrow = 'D';//determine direction
            else if(direction[i][j] == 'U') arrow = 'U';
            else if(direction[i][j] == 'L') arrow = 'L';
            else arrow = ' ';
            cout << setw(3) << matrix[i][j] << arrow;//print score
            if(path[i][j])
                cout << "\033[0m";//resets color
        }
        cout << endl;
    }
}