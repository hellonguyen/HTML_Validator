# HTML_Validator Project

## Why the project matters?

The coding project will help me have a deep understanding of Stacks, Queues, and Lists data structures. The project will have a method to check whether the HTML (at simple level) is valid or not.

## HTML Validator Interface

***Constructor:*** assigns strings into self_closing_tags unsorted_set

***bool load(const string &file_path):*** Takes the path of a html file and loads it into a Queue one word at a time.  The method reads in the file one character at a time, using a state machine with 4  states to parse the tags and words into a Queue for later evaluation.

***bool isMatch(const string & open, const string & close):*** The method compares opening and closing tags to determine whether they match or not

***bool isClosing(const string &s):*** The method checks whether the tag is closing or not

***bool isSelfClosing(const string & s):*** * The method checks whether the tag is in the set of self_closing_tags or not

***bool isWord(const string &s):***  The method checks whether the string is a word (not tag) or not

***bool isValid():*** The method check whether the HTML is valid or not
