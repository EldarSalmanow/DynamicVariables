#include <utility>
#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> input = {
        "int", "test", "=", "5",
        "float", "test_2" , "=", "238",
        "char", "r", "=", "p"
};

enum ValueType {
    INT,
    FLOAT,
    CHAR
};

struct Variable {
    Variable(ValueType type, void *value, std::string name) {
        this->valueType = type;
        this->value = value;
        this->name = std::move(name);
    }
public:
    ValueType valueType;
    void *value;
    std::string name;
};

std::vector<Variable> variables;

int main() {
    for (int index = 0; index < input.size(); ++index) {
        if (input[index] == "int") {
            variables.emplace_back(Variable(INT, new int(std::stoi(input[index + 3])), input[index + 1]));
            index += 3;
        } else if (input[index] == "float") {
            variables.emplace_back(Variable(FLOAT, new float(std::stof(input[index + 3])), input[index + 1]));
            index += 3;
        } else if (input[index] == "char") {
            variables.emplace_back(Variable(CHAR, new char(input[index + 3][0]), input[index + 1]));
            index += 3;
        } else {
            throw std::exception();
        }
    }
    for (auto &variable : variables) {
        if (variable.valueType == INT) {
            std::cout << variable.name << " : " << *reinterpret_cast<int *>(variable.value) << std::endl;
        } else if (variable.valueType == FLOAT) {
            std::cout << variable.name << " : " << *reinterpret_cast<float *>(variable.value) << std::endl;
        } else if (variable.valueType == CHAR) {
            std::cout << variable.name << " : " << *reinterpret_cast<char *>(variable.value) << std::endl;
        } else {
            throw std::exception();
        }
        delete variable.value;
    }
}