#include "Algorithms.h"
#include "Node.h"

#include <string>
#include <vector>

using namespace std;

int main() {

    vector<int> vec = {3, 5, 9};
    Node<int>* head = nullptr;
    for (const auto& item : vec) {
        Algorithms<int>::insert_back(head, item);
    }

    Algorithms<int>::print_list(head);

    Algorithms<int>::remove_first_occurrence(head, 2);
    Algorithms<int>::print_list(head);



    return 0;
}