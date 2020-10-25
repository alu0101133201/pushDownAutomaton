/**
 * Fichero principal del programa
 * Fecha: 11/10/2020
 * Autor: Sergio Guerra Arencibia
 * Universidad de La Laguna (ULL)
 **/
#include <iostream>

#include "automaton.hpp"
#include "transition.hpp"

void keyboardMode(Automaton myAutomaton) {
	std::string keyboardString;
do {
		std::cout << "\nIntroduzca cadena a reconocer por el autómata (X para salir)\n >> ";
		std::cin >> keyboardString;
		try {
			if (keyboardString != "X")
				if (!myAutomaton.test(keyboardString))
					std::cout << "La cadena: " << keyboardString << " no ha sido aceptada\n";
			} catch(bool &e) {
			std::cout << "La cadena: " << keyboardString << " ha sido aceptada\n";
		}
	} while(keyboardString != "X");
}

void fileMode(Automaton myAutomaton) {
	std::string fileName;
	std::cout << "\nIntroduzca nombre del fichero\n >> ";
	std::cin >> fileName;

  std::string line;
	std::ifstream file(fileName);

	if (file.is_open()) {
    while (getline(file, line)) {
			try {
				if (!myAutomaton.test(line))
					std::cout << "La cadena: " << line << " no ha sido aceptada\n";
			} catch(bool &e) {
			std::cout << "La cadena: " << line << " ha sido aceptada\n";
			}
		}
	} else {
		std::string s("ERROR EN TIEMPO DE EJECUCIÓN - No se pudo abrir el fichero\n");
    throw std::runtime_error(s);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Debe introducir el nombre del fichero que contiene al autómata\n";
		return(1);
	}
	else {
		try {
			int option;
			int mode;
			std::cout << "\nSeleccione modo de ejcición:\n 1.- Modo traza\n 2.- Modo normal\n";
			std::cin >> mode;
			
			Automaton testAutomaton(argv[1], mode);
			testAutomaton.write(std::cout);
			std::cout << "\n\nSeleccione método para introducir las cadenas:\n 1.- Teclado\n 2.- Fichero\n >> ";
			std::cin >> option;
			if (option == 1) {
				keyboardMode(testAutomaton);
			} else {
				fileMode(testAutomaton);
			}
		} catch(std::runtime_error &e) {
			std::cerr << e.what();
			return(2);
		}
	}
	return(0);
}