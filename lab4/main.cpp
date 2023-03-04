
#include "include/parent.h"
#include <vector>

int main() {
    int n;
    std::cin >> n;


    std::vector <std::string> input;
    std::string s;

    getline(std::cin, s);
    for (int i = 0; i < n; i++){
        getline(std::cin, s);
        input.push_back(s);
    }
    std::vector <std::string> output = ParentRoutine("./child1_4", "./child2_4", input);

    for (const auto &res : output){
        std::cout << res << std::endl;
    }
    return 0;
}