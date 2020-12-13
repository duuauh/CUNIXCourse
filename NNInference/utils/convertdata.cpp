#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream infile;
    ofstream outfile;

    infile.open("/home/zzl/zzlWorkspace/NNInference/params.txt", ios::in);
    outfile.open("/home/zzl/zzlWorkspace/NNInference/params.bin", ios::out | ios::binary);

    for(int i=0; i<43530; i++) {
        float tmp;
        infile>>tmp;
        outfile.write((char*)&tmp, sizeof(float));
    }

    infile.close();
    outfile.close();

    return 0;
}