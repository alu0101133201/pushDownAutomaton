/**
 * Fichero principal del programa
 * Fecha: 11/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/
#include <iostream>

#include "automaton.hpp"
#include "transition.hpp"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Debe introducir el nombre del fichero que contiene al autómata\n";
		return(1);
	}
	else {
		try {
			Automaton testAutomaton(argv[1]);
			testAutomaton.write(std::cout);
		} catch(std::runtime_error &e) {
			std::cerr << e.what();
			return(2);
		}
	}
}