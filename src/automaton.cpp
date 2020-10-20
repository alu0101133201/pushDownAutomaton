/**
 * Fichero que implementa la clase autómata. Esta clase representará
 * un simulador de un autómata con pila (por vaciado de pila)
 * Fecha: 11/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/

#include "automaton.hpp"

void vectorToSet(std::vector<std::string> &initialVector, std::set<std::string> &destinationSet) {
  for (size_t i = 0; i < initialVector.size(); i++) {
    destinationSet.insert(initialVector[i]);
  }
}

void vectorToStack(std::stack<std::string> &destinationStack, std::vector<std::string> &sourceVector) {
  for (size_t i = 0; i < sourceVector.size(); i++) {
    if (sourceVector[i] != ".")
      destinationStack.push(sourceVector[i]);
  }
}

void storeLine(std::string &line, std::vector<std::string> &words, std::set<std::string> &setToStore) {
    getWords(line, words); // Leemos el alfabeto de entrada de la cadena
    vectorToSet(words, setToStore);
    words.clear();
}

// Constructor del autómata de pila
Automaton::Automaton(char* automatonFile) {
  std::string route = "./examples/";
  std::string line;
  std::vector<std::string> words;
  route += automatonFile;
  std::ifstream file(route.c_str());

  if (file.is_open()) {
    while (getline(file, line)) {   // Eliminamos los comentarios
      if (line[0] != '#') break;
    }
    storeLine(line, words, states);  // Leemos el cjto de estados del autómata
    getline(file, line);
    storeLine(line, words, automatonAlphabet); // Leemos el alfabeto de entrada de la cadena
    getline(file, line);
    storeLine(line, words, stackAlphabet); // Leemos el alfabeto de entrada de la cadena
    getline(file, line);  // Leemos el estado inicial
    initialState = line;
    getline(file, line);  // Leemos símbolo inicial
    initialStackSymbol = line;
    transitionFunction.readFromFile(file);  // Construimos la función de transición

    if (!checkAutomaton()) {  // Comprobamos que el autómata cumpla la definición formal
      std::string s("ERROR EN TIEMPO DE EJECUCIÓN - El autómata no cumple con las restricciones formales\n");
      throw std::runtime_error(s);
    }

  } else {
    std::string s("ERROR EN TIEMPO DE EJECUCIÓN - No se pudo abrir el fichero\n");
    throw std::runtime_error(s);
  }
}

// Destructor del autómata de pila
Automaton::~Automaton() {}


bool Automaton::test(std::string testString) {
  std::string currentState = initialState;
  std::stack<std::string> currentStack;
  currentStack.push(initialStackSymbol);

  return recursiveStep(currentState, testString, currentStack);
}

bool Automaton::recursiveStep(std::string currentState, std::string testString,
    std::stack<std::string> currentStack) {
  std::cout << "Cadena por analizar: " << testString << "\n";
  if ((currentStack.empty()) && (testString.size() == 0)) {
    std::cout << "ACEPTADA\n";
    return true;
  }
  std::string currentSymbol = "";
  currentSymbol += testString[0];
  std::vector<Transition> possibleTransitions = transitionFunction.getFunctionOutput(currentState, 
      currentSymbol, currentStack.top()); // Obtenemos la siguiente transición
  if (possibleTransitions.size() == 0) 
    return false;
  
  currentStack.pop();  // Consumimos elemento top de la pila

  for(size_t i = 0; i < possibleTransitions.size(); i++) {
    if (possibleTransitions[i].getConsumeSymbol() != ".")
      testString.erase(testString.begin()); // Consumimos el elemento si no es una epsilon
    std::stack<std::string> iterationStack = currentStack;  // Preparamos una pila auxiliar para este camino
    std::vector<std::string> symbolsToAdd = possibleTransitions[i].getInsertStackSymbol();
    symbolsToAdd.reserve(0); 
    vectorToStack(iterationStack, symbolsToAdd);  // Añadimos a la pila los elementos de la transición

    recursiveStep(possibleTransitions[i].getNextState(), testString, iterationStack);
  }
  return false;
}

bool Automaton::checkAutomaton(void) {
  if (states.find(initialState) == states.end())
    return false;
  if (stackAlphabet.find(initialStackSymbol) == stackAlphabet.end())
    return false;
  return transitionFunction.check(states, automatonAlphabet, stackAlphabet);
}

std::ostream& Automaton::write(std::ostream& os) {
  os << " - - AUTÓMATA CARGADO - -\n· Conjunto de estados:\n  ";
  for (std::set<std::string>::iterator it = states.begin(); it != states.end(); ++it)
    os << *it << " ";
  os << "\n. Alfabeto de la cadena de entrada:\n  ";
  for (std::set<std::string>::iterator it = automatonAlphabet.begin(); it != automatonAlphabet.end(); ++it)
    os << *it << " ";
  os << "\n. Alfabeto de la pila:\n  ";
  for (std::set<std::string>::iterator it = stackAlphabet.begin(); it != stackAlphabet.end(); ++it)
    os << *it << " ";
  os << "\n. Estado inicial:\n  " << initialState << "\n";
  os << ". Símbolo inicial de la pila:\n  " << initialStackSymbol << "\n";
  os << ". Transiciones: \n";
  transitionFunction.write(os);
  return os;
}
