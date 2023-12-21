
#include <iostream>       // std::cout
#include <string>         // std::string
#include <queue>          // std::queue
#include <unordered_set>  // std::unordered_set
#include <stack>          // std::stack
#include <fstream>        // std::fstream


#ifndef HTMLCHECKER_H
#define HTMLCHECKER_H
using namespace std;
/**
 * HTMLChecker class does two main jobs, which are reading a html file and storing
 * tags and words from the file into a queue
 */
enum State {whitespace, word, tag, tag_attr};
class HTMLChecker {
public:
    /**
     * Constructor assigns strings into self_closing_tags unsorted_set
     */
    HTMLChecker();
    /**
     * Takes the path of a html file and loads it into a
     * Queue one word at a time.  The method reads in the file
     * one character at a time, using a state machine with 4
     * states to parse the tags and words into a Queue for later
     * evaluation.
     *
     * @param file_path
     * @return true if the file could be read.
     */
    bool load(const string &file_path);
    /**
     * The method compares opening and closing tags to determine whether
     * they match or not
     * @param open - holds opening tag
     * @param close - holds closing tag
     * @return true if open and close match; otherwise, returns false
     */
    bool isMatch(const string & open, const string & close);
    /**
     * The method checks whether the tag is closing or not
     * @param s - holds the tag that need to check whether closing tag or not
     * @return true if it is a closing tag; otherwise, returns false
     */
    bool isClosing(const string &s);
    /**
     * The method checks whether the tag is in the set of self_closing_tags or not
     * @param s holds the tag that need to check whether self closing tag or not
     * @return true if it is a self closing tag; otherwise, returns false
     */
    bool isSelfClosing(const string & s);
    /**
     * The method checks whether the string is a word (not tag) or not
     * @param s - the string that need to check whether a word or not
     * @return true if it is a word; otherwise, returns false
     */
    bool isWord(const string &s);
    /**
     * The method pushes opening tags into a stack, and pops off the stack when
     * it finds a matching closing tag. If a closing tag does not match the opening
     * tag, it is invalid html. It is also invalid when the queue is reached but
     * the stack is not empty
     * @return true if it is valid html; otherwise, returns false
     */
    bool isValid();

private:

    queue<string> html_elements;
    unordered_set<string> self_closing_tags;
};


#endif //HTMLCHECKER_H
