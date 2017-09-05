#include "file_read.hpp"

int main()
 {
    Model m1;

    // Read the input file
    m1.read_file();
    m1.setA();
    m1.setB();
    m1.setPi();

    // Print A matrix
    float **A = m1.getA();
    cout<<"\n\nA = \n";
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            cout<<A[i][j]<<"\t";
        }
        cout<<"\n";
    }

    //Print B matrix
    float **B = m1.getB();
    cout<<"\n\nB = \n";
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            cout<<B[i][j]<<"\t";
        }
        cout<<"\n";
    }

    //Print Pi matrix
    float **Pi = m1.getPi();
    cout<<"\n\nPi = \n";
    for(int i=0; i<1; i++)
    {
        for(int j=0; j<4; j++)
        {
            cout<<Pi[i][j]<<"\t";
        }
        cout<<"\n";
    }


        return 0;
}
