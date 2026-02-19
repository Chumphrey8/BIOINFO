#ifndef Bio_H
#define Bio_H
#include <vector>
#include <string>
#include <fstream>
using namespace std;
//constructor
class BIO{//BIO class stores seq1, seq2, match number, int mismatch, int gap, and the parameters for the matrix
private:
    string seq1;
    string seq2;
    int match;
    int mismatch;
    int gap;
    vector<vector<int>> matrix;//used for matrix creation
    vector<vector<char>> direction;//stores where the scores came from
    vector<vector<bool>> path;//marks traceback path and usd fro changing the colors of the values in the matrix
public:
    BIO(const string& s1,const string& s2,//stores strings for seq1 and seq2
        int matchScore = 1,//penalities and scores
        int mismatchScore = -2,
        int gapPenalty = -2);
    void initializeMatrix();//Create the matrix and Fill first row and column with gap penalties
    void fillMatrix();//Fills the rest of the matrix and uses match, mismatch, and gap scoring
    void displayMatrix()const;//displays matrix
    void traceback(ofstream& outFile);//starts at bottom right and follows the direction arrows until it finds the final alignment then writes it to output.txt
    int getAlignmentScore()const;//returns the final alignment score
};
#endif