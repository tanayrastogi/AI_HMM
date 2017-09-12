#include "HMM_Matrix.hpp"
#include "matrix_multi.hpp"

int main()
 {
    HMMmatrix A, B, Pi, Seq;
    unsigned int a_row, a_col, b_row, b_col, pi_row, pi_col;
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
    it = numbers.begin();
    A.setHMMmatrix(numbers, a_row, a_col, it);


    // Matrix B
    numbers.clear();
    cin>>b_row;
    cin>>b_col;
    for(unsigned int i = 0; i<(b_row*b_col); i++)
    {
        cin>>x;
        numbers.push_back(x);
    }
    it = numbers.begin();
    B.setHMMmatrix(numbers, b_row, b_col, it);

//    // Matrix Pi
    numbers.clear();
    cin>>pi_row;
    cin>>pi_col;
    for(unsigned int i = 0; i<(pi_row*pi_col); i++)
    {
        cin>>x;
        numbers.push_back(x);
    }
    it = numbers.begin();
    Pi.setHMMmatrix(numbers, pi_row, pi_col, it);


    //--------------------------------------------------//
    // Probability of next state given the current state//
    //-------------------------------------------------//
    vector< vector<float> > a = A.getHMMmatrix();
    vector< vector<float> > pi = Pi.getHMMmatrix();
    vector< vector<float> > b = B.getHMMmatrix();


    //Probability of next state
    vector< vector<float> > X = cross_matrix_multiply(pi, a);


    //Probability of next observation
    vector< vector<float> > Ob = cross_matrix_multiply(X, b);



    // Print got Kattis
    cout<<Ob.size()<<" "<<Ob[0].size()<<" ";
    for(vector<int>::size_type i = 0; i<Ob.size(); i++)
    {
        for(vector<int>::size_type j = 0; j<Ob[0].size(); j++)
            cout<< Ob[i][j]<<" ";
    }
    return 0;
}
