#ifndef GRAPHICSENGINE3D_TESTER_H
#define GRAPHICSENGINE3D_TESTER_H

#endif //GRAPHICSENGINE3D_TESTER_H
#include <string>
#include <iostream>
/**
 * Test object for Unittests
 */
class Tester{
public:
    Tester();
    void add(bool s, std::string &m);
    void add(bool s, std::string &m, std::string &e, std::string &g);
    friend std::ostream& operator<<(std::ostream &os, const Tester& t);
private:
    void addFailMessage(std::string &m);
    std::string messages;
    int num_tests;
    int passed;
};


/**
 * Function to print the output of all Tester Objects provided
 * @param tests the Tester Objects provided
 */
void getAllTestResults(std::initializer_list<Tester> tests){
    for(auto &test: tests){
        std::cout << "========================================\n"
            << test<< "\n \n" << "========================================\n" ;
    }
}