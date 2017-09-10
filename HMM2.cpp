#include "HMM_Matrix.hpp"
#include "matrix_multi.hpp"
#include "misc.hpp"

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
                  // Veterbi Algorithm //
    //-------------------------------------------------//
    cout<<"\n\n";
    vector< vector<float> > a = A.getHMMmatrix();
    vector< vector<float> > b = B.getHMMmatrix();
    vector< vector<float> > pi = Pi.getHMMmatrix();
    vector< vector<float> > seq = Seq.getHMMmatrix();

    HMMmatrix OB_SEQ;
    int pos;
    float max_val;
    long max_pos;
    vector< vector<float> > delta;
    vector< vector<float> > delta_temp (a_row, std::vector<float>(a_col));
    vector< vector<float> > temp_seq;
    vector< vector<float> > delta_idx (a_row, std::vector<float>(seq_col));
    vector<float> answer;

    // Assigning -1 to the index matrix
    for(unsigned int x = 0; x<a_row; x++)
        for(unsigned int y = 0; y<seq_col; y++)
            delta_idx[x][y] = -1;

    vector< vector<float> > a_trans = matrix_transpose(a);
    vector< vector<float> > b_trans = matrix_transpose(b);

    // Time step = 0; Delta 0;
    cout<<"\nAt Time step 0:";
    it = seq[0].begin();
    pos = *it;
    it = b_trans[pos].begin();
    OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);
    cout<<"\nThe observation at "<<pos<<" is:\n";
    OB_SEQ.printHMMmatrix();
    temp_seq = OB_SEQ.getHMMmatrix();

    delta = element_matrix_multiply(pi, temp_seq);
    cout<<"\nDelta at 0 :\n";
    vector_print(delta);

    OB_SEQ.clear_matrix();

    // Rest of the delta
    for(unsigned int ts = 1; ts<seq[0].size(); ts++)
    {
        cout<<"\nAt Time Step "<<ts<<" :";
        it = seq[0].begin() + ts;
        pos = *it;
        it = b_trans[pos].begin();
        OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);
//        cout<<"\n\nThe observation at "<<pos<<" is:\n";
//        OB_SEQ.printHMMmatrix();
        temp_seq = OB_SEQ.getHMMmatrix();

        for(vector<int>::size_type j = 0; j<delta_temp.size(); j++)
        {
            for(unsigned int k = 0; k<delta_temp[0].size(); k++)
            {
                delta_temp[j][k] = delta[0][k]*a[j][k]*temp_seq[0][j];
            }
        }

//        cout<<"\nDelta_temp at"<<pos<<" :\n";
//        vector_print(delta_temp);

        for(unsigned int j = 0; j<delta_temp.size(); j++)
        {
            max_pos = max_element(delta_temp[j].begin(), delta_temp[j].end()) - delta_temp[j].begin();
            delta_idx[j][ts] = max_pos;

            max_val = *max_element(delta_temp[j].begin(), delta_temp[j].end());
            delta[0][j] = max_val;
        }

        cout<<"\nDelta_idx at"<<ts<<" :\n";
        vector_print(delta_idx);
        cout<<"\nDelta at"<<ts<<" :\n";
        vector_print(delta);

        OB_SEQ.clear_matrix();


    }

    //Backtracking for the
    // Starting by reading the delta to get the last element of seq
    max_pos = max_element(delta[0].begin(), delta[0].end()) - delta[0].begin();
    cout<<"\nMax_position: "<<max_pos;
    cout<<"\n";
    answer.push_back(int(max_pos));


    for(int ts = (seq_col-1); ts!= 0; ts--)
    {
        max_pos = delta_idx[max_pos][ts];
        answer.push_back(max_pos);
    }

    reverse(answer.begin(), answer.end());

    cout<<"\nResult: ";
    for(it = answer.begin(); it!= answer.end() ; it++)
        cout<<*it<<"\t";
    cout<<"\n";

    return 0;
}

