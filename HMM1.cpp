#include "HMM_Matrix.hpp"
#include "matrix_multi.hpp"


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
//    cout<<"\nObservation Sequence:\n";
//    Seq.printHMMmatrix();




    //--------------------------------------------------//
            // Forward Algorithm or Alpha - pass//
    //-------------------------------------------------//
    vector< vector<float> > a = A.getHMMmatrix();
    vector< vector<float> > b = B.getHMMmatrix();
    vector< vector<float> > pi = Pi.getHMMmatrix();
    vector< vector<float> > seq = Seq.getHMMmatrix();
    vector< vector<float> > alpha;
    vector< vector<float> > temp1;
    vector< vector<float> > temp2;
    int pos;
    vector< vector<float> > b_trans = matrix_transpose(b);
    HMMmatrix OB_SEQ;


    // Alpha 0
    it = seq[0].begin();
    pos = *it;

    it = b_trans[pos].begin();
    OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);
//    cout<<"\n\nThe observation at "<<pos<<" is:\n";
//    OB_SEQ.printHMMmatrix();

    temp1 = OB_SEQ.getHMMmatrix();
    alpha = element_matrix_multiply(pi, temp1);
//    cout<<"\n\nAlpha at 0 :\n";
//    vector_print(alpha);

    temp1.clear();
    OB_SEQ.clear_matrix();

    // Rest of the alpha
    for(unsigned int i = 1; i<seq[0].size(); i++)
    {
        it = seq[0].begin() + i;
        pos = *it;

        it = b_trans[pos].begin();
        OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);
//        cout<<"\n\nThe observation at "<<pos<<" is:\n";
//        OB_SEQ.printHMMmatrix();

        temp1 = OB_SEQ.getHMMmatrix();
        temp2 = cross_matrix_multiply(alpha, a);

        // Next Alpha
        alpha = element_matrix_multiply(temp2, temp1);

//        cout<< "\n\nAlpha at "<<i<<" :\n\n";
//        vector_print(alpha);

        temp1.clear();
        temp2.clear();
        OB_SEQ.clear_matrix();


    }

    float sum = 0;
    for(unsigned int i=0; i<alpha.size(); i++)
        for(unsigned int j=0; j<alpha[0].size(); j++)
            sum = sum + alpha[i][j];

    cout<<"\nThe probability of the given sequence for the given model is: "<<sum;
    cout<<"\n";


    return 0;
}

