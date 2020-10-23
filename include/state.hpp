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
    std::string id;
    std::vector<Transition> transitions;

  public:
    State(std::string);
    ~State();

  std::string getID (void) const;
  void pushTransition(Transition);
  std::vector<Transition> getTransitions();
  
  std::vector<Transition> getPossibleTransitions(std::string stringSymbol, std::string stackSymbol);
  std::ostream& writeTransitions(std::ostream&) ;
};