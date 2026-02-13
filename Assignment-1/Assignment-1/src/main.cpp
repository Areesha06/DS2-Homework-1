#include "../include/PostScriptFileSimplifier.hpp"
#include <filesystem>
#include <iostream>

// namespace fs = std::filesystem;

// int main() {

//     std::string inputDir = "input";
//     std::string outputDir = "test-output";

//     for (const auto& entry : fs::directory_iterator(inputDir)) {

//         std::string inputFile = entry.path().string();
//         std::string filename = entry.path().filename().string();

//         std::cout << "Processing: " << filename << std::endl;

//         PostScriptFileSimplifier ps(inputFile);

//         ps.simplify_definitions();
//         ps.evaluate_operations();

//         std::string outputFile =
//             outputDir + "/" +
//             filename.substr(0, filename.find_last_of('.')) +
//             "-simplified.eps";

//         ps.writefile(outputFile);
//     }

//     std::cout << "Done.\n";
//     return 0;
// }



int main() {
    PostScriptFileSimplifier simpl("input/example.ps");
    simpl.simplifyFile(); // reads, evaluates, writes output
    return 0;
}
