#include "HMM_Matrix.hpp"
#include "matrix_multi.hpp"
#include "misc.hpp"

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
    vector<float> c (seq_col); // used for scaling of the probabilities

    // Alpha 0
    it = seq[0].begin();
    pos = *it;
    it = b_trans[pos].begin();
    OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);
//    cout<<"\n\nThe observation at "<<pos<<" is:\n";
//    OB_SEQ.printHMMmatrix();

    temp1 = OB_SEQ.getHMMmatrix();
    //Alpha 0
    alpha = element_matrix_multiply(pi, temp1);
    cout<<"\nAlpha at 0 [before scaling]:\n";
    vector_print(alpha);


    // Scaling factor at zero
    for(unsigned int x = 0; x<alpha[0].size(); x++)
        c[0] = c[0] + alpha[0][x];
    // Scale the alpha0
    c[0] = 1 / c[0];
    for(unsigned int x = 0; x<alpha[0].size(); x++)
          alpha[0][x] = alpha[0][x]*c[0];


    cout<<"\nAlpha at 0 [after scaling]:\n";
    vector_print(alpha);
    cout<<"\nC0 :";
    for(it = c.begin(); it!=c.end(); it++)
        cout<<" "<<*it;


    temp1.clear();
    OB_SEQ.clear_matrix();

    // Rest of the alpha
    for(unsigned int ts = 1; ts<seq[0].size(); ts++)
    {
        it = seq[0].begin() + ts;
        pos = *it;

        it = b_trans[pos].begin();
        OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);
//        cout<<"\n\nThe observation at "<<pos<<" is:\n";
//        OB_SEQ.printHMMmatrix();

        temp1 = OB_SEQ.getHMMmatrix();
        temp2 = cross_matrix_multiply(alpha, a);

        // Next Alpha
        alpha = element_matrix_multiply(temp2, temp1);
        cout<<"\nAlpha at "<<ts<<" [before scaling]:\n";
        vector_print(alpha);


        // Scaling factor at zero
        for(unsigned int x = 0; x<alpha[0].size(); x++)
            c[ts] = c[ts] + alpha[0][x];

        // Scale the alpha0
        c[ts] = 1 / c[ts];
        for(unsigned int x = 0; x<alpha[0].size(); x++)
          alpha[0][x] = alpha[0][x]*c[ts];

        cout<< "\nAlpha at [after scaling] "<<ts<<" :\n\n";
        vector_print(alpha);
        cout<<"\nC"<<ts<<" :";
        for(it = c.begin(); it!=c.end(); it++)
            cout<<" "<<*it;

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

