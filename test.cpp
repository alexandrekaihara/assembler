//g++ test.cpp assembler.cpp lexical_analyzer.cpp semantic_analyzer.cpp syntatic_analyzer.cpp error_dealer.cpp object_generator.cpp
#include "test.hpp"
#include <cassert>
#include <iostream>


void TestLex::set_up(){
    this->Lex = new LexicalAnalyzer(OPTION_MAC_NUM, new ErrorDealer(OPTION_MAC_NUM));
}

void TestLex::tear_down(){
    delete this->Lex;
}

void TestLex::test(){
    string res = this->Lex->to_upper("abcdefghijklmnopqrstuvwxyz1234567890_");
    assert(res.compare("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_") == 0);

    res = this->Lex->to_upper("aB");
    assert(res.compare("AB") == 0);
    
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
    vector<string> answer = {"COPY", "A, ", "B"};
    for(int i=0; i<tokens.size(); i++)
        assert(tokens[i] == answer[i]);    
    
    // Test if it splits commands correctly with label
    tokens = this->Lex->split("LABEL: COPY A, B");
    answer = {"LABEL:", "COPY", "A, ", "B"};
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



void TestSyn::set_up(){
    char* input =(char*)"factorial.s";
    char* output = (char*)"output";
    this->A = new Assembler(OPTION_OBJ_NUM, input, output);
    this->Syn = new SyntacticAnalyzer(OPTION_MAC_NUM, new ErrorDealer(OPTION_MAC_NUM), this->A->DirectivesTable, this->A->InstructionsTable);
}

void TestSyn::tear_down(){
    delete this->A;
    delete this->Syn;
}

void TestSyn::test(){
    // Verify if a string containing number is detected
    assert(this->Syn->is_number("-10"));
    assert(this->Syn->is_number("20"));
    assert(this->Syn->is_number("-1a") == false);
    assert(this->Syn->is_number("aa") == false);

    // Assert if all directives are detected
    assert(this->Syn->is_directive("SPACE"));
    assert(this->Syn->is_directive("CONST"));
    assert(this->Syn->is_directive("EQU"));
    assert(this->Syn->is_directive("IF"));
    assert(this->Syn->is_directive("MACRO"));
    assert(this->Syn->is_directive("ENDMACRO"));
    assert(this->Syn->is_directive("ASDS") == false);

    // Assert if all instructions are detected
    assert(this->Syn->is_instruction("ADD"));
    assert(this->Syn->is_instruction("SUB"));
    assert(this->Syn->is_instruction("MULT"));
    assert(this->Syn->is_instruction("DIV"));
    assert(this->Syn->is_instruction("JMP"));
    assert(this->Syn->is_instruction("JMPN"));
    assert(this->Syn->is_instruction("JMPP"));
    assert(this->Syn->is_instruction("JMPZ"));
    assert(this->Syn->is_instruction("COPY"));
    assert(this->Syn->is_instruction("STORE"));
    assert(this->Syn->is_instruction("INPUT"));
    assert(this->Syn->is_instruction("OUTPUT"));
    assert(this->Syn->is_instruction("STOP"));
    assert(this->Syn->is_instruction("AAAAA") == false);

    // Test if all commands are detected
    assert(this->Syn->analyze({"SPACE"}, 0));
    assert(this->Syn->analyze({"CONST", "40"}, 0));
    assert(this->Syn->analyze({"CONST", "-40"}, 0));
    assert(this->Syn->analyze({"EQU", "LABEL"}, 0));
    assert(this->Syn->analyze({"IF", "LABEL"}, 0));
    assert(this->Syn->analyze({"MACRO"}, 0));
    assert(this->Syn->analyze({"ENDMACRO"}, 0));
    // Check if error is detected if number of arguments are invalid
    assert(this->Syn->analyze({"SPACE", "LABEL"}, 0) == false);
    assert(this->Syn->analyze({"EQU"}, 0) == false);
    // Check if error is detected if the directive name is wrong
    assert(this->Syn->analyze({"SPACES", "LABEL"}, 0) == false);
    // Check if the CONST reject non number values
    assert(this->Syn->analyze({"CONST", "LABEL"}, 0) == false);
    assert(this->Syn->analyze({"CONST", "-9s"}, 0) == false);
    
    // Test all instructions
    assert(this->Syn->analyze({"ADD", "LABEL"}, 0));
    assert(this->Syn->analyze({"SUB", "LABEL"}, 0));
    assert(this->Syn->analyze({"MULT", "LABEL"}, 0));
    assert(this->Syn->analyze({"DIV", "LABEL"}, 0));
    assert(this->Syn->analyze({"JMP", "LABEL"}, 0));
    assert(this->Syn->analyze({"JMPN", "LABEL"}, 0));
    assert(this->Syn->analyze({"JMPP", "LABEL"}, 0));
    assert(this->Syn->analyze({"JMPZ", "LABEL"}, 0));
    assert(this->Syn->analyze({"COPY", "LABEL, ", "LABEL"}, 0));
    assert(this->Syn->analyze({"STORE", "LABEL"}, 0));
    assert(this->Syn->analyze({"INPUT", "LABEL"}, 0));
    assert(this->Syn->analyze({"OUTPUT", "LABEL"}, 0));
    assert(this->Syn->analyze({"STOP"}, 0));
    // Check if error is detected if number of arguments are invalid
    assert(this->Syn->analyze({"ADD"}, 0) == false);
    assert(this->Syn->analyze({"STOP", "LABEL"}, 0) == false);
    // Check if error is detected if the directive name is wrong
    assert(this->Syn->analyze({"ADDD", "LABEL"}, 0) == false);
    // Check if the error of COPY is identified
    assert(this->Syn->analyze({"COPY", "LABEL,", "LABEL"}, 0) == false);
    assert(this->Syn->analyze({"COPY", "LABEL ", "LABEL"}, 0) == false);
    assert(this->Syn->analyze({"COPY", "LABEL", "LABEL"}, 0) == false);
}



void TestSem::set_up(){
    char* input =(char*)"factorial.s";
    char* output = (char*)"output";
    this->A = new Assembler(OPTION_OBJ_NUM, input, output);
    this->Sem = new SemanticAnalyzer(OPTION_MAC_NUM, new ErrorDealer(OPTION_MAC_NUM), this->A->SymbolsTable);
}

void TestSem::tear_down(){
    delete this->A;
    delete this->Sem;
}

void TestSem::test(){
    // Starts a program with EQU definition
    assert(this->Sem->check_EQU({"EQU", "1"}, "UM", 1));
    this->A->SymbolsTable["UM"] = {true, -1, 5};
    // Second instruction is a ADD
    assert(this->Sem->check_EQU({"ADD", "DOIS"}, "", 1));
    this->A->SymbolsTable["DOIS"] = {true, -1, 5};
    // Try to add a EQU definition after a normal instruction 
    assert(this->Sem->check_EQU({"EQU", "3"}, "TRES", 1) == false);

    // Check if the IF recognizes the UM: EQU 1 label
    assert(this->Sem->check_IF({"IF", "UM"}, 3));
    // check if the IF rejects the TREs label. because it couldn't be defined
    assert(this->Sem->check_IF({"IF", "TRES"}, 3) == false);

    // Define a ENDMACRO without macro is illegal
    assert(this->Sem->check_MACRO({"ENDMACRO"}, 4) == false);
    // Define macro
    assert(this->Sem->check_MACRO({"MACRO"}, 4));


    // Trying to define a defined label, must raise error
    assert(this->Sem->analyze({"MUL", "AUX"}, "UM", 4) == false);
    assert(this->Sem->analyze({"MUL", "AUX"}, "FATORIAL", 5) == false);
}


//void TestLex::set_up(){}

//void TestLex::tear_down(){}

//void TestLex::success_test(){}


int main(){
    TestLex* TLex = new TestLex();
    TLex->set_up();
    TLex->test();
    TLex->tear_down();

    TestSyn* TSyn = new TestSyn();
    TSyn->set_up();
    TSyn->test();
    TSyn->tear_down();

    TestSem* TSem = new TestSem();
    TSem->set_up();
    TSem->test();
    TSem->tear_down();
    return 0;
}