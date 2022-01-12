#include <iostream>

using namespace std;

int main(){
    int rows = 3;
    int cols = 5;

    for(unsigned int prog = 0; prog < rows * cols; prog += 3){
        int i = prog/ cols;
        int j = prog% cols;
        cout << i << " " << j++ << endl;
        i = (prog+1)/ cols;
        j = (prog+1)% cols;
        cout << i << " " << j++ << endl;
        i = (prog+2)/ cols;
        j = (prog+2)% cols;
        cout << i << " " << j++ << endl;
    }

    cout << endl;

    for(int i =0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << i << " " << j << endl;
        }
    }
}
