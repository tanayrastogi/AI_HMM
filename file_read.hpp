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
    //Variable to find the matrix dimension of B
    int b_row;
    int b_col;

    // Variables for parsing the file
    vector<float> numbers;

public:
    void read_file();
    void setA();
    float **getA();

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

//    // Original vector
//    cout<<"\nOriginal Vector: ";
//    for(it = numbers.begin(); it!= numbers.end(); ++it)
//        cout<<*it<<" ;";

    //Erase the first two entries
    numbers.erase(numbers.begin(), numbers.begin()+2);

    // Initialize the iterator for vector back to begin
    it = numbers.begin();

    // To see what number are in vector after deletion
//    cout<<"\nVector after deletion: ";
//    for(it = numbers.begin(); it!= numbers.end(); ++it)
//        cout<<*it<<" ";

    for(int i=0; i<a_row; i++)
        for(int j=0; j<a_col; j++)
        {
            A[i][j] = *it;
            ++it;
        }

    // Clear out the vector with values of A
    numbers.erase(numbers.begin(), numbers.begin()+16);

    // To see what number are in vector after deletion
//    cout<<"\n\nVector after deletion of A: ";
//    for(it = numbers.begin(); it!= numbers.end(); ++it)
//        cout<<*it<<" ;";
}

// Get the value of transition array
float** Model::getA()
{
    float** array2D = 0;
    array2D = new float*[a_row];

    for (int i=0; i<a_row; i++)
    {
        array2D[i] = new float[a_col];
        for(int j=0; j<a_col; j++)
            array2D[i][j] = A[i][j];
    }

    return array2D;
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

    // Just to see what number the vector stored
    /*cout << "\nNumbers:\n";
    for (unsigned int i=0; i < numbers.size(); i++)
    {
        cout << numbers[i] <<" ";
    }*/
}
