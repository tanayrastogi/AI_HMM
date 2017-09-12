

////tic
//high_resolution_clock::time_point t1 = high_resolution_clock::now();
////toc
//high_resolution_clock::time_point t2 = high_resolution_clock::now();
//
//auto duration = duration_cast<microseconds> (t2-t1).count();
//cout<<duration;

void vector_print(vector< vector<float> >& a);

void vector_print(vector< vector<float> >& a)
{
    for(vector<int>::size_type i = 0; i<a.size(); i++)
    {
        for(vector<int>::size_type j = 0; j<a[0].size(); j++)
            cout<< a[i][j]<<"\t\t";
        cout<<"\n";
    }
}

