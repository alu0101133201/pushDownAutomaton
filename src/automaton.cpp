/**
 * Fichero que implementa la clase autómata. Esta clase representará
 * un simulador de un autómata con pila (por vaciado de pila)
 * Fecha: 11/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/

#include "automaton.hpp"

Automaton::Automaton(char* automatonFile) {
  std::string route = "./examples/";
  std::string line;
  route += automatonFile;
  std::ifstream file(route.c_str());
  if (file.is_open()) {
    while (getline(file, line)) {
      std::cout << line << "\n";
    }
  } else {
    std::string s("ERROR EN TIEMPO DE EJECUCIÓN - No se pudo abrir el fichero\n");
    throw std::runtime_error(s);
  }
}

Automaton::~Automaton() {}