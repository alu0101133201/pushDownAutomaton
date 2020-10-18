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
#include <string.h>
#include <sstream>

class Automaton {
  private:
    std::set<std::string> states;// Cjto de estados
    std::set<std::string>  automatonAlphabet;  // Alfabeto del autómata
    std::string initialState; // Estado inicial
    // Función de transición
    std::set<int> acceptanceStates; // Cjto de estados de aceptación
    std::set<std::string> stackAlphabet;  // Alfabeto de la pila
    std::string initialStackSymbol; // Símbolo inicial de la pila

  public:
    Automaton(char* automatonFile);
    ~Automaton();

    std::ostream& write(std::ostream& os);
};

