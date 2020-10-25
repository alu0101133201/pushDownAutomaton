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
#include <iomanip>

#include "transition.hpp"
#include "state.hpp"

// Funciones auxiliares
void vectorToSet(std::vector<std::string> &initialVector, std::set<std::string> &destinationSet);
void storeLine(std::string &line, std::vector<std::string> &words, std::set<std::string> &setToStore);

class Automaton {
  private:
    std::vector<State> allStates; // Cjto de estados
    std::set<std::string>  automatonAlphabet;  // Alfabeto del autómata
    std::string initialState;  // Estado inicial
    std::set<int> acceptanceStates;  // Cjto de estados de aceptación
    std::set<std::string> stackAlphabet;  // Alfabeto de la pila
    std::string initialStackSymbol;  // Símbolo inicial de la pila
    
    bool trace; // Atributo que indica si estamos en modo traza o no

    /* Método que comprueba si el autómata está correctamente definido */
    bool checkAutomaton(void);
    /* Método que comprueba si las transiciones del autómata son correctas */
    bool checkTransitions(void);
    /* Método recursivo para realizar la ejecución del autómata */
    bool recursiveStep(std::string, std::string, std::stack<std::string>);
    /* Método que comprueba si un estado existe en el autómata */
    bool existState(std::string); 

  public:
    Automaton(char* automatonFile, int mode);
    ~Automaton();

    /* Método que comprueba si una cadena es reconocida por el autómata*/
    bool test(std::string);
    /* Método de impresión*/
    std::ostream& write(std::ostream& os);
};

