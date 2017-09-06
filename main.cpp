#include "file_read.hpp"

int main()
 {
    HMMmatrix A, B, Pi;

    // Read the input file
    vector<float> numbers;
    numbers = read_file();
    A.setHMMmatrix(numbers);
    B.setHMMmatrix(numbers);
    Pi.setHMMmatrix(numbers);


    // Print A matrix
    //float **A = A.getHMMmatrix();
    cout<<"\n\nA = \n";
    A.printHMMmatrix();
    cout<<"\n\nB = \n";
    B.printHMMmatrix();
    cout<<"\n\nPi = \n";
    Pi.printHMMmatrix();

    return 0;
}
