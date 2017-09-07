#include<iostream>
#include<algorithm>
#include<functional>

using namespace std;

vector< vector<float> > cross_matrix_multiply(vector< vector<float> >& a, vector< vector<float> >& b);
vector< vector<float> > dot_matrix_multiply  (vector< vector<float> >& a, vector< vector<float> >& b);
vector< vector<float> > matrix_transpose(vector< vector<float> >& a);

vector< vector<float> > cross_matrix_multiply(vector< vector<float> >& a, vector< vector<float> >& b)
{
    const unsigned int a_row = a.size();
    const unsigned int a_col = a[0].size();
    const unsigned int b_row = b.size();
    const unsigned int b_col = b[0].size();

    const unsigned int c_row = a_row;
    const unsigned int c_col = b_col;
    vector< vector<float> > c(c_row, std::vector<float>(c_col));

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
    return c;

}


vector< vector<float> > element_matrix_multiply(vector< vector<float> >& a, vector< vector<float> >& b)
{

    const unsigned int a_col = a[0].size();


    const unsigned int c_row = 1;
    const unsigned int c_col = a_col;
    vector< vector<float> > c(c_row, std::vector<float>(c_col));
    vector<float>::iterator it;

//    // Print A
//    cout<< "\n\nMatrix A :\n\n";
//    for(vector<int>::size_type i = 0; i<a_row; i++)
//        {
//            for(vector<int>::size_type j = 0; j<a_col; j++)
//                cout<< a[i][j]<< " ";
//            cout<<"\n";
//        }

//    // Print B
//    cout<< "\n\nMatrix B :\n\n";
//    for(vector<int>::size_type i = 0; i<b_row; i++)
//        {
//            for(vector<int>::size_type j = 0; j<b_col; j++)
//                cout<< b[i][j]<< " ";
//            cout<<"\n";
//        }

    for(vector<int>::size_type i = 0; i<c_row; i++)
    {
        for(unsigned int j = 0; j<c_col; j++)
        {
            c[i][j] = a[i][j] * b[i][j];
        }
    }

//    // Print C
//    cout<< "\n\nMatrix C :\n\n";
//    for(vector<int>::size_type i = 0; i<c_row; i++)
//    {
//        for(vector<int>::size_type j = 0; j<c_col; j++)
//            cout<< c[i][j]<< " ";
//        cout<<"\n";
//
//    }


    return c;
}


vector< vector<float> > matrix_transpose(vector< vector<float> >& a)
{
    const unsigned int row = a.size();
    const unsigned int col = a[0].size();
    vector< vector<float> > b(col, std::vector<float>(row));
    for (unsigned int i=0; i<col; i++)
    {
        for(unsigned int j=0; j<row; j++)
        {
            b[i][j] = a[j][i];
        }
    }

    return b;
}
