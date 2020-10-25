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
    int id;

    std::string initialState; // Estado inicial
    std::string consumeSymbol;  // Símbolo de la cadena que se comsume
    std::string consumeStackSymbol; // Símbolo de la pila que se consume
    std::string nextState;  // Estado destino de la transición
    std::vector<std::string> insertStackSymbol; // Símbolo a insertar en la pila

  public:
    Transition(std::string iniSt, std::string consSymb, std::string consStackSymb,
        std::string nextSt, std::vector<std::string> insertStackSymb, int localId);
    ~Transition();

    /* Getters */
    int getID(void) const;
    std::string getInitialState(void) const;
    std::string getConsumeSymbol(void) const;
    std::string getConsumeStackSymbol(void) const;
    std::string getNextState(void) const;
    std::vector<std::string> getInsertStackSymbol(void) const;

    /* Método que comprueba que todos los símbolo de la pila existan en el alfabeto de la misma*/
    bool checkAllStackSymb(std::set<std::string> alphabet);

    // Método de impresión
    std::ostream& write(std::ostream &os);
};
