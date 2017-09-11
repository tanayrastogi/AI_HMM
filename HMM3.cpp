#include "HMM_Matrix_hmm3.hpp"
#include "misc_hmm3.hpp"
#include "math.h"

// Alpha Pass

int main()
 {
    HMMmatrix A, B, Pi, Seq;
    unsigned int a_row, a_col, b_row, b_col, pi_row, pi_col, seq_row, seq_col;
    double x;
    vector<double> numbers;
    vector<double>::iterator it;

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
    cout<<"\nSeq_row:"<<seq_row;
    cout<<"\nSeq_col:"<<seq_col;
    it = numbers.begin();
    Seq.setHMMmatrix(numbers, seq_row, seq_col, it);
//    cout<<"\nObservation Sequence:\n";
//    Seq.printHMMmatrix();



         //--------------------------------------------------//
        //--------------------------------------------------//
                // Baum - Welch Learning Algorithm //
        //-------------------------------------------------//
       //-------------------------------------------------//

    cout<<"\n";
    vector< vector<double> > a = A.getHMMmatrix();
    vector< vector<double> > b = B.getHMMmatrix();
    vector< vector<double> > pi = Pi.getHMMmatrix();
    vector< vector<double> > seq = Seq.getHMMmatrix();
    int observpos;

    int num_states = a_row; // Number of states
    int len_obs = seq_col; // Length of observation sequence
    int num_ob = b_col;   // Number of possible observations

    vector< vector<double> > alpha (len_obs, vector<double>(num_states));
    vector< vector<double> > beta  (len_obs, vector<double>(num_states));
    vector< vector<double> > gamma (len_obs, vector<double>(num_states));
    vector< vector< vector<double> > > digamma (len_obs,vector< vector<double> >(num_states, vector<double>(num_states)));
    vector<double> c (len_obs); // used for scaling of the probabilities



    int maxiter = 100; // Number of iterations
    int flag = 0; // Variable to check the loop for iteration of learning
    int iter = 0; // Number of actual iteration
    double denom;
    double numer;
    double logProb;
    double oldlogProb = -10000000;

    //-----------------------Testing Area-----------------//
//    cout<<"\nSize of beta 1st vector:"<<beta.size();
//    cout<<"\nSize of beta 2nd vector:"<<beta[0].size();
//    cout<<"\nSize of di-gamma 3rd vector:"<<digamma[0][0].size();
    //-----------------------Testing Area-----------------//


    do
    {
        //--------------------------------------------------//
                // Alpha - pass// (Step2)
        //-------------------------------------------------//
        cout<<"\nLoop number: "<<iter;

        // Alpha @ t=0
        observpos = seq[0][0];
        c[0] = 0;
        for(int i = 0; i<num_states; i++)
        {
            alpha[0][i] = pi[0][i]*b[i][observpos];
            c[0] = c[0] + alpha[0][i];
        }

        // Scale the alpha0
        c[0] = 1 / c[0];
        for(int i = 0; i<num_states; i++)
              alpha[0][i] = alpha[0][i]*c[0];

        // Rest of the alpha
        for(int ts = 1; ts<len_obs; ts++)
        {
            observpos = seq[0][ts];
            c[ts] = 0;
            for(int i=0; i<num_states; i++)
            {
                alpha[ts][i] = 0;
                for(int j = 0; j<num_states; j++)
                    alpha[ts][i] = alpha[ts][i] + alpha[ts-1][j]*a[j][i];

                alpha[ts][i] = alpha[ts][i]*b[i][observpos];
                c[ts] = c[ts] + alpha[ts][i];
            }
            // Rescaling of rest of the alpha
            c[ts] = 1 / c[ts];
            for(int i=0; i<num_states; i++)
                alpha[ts][i] = c[ts]*alpha[ts][i];
        }

//        //--------------------Testing Area------------------//
//        cout<<"\nALPHA :\n";
//        vector_print(alpha);
//        cout<<"\nMATRIX C:\n";
//        for(it = c.begin(); it!= c.end(); it++)
//            cout<<*it<<"\t";
//        cout<<"\n";
//        //--------------------Testing Area------------------//




        //--------------------------------------------------//
                // Beta - pass// (Step 3)
        //-------------------------------------------------//

        // Beta @ t-1
        for(int i=0; i<num_states; i++)
            beta[len_obs-1][i] = c[len_obs-1];


        // Beta for t-2 until 0
        for(int ts=len_obs-2; ts>-1; ts--)
        {
            observpos = seq[0][ts+1];

            // Rest of beta
            for(int i = 0; i<num_states; i++)
            {
                beta[ts][i] = 0;
                for(int j = 0; j<num_states; j++)
                    beta[ts][i] = beta[ts][i] + a[i][j]*b[j][observpos]*beta[ts+1][j];

                beta[ts][i] = c[ts]*beta[ts][i];
            }
        }

//        //--------------------Testing Area------------------//
//        cout<<"\nBETA :\n";
//        vector_print(beta);
//        //--------------------Testing Area------------------//



        //--------------------------------------------------//
                // Find Gamma / Di-Gamma//  (STEP 4)
        //-------------------------------------------------//

        for(int ts=0; ts < len_obs-1; ts++)
        {
            denom = 0;
            // We always calculate the next observation sequence (t+1)
            observpos = seq[0][ts+1];

            for(int i = 0; i <num_states; i++)
            {
                for(int j = 0; j <num_states; j++ )
                {
                    denom = denom + alpha[ts][i]*a[i][j]*b[j][observpos]*beta[ts+1][j];
                }
            }

            for(int i = 0; i <num_states; i++)
            {
                gamma[ts][i] = 0;
                for(int j = 0; j <num_states; j++ )
                {
                    digamma[ts][i][j] = (alpha[ts][i]*a[i][j]*b[j][observpos]*beta[ts+1][j]) / denom;
                    gamma[ts][i] = gamma[ts][i] + digamma[ts][i][j];
                }

            }
        }


        // Special case : Gamma for ts = T - 1;
        denom = 0;
        for (int i=0; i<num_states; i++)
            denom = denom + alpha[len_obs-1][i];

        for (int i=0; i<num_states; i++)
            gamma[len_obs-1][i] = alpha[len_obs-1][i] / denom;


//        //--------------------Testing Area------------------//
//        cout<<"\nGAMMA :\n";
//        vector_print(gamma);
//        cout<<"\nDIGAMMA :\n";
//        for(int i = 0; i<digamma.size(); i++)
//        {
//            cout<<"\nFor time step "<<i<<" :\n";
//            for(int j=0; j<digamma[0].size(); j++)
//                {
//                    for(int k=0; k<digamma[0][0].size(); k++)
//                        cout<<digamma[i][j][k]<<"\t";
//                    cout<<"\n";
//                }
//                cout<<"\n";
//        }
//        //--------------------Testing Area------------------//





        //--------------------------------------------------//
                // Re-Estimate A, B, pi //  (STEP 5)
        //-------------------------------------------------//

        // Re-estimate Pi

        for (int i=0; i<num_states; i++)
        {
            pi[0][i] = gamma[0][i];
        }
        // Re-estimate A
        for (int i=0; i<num_states; i++)
        {
            for (int j=0; j<num_states; j++)
            {
                numer = 0;
                denom = 0;
                for (int ts = 0; ts<len_obs-1; ts++)
                {
                    numer += digamma[ts][i][j];
                    denom += gamma[ts][i];
                }
                a[i][j] = numer / denom;
            }
        }

        // Re-estimate B
        for (int i=0; i<num_states; i++)
        {
            for (int j=0; j<num_ob; j++)
            {
                numer = 0;
                denom = 0;
                for (int ts = 0; ts<len_obs; ts++)
                {
                    if(seq[0][ts]==j)
                        numer += gamma[ts][i];

                    denom += gamma[ts][i];
                }
                b[i][j] = numer / denom;
            }
        }





        //--------------------------------------------------//
                // Compute log(P(O|lamda)) //  (STEP 6)
        //-------------------------------------------------//

        logProb = 0;
        for (int i = 0; i < len_obs; i++)
            logProb += log(c[i]);

        logProb = -logProb;


        //--------------------------------------------------//
                // Check Iterations //  (STEP 7)
        //-------------------------------------------------//
        iter++;
        cout<<"\nLogProb: "<<logProb;
        cout<<"\nOLDLogProb: "<<oldlogProb;
        if(iter<maxiter && logProb > oldlogProb)
        {
            oldlogProb = logProb;
            flag = 0;
        }
        else
            flag = 1;
    }
    while(flag != 1);

    cout<<"\n\nShit is done!\n";

    cout<<"\n\nThe model after learning is:";
    cout<<"\nMatrix A:\n";
    vector_print(a);
    cout<<"\nMatrix B:\n";
    vector_print(b);
    cout<<"\nMatrix Pi:\n";
    vector_print(pi);



return 0;
}

