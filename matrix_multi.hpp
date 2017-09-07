#include<iostream>
#include<algorithm>
#include<functional>

using namespace std;

vector< vector<float> > cross_matrix_multiply(vector< vector<float> >& a, vector< vector<float> >& b);
vector< vector<float> > element_matrix_multiply(vector< vector<float> >& a, vector< vector<float> >& b);



vector< vector<float> > cross_matrix_multiply(vector< vector<float> >& a, vector< vector<float> >& b)
{
    const unsigned int a_row = a.size();
    const unsigned int a_col = a[0].size();
    const unsigned int b_row = b.size();
    const unsigned int b_col = b[0].size();

    if(a_col == b_row)
    {
        const unsigned int c_row = a_row;
        const unsigned int c_col = b_col;
        vector< vector<float> > c(c_row, std::vector<float>(c_col));

        for(unsigned int i = 0; i<c_row; i++)
        {
            for(unsigned int j = 0; j<c_col; j++)
            {
                c[i][j] = 0;
                for (unsigned int k = 0; k < b_row; k++)
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }

        }

        return c;
    }
    else
        {
            cout<<"\nCannot Multiply, matrix dimension does not match";
        }

}


vector< vector<float> > element_matrix_multiply(vector< vector<float> >& a, vector< vector<float> >& b)
{
    const unsigned int a_row = a.size();
    const unsigned int a_col = a[0].size();
    const unsigned int b_row = b.size();
    const unsigned int b_col = b[0].size();
    const unsigned int c_row = a_row;
    const unsigned int c_col = 1;
    vector< vector<float> > c(c_row, std::vector<float>(c_col));
    vector<float>::iterator it;



    for(vector<int>::size_type i = 0; i<c_row; i++)
    {
        for(unsigned int j = 0; j<c_col; j++)
        {
            c[i][j] = a[i][j] * b[i][j];
        }
    }

            // Print C
    cout<< "\n\nMatrix C :\n\n";
    for(vector<int>::size_type i = 0; i<c_row; i++)
        {
            for(vector<int>::size_type j = 0; j<c_col; j++)
                cout<< c[i][j]<< " ";
            cout<<"\n";

        }



    return c;
}


/*
vector<float> element_matrix_multiply(vector<float>& a, vector<float>& b)
{
    vector<float> c;
    vector<float>::iterator it;

    cout<<"\nMatrix A:";
    for(it=a.begin(); it!=a.end(); ++it)
        cout<<" "<<*it<<"\t";

    cout<<"\nMatrix B:";
    for(it=b.begin(); it!=b.end(); ++it)
        cout<<" "<<*it<<"\t";



    //Multiply the value
    if(a.size()==b.size())
    {
        for(int i=0; i<a.size(); i++)
            c.push_back(a[i]*b[i]);
    }


    return c;
}
*/
