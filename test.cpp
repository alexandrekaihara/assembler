#include "test.hpp"


void Test::run(){
    TestLex* TLex = new TestLex();
    TLex->set_up();

    TLex->test();

    TLex->tear_down();
}


void TestLex::set_up(){
    this->Lex = new LexicalAnalyzer(OPTION_OBJ, new ErrorDealer(OPTION_OBJ));
}

void TestLex::tear_down(){
    delete this->Lex;
}

void TestLex::test(){
    string res = this->Lex->to_lower("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_");
    assert(res.compare("abcdefghijklmnopqrstuvwxyz1234567890_") == 0);

    res = this->Lex->to_lower("aB");
    assert(res.compare("ab") == 0);
    
    // Test if it cleans the first whitespaces
    res = this->Lex->clean_line("  COPY A, B");
    assert(res.compare("COPY A, B") == 0);

    // Test if it removes the double spaces
    res = this->Lex->clean_line("  COPY  A,      B");
    assert(res.compare("COPY A, B") == 0);

    // Test if it removes tabs and breaklines
    res = this->Lex->clean_line("  \t\tCOPY A, \tB");
    assert(res.compare("COPY A, B") == 0);

    // Test if it removes comments
    res = this->Lex->clean_line("  COPY A, B ; askksksdlafkçasl k lçdkfçalkweopiop  0909kdsçla 9012 i00");
    assert(res.compare("COPY A, B") == 0);

    // Test if it splits commands correctly
    vector<string> tokens = this->Lex->split("COPY A, B");
    vector<string> answer = {"COPY", "A", "B"};
    for(i=0; i<tokens.length(); i++)
        assert(tokens[i] == answer[i]);    
    
    // Test if it splits commands correctly with label
    tokens = this->Lex->split("LABEL: COPY A, B");
    answer = {"LABEL:", "COPY", "A", "B"};
    for(i=0; i<tokens.length(); i++)
        assert(tokens[i] == answer[i]);    

    // Test if it splits commands correctly with one parameter only
    tokens = this->Lex->split("CONST -48");
    answer = {"CONST", "-48"};
    for(i=0; i<tokens.length(); i++)
        assert(tokens[i] == answer[i]);    

    // Test if it splits commands correctly with no parameters
    tokens = this->Lex->split("STOP");
    answer = {"STOP"};
    for(i=0; i<tokens.length(); i++)
        assert(tokens[i] == answer[i]);    

    // Test if it detects if there is more than 99 chars
    assert(this->Lex->is_valid_variable_name("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") == false);
    // Test if it detects invalid char
    assert(this->Lex->is_valid_variable_name("!") == false);
    // Test if it detects if starts with number
    assert(this->Lex->is_valid_variable_name("1a") == false);
    // Test if accepts a correct name
    assert(this->Lex->is_valid_variable_name("IAL900_aa"));

    // Assert if is a label
    assert(this->Lex->is_label("LABEL:"));
    assert(this->Lex->is_label("LABEL") == false);

    this->state = true;
}



//void TestLex::set_up(){}

//void TestLex::tear_down(){}

//void TestLex::success_test(){}


int main(){
    Test* T = new Test();
    T->run();
    return 0;
}