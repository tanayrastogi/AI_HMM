#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Model
{
    // Variable for the model
    float A[100][100];
    float B[100][100];
    float pi[100][100];

    //Variable to find the matrix dimension of A
    int a_row;
    int a_col;
    //Variable to find the matrix dimension of B
    int b_row;
    int b_col;
    //Variable to find the matrix dimension of pi
    int pi_row;
    int pi_col;

    // Variables for parsing the file
    vector<float> numbers;

public:
    void read_file();
    void setA();
    void setB();
    void setPi();
    float **getA();
    float **getB();
    float **getPi();

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
    numbers.erase(numbers.begin(), numbers.begin()+(a_row*a_col));

    // To see what number are in vector after deletion
//    cout<<"\n\nVector after deletion of A: ";
//    for(it = numbers.begin(); it!= numbers.end(); ++it)
//        cout<<*it<<" ;";
}

// Get the value of transition matrix B
void Model::setB()
{
    vector<float>:: iterator it;

    //Row
    it = numbers.begin();
    b_row = *it;
    //Coloumn
    it = numbers.begin() + 1;
    b_col = *it;

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

    for(int i=0; i<b_row; i++)
        for(int j=0; j<b_col; j++)
        {
            B[i][j] = *it;
            ++it;
        }

    // Clear out the vector with values of A
    numbers.erase(numbers.begin(), numbers.begin()+(b_row*b_col));

    // To see what number are in vector after deletion
//    cout<<"\n\nVector after deletion of A: ";
//    for(it = numbers.begin(); it!= numbers.end(); ++it)
//        cout<<*it<<" ;";
}

// Get the value of transition matrix Pi
void Model::setPi()
{
    vector<float>:: iterator it;

    //Row
    it = numbers.begin();
    pi_row = *it;
    //Coloumn
    it = numbers.begin() + 1;
    pi_col = *it;

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

    for(int i=0; i<pi_row; i++)
        for(int j=0; j<pi_col; j++)
        {
            pi[i][j] = *it;
            ++it;
        }

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

// Get the value of observation array
float** Model::getB()
{
    float** array2D = 0;
    array2D = new float*[b_row];

    for (int i=0; i<b_row; i++)
    {
        array2D[i] = new float[b_col];
        for(int j=0; j<b_col; j++)
            array2D[i][j] = B[i][j];
    }

    return array2D;
}

// Get the value of observation array
float** Model::getPi()
{
    float** array2D = 0;
    array2D = new float*[pi_row];

    for (int i=0; i<pi_row; i++)
    {
        array2D[i] = new float[pi_col];
        for(int j=0; j<pi_col; j++)
            array2D[i][j] = pi[i][j];
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
