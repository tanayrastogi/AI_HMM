#include "HMM_Matrix.hpp"
#include "matrix_multi.hpp"
#include "read_file.hpp"

int main()
 {
    HMMmatrix A, B, Pi;
    unsigned int a_row, a_col, b_row, b_col, pi_row, pi_col;

    // Read the input file
    vector<float> numbers;
    numbers = read_file();
    vector<float>::iterator it = numbers.begin();

    // Matrix A
    a_row = *it;
//    cout<<"\nA_row:"<<a_row;
    ++it;
    a_col = *it;
//    cout<<"\nA_col:"<<a_col;
    ++it;
    A.setHMMmatrix(numbers, a_row, a_col, it);
//    cout<<"\nTransition Matrix A:\n";
//    A.printHMMmatrix();

    // Matrix B
    it = numbers.begin() + ((a_row*a_col) + 2);
    b_row = *it;
//    cout<<"\nB_row:"<<b_row;
    ++it;
    b_col = *it;
//    cout<<"\nB_col:"<<b_col;
    ++it;
    B.setHMMmatrix(numbers, b_row, b_col, it);
//    cout<<"\nObservation Matrix B:\n";
//    B.printHMMmatrix();

    // Matrix Pi
    it = numbers.begin() + ((a_row*a_col) + 2) + ((b_row*b_col) + 2);
    pi_row = *it;
//    cout<<"\nPi_row:"<<pi_row;
    ++it;
    pi_col = *it;
//    cout<<"\nPi_col:"<<pi_col;
    ++it;
    Pi.setHMMmatrix(numbers, pi_row, pi_col, it);
//    cout<<"\nInitial Probability distrubution Pi:\n";
//    Pi.printHMMmatrix();
//
    //--------------------------------------------------//
    // Probability of next state given the current state//
    //-------------------------------------------------//
    vector< vector<float> > a = A.getHMMmatrix();
    vector< vector<float> > pi = Pi.getHMMmatrix();

//    //Probability of next state
    vector< vector<float> > X = cross_matrix_multiply(pi, a);
//    cout<< "\n\nProbability Distribution of Next state :\n\n";
//    for(vector<int>::size_type i = 0; i<X.size(); i++)
//    {
//        for(vector<int>::size_type j = 0; j<X[0].size(); j++)
//            cout<< X[i][j]<< "\t";
//        cout<<"\n";
//
//    }

    //--------------------------------------------------//
    // Probability of next observation given the current state//
    //-------------------------------------------------//
    vector< vector<float> > b = B.getHMMmatrix();

    //Probability of next state
    vector< vector<float> > Ob = cross_matrix_multiply(X, b);
//    cout<< "\n\nProbability Distribution of Observation :\n\n";
//    for(vector<int>::size_type i = 0; i<Ob.size(); i++)
//    {
//        for(vector<int>::size_type j = 0; j<Ob[0].size(); j++)
//            cout<< Ob[i][j]<< "\t";
//        cout<<"\n";
//
//    }

    // Print got Kattis
    cout<<Ob.size()<<" "<<Ob[0].size()<<" ";
    for(vector<int>::size_type i = 0; i<Ob.size(); i++)
    {
        for(vector<int>::size_type j = 0; j<Ob[0].size(); j++)
            cout<< Ob[i][j]<<" ";
    }

    return 0;
}
