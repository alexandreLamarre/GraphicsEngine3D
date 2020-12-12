#include "tester.h"

//Implementations details of Tester class

/**
 * Initialize a unittest object
 */
Tester::Tester(){
    messages = "";
    num_tests = 0;
    passed = 0;
}

/**
 * Add a test result and error message
 * @param s the boolean statement representing a unittest
 * @param m the error message to display should the test fail
 */
void Tester::add(bool s, std::string &m){
    num_tests++;
    if(s) passed ++;
    else{addFailMessage(m);}
}

/**
 * Add a test result and error message containing the expected and
 * obtained behaviour from the test
 * @param s the boolean statement representing a unittest
 * @param m the error message to display should the test fail
 * @param e the expected result
 * @param g the obtained result
 */
void Tester::add(bool s, std::string &m, std::string &e, std::string &g){
    num_tests++;
    if(s) passed ++;
    else {
        std::string new_message = m + "\n" + "Expected :" + e + "\n" + "Got: " + g;
        addFailMessage(new_message);
    }
}

/**
 * helper method for adding failed tests output to Tester Object.
 * @param m the error message to display should a test fail
 */
void Tester::addFailMessage(std::string &m){
    messages += m;
    messages += "\n";
}

/**
 * String representation of Tester Object
 * @param os the output file
 * @param t the tester to output to the output stream
 * @return output stream
 */
std::ostream& operator<<(std::ostream &os, const Tester &t){
    os << t.passed << "/" << t.num_tests << " tests passed. \n" << t.messages;
    return os;
}