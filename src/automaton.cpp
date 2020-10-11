/**
 * Fichero que implementa la clase autómata. Esta clase representará
 * un simulador de un autómata con pila (por vaciado de pila)
 * Fecha: 11/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/

#include "automaton.hpp"

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

void vectorToSet(std::vector<std::string> &initialVector, std::set<std::string> &destinationSet) {
  for (size_t i = 0; i < initialVector.size(); i++) {
    destinationSet.insert(initialVector[i]);
  }
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
    getWords(line, words);  // Leemos el cjto de estados del autómata
    vectorToSet(words, states);

  } else {
    std::string s("ERROR EN TIEMPO DE EJECUCIÓN - No se pudo abrir el fichero\n");
    throw std::runtime_error(s);
  }
}

// Destructor del autómata de pila
Automaton::~Automaton() {}


std::ostream& Automaton::write(std::ostream& os) {
  os << " - - AUTÓMATA DE PILA - -\n";
  os << "· Conjunto de estados:\n  ";
  for (std::set<std::string>::iterator it = states.begin(); it != states.end(); ++it)
    os << *it << " ";
  os << "\n";
  return os;
}
