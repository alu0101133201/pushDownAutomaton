/**
 * Fichero que define la clase estado. Esta clase representará
 * un estado de un autómata de pila
 * Fecha: 23/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/

#pragma once

#include "transition.hpp"
#include <iostream>
#include <string>
 
class State {
  private:
    std::string id; // identificador del estado
    std::vector<Transition> transitions;  // Cjto de transiciones del estado

  public:
    State(std::string);
    ~State();

  /* Getters*/
  std::string getID (void) const;
  std::vector<Transition> getTransitions();
  /* Metodo para añadirle una transición al autómata*/
  void pushTransition(Transition);
  /* Método que devuelve las transiciones posibles dado un símbolo de entrada y un símbolo de pila */
  std::vector<Transition> getPossibleTransitions(std::string stringSymbol, std::string stackSymbol);
  /* Método de impresión del autómata */
  std::ostream& writeTransitions(std::ostream&) ;
};