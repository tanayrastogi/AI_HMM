#include "HMM_Matrix.hpp"
#include "matrix_multi.hpp"

int main()
 {
    HMMmatrix A, B, Pi, Seq;
    unsigned int a_row, a_col, b_row, b_col, pi_row, pi_col, seq_row, seq_col;
    float x;
    vector<float> numbers;
    vector<float>::iterator it;

    // Matrix A
    cin>>a_row;
    cin>>a_col;
    for(unsigned int i = 0; i<(a_row*a_col); i++)
    {
        cin>>x;
        numbers.push_back(x);
    }
//    cout<<"\nA_row:"<<a_row;
//    cout<<"\nA_col:"<<a_col;
    it = numbers.begin();
    A.setHMMmatrix(numbers, a_row, a_col, it);
//    cout<<"\nTransition Matrix A:\n";
//    A.printHMMmatrix();



    // Matrix B
    numbers.clear();
    cin>>b_row;
    cin>>b_col;
    for(unsigned int i = 0; i<(b_row*b_col); i++)
    {
        cin>>x;
        numbers.push_back(x);
    }
//    cout<<"\nB_row:"<<b_row;
//    cout<<"\nB_col:"<<b_col;
    it = numbers.begin();
    B.setHMMmatrix(numbers, b_row, b_col, it);
//    cout<<"\nObservation Matrix B:\n";
//    B.printHMMmatrix();

//    // Matrix Pi
    numbers.clear();
    cin>>pi_row;
    cin>>pi_col;
    for(unsigned int i = 0; i<(pi_row*pi_col); i++)
    {
        cin>>x;
        numbers.push_back(x);
    }
//    cout<<"\nPi_row:"<<pi_row;
//    cout<<"\nPi_col:"<<pi_col;
    it = numbers.begin();
    Pi.setHMMmatrix(numbers, pi_row, pi_col, it);
//    cout<<"\nInitial Pi:\n";
//    Pi.printHMMmatrix();

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
    cout<<"\n";

    return 0;
}
