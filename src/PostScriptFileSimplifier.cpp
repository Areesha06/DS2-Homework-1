#include "../include/PostScriptFileSimplifier.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "../include/stackPostScript.hpp"
#include "../include/utils.hpp"

PostScriptFileSimplifier::PostScriptFileSimplifier(std::string filename) {
    /*
    Your implementation goes here
    */
   std::ifstream file(filename);
    // std::ifstream file("example.txt");

    if (file.is_open()) {
        std::cout << "File opened successfully.\n";
    } else {
        std::cout << "Failed to open file.\n";
    }
//    std::cout<<1;
   std::string line;
   while(getline(file,line)){
    fileContents.push_back(line);
   }
    // for (const auto& element : fileContents) {
    //     std::cout << element << " "<<std::endl;
    // }
   }


void PostScriptFileSimplifier::simplify_definitions() {
    /*
    Your implementation goes here
    */
//    std::cout<<2;
   auto tokens=get_tokens();
//    std::cout<<3;
//    std::cout<<get_tokens();
 
    replace_tokens(tokens);
}

void PostScriptFileSimplifier::display_file() const {
    /*
    Your implementation goes here
    */
   for (const auto& line:fileContents){
        std::cout<<line<<std::endl;
   }
}

void PostScriptFileSimplifier::writefile(std::string file) const {
    /*
    Your implementation goes here
    */
//    std::string namestr;
//    for (const auto& letter:file){
//         if (letter=='-'){
//             break;
//         }
//         else{
//             namestr+=letter;
//         }
//    }
//    std::string newname=file+"-simplified.eps";
//    newname+= "-simplified.eps";
//    std::cout<<file[file.size()-4]<<std::endl;
   std::ofstream outFile("-simplified.eps");

   if(!outFile.is_open()){
    std::cout<<"failed to open\n";
   }

   for (const auto& line:fileContents){
    outFile<<line;
    outFile<<"\n";
   }
}


void PostScriptFileSimplifier::evaluate_operations() {

    std::vector<std::string> newcontent;
    // // Skip definition lines
    // std::string trimmed = line;
    // trimmed.erase(0, trimmed.find_first_not_of(" \t")); // trim leading spaces

    // if (trimmed.empty()) continue;

    // if (trimmed[0] == '/' && trimmed.find("def") != std::string::npos) {
    //     continue; // skip procedure/variable definition lines
    // }

    for (const std::string& line : fileContents) {

        StackPostScript A;   // reset per line
        std::istringstream iss(line);
        std::ostringstream newline;
        std::string word;

        while (iss >> word) {
            // std::cout<<word<<std::endl;
            if (word == "add") {
                A.add();
            
            }

            else if (word == "sub") {
                A.subtract();
                // A.pop();
            }

            else if (word == "mul") {
                A.multiply();
                // A.pop();
            }
            else if (word=="div"){
                A.divide();
            }
            else if (word=="sin"){
                A.sin();
            }
            else if (word=="cos"){
                A.cos();
            }
            else if (word=="mod"){
                A.mod();
            }
            else if (word=="exp"){
                A.exp();
            }
            else if (word=="sqrt"){
                A.sqrt();
            }
            else if (word=="dup"){
                A.dup();
            }
            else if (word=="exch"){
                A.exch();
            }
            else if(word=="atan")
                A.atan();
            else if (word=="roll"){
                A.roll(A.pop(),A.pop());
            }
            else if (word=="dir" && line[line.size()-3]!='d'){
                A.dup();
                A.cos();
                A.exch();
                A.sin();
            }

            else if (word == "lineto" ||word=="setlinecap"||word=="moveto"||word == "setlinewidth" ||word=="stroke"||word=="rlineto") {

                // pop all numbers in correct order
                std::vector<long double> temp;

                while (!A.is_empty()) {
                    temp.push_back(A.pop());
                }

                std::reverse(temp.begin(), temp.end());

                for (long double v : temp) {
                    // std::cout<<"temp"<<v<<std::endl;
                    newline << v << " ";
                }

                newline << word<<" ";
            }

            else {
                try {
                    long double value = std::stold(word);
                    // newline<<word<<" ";
                    A.push(value);
                }
                catch (...) {
                    newline << word<< " ";
                }
            }
        }

        newcontent.push_back(newline.str());
    }

    fileContents = newcontent;
}

std::unordered_map<std::string, std::string>
PostScriptFileSimplifier:: get_tokens() const{
    // std::cout<<3;
    std::unordered_map<std::string,std::string> tokens;
    for (const std::string& line : fileContents){
        std::istringstream iss(line);
        std::string name, value, keyword;

        if (iss>>name>>value>>keyword){
            if (name[0]=='/' && keyword=="def"){
                name.erase(0,1); //removing '/'

                tokens[name]=value;
            }
        }
    }
    // std::cout<<"l";
    std::cout << "Size of tokens: " << tokens.size() << std::endl;
       for (const auto& pair : tokens) {
        // std::cout<<"kk";
            std::cout << "Key: " << pair.first 
                    << "  →  Value: " << pair.second 
                    << std::endl;
        }

        return tokens;


    }

// std::unordered_map<std::string, std::string>
// PostScriptFileSimplifier::get_tokens() const {
//     std::unordered_map<std::string, std::string> tokens;

//     for (const std::string& line : fileContents) {
//         std::string trimmed = line;
//         trimmed.erase(0, trimmed.find_first_not_of(" \t")); // remove leading spaces

//         if (trimmed.empty()) continue;

//         if (trimmed[0] == '/') {
//             size_t posDef = trimmed.find("def");
//             if (posDef != std::string::npos) {
//                 size_t posSpace = trimmed.find(' ');
//                 if (posSpace != std::string::npos) {
//                     std::string name = trimmed.substr(1, posSpace - 1); // remove '/'
//                     std::string value = trimmed.substr(posSpace + 1, posDef - posSpace - 2); 
//                     // -2 trims space before "def"
//                     tokens[name] = value;
//                 }
//             }
//         }
//     }

//     // Debug print
//     for (const auto& [k,v] : tokens)
//         std::cout << "Procedure/Var: " << k << " → " << v << std::endl;

//     return tokens;
// }

// std::unordered_map<std::string, std::string>
// PostScriptFileSimplifier::get_tokens() const {
//     std::unordered_map<std::string,std::string> tokens;

//     for (const std::string& line : fileContents) {
//         std::string trimmed = line;
//         trimmed.erase(0, trimmed.find_first_not_of(" \t")); // remove leading spaces

//         if (trimmed.empty()) continue;

//         if (trimmed[0] == '/') {
//             size_t posDef = trimmed.find("def");
//             if (posDef != std::string::npos) {
//                 size_t posSpace = trimmed.find(' ');
//                 if (posSpace != std::string::npos) {
//                     std::string name = trimmed.substr(1, posSpace - 1); // remove '/'
//                     std::string value = trimmed.substr(posSpace + 1, posDef - posSpace - 2); 
//                     // -2 trims space before "def"

//                     // 🔹 Strip braces if it’s a procedure
//                     if (!value.empty() && value.front() == '{' && value.back() == '}') {
//                         value = value.substr(1, value.size() - 2); // remove { and }
//                         // optional: trim leading/trailing spaces
//                         size_t start = value.find_first_not_of(" \t");
//                         size_t end = value.find_last_not_of(" \t");
//                         value = value.substr(start, end - start + 1);
//                     }

//                     tokens[name] = value;
//                 }
//             }
//         }
//     }

//     // Debug print
//     for (const auto& [k,v] : tokens)
//         std::cout << "Token: " << k << " → " << v << std::endl;

//     return tokens;
// }



    
void PostScriptFileSimplifier::replace_tokens(
    std::unordered_map<std::string, std::string>& tokens) {

    std::vector<std::string> newcontent;

    for (const std::string& line : fileContents) {

        std::istringstream iss(line);
        std::ostringstream newline;
        std::string word;

        // bool def = false;

        while (iss >> word) {

            // // Skip definition lines
            // if (word == "def") {
            //     def = true;
            //     break;
            // }

            // If token is a variable or procedure
            if (tokens.find(word) != tokens.end()) {
                std::string body = tokens[word];

                // If procedure, body may have multiple tokens
                std::istringstream bodyStream(body);
                std::string token;
                while (bodyStream >> token) {
                    newline << token << " ";
                }

                // Do NOT add tokens[word] again!
            } 
            else {
                newline << word << " ";
            }
        }

        // Only add line if not a definition
        
        newcontent.push_back(newline.str());
        
    }

    fileContents = newcontent;
}


// void PostScriptFileSimplifier::replace_tokens(
//     std::unordered_map<std::string, std::string>& tokens) {
//     /*
//     Your implementation goes here
//     */
//    std::vector<std::string> newcontent;
//    for (const std::string& line : fileContents){ //loop through line

//         std::istringstream iss(line);
//         std::ostringstream newline;
//         std::string word;


//         bool def=false;

//         while(iss >> word){ //iterate through each word
//         // if (word == "def") { 
//         //     def = true;  }
//         if (tokens.find(word)!=tokens.end()){
//             std::string body = tokens[word];

//             // Split body into tokens and insert in-place
//             std::istringstream iss(body);
//             std::string token;
//             while (iss >> token) {
//                 newline << token << " ";
//             }
// }
//             newline <<tokens[word]<<" "; //add the value if found in key-value pair
//         }

//         else{
//             newline<<word<<" "; //add to newline as it is
//         }
//    }
//    if (!def){
//         newcontent.push_back(newline.str()); //add line as it is
//    }}
//    fileContents=newcontent; //replace old file with new file
// //    for (const auto& element : fileContents) {
// //         std::cout << element << " "<<std::endl;
// //     }
// //    std::cout<<5;

// }

int main(){
    // PostScriptFileSimplifier A("Assignment-1/input/file-1.ps");
    PostScriptFileSimplifier A("C:/HabibUniversity/Spring-2026/DS2/Assignment-1/Assignment-1/input/file-7.eps");
    // A.display_file();
    A.simplify_definitions();
    A.evaluate_operations();
    A.display_file();
    A.writefile("C:/HabibUniversity/Spring-2026/DS2/Assignment-1/Assignment-1/input/file-7.eps");
}
