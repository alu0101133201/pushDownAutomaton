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
        std::string nextSt, std::vector<std::string> insertStackSymb, int localId) :
    id(localId),   
    initialState(iniSt), 
    consumeSymbol(consSymb), 
    consumeStackSymbol(consStackSymb), 
    nextState(nextSt), 
    insertStackSymbol(insertStackSymb) {}

Transition::~Transition() {}

int Transition::getID(void) const {
  return id;
}

std::string Transition::getInitialState(void) const {
  return initialState;
}
std::string Transition::getConsumeSymbol(void) const {
  return consumeSymbol;
}
std::string Transition::getConsumeStackSymbol(void) const {
  return consumeStackSymbol;
}
std::string Transition::getNextState(void) const {
  return nextState;
}
std::vector<std::string> Transition::getInsertStackSymbol(void) const {
  return insertStackSymbol;
}

bool Transition::checkAllStackSymb(std::set<std::string> alphabet) {
  for (size_t i = 0; i < insertStackSymbol.size(); i++) {
    if (insertStackSymbol[i] != "." && 
      alphabet.find(insertStackSymbol[i]) == alphabet.end())
      return false;
  }
  return true;
}

std::ostream& Transition::write(std::ostream &os) {
    os << "   " << initialState << ", ";
    os << consumeSymbol << ", ";
    os << consumeStackSymbol << ", ";
    os << nextState << ", ";
    for (size_t i = 0; i < insertStackSymbol.size(); i++) {
      os << insertStackSymbol[i] << " ";
    }
    os << "  id: " << id;
    os << "\n";
  return os;
}
