#include "Singly_Linked_List.h"

#include <vector>

using namespace std;

int main() {

    vector<string> data = {"Mom", "Bin", "Quay", "Chi Le", "Phuong Anh", "Bai Bai", "Hoa Thanh", "Thuy Duong"};

    Singly_Linked_List<string> list;
    for (size_t i = 0; i < data.size(); ++i) {
        list.push_back(data[i]);
    }

    //algorithms.make_circular(head,string("Bin"));
    

    cout << list << endl;
    
    return 0;
}