
#include <iostream>
#include <fstream>
#include <string>

class RoutingMapTree {
public:
    void performAction(const std::string& action) {
        // Implement the action handling logic here
        std::cout << "Performing action: " << action << std::endl;
    }
};                       

int main() {
    std::ifstream file("actions1.txt");
    RoutingMapTree r;

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string actionString;
    while (std::getline(file, actionString)) {
        r.performAction(actionString);
    }

    file.close();
    return 0;
}
