Disciplina: Software Básico
Código: CIC104
Turma: B
Docente: Bruno Luiggi Macchiavello Espinoza
Discente: Alexandre Mitsuru Kaihara

TRABALHO 1

1. Dependências
O compilador utilizado foi apenas o g++ na versão:    
    - g++ versão (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0.
Para instalar o g++ na versão utilizada no Linux, use o seguinte comnado:
    - sudo apt install g++=4:9.3.0-1ubuntu2

2. Instruções de uso
    Para compilar, acesse o diretório raiz onde se localiza a main.cpp e execute o seguinte comando:
    g++ -o montador  main.cpp assembler.cpp lexical_analyzer.cpp semantic_analyzer.cpp syntactic_analyzer.cpp object_generator.cpp error_dealer.cpp

