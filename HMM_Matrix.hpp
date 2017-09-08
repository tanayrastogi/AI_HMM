#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

class HMMmatrix
{
private:
    vector< vector<float> > mtrx;
public:
    void  setHMMmatrix(vector<float> nmbrs, unsigned int row, unsigned int col, vector<float>:: iterator it);
    vector< vector<float> > getHMMmatrix();
    void  printHMMmatrix();
    void  clear_matrix();

};

void HMMmatrix::printHMMmatrix()
{
    for(vector<int>::size_type i = 0; i<mtrx.size(); i++)
        {
            for(vector<int>::size_type j = 0; j<mtrx[0].size(); j++)
                cout<< mtrx[i][j]<< "\t";
            cout<<"\n";
        }
}


void HMMmatrix::setHMMmatrix(vector<float> nmbrs, unsigned int row, unsigned int col, vector<float>:: iterator it)
{

    vector<float> temp(0);
    for(unsigned int i = 0; i<row; i++)
    {
        for(unsigned int j = 0; j<col; j++)
        {
            temp.push_back(*it);
            ++it;
        }
        mtrx.push_back(temp);
        temp.clear();
    }
}


vector< vector<float> > HMMmatrix::getHMMmatrix()
{
    return mtrx;
}

void HMMmatrix::clear_matrix()
{
    mtrx.clear();
}
