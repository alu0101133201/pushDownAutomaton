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
  for (int i = sourceVector.size() - 1; i >= 0; i--) {
    if (sourceVector[i] != ".")
      destinationStack.push(sourceVector[i]);
  }
}

void storeLine(std::string &line, std::vector<std::string> &words, std::set<std::string> &setToStore) {
    getWords(line, words); // Leemos el alfabeto de entrada de la cadena
    vectorToSet(words, setToStore);
    words.clear();
}  

void showStack(std::stack<std::string> stack) {
  std::string result = "";
  while (!stack.empty()) {
    result += stack.top();
    stack.pop();
  }
  std::cout << std::setw(10) << result;
}

// Constructor del autómata de pila
Automaton::Automaton(char* automatonFile, int mode) {
  std::string route = "./examples/";
  std::string line;
  std::vector<std::string> words;
  route += automatonFile;
  std::ifstream file(route.c_str());

  if (mode == 1) 
    trace = true;
  else 
    trace = false;

  if (file.is_open()) {
    while (getline(file, line)) {   // Eliminamos los comentarios
      if (line[0] != '#') break;
    }
    getWords(line, words);  // Leemos el cjto de estados del autómata
    for (size_t i = 0; i < words.size(); i++) { 
      allStates.push_back(*(new State(words[i])));
    }
    getline(file, line);
    storeLine(line, words, automatonAlphabet); // Leemos el alfabeto de entrada de la cadena
    getline(file, line);
    storeLine(line, words, stackAlphabet); // Leemos el alfabeto de entrada de la cadena
    getline(file, line);  // Leemos el estado inicial
    initialState = line;
    getline(file, line);  // Leemos símbolo inicial
    initialStackSymbol = line;
    int transitionId = 0;
    while (getline(file, line)) {   // Leemos todas las transiciones
      getWords(line, words);
      std::vector<std::string> multipleStackSymb;
      for (size_t i = 4; i < words.size(); i++) { // Almaceno los símbolos a introducir en la pila
        multipleStackSymb.push_back(words[i]);
      }
      if (!existState(words[0])) {  // compruebo que el estado de partida existe
        std::string s("ERROR EN TIEMPO DE EJECUCIÓN - El autómata no cumple con las restricciones formales\n");
        throw std::runtime_error(s);
      }
      for (size_t i = 0; i < allStates.size(); i++) { // Almaceno al transición en su estado correspondiente
        if (allStates[i].getID() == words[0]) {
          Transition aux(words[0], words[1], words[2], words[3], multipleStackSymb, transitionId++);
          allStates[i].pushTransition(aux);
        }
          words.clear();
      }
    }
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

  return recursiveStep(currentState, testString, currentStack);  // comprobamos si la cadena es aceptada
}


bool Automaton::recursiveStep(std::string currentState, std::string testString,
    std::stack<std::string> currentStack) {
  if ((currentStack.empty()) && (testString.size() == 0)) { // Comprobamos si la cadena es aceptada
    throw true;
  }
  std::vector<Transition> possibleTransitions;
  std::string currentSymbol = "";
  currentSymbol += testString[0];

  if (!currentStack.empty()) {  // Si la pila tiene algún elemento (condición necesaria), buscamos las transiciones posibles
    for (size_t i = 0; i < allStates.size(); i++) {
      if (allStates[i].getID() == currentState) {
        possibleTransitions = allStates[i].getPossibleTransitions(currentSymbol, currentStack.top()); // Obtenemos la siguiente transición
        break;
      }
    }
  }

  // Posible modo traza
  if (trace) {  
    std::cout << "Estado actual: " << currentState << std::setw(10) << " | entrada: " << std::setw(10) <<  testString << std::setw(10) << " | Pila: ";
    showStack(currentStack);
    std::cout << std::setw(10) << " | transiciones: ";
    for (size_t i = 0; i < possibleTransitions.size(); i++)
      std::cout << possibleTransitions[i].getID() << " ";
    std::cout << "\n";
  }

  if (possibleTransitions.size() == 0) {  
    if (trace)
      std::cout << "Esta rama no acepta la cadena - - - - - -\n";
    return false;
  }
  currentStack.pop();  // Consumimos elemento top de la pila
  
  for(size_t i = 0; i < possibleTransitions.size(); i++) {
    std::string iterationString = testString;
    if (possibleTransitions[i].getConsumeSymbol() != ".")
      iterationString.erase(iterationString.begin()); // Consumimos el elemento si no es una epsilon
    std::stack<std::string> iterationStack = currentStack;  // Preparamos una pila auxiliar para este camino
    std::vector<std::string> symbolsToAdd = possibleTransitions[i].getInsertStackSymbol();
    vectorToStack(iterationStack, symbolsToAdd);  // Añadimos a la pila los elementos de la transición
    recursiveStep(possibleTransitions[i].getNextState(), iterationString, iterationStack);
  }
  return false;
}

bool Automaton::checkAutomaton(void) {
  bool stateFlag = false;
  for (size_t i = 0; i < allStates.size(); i++) { // Comprobamos que el estado inicial existe en Q
    if (allStates[i].getID() == initialState) 
      stateFlag = true;
  }
  if (!stateFlag) return false;
  if (stackAlphabet.find(initialStackSymbol) == stackAlphabet.end())  // Comprobamos que el símbolo inicial de la pila está en el alfabeto de la pila
    return false;
  return checkTransitions();  // Por último comprobamos que las transiciones sean posibles
}

bool Automaton::existState(std::string name) {
  for (size_t i = 0; i < allStates.size(); i++) {
    if (allStates[i].getID() == name)
      return true;
  }
  return false;
}

bool Automaton::checkTransitions(void) {
  // Recorremos todas las transiciones y comprobamos que cada uno de sus elementos existan
  // en sus cjtos correspondientes
  for (size_t i = 0; i < allStates.size(); i++) {
    std::vector<Transition> currentTransitions = allStates[i].getTransitions();
    for (size_t j = 0; j < currentTransitions.size(); j++) {
      if (!existState(currentTransitions[j].getNextState()) ||
          (automatonAlphabet.find(currentTransitions[j].getConsumeSymbol()) == automatonAlphabet.end() 
          && currentTransitions[j].getConsumeSymbol() != ".") ||
          (stackAlphabet.find(currentTransitions[j].getConsumeStackSymbol()) == stackAlphabet.end()) ||
          !(currentTransitions[j].checkAllStackSymb(stackAlphabet))){
        return false;
      }
    }
  }
  return true;
}

std::ostream& Automaton::write(std::ostream& os) {
  os << " - - AUTÓMATA CARGADO - -\n· Conjunto de estados:\n  ";
  for(size_t i = 0; i < allStates.size(); i++)
    os << allStates[i].getID() << " ";


  os << "\n. Alfabeto de la cadena de entrada:\n  ";
  for (std::set<std::string>::iterator it = automatonAlphabet.begin(); it != automatonAlphabet.end(); ++it)
    os << *it << " ";
  os << "\n. Alfabeto de la pila:\n  ";
  for (std::set<std::string>::iterator it = stackAlphabet.begin(); it != stackAlphabet.end(); ++it)
    os << *it << " ";
  os << "\n. Estado inicial:\n  " << initialState << "\n";
  os << ". Símbolo inicial de la pila:\n  " << initialStackSymbol << "\n";
  os << ". Transiciones: \n";
  for (size_t i = 0; i < allStates.size(); i++) 
    allStates[i].writeTransitions(os);
  return os;
}
