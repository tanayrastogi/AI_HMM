#include "HMM_Matrix.hpp"

// Alpha Pass

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
    cout<<"\nTransition Matrix A:\n";
    A.printHMMmatrix();



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
    cout<<"\nObservation Matrix B:\n";
    B.printHMMmatrix();

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
    cout<<"\nInitial Pi:\n";
    Pi.printHMMmatrix();

    // Observation Sequence
    numbers.clear();
    seq_row = 1;
    cin>>seq_col;
    for(unsigned int i = 0; i<(seq_row*seq_col); i++)
    {
        cin>>x;
        numbers.push_back(x);
    }
//    cout<<"\nSeq_row:"<<seq_row;
//    cout<<"\nSeq_col:"<<seq_col;
    it = numbers.begin();
    Seq.setHMMmatrix(numbers, seq_row, seq_col, it);
    cout<<"\nObservation Sequence:\n";
    Seq.printHMMmatrix();




    //--------------------------------------------------//
            // Forward Algorithm or Alpha - pass//
    //-------------------------------------------------//
    vector< vector<float> > a = A.getHMMmatrix();
    vector< vector<float> > b = B.getHMMmatrix();
    vector< vector<float> > pi = Pi.getHMMmatrix();
    vector< vector<float> > seq = Seq.getHMMmatrix();
    vector< vector<float> > alpha (seq_col, vector<float>(a_col));

    int observpos;

    // Alpha 0
    observpos = seq[0][0];
    for(unsigned int i = 0; i<a_col; i++)
        alpha[0][i] = pi[0][i]*b[i][observpos];

    // Rest of the alpha
    for(unsigned int ts = 1; ts<seq[0].size(); ts++)
    {
        observpos = seq[0][ts];
        for(unsigned int i=0; i<a_col; i++)
        {
            for(unsigned int j = 0; j<a_col; j++)
                alpha[ts][i] = alpha[ts][i] + alpha[ts-1][j]*a[j][i];

            alpha[ts][i] = alpha[ts][i]*b[i][observpos];
        }
    }

    float sum = 0;
    for(unsigned int i=0; i<alpha[0].size(); i++)
        sum += alpha[seq_col-1][i];

    cout<<"\nThe probability of the given sequence for the given model is: "<<sum;
    cout<<"\n";


    return 0;
}

