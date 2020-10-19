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

std::vector<Transition> TransitionFunction::getFunctionOutput(std::string initialState, 
    std::string stringSymbol, std::string stackSymbol) {
  std::vector<Transition> validTransitions;
  for (size_t i = 0; i < transitions.size(); i++) {
    if ((transitions[i].getInitialState() == initialState) &&
        (transitions[i].getConsumeSymbol() == stringSymbol) &&
        (transitions[i].getConsumeStackSymbol() == stackSymbol)) {
      validTransitions.push_back(transitions[i]);
    }
  }
  return validTransitions;
}

void TransitionFunction::readFromFile(std::ifstream &file) {
  std::string line;
  std::vector<std::string> words;

  while (getline(file, line)) {
    getWords(line, words);
    std::vector<std::string> multipleStackSymb;
    for (size_t i = 4; i < words.size(); i++) {
      multipleStackSymb.push_back(words[i]);
    }
    Transition aux(words[0], words[1], words[2], words[3], multipleStackSymb);
    transitions.push_back(aux);
    words.clear();
  }
}

bool TransitionFunction::check(std::set<std::string> states, std::set<std::string> automatonAlphabet, 
  std::set<std::string> stackAlphabet) {
  for (size_t i = 0; i < transitions.size(); i++) {
    if ((states.find(transitions[i].getInitialState()) == states.end()) ||
        (automatonAlphabet.find(transitions[i].getConsumeSymbol()) == automatonAlphabet.end() 
            && transitions[i].getConsumeSymbol() != ".") ||
        (stackAlphabet.find(transitions[i].getConsumeStackSymbol()) == stackAlphabet.end()) ||
        (states.find(transitions[i].getNextState()) == states.end()) ||
        !(transitions[i].checkAllStackSymb(stackAlphabet))){
      return false;
    }
  }
  return true;
}

std::ostream& TransitionFunction::write(std::ostream& os) {
  for (size_t i = 0; i < transitions.size(); i++) {
    transitions[i].write(os);
  }
  return os;
}
