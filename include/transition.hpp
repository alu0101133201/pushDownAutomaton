/**
 * Fichero que define la clase transición. Esta clase representará
 * una transición de nuestro autómata de pila
 * Fecha: 18/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

void getWords(std::string initialString, std::vector<std::string> &words);

class Transition {
  private:
    std::string initialState;
    std::string consumeSymbol;
    std::string consumeStackSymbol;
    std::string nextState;
    std::string insertStackSymbol;

  public:
    Transition(std::string iniSt, std::string consSymb, std::string consStackSymb,
        std::string nextSt, std::string insertStackSymb);
    ~Transition();

    std::string getInitialState(void);
    std::string getConsumeSymbol(void);
    std::string getConsumeStackSymbol(void);
    std::string getNextState(void);
    std::string getInsterStackSymbol(void);

    std::ostream& write(std::ostream &os);
};
