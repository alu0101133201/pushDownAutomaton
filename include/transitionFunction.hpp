/**
 * Fichero que define la clase función de transición. Esta clase representará
 * una transición de nuestro autómata de pila
 * Fecha: 18/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "transition.hpp"

class TransitionFunction {
  private:
    std::vector<Transition> transitions;

  public:
    TransitionFunction();
    ~TransitionFunction();

    void readFromFile(std::ifstream &file);
    std::ostream& write(std::ostream& os);
};