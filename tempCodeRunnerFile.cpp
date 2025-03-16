#include <iostream>
using namespace std;

main (){
    struct {
        int x;
        string y;
    } tes[] = {
        {1, "a"},
        {2, "b"}
    };

    cout << tes[0].x << " " << tes[0].y << endl;
    cout << tes[1].x << " " << tes[1].y << endl;
    swap(tes[0], tes[1]);
    cout << tes[0].x << " " << tes[0].y << endl;
    cout << tes[1].x << " " << tes[1].y << endl;
}