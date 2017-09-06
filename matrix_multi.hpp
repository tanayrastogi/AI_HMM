#include<iostream>
using namespace std;

vector< vector<float> > matrix_multiply(vector< vector<float> >& a, vector< vector<float> >& b);

vector< vector<float> > matrix_multiply(vector< vector<float> >& a, vector< vector<float> >& b)
{
    const unsigned int a_row = a.size();
    const unsigned int a_col = a[0].size();
    const unsigned int b_row = b.size();
    const unsigned int b_col = b[0].size();

    // Print A
//    cout<< "\n\nMatrix A :\n\n";
//    for(vector<int>::size_type i = 0; i<a_row; i++)
//        {
//            for(vector<int>::size_type j = 0; j<a_col; j++)
//                cout<< a[i][j]<< " ";
//            cout<<"\n";
//        }

    // Print B
//    cout<< "\n\nMatrix B :\n\n";
//    for(vector<int>::size_type i = 0; i<b_row; i++)
//        {
//            for(vector<int>::size_type j = 0; j<b_col; j++)
//                cout<< b[i][j]<< " ";
//            cout<<"\n";
//        }
    // Multiply C = A*B

    // Check if the row and col satisfy the rule
    if(a_col == b_row)
    {
//        cout<<"\nMatix Multiplicaiton happening!!!";
        const unsigned int c_row = a_row;
        const unsigned int c_col = b_col;
        vector< vector<float> > c(c_row, std::vector<float>(c_col));

        for(vector<int>::size_type i = 0; i<c_row; i++)
        {
            for(vector<int>::size_type j = 0; j<c_col; j++)
            {
                c[i][j] = 0;
                for (vector<int>::size_type k = 0; k < b_row; k++)
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }

        }

//        // Print C
//        cout<< "\n\nMatrix C :\n\n";
//        for(vector<int>::size_type i = 0; i<c_row; i++)
//            {
//                for(vector<int>::size_type j = 0; j<c_col; j++)
//                    cout<< c[i][j]<< " ";
//                cout<<"\n";
//
//            }

        return c;
    }
    else
        {
            cout<<"\nCannot Multiply, matrix dimension does not match";
        }

}
