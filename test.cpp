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
    // Test if it can detect correctly the 
    assert(this->Lex->is_empty_line(" "));
    assert(this->Lex->is_empty_line(" \t"));
    assert(this->Lex->is_empty_line("ADD UM ;Teste") == false);
    assert(this->Lex->is_empty_line(";Teste"));
    assert(this->Lex->is_empty_line(" ;Teste"));

    string res = this->Lex->to_upper("abcdefghijklmnopqrstuvwxyz1234567890_");
    assert(res.compare("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_") == 0);

    res = this->Lex->to_upper("aB");
    assert(res.compare("AB") == 0);
    
    // Test if it cleans the first whitespaces
    res = this->Lex->clean_line("  COPY A, B");
    assert(res.compare("COPY A, B") == 0);

    // Test if it cleans the last whitespaces
    res = this->Lex->clean_line("COPY A, B  ");
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
    assert(tokens.size() == 3);

    // Test if it splits commands correctly with label
    tokens = this->Lex->split("LABEL: COPY A, B");
    answer = {"LABEL:", "COPY", "A, ", "B"};
    for(int i=0; i<tokens.size(); i++)
        assert(tokens[i] == answer[i]);    
    assert(tokens.size() == 4);

    // Test if it splits commands correctly with one parameter only
    tokens = this->Lex->split("CONST -48");
    answer = {"CONST", "-48"};
    for(int i=0; i<tokens.size(); i++)
        assert(tokens[i] == answer[i]);    
    assert(tokens.size() == 2);

    // Test if it splits commands correctly with no parameters
    tokens = this->Lex->split("STOP");
    answer = {"STOP"};
    for(int i=0; i<tokens.size(); i++)
        assert(tokens[i] == answer[i]);  
    assert(tokens.size() == 1);

    // Test if it splits commands correctly with no parameters
    tokens = this->Lex->split("TEST:");
    answer = {"TEST:"};
    for(int i=0; i<tokens.size(); i++)
        assert(tokens[i] == answer[i]);    
    assert(tokens.size() == 1);

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
    this->Syn = new SyntacticAnalyzer(OPTION_MAC_NUM, new ErrorDealer(OPTION_MAC_NUM), &this->A->DirectivesTable, &this->A->InstructionsTable);
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
    this->Syn->set_macro_name("TESTE");
    assert(this->Syn->analyze({"SPACES", "LABEL"}, 0) == false);
    assert(this->Syn->analyze({"TESTE"}, 0));
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
    this->Sem = new SemanticAnalyzer(OPTION_MAC_NUM, new ErrorDealer(OPTION_MAC_NUM), &this->A->SymbolsTable);
}

void TestSem::tear_down(){
    delete this->A;
    delete this->Sem;
}

void TestSem::test(){
    // Starts a program with EQU definition
    assert(this->Sem->check_EQU({"EQU", "1"}, "UM", 1));
    this->A->SymbolsTable["UM"] = {true, -1, 5};
    assert(this->Sem->check_EQU({"EQU", "TESTE"}, "TESTE", 1));
    this->A->SymbolsTable["TESTE"] = {true, -1, 5};
    assert(this->Sem->check_EQU({"EQU", "20"}, "VINTE", 1));
    this->A->SymbolsTable["VINTE"] = {true, -1, 5};
    // Second instruction is a ADD
    assert(this->Sem->check_EQU({"ADD", "DOIS"}, "", 1));
    this->A->SymbolsTable["DOIS"] = {true, -1, 5};
    // Try to add a EQU definition after a normal instruction 
    assert(this->Sem->check_EQU({"EQU", "3"}, "TRES", 1) == false);

    // Check if the IF recognizes the UM: EQU 1 label
    assert(this->Sem->check_IF({"IF", "UM"}, 3));
    // check if the IF rejects the TREs label. because it couldn't be defined
    assert(this->Sem->check_IF({"IF", "TRES"}, 3) == false);
    // Must fail because IF does not support string values
    assert(this->Sem->check_IF({"IF", "TESTE"}, 3) == false);
    // Must fail because it may not support numbers different from 1 and 0
    assert(this->Sem->check_IF({"IF", "VINTE"}, 3) == false);

    // Define a ENDMACRO without macro is illegal
    assert(this->Sem->check_MACRO({"ENDMACRO"}, "", 4) == false);
    // Define macro
    assert(this->Sem->check_MACRO({"MACRO"}, "", 4));
    // Will fail because the ENDMACRO was not defined
    assert(this->Sem->end_check_MACRO() == false);
    // Test it gives no error after defining ENDMACRO correctly
    assert(this->Sem->check_MACRO({"ENDMACRO"}, "", 5));
    // May fail because the macro was not used
    assert(this->Sem->end_check_MACRO() == false);
    // Will accept because ENDMACRO WAS DEFINED AND MACRO WAS USED
    this->Sem->set_macro_used();
    assert(this->Sem->end_check_MACRO());

    // Trying to define a defined label, must raise error
    assert(this->Sem->analyze({"MUL", "AUX"}, "UM", 6) == false);
    // Case in which the label is not defined    
    assert(this->Sem->analyze({"MUL", "AUX"}, "FATORIAL", 7));
}


void TestObjGen::set_up(){
    char* input =(char*)"factorial.s";
    char* output = (char*)"output";
    this->A = new Assembler(OPTION_MAC_NUM, input, output);
    this->ObjGen = new ObjectGenerator(OPTION_MAC_NUM, new ErrorDealer(OPTION_MAC_NUM), &this->A->DirectivesTable, &this->A->InstructionsTable, &this->A->SymbolsTable);
}

void TestObjGen::tear_down(){
    delete this->A;
    delete this->ObjGen;
}

void TestObjGen::test(){
        this->ObjGen->add_symbol("TESTE", true, -1, 5);
        assert(this->ObjGen->SymbolsTable->count("TESTE") != 0);

        assert(this->ObjGen->symbol_exists("TESTE"));
        assert(this->ObjGen->symbol_exists("ALHO") == false);

        assert(this->ObjGen->is_symbol_defined("TESTE"));
        assert(this->ObjGen->is_symbol_defined("ALHO") == false);

        this->ObjGen->update_symbol("TESTE", false, 3, 5);
        assert(this->ObjGen->is_symbol_defined("TESTE") == false);
        
        Symbol sym = this->ObjGen->get_symbol("TESTE");
        assert(sym.last_occurence == 3);

        assert(this->ObjGen->get_last_occurence_symbol("TESTE") == 3);

        this->ObjGen->add_equ_definition("ONE", "1", false);
        assert(this->ObjGen->EQU_definitions["ONE"].token.compare("1") == 0);
        
        assert(this->ObjGen->resolve_equ_definitions("ONE").compare("1") == 0);
        
        assert(this->ObjGen->is_equ_definition("ONE"));
        assert(this->ObjGen->is_equ_definition("TWO") == false);

        EQU equ = this->ObjGen->get_equ("ONE");
        assert(equ.token.compare("1") == 0);

        this->ObjGen->set_equ_used("ONE");
        assert(this->ObjGen->EQU_definitions["ONE"].used == true);

        assert(this->ObjGen->get_opcode("ADD") == 1);
        
        this->ObjGen->add_to_objectfile(10);
        assert(this->ObjGen->objectfile[0] == 10);

        this->ObjGen->update_objectfile(20, 0);
        assert(this->ObjGen->objectfile[0] == 20);

        assert(this->ObjGen->get_instruction_size("ADD") == 2);
        assert(this->ObjGen->get_instruction_size("COPY") == 3);

        assert(this->ObjGen->get_directive_size("SPACE") == 1);
        assert(this->ObjGen->get_directive_size("EQU") == 0);

        // Creating scenerio to test further reference resolv
        this->ObjGen->add_space_definition("AUX", 0);
        assert(this->ObjGen->spacedefinition[0].name.compare("AUX") == 0);
        assert(this->ObjGen->spacedefinition[0].value == 0);
        this->ObjGen->add_space_definition("AUX2", 2);
        assert(this->ObjGen->spacedefinition[1].name.compare("AUX2") == 0);
        this->ObjGen->add_space_definition("TEMP", 0);
        assert(this->ObjGen->spacedefinition[2].name.compare("TEMP") == 0);

        this->ObjGen->add_symbol("AUX", true, 8, -1);
        this->ObjGen->add_symbol("AUX2", true, 5, -1);
        this->ObjGen->add_symbol("TEMP", true, 7, -1);

        assert(this->ObjGen->is_a_space_label("AUX"));
        assert(this->ObjGen->is_a_space_label("TESTE") == false);
        
        int position_counter = 1;
        this->ObjGen->add_to_objectfile(-1); // pos 1 / AUX: -1
        position_counter++;
        this->ObjGen->add_to_objectfile(-1); // pos 2 / AUX2: -1
        position_counter++;
        this->ObjGen->add_to_objectfile(-1); // pos 3 / TEMP: -1
        position_counter++;
        this->ObjGen->add_to_objectfile(1); // pos 4 / AUX: -1/1
        position_counter++;
        this->ObjGen->add_to_objectfile(2); // pos 5 / AUX2: -1/2
        position_counter++;
        this->ObjGen->add_to_objectfile(-1); // pos 6 / TESTE: -1
        position_counter++;
        this->ObjGen->add_to_objectfile(3); // pos 7 / TEMP: -1/3
        position_counter++;
        this->ObjGen->add_to_objectfile(4); // pos 8 / AUX: -1/1/4
        position_counter++;
        this->ObjGen->add_to_objectfile(6); // pos 9 / TESTE: -1/6
        position_counter++;

        this->ObjGen->further_reference_dealer("TESTE", 9);
        assert(this->ObjGen->objectfile[9] == 5);
        assert(this->ObjGen->objectfile[6] == 5);

        this->ObjGen->add_spaces_to_objectfile(position_counter);
        // Check AUX references
        assert(this->ObjGen->objectfile[8] == 10);
        assert(this->ObjGen->objectfile[4] == 10);
        assert(this->ObjGen->objectfile[1] == 10);
        // Check AUX2 references
        assert(this->ObjGen->objectfile[5] == 11);
        assert(this->ObjGen->objectfile[2] == 11);
        // Check AUX2 references
        assert(this->ObjGen->objectfile[7] == 12);
        assert(this->ObjGen->objectfile[3] == 12);
        
        // Test if the content is the right one and the file is created
        string filename = "test.out";
        this->ObjGen->generate_objectfile(filename);
        string file = this->A->read_file((char*)filename.c_str());
        string outfile = "20 10 11 12 10 11 5 12 10 5 0 2 0";
        assert(file.compare(outfile) == 0);
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

    TestObjGen* TObjGen = new TestObjGen();
    TObjGen->set_up();
    TObjGen->test();
    TObjGen->tear_down();
    return 0;
}