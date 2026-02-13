/**
 * ! Don't change anything in this file.
 */

#ifndef POSTSCRIPTFILESIMPLIFIER_HPP
#define POSTSCRIPTFILESIMPLIFIER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class PostScriptFileSimplifier {
public:

    /**
     * @brief Construct a new Post Script File Simplifier object
     *
     * @param file File to be read
     *
     * @note The constructor reads the file into fileContents
     */
    PostScriptFileSimplifier(std::string);  // Constructor: Reads File into fileContents

    /**
     * @brief Simplify definitions by replacing tokens with their respective values
     */
    void simplify_definitions();

    /**
     * @brief Display the file line-by-line
     */
    void display_file() const;

    /**
     * @brief Write the stored representation into a file line-by-line
     */
    void writefile(std::string) const;

    /**
     * @brief Evaluate the operations in the file
     */
    void evaluate_operations();

private:

    std::vector<std::string> fileContents{};

    /**
     * @brief Get tokens from the fileContents
     */
    std::unordered_map<std::string, std::string> get_tokens() const;

    /**
     * @brief Replace tokens in fileContents with their respective values
     */
    void replace_tokens(std::unordered_map<std::string, std::string>& tokens);

    /**
     * @brief Keywords along with the number of arguments required for each
     */
    std::unordered_map<std::string, int> keywords = {
        {         "arc", 5},
        {        "arcn", 5},
        {        "fill", 0},
        {       "gsave", 0},
        {       "scale", 2},
        {      "lineto", 2},
        {      "moveto", 2},
        {      "stroke", 0},
        {     "newpath", 0},
        {     "rlineto", 2},
        {     "setgray", 1},
        {    "grestore", 0},
        {    "showpage", 0},
        {    "showpage", 2},
        {   "closepath", 0},
        {   "translate", 2},
        {  "setlinecap", 1},
        {"setlinewidth", 1},
    };
};

#endif  // POSTSCRIPTFILESIMPLIFIER_HPP
