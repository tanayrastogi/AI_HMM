////tic
//high_resolution_clock::time_point t1 = high_resolution_clock::now();
////toc
//high_resolution_clock::time_point t2 = high_resolution_clock::now();
//
//auto duration = duration_cast<microseconds> (t2-t1).count();
//cout<<duration;

void vector_print(vector< vector<double> >& a);
void vector_diff(vector< vector<double> >& a, vector< vector<double> >& b);

void vector_print(vector< vector<double> >& a)
{
    for(vector<int>::size_type i = 0; i<a.size(); i++)
    {
        for(vector<int>::size_type j = 0; j<a[0].size(); j++)
            cout<<a[i][j]<<"\t";
        cout<<"\n";
    }
}


void vector_diff(vector< vector<double> >& a, vector< vector<double> >& b)
{
    for(vector<int>::size_type i = 0; i<a.size(); i++)
    {
        for(vector<int>::size_type j = 0; j<a[0].size(); j++)
            cout<<a[i][j] - b[i][j]<<"\t\t";
        cout<<"\n";
    }
}


