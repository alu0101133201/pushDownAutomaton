/**
 * Fichero que implementa la clase estado. Esta clase representará
 * un estado de un autómata de pila
 * Fecha: 23/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/

 #include "state.hpp"

State::State(std::string id_):
    id(id_) {}

State::~State() {}

std::string State::getID (void) const{
  return id;
}

void State::pushTransition(Transition tran) {
  transitions.push_back(tran);
}

std::vector<Transition> State::getTransitions() {
  return transitions;
}

std::vector<Transition> State::getPossibleTransitions(std::string stringSymbol, std::string stackSymbol) {
  std::vector<Transition> validTransitions;
  for (size_t i = 0; i < transitions.size(); i++) {
    if ((transitions[i].getInitialState() == id) &&
        ((transitions[i].getConsumeSymbol() == stringSymbol) || (transitions[i].getConsumeSymbol() == ".")) &&
        (transitions[i].getConsumeStackSymbol() == stackSymbol)) {
      validTransitions.push_back(transitions[i]);
    }
  }
  return validTransitions;
}

std::ostream& State::writeTransitions(std::ostream &os) {
  for (size_t i = 0; i < transitions.size(); i++) {
    transitions[i].write(os);
  }
  return os;
}

