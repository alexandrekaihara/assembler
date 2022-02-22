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

    string res = this->Lex->to_lower("aB");
    assert(res.compare("ab") == 0);
    
    // Test if it cleans the first whitespaces
    string res = this->Lex->clean_line("  COPY A, B");
    assert(res.compare("COPY A, B") == 0);

    // Test if it removes the double spaces
    string res = this->Lex->clean_line("  COPY  A,      B");
    assert(res.compare("COPY A, B") == 0);

    // Test if it removes tabs and breaklines
    string res = this->Lex->clean_line("  \t\tCOPY A, \tB");
    assert(res.compare("COPY A, B") == 0);

    // Test if it removes comments
    string res = this->Lex->clean_line("  COPY A, B ; askksksdlafkçasl k lçdkfçalkweopiop  0909kdsçla 9012 i00");
    assert(res.compare("COPY A, B") == 0);

    // Test if it splits commands correctly
    vector<string> res = this->Lex->split("COPY A, B");
    vector<string> answer = {"COPY", "A", "B"};
    for(i=0; i<res.length(); i++)
        assert(res[i] == answer[i]);    
    
    // Test if it splits commands correctly with label
    vector<string> res = this->Lex->split("LABEL: COPY A, B");
    vector<string> answer = {"LABEL:", "COPY", "A", "B"};
    for(i=0; i<res.length(); i++)
        assert(res[i] == answer[i]);    

    // Test if it splits commands correctly with one parameter only
    vector<string> res = this->Lex->split("CONST -48");
    vector<string> answer = {"CONST", "-48"};
    for(i=0; i<res.length(); i++)
        assert(res[i] == answer[i]);    

    // Test if it splits commands correctly with no parameters
    vector<string> res = this->Lex->split("STOP");
    vector<string> answer = {"STOP"};
    for(i=0; i<res.length(); i++)
        assert(res[i] == answer[i]);    

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