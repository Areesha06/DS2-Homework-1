#include "../include/PostScriptFileSimplifier.hpp"

#include <string>

#include "../include/stackPostScript.hpp"
#include "../include/utils.hpp"

#include <algorithm>


PostScriptFileSimplifier::PostScriptFileSimplifier(std::string file) {
    std::ifstream fin(file);
    std::string line;

    while (std::getline(fin, line))
        fileContents.push_back(line);

    fin.close();
}

void PostScriptFileSimplifier::simplify_definitions() {
    // Step 1: collect tokens
    auto tokens = get_tokens();

    // Step 2: REMOVE definition lines FIRST
    std::vector<std::string> cleaned;

    for (const auto& line : fileContents) {
        if (!(line.find("def") != std::string::npos &&
              line.find("/") != std::string::npos)) {
            cleaned.push_back(line);
        }
    }

    fileContents = cleaned;

    // Step 3: replace tokens safely
    replace_tokens(tokens);
}

void PostScriptFileSimplifier::display_file() const {
    for (const auto& line : fileContents)
        std::cout << line << '\n';
}

void PostScriptFileSimplifier::writefile(std::string file) const {
    std::ofstream fout(file);
    for (const auto& line : fileContents)
        fout << line << '\n';
    fout.close();
}


auto is_number = [](const std::string& s) {
    char* end = nullptr;
    std::strtold(s.c_str(), &end);
    return end != s.c_str() && *end == '\0';
};


void PostScriptFileSimplifier::evaluate_operations() {
        StackPostScript stack;

    for (auto& line : fileContents) {
        auto tokens = str_split(line);
        std::vector<std::string> output;

        for (const auto& t : tokens) {

            if (is_number(t)) {
                stack.push(std::stold(t));
            }
            else if (t == "add" && !stack.is_empty()) stack.add();
            else if (t == "sub" && !stack.is_empty()) stack.subtract();
            else if (t == "mul" && !stack.is_empty()) stack.multiply();
            else if (t == "div" && !stack.is_empty()) stack.divide();
            else if (t == "sin" && !stack.is_empty()) stack.sin();
            else if (t == "cos" && !stack.is_empty()) stack.cos();
            else if (t == "mod" && !stack.is_empty()) stack.mod();
            else if (t == "exp" && !stack.is_empty()) stack.exp();
            else if (t == "sqrt" && !stack.is_empty()) stack.sqrt();
            else if (t == "dup" && !stack.is_empty()) stack.dup();
            else if (t == "exch" && !stack.is_empty()) stack.exch();
            else if (keywords.count(t)) {
                // flush stack safely
                std::vector<long double> temp;
                while (!stack.is_empty())
                    temp.push_back(stack.pop());

                std::reverse(temp.begin(), temp.end());

                for (auto v : temp)
                    output.push_back(removeTrailingZeros(v));

                output.push_back(t);
            }

        }

        // rebuild line
        line.clear();
        for (auto& s : output)
            line += s + " ";
    }
}

void PostScriptFileSimplifier::replace_tokens(
    std::unordered_map<std::string, std::string>& tokens) {

    for (auto& line : fileContents) {
        auto parts = str_split(line);
        std::string rebuilt;

        for (auto& p : parts) {
            if (tokens.count(p))
                rebuilt += tokens[p];
            else
                rebuilt += p + " ";
        }

        line = rebuilt;
    }

}


std::unordered_map<std::string, std::string>
PostScriptFileSimplifier::get_tokens() const {

    std::unordered_map<std::string, std::string> tokens;

    for (const auto& line : fileContents) {
        auto parts = str_split(line);

        if (parts.size() >= 3 &&
            parts[0][0] == '/' &&
            parts.back() == "def") {

            std::string name = parts[0].substr(1);
            std::string value;

            for (size_t i = 1; i < parts.size() - 1; i++)
                value += parts[i] + " ";

            tokens[name] = value;
        }
    }
    return tokens;
}
