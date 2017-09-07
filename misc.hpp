void vector_print(vector< vector<float> >& a);

void vector_print(vector< vector<float> >& a)
{
    for(vector<int>::size_type i = 0; i<a.size(); i++)
    {
        for(vector<int>::size_type j = 0; j<a[0].size(); j++)
            cout<< a[i][j]<<"\t";
        cout<<"\n";
    }
}

