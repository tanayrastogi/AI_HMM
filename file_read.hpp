#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Model
{
    int A[100][100];
    int B[100][100];
    int pi[100];
    vector<float> numbers;
public:
    void read_file();

};

void Model::read_file()
 {

	fstream fp;
    float innum;

    fp.open("sample_00.in");

    if(fp.is_open())
    {
        cout<< "\nThe File is open";
        while(fp >> innum)
        {
            cout <<"\nNumbr read";
            numbers.push_back(innum);
        }
    }
    fp.close();

    cout << "\nNumbers:\n";

    for (int i=0; i < numbers.size(); i++)
    {
        cout << numbers[i] << '\n';
    }
}
