#include "HTMLChecker.h"


HTMLChecker::HTMLChecker() {
    self_closing_tags = {
            "<!doctype>", "<area>", "<base>", "<br>", "<col>", "<embed>", "<hr>",
            "<img>", "<input>", "<link>", "<meta>", "<param>", "<source>", "<track>", "<wbr>",
            "<!doctype/>", "<area/>", "<base/>", "<br/>", "<col/>", "<embed/>", "<hr/>",
            "<img/>", "<input/>", "<link/>", "<meta/>", "<param/>", "<source/>", "<track/>", "<wbr/>"
    };
}



bool HTMLChecker::load(const string &file_path) {
    // open the file and make sure there is something in it.
    fstream file_in(file_path, fstream::in);
    bool is_empty = file_in.peek() == std::ifstream::traits_type::eof();
    if (is_empty) return false;

    string buff = "";            // holds the word or tag string as we build it.
    char character;              // holds the char we read from the file
    State state = whitespace;    // set our initial state to whitespace

    // loop though each char in the file
    while (file_in >> noskipws >> character) {

        if (state == whitespace) {
            if (!isspace(character)) {
                // if you find a < is the start of a tag
                // otherwise its the start of a word
                if (character == '<') state = tag;
                else state = word;
                buff = character;
            }
        } else if (state == tag) {
            // if it's a > we've reached the end of the tag
            if (character == '>') {
                buff += '>';
                state = whitespace;
                // add the tag to the heml elements queue
                html_elements.push(buff);
                buff = "";

            } else if (isspace(character)) {
                // space in the tag means we're looking at attributes
                state = tag_attr;
            } else {
                buff += tolower(character);
            }
        } else if (state == tag_attr) {
            // in the tag attributes ignore everything but the >
            if (character == '>') {
                buff += '>';
                html_elements.push(buff);
                buff = "";
                state = whitespace;
            }
        } else if (state == word) {
            if (isspace(character)) {
                html_elements.push(buff);
                buff = "";
                state = whitespace;
            } else if (character == '<') {
                html_elements.push(buff);
                buff = "";
                state = tag;
                buff += character;
            } else {
                buff += character;
            }
        }
    }
    return true;
}
bool HTMLChecker::isMatch(const string & open, const string & close)
{
    // take substr of close to omit the first part, including </
    string sub_close= close.substr(2);
    // determine whether the rest of closing tag matches with the open tag or not
    long found = open.find(sub_close);
    if (found==string::npos)
    {
        return false;
    }
    return true;
}
bool HTMLChecker::isClosing(const string &s)
{
    // the closing tag should contain "/"
    int pos=s.find("/");
    if (pos==1)
    {
        return true;
    }
    return false;
}
bool HTMLChecker::isSelfClosing(const string & s)
{
    if(self_closing_tags.count(s))
    {
        return true;
    }
    return false;
}
bool HTMLChecker::isWord(const string &s)
{
    int pos=s.find("<");
    if (pos==0)
    {
        return false;
    }
    return true;
}
bool HTMLChecker::isValid()
{
    stack<string> stack;
    int i=0;
    int j=html_elements.size();
    do
    {
        // if the tag is self closing or a word, we remove it from the queue
        if (isSelfClosing(html_elements.front()) || isWord(html_elements.front())) {html_elements.pop();}
        // if it is opening tag ->push into stack and delete from queue
        else if (!isClosing(html_elements.front()))
        {
            stack.push(html_elements.front());
            html_elements.pop();
        }
        // check if it is closing tag or not
        else if (isClosing(html_elements.front()))
        {
            if (stack.empty()) // check whether the stack is empty or not
            {
                // if the stack is empty -> return false
                return false;
            }
            else
            {
                // compare whether opening and closing tags match or not
                if(isMatch(stack.top(),html_elements.front()))
                    //if match -> delete from queue and stack
                {
                    stack.pop();
                    html_elements.pop();
                }
                else
                {
                    // return false if they don't match
                    return false;
                }
            }
        }
        i++;
    } while(i<j);
    // if the end of the queue is reached and the stack is not empty.
    if(stack.size()>=1) {return false;}
    return true;
}


