#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Model
{
    // Variable for the model
    float A[100][100];
    float B[100][100];
    float pi[100];

    //Variable to find the matrix dimension of A
    int a_row;
    int a_col;

    // Variables for parsing the file
    vector<float> numbers;

public:
    void read_file();
    void setA();
    float * getA();

};

// Get the value of transition matrix A
void Model::setA()
{
    vector<float>:: iterator it;

    //Row
    it = numbers.begin();
    a_row = *it;
    //Coloumn
    it = numbers.begin() + 1;
    a_col = *it;

    //Erase the first two entries
    numbers.erase(numbers.begin(), numbers.begin()+1);

    // Initialize the iterator for vector back to begin
    it = numbers.begin();

    for(int i=0; i<a_row; i++)
        for(int j=0; j<a_col; j++)
        {
            A[i][j] = *it;
            ++it;
        }

}

// Get the value of transition array
float * Model::getA()
{
    return A[a_row][a_col];
}


// Parse the input file and save the value into a vector
void Model::read_file()
 {

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

    cout << "\nNumbers:\n";

    for (unsigned int i=0; i < numbers.size(); i++)
    {
        cout << numbers[i] <<" ";
    }
}
