#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED


#include "error_dealer.hpp"
#include "lexical_analyzer.hpp"
#include "object_generator.hpp"
#include "semantic_analyzer.hpp"
#include "syntatic_analyzer.hpp"
#include <string>
#include <vector>


using namespace std;


class Test{
protected:
    bool state = false;
public:
    virtual void set_up() = 0;
    virtual void tear_down() = 0;
    virtual void test() = 0;
    int run();
};


class TestLex{
    private:
        LexicalAnalyzer* Lex;
    public:
        void set_up();
        void tear_down();
        void test();
        int run();
};


#endif