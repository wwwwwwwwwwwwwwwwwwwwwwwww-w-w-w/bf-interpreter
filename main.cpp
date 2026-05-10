#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

int main() {
    std::ifstream read("main_bf.txt");
    std::string code;

    if (read.is_open()) {
        std::string line;
        while (std::getline(read, line)) {
            code += line;
        }
    } else {
        std::cout << "type the code:\n";
        std::cin >> code;
    }

    // Precompute bracket pairs
    std::unordered_map<size_t, size_t> jump;
    std::vector<size_t> stack;

    for (size_t i = 0; i < code.size(); i++) {
        if (code[i] == '[') {
            stack.push_back(i);
        } 
        else if (code[i] == ']') {
            size_t start = stack.back();
            stack.pop_back();
            jump[start] = i;
            jump[i] = start;
        }
    }

    std::vector<uint8_t> cells(30000, 0);
    size_t ptr = 0;

    for (size_t i = 0; i < code.size(); i++) {
        char op = code[i];

        switch (op) {
            case '+':
                cells[ptr]++;
                break;

            case '-':
                cells[ptr]--;
                break;

            case '>':
                if (ptr < cells.size() - 1) ptr++;
                break;

            case '<':
                if (ptr > 0) ptr--;
                break;

            case '.':
                std::cout << static_cast<char>(cells[ptr]);
                break;

            case ',':
            {
                char c;
                std::cin >> c;
                cells[ptr] = static_cast<uint8_t>(c);
                break;
            }

            case '[':
                if (cells[ptr] == 0)
                    i = jump[i];
                break;

            case ']':
                if (cells[ptr] != 0)
                    i = jump[i];
                break;

            default:
                break; // ignore any non-BF characters
        }
    }

    return 0;
}
