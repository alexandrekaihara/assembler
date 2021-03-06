#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED


#include "etc.hpp"
#include "assembler.hpp"
#include "error_dealer.hpp"
#include "lexical_analyzer.hpp"
#include "object_generator.hpp"
#include "semantic_analyzer.hpp"
#include "syntactic_analyzer.hpp"
#include <string>
#include <algorithm>
#include <vector>


using namespace std;


class Test{
public:
    virtual void set_up() = 0;
    virtual void tear_down() = 0;
    virtual void test() = 0;
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


class TestSyn{
    private:
        Assembler* A;
        SyntacticAnalyzer* Syn;
    public:
        void set_up();
        void tear_down();
        void test();
        int run();
};


class TestSem{
    private:
        Assembler* A;
        SemanticAnalyzer* Sem;
    public:
        void set_up();
        void tear_down();
        void test();
        int run();
};


class TestObjGen{
    private:
        Assembler* A;
        ObjectGenerator* ObjGen;
    public:
        void set_up();
        void tear_down();
        void test();
        int run();
};


class TestAssembler{
    public:
        void set_up();
        void tear_down();
        void test();
        int run();
};


#endif