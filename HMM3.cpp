#include "HMM_Matrix.hpp"
#include "matrix_multi.hpp"
#include "misc.hpp"
#include "math.h"

// Alpha Pass

int main()
 {
    int flag = 0;
    int maxiter = 10;
    int iter;
    float denom;
    float numer;
    float logProb;
    float oldlogProb = -1000;
    int pos;

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

    vector< vector<float> > a = A.getHMMmatrix();
    vector< vector<float> > b = B.getHMMmatrix();
    vector< vector<float> > pi = Pi.getHMMmatrix();
    vector< vector<float> > seq = Seq.getHMMmatrix();

    vector< vector<float> > alpha (seq_col, vector<float>(a_col));
    vector< vector<float> > beta  (seq_col, vector<float>(a_col));
    vector< vector<float> > gamma (1, vector<float>(a_col));
    vector< vector< vector<float> > > digamma (seq_col,vector< vector<float> >(a_col, vector<float>(a_col)));
    vector< vector<float> > temp1;
    vector< vector<float> > temp2;
    vector< vector<float> > temp3;
    vector< vector<float> > temp4;
    vector< vector<float> > b_trans = matrix_transpose(b);
    HMMmatrix OB_SEQ;
    vector<float> c (seq_col); // used for scaling of the probabilities

    do
    {
        //--------------------------------------------------//
                // Forward Algorithm or Alpha - pass//
        //-------------------------------------------------//


        // Alpha 0
        it = seq[0].begin();
        pos = *it;
        it = b_trans[pos].begin();
        OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);
    //    cout<<"\n\nThe observation at "<<pos<<" is:\n";
    //    OB_SEQ.printHMMmatrix();

        temp1 = OB_SEQ.getHMMmatrix();
        //Alpha 0
        cout<<"\nAlpha at [before scaling] 0:\n";
        for(unsigned int j = 0; j<a_col; j++)
        {
            alpha[0][j] = pi[0][j]*temp1[0][j];
            cout<<"\t"<<alpha[0][j];
            c[0] = c[0] + alpha[0][j];
        }
        // Scale the alpha0
        c[0] = 1 / c[0];
        for(unsigned int x = 0; x<alpha[0].size(); x++)
              alpha[0][x] = alpha[0][x]*c[0];


        cout<<"\nAlpha at [after scaling] 0:\n";
        vector_print(alpha);
        cout<<"\nC0 :";
        for(it = c.begin(); it!=c.end(); it++)
            cout<<" "<<*it;


        temp1.clear();
        OB_SEQ.clear_matrix();

        // Rest of the alpha
        for(unsigned int ts = 1; ts<seq_col; ts++)
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
            cout<<"\nAlpha at [before scaling] "<<ts<<" :";
            for(unsigned int j = 0; j<a_col; j++)
            {
                alpha[ts][j] = temp2[ts][j] * temp1[0][j];
                c[ts] = c[ts] + alpha[ts][j];

            }


            // Scale the alpha0
            c[ts] = 1 / c[ts];
            for(unsigned int x = 0; x<alpha[ts].size(); x++)
              alpha[ts][x] = alpha[ts][x]*c[ts];

            cout<< "\nAlpha at [after scaling] "<<ts<<" :\n\n";
            vector_print(alpha);
            cout<<"\nC"<<ts<<" :";
            for(it = c.begin(); it!=c.end(); it++)
                cout<<" "<<*it;

            temp1.clear();
            temp2.clear();
            OB_SEQ.clear_matrix();


        }

        //--------------------------------------------------//
                // Backward Algorithm or Beta - pass//
        //-------------------------------------------------//
        // Beta @ t-1
        for(unsigned int i=0; i<a_col; i++)
        {
            beta[seq_col][i] = c[seq_col];
        }


        // Beta for t>0
        for(unsigned int ts=seq_col-1; ts>0; ts--)
        {
            it = seq[0].begin() + ts;
            pos = *it;

            it = b_trans[pos].begin();
            OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);


            temp1 = OB_SEQ.getHMMmatrix();
            //temp2 = cross_matrix_multiply(alpha, a);
            //temp3 = cross_matrix_multiply(temp2, beta);

            for(unsigned int i = 0; i<a_col; i++)
            {
                beta[ts][i] = 0;
                for(unsigned int j = 0; j<a_col; j++)
                {
                    beta[ts][i] = beta[ts][i] + a[i][j]*b[ts][j]*beta[ts][j];
                }
                beta[ts][i] = c[ts]*beta[ts][i];
            }
        }

        //--------------------------------------------------//
                // Find Gamma / Di-Gamma//  (STEP 4)
        //-------------------------------------------------//

        for(unsigned int ts=0; ts < seq_col-1; ts++)
        {
            denom = 0;
            // We always calculate the next observation sequence (t+1)
            it = seq[0].begin() + ts + 1;
            pos = *it;

            it = b_trans[pos].begin();
            OB_SEQ.setHMMmatrix(b_trans[pos], 1, b_col, it);
            temp1 = OB_SEQ.getHMMmatrix();

            for(unsigned int i = 0; i <a_col; i++)
            {
                for(unsigned int j = 0; j <a_col; j++ )
                {
                    denom += alpha[ts][i]*a[i][j]*temp1[0][j]*beta[ts+1][j];
                }
            }
            for(unsigned int i = 0; i <a_col; i++)
            {
                for(unsigned int j = 0; j <a_col; j++ )
                {
                    digamma[ts][i][j] = (alpha[ts][i]*a[i][j]*temp1[0][j]*beta[ts+1][j])/denom;
                    gamma[ts][i] += digamma[ts][i][j];
                }
            }

        }

        // For ts = T - 1;
        denom = 0;
        for (unsigned int i=0; i<a_col; i++)
        {
            denom += alpha[seq_col-1][i];
        }

        for (unsigned int i=0; i<a_col; i++)
        {
            gamma[seq_col-1][i] = alpha[seq_col-1][i]/denom;
        }

        //--------------------------------------------------//
                // Re-Estimate A, B, pi //  (STEP 5)
        //-------------------------------------------------//

        // Re-estimate Pi
        for (unsigned int i=0; i<pi_col; i++)
        {
            pi[0][i] = gamma[0][i];
        }

        // Re-estimate A
        for (unsigned int i=0; i<a_row; i++)
        {
            for (unsigned int j=0; j<a_col; j++)
            {
                numer = 0;
                denom = 0;
                for (unsigned ts = 0; ts < seq_col - 1; ts++)
                {
                    numer += digamma[ts][i][j];
                    denom += gamma[ts][i];
                }
            a[i][j] = numer / denom;
            }
        }


        // Re-estimate B
        for (unsigned int i=0; i<b_row; i++)
        {
            for (unsigned int j=0; i<b_col; j++)
            {
                numer = 0;
                denom = 0;
                for (unsigned ts = 0; ts < seq_col; ts++)
                {
                    if(seq[0][ts]==j)
                    {
                        numer += gamma[ts][i];
                    }
                    denom += gamma[ts][i];
                }
                b[i][j] = numer/denom;
            }
        }

        //--------------------------------------------------//
                // Compute log(P(O|lamda)) //  (STEP 6)
        //-------------------------------------------------//

        logProb = 0;
        for (unsigned i = 0; i < seq_col; i++)
        {
            logProb += log(c[i]);
        }
        logProb = -logProb;


        //--------------------------------------------------//
                // Check Iterations //  (STEP 7)
        //-------------------------------------------------//
        iter++;
        if(iter<maxiter && logProb > oldlogProb)
        {
            oldlogProb = logProb;
            flag = 0;
        }
        else
        {
            flag = 1;
        }


    }
    while(flag != 1);

return 0;
}

