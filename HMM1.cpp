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
//    cout<<"\nInitial Pi:\n";
//    Pi.printHMMmatrix();

    // Observation Sequence
    it = numbers.begin() + ((a_row*a_col) + 2) + ((b_row*b_col) + 2) + ((pi_row*pi_col) + 2);
    seq_row = 1;
//    cout<<"\nSeq_row:"<<seq_row;
    seq_col = *it;
//    cout<<"\nSeq_col:"<<seq_col;
    ++it;
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
    vector< vector<float> > temp;
    int pos;
    vector< vector<float> > b_trans = matrix_transpose(b);
    HMMmatrix ob_at_seq;


    it = seq[0].begin();
    pos = *it;

    it = b_trans[pos].begin();
    ob_at_seq.setHMMmatrix(b_trans[pos], 1, b_col, it);
    temp = ob_at_seq.getHMMmatrix();

    // Alpha 0
    alpha = element_matrix_multiply(pi, temp);

    // Rest of the alpha
    for(unsigned int i = 1; i<seq[0].size(); i++)
    {
        it = seq[0].begin() + i;
        pos = *it;
        cout<<"\n\nThe position is: "<<pos;

        it = b_trans[pos].begin();
        ob_at_seq.setHMMmatrix(b_trans[pos], 1, b_col, it);
        temp = ob_at_seq.getHMMmatrix();

        cout<< "\n\Temp at"<<i<<":\n\n";
        for(vector<int>::size_type i = 0; i<temp.size(); i++)
        {
            for(vector<int>::size_type j = 0; j<temp[0].size(); j++)
                cout<< temp[i][j]<<"\t";
            cout<<"\n";
        }

        alpha = element_matrix_multiply(alpha, temp);
        temp.clear();

        cout<< "\n\nAlpha at "<<i<<" :\n\n";
        for(vector<int>::size_type i = 0; i<alpha.size(); i++)
        {
            for(vector<int>::size_type j = 0; j<alpha[0].size(); j++)
                cout<< alpha[i][j]<<"\t";
            cout<<"\n";
        }
    }



    return 0;
}

