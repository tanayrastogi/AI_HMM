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

    // Observation Sequence
    numbers.clear();
    seq_row = 1;
    cin>>seq_col;
    for(unsigned int i = 0; i<(seq_row*seq_col); i++)
    {
        cin>>x;
        numbers.push_back(x);
    }
    it = numbers.begin();
    Seq.setHMMmatrix(numbers, seq_row, seq_col, it);


    //--------------------------------------------------//
                  // Veterbi Algorithm //
    //-------------------------------------------------//
    vector< vector<float> > a = A.getHMMmatrix();
    vector< vector<float> > b = B.getHMMmatrix();
    vector< vector<float> > pi = Pi.getHMMmatrix();
    vector< vector<float> > seq = Seq.getHMMmatrix();
    int observpos;

    float max_val;
    long max_pos;
    vector< vector<float> > delta (a_col, std::vector<float>(seq_col));
    vector< vector<float> > delta_trans (seq_col, std::vector<float>(a_col));
    vector< vector<float> > delta_idx (a_row, std::vector<float>(seq_col));
    // Assigning -1 to the index matrix
    for(unsigned int x = 0; x<a_row; x++)
        for(unsigned int y = 0; y<seq_col; y++)
            delta_idx[x][y] = -1;

    vector< vector<float> > delta_temp (a_row, std::vector<float>(a_col));
    vector<float> answer;


    // Delta0 @ t = 0
    observpos = seq[0][0];
    for(unsigned int i = 0; i<a_col; i++)
        delta[i][0] = pi[0][i]*b[i][observpos];

    // Rest of the delta
    for(unsigned int ts = 1; ts<seq[0].size(); ts++)
    {
        observpos = seq[0][ts];
        for(unsigned int i = 0; i<a_col; i++)
        {
            for(unsigned int j = 0; j<a_col; j++)
                delta_temp[i][j] = delta[j][ts-1]*a[j][i]*b[i][observpos];
        }

        // Find the max element in delta_temp
        for(unsigned int j = 0; j<a_row; j++)
        {
            max_val = *max_element(delta_temp[j].begin(), delta_temp[j].end());
            delta[j][ts] = *max_element(delta_temp[j].begin(), delta_temp[j].end());

            if(max_val != 0)
            {
                max_pos = max_element(delta_temp[j].begin(), delta_temp[j].end()) - delta_temp[j].begin();
                delta_idx[j][ts] = max_pos;
            }

        }
    }

    //Backtracking
    // Transposing the delta
    delta_trans = matrix_transpose(delta);
    // Starting by reading the delta to get the last element of seq
    max_pos = max_element(delta_trans[seq_col - 1].begin(), delta_trans[seq_col - 1].end()) - delta_trans[seq_col - 1].begin();
    answer.push_back(int(max_pos));

    for(int ts = (seq_col-1); ts!= 0; ts--)
    {
        max_pos = delta_idx[max_pos][ts];
        answer.push_back(max_pos);
    }

    reverse(answer.begin(), answer.end());

    for(it = answer.begin(); it!= answer.end() ; it++)
        cout<<*it<<" ";

    return 0;
}

