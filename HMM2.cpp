#include "HMM_Matrix.hpp"
#include "matrix_multi.hpp"
#include "read_file.hpp"
#include "misc.hpp"

int main()
 {
    HMMmatrix A, B, Pi, Seq;
    unsigned int a_row, a_col, b_row, b_col, pi_row, pi_col, seq_row, seq_col;

    // Read the input file
    vector<float> numbers;
    numbers = read_file();
    vector<float>::iterator it;


    // Matrix A
    it = numbers.begin();
    a_row = *it;
//    cout<<"\nA_row:"<<a_row;
    ++it;
    a_col = *it;
//    cout<<"\nA_col:"<<a_col;
    ++it;
    A.setHMMmatrix(numbers, a_row, a_col, it);
    cout<<"\nTransition Matrix A:\n";
    A.printHMMmatrix();

    // Matrix B
    it = numbers.begin() + ((a_row*a_col) + 2);
    b_row = *it;
//    cout<<"\nB_row:"<<b_row;
    ++it;
    b_col = *it;
//    cout<<"\nB_col:"<<b_col;
    ++it;
    B.setHMMmatrix(numbers, b_row, b_col, it);
    cout<<"\nObservation Matrix B:\n";
    B.printHMMmatrix();

    // Matrix Pi
    it = numbers.begin() + ((a_row*a_col) + 2) + ((b_row*b_col) + 2);
    pi_row = *it;
//    cout<<"\nPi_row:"<<pi_row;
    ++it;
    pi_col = *it;
//    cout<<"\nPi_col:"<<pi_col;
    ++it;
    Pi.setHMMmatrix(numbers, pi_row, pi_col, it);
    cout<<"\nInitial Pi:\n";
    Pi.printHMMmatrix();

    // Observation Sequence
    it = numbers.begin() + ((a_row*a_col) + 2) + ((b_row*b_col) + 2) + ((pi_row*pi_col) + 2);
    seq_row = 1;
//    cout<<"\nSeq_row:"<<seq_row;
    seq_col = *it;
//    cout<<"\nSeq_col:"<<seq_col;
    ++it;
    Seq.setHMMmatrix(numbers, seq_row, seq_col, it);
    cout<<"\nObservation Sequence:\n";
    Seq.printHMMmatrix();

    //--------------------------------------------------//
                  // Veterbi Algorithm //
    //-------------------------------------------------//
    vector< vector<float> > a = A.getHMMmatrix();
    vector< vector<float> > b = B.getHMMmatrix();
    vector< vector<float> > pi = Pi.getHMMmatrix();
    vector< vector<float> > seq = Seq.getHMMmatrix();

    vector< vector<float> > delta;
    vector< vector<float> > delta_temp (a_row, std::vector<float>(a_col));
    vector< vector<float> > temp_seq;
    int pos;
    float max_val;
    long max_pos;
    vector< vector<float> > a_trans = matrix_transpose(a);
    vector< vector<float> > b_trans = matrix_transpose(b);
    HMMmatrix OB_SEQ;


    // Delta 0
    it = seq[0].begin();
    pos = *it;

    it = b_trans[pos].begin();
    OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);
    cout<<"\n\nThe observation at "<<pos<<" is:\n";
    OB_SEQ.printHMMmatrix();

    temp_seq = OB_SEQ.getHMMmatrix();
    delta = element_matrix_multiply(pi, temp_seq);
    cout<<"\n\ndelta at 0 :\n";
    vector_print(delta);

    temp_seq.clear();
    OB_SEQ.clear_matrix();

//    // Rest of the delta
    for(unsigned int i = 1; i<seq[0].size(); i++)
    {
        it = seq[0].begin() + i;
        pos = *it;

        it = b_trans[pos].begin();
        OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);
        cout<<"\n\nThe observation at "<<pos<<" is:\n";
        OB_SEQ.printHMMmatrix();
        temp_seq = OB_SEQ.getHMMmatrix();

        for(vector<int>::size_type j = 0; j<delta_temp.size(); j++)
        {
            for(unsigned int k = 0; k<delta_temp[0].size(); k++)
            {
                delta_temp[j][k] = delta[0][k]*a[j][k]*temp_seq[0][j];
            }
        }

        cout<<"\nDelta at"<<pos<<" :\n";
        vector_print(delta_temp);

        max_pos = max_element(delta_temp[1].begin(), delta_temp[1].end()) - delta_temp[1].begin();
        max_val = *max_element(delta_temp[1].begin(), delta_temp[1].end());

        cout<<"\nMaximum value position: "<<max_pos;
        cout<<"\nMaximum value: "<<max_val;


//
//        temp1 = OB_SEQ.getHMMmatrix();
//        temp2 = cross_matrix_multiply(alpha, a);
//
//        // Next Alpha
//        alpha = element_matrix_multiply(temp2, temp1);
//
////        cout<< "\n\nAlpha at "<<i<<" :\n\n";
////        vector_print(alpha);
//
        temp_seq.clear();
        OB_SEQ.clear_matrix();
//
//
    }
//
//    float sum = 0;
//    for(int i=0; i<alpha.size(); i++)
//        for(int j=0; j<alpha[0].size(); j++)
//            sum = sum + alpha[i][j];
//
//    cout<<"\nThe probability of the given sequence for the given model is: "<<sum;


    return 0;
}

