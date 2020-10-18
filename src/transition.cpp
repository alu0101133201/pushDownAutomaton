/**
 * Fichero que implementa la clase transición. Esta clase representará
 * una transición de nuestro autómata de pila
 * Fecha: 18/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/

#include "transition.hpp"

// Función auxiliar para dividir una cadena por los espacios
void getWords(std::string initialString, std::vector<std::string> &words) {
  std::istringstream ourString(initialString);
  do {
    std::string word;
    ourString >> word;
    if (word.length() > 0)
      words.push_back(word);
  } while(ourString);
}

Transition::Transition(std::string iniSt, std::string consSymb, std::string consStackSymb,
        std::string nextSt, std::string insertStackSymb) :
    initialState(iniSt), 
    consumeSymbol(consSymb), 
    consumeStackSymbol(consStackSymb), 
    nextState(nextSt), 
    insertStackSymbol(insertStackSymb) {}

Transition::~Transition() {}

std::string Transition::getInitialState(void) {
  return initialState;
}
std::string Transition::getConsumeSymbol(void) {
  return consumeSymbol;
}
std::string Transition::getConsumeStackSymbol(void) {
  return consumeStackSymbol;
}
std::string Transition::getNextState(void) {
  return nextState;
}
std::string Transition::getInsterStackSymbol(void) {
  return insertStackSymbol;
}

std::ostream& Transition::write(std::ostream &os) {
    os << "   " << initialState << ", ";
    os << consumeSymbol << ", ";
    os << consumeStackSymbol << ", ";
    os << nextState << ", ";
    os << insertStackSymbol << "\n";
  return os;
}
