#include "HMM_Matrix.hpp"
#include "matrix_multi.hpp"
#include "read_file.hpp"

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
            // Forward Algorithm or Alpha - pass//
    //-------------------------------------------------//
    vector< vector<float> > a = A.getHMMmatrix();
    vector< vector<float> > b = B.getHMMmatrix();
    vector< vector<float> > pi = Pi.getHMMmatrix();
    vector< vector<float> > seq = Seq.getHMMmatrix();

    vector< vector<float> > alpha (a_row, std::vector<float>(seq_col));
    vector<float> ob_at_seq;
    vector<float> temp;

    alpha = element_matrix_multiply(a,b);

    // Alpha 0
//    int pos = seq[0][0];
//   //Observation matrix at 0
//    for(unsigned int i = 0; i<b_col; i++)
//        ob_at_seq.push_back(b[i][pos]);
//
//    temp = element_matrix_multiply(pi[0], ob_at_seq);
//    alpha[0].push_back(temp);



    return 0;
}

