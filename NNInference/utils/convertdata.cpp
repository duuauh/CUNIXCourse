#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream infile;
    infile.open("../params.bin", ios::in | ios::binary);
    float* conv1weight = new float[144];
    infile.read((char*)conv1weight, 144*sizeof(float));

    cout<<"read by block"<<endl;
    for(int i=0; i<16; i++){
        for(int j=0; j<9; j++){
            cout<<conv1weight[i*16+j]<<' ';
        }
        cout<<endl;
    }
    
    infile.close();
    cout<<endl;

    ifstream infile2;
    infile2.open("../params.bin", ios::in | ios::binary);
    cout<<"read one by one"<<endl;
    for(int i=0; i<16; i++){
        for(int j=0; j<9; j++){
            float tmp;
            infile2.read((char*)&tmp, sizeof(float));
            cout<<tmp<<' ';
        }
        cout<<endl;
    }
    infile2.close();

    return 0;
}