//g++ test.cpp assembler.cpp lexical_analyzer.cpp semantic_analyzer.cpp syntatic_analyzer.cpp error_dealer.cpp object_generator.cpp
#include "test.hpp"
#include <cassert>
#include <iostream>


void Test::run(){
}


void TestLex::set_up(){
    this->Lex = new LexicalAnalyzer(OPTION_OBJ_NUM, new ErrorDealer(OPTION_OBJ_NUM));
}

void TestLex::tear_down(){
    delete this->Lex;
}

void TestLex::test(){
    string res = this->Lex->to_lower("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_");
    cout << res << "\n";
    assert(res.compare("abcdefghijklmnopqrstuvwxyz1234567890_") == 0);

    res = this->Lex->to_lower("aB");
    cout << res << "\n";
    assert(res.compare("ab") == 0);
    
    // Test if it cleans the first whitespaces
    res = this->Lex->clean_line("  COPY A, B");
    stringstream ss;
    ss << res.compare("COPY A, B"); 
    cout << res << " " << aa.str() <<  "\n";
    assert(res.compare("COPY A, B") == 0);

    // Test if it removes the double spaces
    res = this->Lex->clean_line("  COPY  A,      B");
    cout << res << "\n";
    assert(res.compare("COPY A, B") == 0);

    // Test if it removes tabs and breaklines
    res = this->Lex->clean_line("  \t\tCOPY A, \tB");
    cout << res << "\n";
    assert(res.compare("COPY A, B") == 0);

    // Test if it removes comments
    res = this->Lex->clean_line("  COPY A, B ; askksksdlafkçasl k lçdkfçalkweopiop  0909kdsçla 9012 i00");
    cout << res << "\n";
    assert(res.compare("COPY A, B") == 0);

    // Test if it splits commands correctly
    vector<string> tokens = this->Lex->split("COPY A, B");
    vector<string> answer = {"COPY", "A", "B"};
    for(int i=0; i<tokens.size(); i++)
        assert(tokens[i] == answer[i]);    
    
    // Test if it splits commands correctly with label
    tokens = this->Lex->split("LABEL: COPY A, B");
    answer = {"LABEL:", "COPY", "A", "B"};
    for(int i=0; i<tokens.size(); i++)
        assert(tokens[i] == answer[i]);    

    // Test if it splits commands correctly with one parameter only
    tokens = this->Lex->split("CONST -48");
    answer = {"CONST", "-48"};
    for(int i=0; i<tokens.size(); i++)
        assert(tokens[i] == answer[i]);    

    // Test if it splits commands correctly with no parameters
    tokens = this->Lex->split("STOP");
    answer = {"STOP"};
    for(int i=0; i<tokens.size(); i++)
        assert(tokens[i] == answer[i]);    

    // Test if it detects if there is more than 99 chars
    assert(this->Lex->is_valid_variable_name("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 0) == false);
    // Test if it detects invalid char
    assert(this->Lex->is_valid_variable_name("!", 0) == false);
    // Test if it detects if starts with number
    assert(this->Lex->is_valid_variable_name("1a", 0) == false);
    // Test if accepts a correct name
    assert(this->Lex->is_valid_variable_name("IAL900_aa", 0));

    // Assert if is a label
    assert(this->Lex->is_label("LABEL:"));
    assert(this->Lex->is_label("LABEL") == false);
}



//void TestLex::set_up(){}

//void TestLex::tear_down(){}

//void TestLex::success_test(){}


int main(){
    TestLex* TLex = new TestLex();
    TLex->set_up();

    TLex->test();

    TLex->tear_down();
    return 0;
}