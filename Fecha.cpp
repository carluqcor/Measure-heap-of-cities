/*! 
   \file  Fecha.cpp
   \brief Fichero que contiene el código de las funciones de la clase Fecha
   \author Carlos Luque Córdoba
   \date   25/04/2018
*/


// Ficheros de cabecera
#include <iostream>

// atoi
#include <stdlib.h>

#include "Fecha.hpp"

#include "macros.hpp"

/*
 Definiciones de esBisiesto y esCorrecta
*/

bool ed::Fecha::esBisiesto() const
{
	if ( (this->getAgno() % 4 == 0) and 
         ( (not (this->getAgno() % 100 == 0)) or  (this->getAgno() % 400 == 0) )
	  )
		return true;
	else
		return false;
}


bool ed::Fecha::esCorrecta() const
{

 if (this->getAgno() > 0)
	{
	 if ( (this->getMes() >= 1) and (this->getMes() <= 12) )
		{
		 switch (this->getMes())
		 {
			case 1: // Enero
			case 3: // Marzo
			case 5: // Mayo
			case 7: // Julio
			case 8: // Agosto
			case 10: // Octubre
			case 12: // Diciembre
					if ( (this->getDia() >= 1) and (this->getDia() <= 31) )
						return true;
					else
						return false;

					break;

		  case 2: // Febrero
				  // Es bisiesto
				if ( this->esBisiesto() == true )
				  {
					if ( (this->getDia() >= 1) and (this->getDia() <= 29) )
						return true;
					else 
						return false;
				   }
				  // No es bisiesto
 				  else
					{
					  if ( (this->getDia() >= 1) and (this->getDia() <= 28) )
						return true;
					  else 
						return false;
					}
					break;

		 default: // Abril, Junio, Septiembre y Noviembre
					if ( (this->getDia() >= 1) and (this->getDia() <= 30) )
						return true;
					else
						return false;

					break;
		}
	}
	// El número de mes no es correcto
	else
		return false;
	}
	// El número de año no es correcto
	else
		return false;


 return true;
}

/*
 Definiciones de las funciones de lectura y escritura de la clase Fecha
*/

void ed::Fecha::escribirFecha()const
{
  std::cout << this->getDia() << "-" 
            << this->getMes() << "-"
            << this->getAgno() << std::endl; 
}


void ed::Fecha::leerFecha(){
	double dia, mes, agno;
	std::string f;
	  
	std::cout <<BIYELLOW<< "\n Lectura de una fecha" <<RESET<< std::endl;

	std::cout<<BIBLUE<< " Día --> "<<RESET<<BIYELLOW;
	std::cin >> dia;

	std::cout <<RESET<<BIBLUE<<" Mes --> "<<RESET<<BIYELLOW;
	std::cin >> mes;

	std::cout <<RESET<<BIBLUE<<" Año --> "<<RESET<<BIYELLOW;
	std::cin >> agno;

	// Se asignan los valores leídos a los atributos del vertice   
	this->setDia(dia);
	this->setMes(mes);
	this->setAgno(agno);

	std::cout<<RESET;
	if((this->esCorrecta())==true){
		
		#ifndef NDEBUG
  		// Se comprueba la postcondición
 		 assert(this->esCorrecta() == true);
 	 	#endif //NDEBUG	
	}else{
		std::cout<<BIRED<<"Error, la fecha introducida es errónea"<<RESET<<std::endl;
		std::cout<<BIYELLOW<<"¿Quiere intentar introducir la fecha otra vez?\nIntroduzca"<<BICYAN<<" Si "<<BIYELLOW<<"o"<<BICYAN<<" No"<<RESET<<BIBLUE<<std::endl;
		std::cin>>f;
		std::cout<<RESET;
		if(f=="Si" || f=="si"){
			std::cout<<CLEAR_SCREEN;
			PLACE(1,1);
			leerFecha();
		}else{
			std::cout<<BIRED<<"Abandonando..."<<std::endl;
		}
	}		
}


////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{

// Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, ed::Fecha const &fecha)
{
  stream << fecha.getDia();
  stream << "-";
  stream << fecha.getMes();
  stream << "-";
  stream << fecha.getAgno();

  return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Fecha &fecha)
{
 // Se lee la fecha teniendo en cuenta el formato: DD-MM-AAAA
  std::string cadena;

  std::getline(stream,cadena,'-');
  fecha.setDia(atoi(cadena.c_str()));

  std::getline(stream,cadena,'-');
  fecha.setMes(atoi(cadena.c_str()));

  std::getline(stream,cadena,' ');
  fecha.setAgno(atoi(cadena.c_str()));

  return stream;
} 

} // Fin del espacio de nombres ed
