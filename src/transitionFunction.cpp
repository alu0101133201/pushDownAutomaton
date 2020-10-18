/**
 * Fichero que implementa la clase función de transición. Esta clase representará
 * una transición de nuestro autómata de pila
 * Fecha: 18/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/

 #include "transitionFunction.hpp"

TransitionFunction::TransitionFunction(void) {}

TransitionFunction::~TransitionFunction() {}

void TransitionFunction::readFromFile(std::ifstream &file) {
  std::string line;
  std::vector<std::string> words;

  while (getline(file, line)) {
    getWords(line, words);
    words.clear();
    Transition aux(words[0], words[1], words[2], words[3], words[4]);
    transitions.push_back(aux);
  }
}

std::ostream& TransitionFunction::write(std::ostream& os) {
  for (size_t i = 0; i < transitions.size(); i++) {
    transitions[i].write(os);
  }
  return os;
}
