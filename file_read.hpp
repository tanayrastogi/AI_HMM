#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<float> read_file();

//vector<float> numbers;

class HMMmatrix
{
private:
    float mtrx[100][100];
    int   row, col;
public:
    void  setHMMmatrix(vector<float> nmbrs);
    float **getHMMmatrix();
    void  printHMMmatrix();

};

void HMMmatrix::printHMMmatrix()
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            cout<<getHMMmatrix()[i][j]<<"\t";
        }
        cout<<"\n";
    }
}

void HMMmatrix::setHMMmatrix(vector<float> nmbrs)
{

    vector<float>:: iterator it;

    //Row
    it = nmbrs.begin();
    row = *it;
    //Column
    it = nmbrs.begin() + 1;
    col = *it;

    //Erase the first two entries
    nmbrs.erase(nmbrs.begin(), nmbrs.begin()+2);

    // Initialize the iterator for vector back to begin
    it = nmbrs.begin();


    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            mtrx[i][j] = *it;
            ++it;
        }
    }
    // Clear out the vector with values of A
    nmbrs.erase(nmbrs.begin(), nmbrs.begin()+(row*col));
}

float** HMMmatrix::getHMMmatrix()
{
    float** array2D = 0;
    array2D = new float*[row];

    for (int i=0; i<row; i++)
    {
        array2D[i] = new float[col];
        for(int j=0; j<col; j++)
            array2D[i][j] = mtrx[i][j];
    }

    return array2D;
}

// This method is outside of the HMMmatrix class
vector<float> read_file()
 {
    // Variables for parsing the file
    vector<float> numbers;
	fstream fp;
    float innum;

    fp.open("sample_00.in");

    if(fp.is_open())
    {
        cout<< "\nThe File is open";
        while(fp >> innum)
            numbers.push_back(innum);

    }
    fp.close();
    return numbers;
}
