#include "file_read.hpp"

int main()
 {
    Model m1;

    // Read the input file
    m1.read_file();
    m1.setA();
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
        return 0;
}
