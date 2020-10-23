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
#include <set>

void getWords(std::string initialString, std::vector<std::string> &words);

class Transition {
  private:
    std::string initialState;
    std::string consumeSymbol;
    std::string consumeStackSymbol;
    std::string nextState;
    std::vector<std::string> insertStackSymbol;

  public:
    Transition(std::string iniSt, std::string consSymb, std::string consStackSymb,
        std::string nextSt, std::vector<std::string> insertStackSymb);
    ~Transition();

    std::string getInitialState(void) const;
    std::string getConsumeSymbol(void) const;
    std::string getConsumeStackSymbol(void) const;
    std::string getNextState(void) const;
    std::vector<std::string> getInsertStackSymbol(void) const;

    bool checkAllStackSymb(std::set<std::string> alphabet);

    std::ostream& write(std::ostream &os);
};
