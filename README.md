# Pushdown automaton
### Práctica 01 - Complejidad computacional 
###### Sergio Guerra Arencibia - ULL
###### 29/10/2020
  
Este repositorio contiene la implementación de un autómata con pila. El método de aceptación 
es por vaciado de pila.  

Definición  
```  
Un autómata con pila, autómata a pila o autómata de pila es un modelo matemático de un sistema  
que recibe una cadena constituida por símbolos de un alfabeto y determina si esa cadena pertenece  
al lenguaje que el autómata reconoce. El lenguaje que reconoce un autómata con pila pertenece al  
grupo de los lenguajes libres de contexto en la clasificación de la Jerarquía de Chomsky.
```  
  
La implementación se ha realizado en el lenguaje C++.  
La orientación a objetos utilizada consta de tres clases diferentes. La que está en un nivel más bajo (no usa ninguna de 
las otras dos) es la clase transición. Esta clase representa una transición simple entre dos estados del autómata.  
Después tenemos la clase estado, que es un objeto con un identificador y un conjunto de transiciones.  Por último tenemos la clase autómata, con diferentes atributos y, entre ellos, un conjunto de estados. 
La relación entre las clases se basa en la composición.  

### Referencias  
[wikipedia](https://es.wikipedia.org/wiki/Aut%C3%B3mata_con_pila#:~:text=Un%20aut%C3%B3mata%20con%20pila%2C%20aut%C3%B3mata,lenguaje%20que%20el%20aut%C3%B3mata%20reconoce.)  
[video explicativo](https://www.youtube.com/watch?v=ufRfjKgaUgo&ab_channel=Flacoloide)
