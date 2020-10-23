/**
 * Fichero que define la clase autómata. Esta clase representará
 * un simulador de un autómata con pila (por vaciado de pila)
 * Fecha: 11/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/

#pragma once

#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <string>
#include <fstream>

#include "transitionFunction.hpp"
#include "transition.hpp"
#include "state.hpp"

void vectorToSet(std::vector<std::string> &initialVector, std::set<std::string> &destinationSet);
void storeLine(std::string &line, std::vector<std::string> &words, std::set<std::string> &setToStore);

class Automaton {
  private:
    std::vector<State> allStates; // Cjto de estados
    std::set<std::string>  automatonAlphabet;  // Alfabeto del autómata
    std::string initialState;  // Estado inicial
    TransitionFunction transitionFunction;  // Función de transición
    std::set<int> acceptanceStates;  // Cjto de estados de aceptación
    std::set<std::string> stackAlphabet;  // Alfabeto de la pila
    std::string initialStackSymbol;  // Símbolo inicial de la pila

  public:
    Automaton(char* automatonFile);
    ~Automaton();

    bool existState(std::string);
    bool test(std::string);
    bool checkAutomaton(void);
    bool checkTransitions(void);

    bool recursiveStep(std::string, std::string, std::stack<std::string>);
    std::ostream& write(std::ostream& os);
};

