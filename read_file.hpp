// This method is outside of the HMMmatrix class
vector<float> read_file()
 {
    // Variables for parsing the file
    vector<float> numbers;
    vector<float>::iterator it;
	fstream fp;
    float innum;

    fp.open("sample_00.in");

    if(fp.is_open())
    {
        cout<< "\nThe File is open";
        while(fp >> innum)
            numbers.push_back(innum);
        fp.close();

//        // Print the content of the file
//        for(it=numbers.begin(); it!=numbers.end(); ++it)
//            cout<<" "<<*it<<"\t";
    }
    else
        cout<<"\nDidnt open the file!!!!";

    return numbers;
}
