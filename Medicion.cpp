/*! 
   \file  Medicion.cpp
   \brief Fichero que contiene el código de las funciones de la clase Medicion
   \author Carlos Luque Córdoba
   \date   25/04/2018
*/


// Ficheros de cabecera
#include <iostream>

// atoi, atof
#include <stdlib.h>

// Abs para cotas de error de numeros reales positivos
#include <cmath>

#include "Medicion.hpp"
#include "macros.hpp"

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación de números reales


//! \name Operadores
bool ed::Medicion::operator==(ed::Medicion const &medicion) const {
	bool boolVal;
	if(getFecha()==medicion.getFecha())
		boolVal=true;
	else 
		boolVal=false;
	#ifndef NDEBUG
		assert((getFecha()==medicion.getFecha())==boolVal);
	#endif
		return boolVal;
}

bool ed::Medicion::operator<(ed::Medicion const &h)const{
	if(this->getPrecipitacion()<h.getPrecipitacion())
		return true;
	else
		return false;
}

bool ed::Medicion::operator>(ed::Medicion const &h)const{
	if(this->getPrecipitacion()>h.getPrecipitacion())
		return true;
	else
		return false;
}


/*COMPROBAR GRADOS -273 F*/

//! \name Funciones de lectura y escritura de la clase Medicion
void ed::Medicion::leerMedicion(){
	double prec;
	ed:: Fecha fecha;
	fecha.leerFecha();

	std::cout <<BIGREEN<< " \nIntroduzca la temperatura: "<<RESET<<std::endl;
	std::cout <<BIBLUE<< " Temperatura --> "<<RESET<<BIYELLOW;
	std::cin>>prec;
	std::cout<<RESET<<std::endl;
	setTemperatura(prec);

	std::cout <<BIGREEN<< " Introduzca la humedad: "<<RESET<<std::endl;
	std::cout <<BIBLUE<< " Humedad --> "<<RESET<<BIYELLOW;
	std::cin>>prec;
	std::cout<<RESET<<std::endl;
	if(prec<0.0){
		do{
			std::cout<<BIRED<<"Error, la humedad tiene que ser mayor o igual que 0.0\n"<<RESET<<std::endl;
			std::cout <<BIGREEN<< " Introduzca la humedad: "<<RESET<<std::endl;
			std::cout <<BIBLUE<< " Humedad --> "<<RESET<<BIYELLOW;
			std::cin>>prec;
			std::cout<<RESET<<std::endl;
		}while(prec<0.0);
	}else
		setHumedad(prec);

	std::cout <<BIGREEN<< " Introduzca la velocidad del viento: "<<RESET<<std::endl;
	std::cout <<BIBLUE<< " Velocidad del viento --> "<<RESET<<BIYELLOW;
	std::cin>>prec;
	std::cout<<RESET<<std::endl;
	if(prec<0.0){
		do{
			std::cout<<BIRED<<"Error, la velocidad del viento tiene que ser mayor o igual que 0.0"<<RESET<<std::endl;
			std::cout <<BIGREEN<< " Introduzca la velocidad del viento: "<<RESET<<std::endl;
			std::cout <<BIBLUE<< " Velocidad del viento --> "<<RESET<<BIYELLOW;
			std::cin>>prec;
			std::cout<<RESET<<std::endl;
		}while(prec<0.0);
	}else
		setVelocidadViento(prec);

	std::cout <<BIGREEN<< " Introduzca la radiación: "<<RESET<<std::endl;
	std::cout <<BIBLUE<< " Radiacion --> "<<RESET<<BIYELLOW;
	std::cin>>prec;
	std::cout<<RESET<<std::endl;
	if(prec<0.0){	
		do{
			std::cout<<BIRED<<"Error, la radiacion tiene que ser mayor o igual que 0.0"<<RESET<<std::endl;
			std::cout <<BIGREEN<< " Introduzca la radiación: "<<RESET<<std::endl;
			std::cout <<BIBLUE<< " Radiacion --> "<<RESET<<BIYELLOW;
			std::cin>>prec;
			std::cout<<RESET<<std::endl;
		}while(prec<0.0);
	}else
		setRadiacion(prec);

	std::cout <<BIGREEN<< " Introduzca la precipitación: "<<RESET<<std::endl;
	std::cout <<BIBLUE<< " Precipitacion --> "<<RESET<<BIYELLOW;
	std::cin>>prec;
	std::cout<<RESET<<std::endl;
	if(prec<0){
		do{	
			std::cout<<BIRED<<"Error, la precipitación tiene que ser mayor o igual que 0.0"<<RESET<<std::endl;
			std::cout <<BIGREEN<< " Introduzca la precipitación: "<<RESET<<std::endl;
			std::cout <<BIBLUE<< " Precipitacion --> "<<RESET<<BIYELLOW;
			std::cin>>prec;
			std::cout<<RESET<<std::endl;
		}while(prec<0.0);
	}else{
		setPrecipitacion(prec);
	}
	setFecha(fecha);
	escribirMedicion();
	std::cin.ignore();
}

void ed::Medicion::leerMedicion2(){
	double prec;
	std::cout <<BIGREEN<< " \nIntroduzca la nueva temperatura: "<<RESET<<std::endl;
	std::cout <<BIBLUE<< " Temperatura --> "<<RESET<<BIYELLOW;
	std::cin>>prec;
	std::cout<<RESET<<std::endl;
	setTemperatura(prec);

	std::cout <<BIGREEN<< " Introduzca la nueva humedad: "<<RESET<<std::endl;
	std::cout <<BIBLUE<< " Humedad --> "<<RESET<<BIYELLOW;
	std::cin>>prec;
	std::cout<<RESET<<std::endl;
	if(prec<0.0){
		do{
			std::cout<<BIRED<<"Error, la nueva humedad tiene que ser mayor o igual que 0.0\n"<<RESET<<std::endl;
			std::cout <<BIGREEN<< " Introduzca la nueva humedad: "<<RESET<<std::endl;
			std::cout <<BIBLUE<< " Humedad --> "<<RESET<<BIYELLOW;
			std::cin>>prec;
			std::cout<<RESET<<std::endl;
		}while(prec<0.0);
	}else
		setHumedad(prec);

	std::cout <<BIGREEN<< " Introduzca la nueva velocidad del viento: "<<RESET<<std::endl;
	std::cout <<BIBLUE<< " Velocidad del viento --> "<<RESET<<BIYELLOW;
	std::cin>>prec;
	std::cout<<RESET<<std::endl;
	if(prec<0.0){
		do{
			std::cout<<BIRED<<"Error, la nueva velocidad del viento tiene que ser mayor o igual que 0.0"<<RESET<<std::endl;
			std::cout <<BIGREEN<< " Introduzca la nueva velocidad del viento: "<<RESET<<std::endl;
			std::cout <<BIBLUE<< " Velocidad del viento --> "<<RESET<<BIYELLOW;
			std::cin>>prec;
			std::cout<<RESET<<std::endl;
		}while(prec<0.0);
	}else
		setVelocidadViento(prec);

	std::cout <<BIGREEN<< " Introduzca la nueva radiación: "<<RESET<<std::endl;
	std::cout <<BIBLUE<< " Radiacion --> "<<RESET<<BIYELLOW;
	std::cin>>prec;
	std::cout<<RESET<<std::endl;
	if(prec<0.0){	
		do{
			std::cout<<BIRED<<"Error, la nueva radiacion tiene que ser mayor o igual que 0.0"<<RESET<<std::endl;
			std::cout <<BIGREEN<< " Introduzca la nueva radiación: "<<RESET<<std::endl;
			std::cout <<BIBLUE<< " Radiacion --> "<<RESET<<BIYELLOW;
			std::cin>>prec;
			std::cout<<RESET<<std::endl;
		}while(prec<0.0);
	}else
		setRadiacion(prec);

	std::cout <<BIGREEN<< " Introduzca la nueva precipitación: "<<RESET<<std::endl;
	std::cout <<BIBLUE<< " Precipitacion --> "<<RESET<<BIYELLOW;
	std::cin>>prec;
	std::cout<<RESET<<std::endl;
	if(prec<0){
		do{	
			std::cout<<BIRED<<"Error, la nueva precipitación tiene que ser mayor o igual que 0.0"<<RESET<<std::endl;
			std::cout <<BIGREEN<< " Introduzca la nueva precipitación: "<<RESET<<std::endl;
			std::cout <<BIBLUE<< " Precipitacion --> "<<RESET<<BIYELLOW;
			std::cin>>prec;
			std::cout<<RESET<<std::endl;
		}while(prec<0.0);
	}else{
		setPrecipitacion(prec);
	}
	escribirMedicion2();
	std::cin.ignore();
}

void ed::Medicion::escribirMedicion(){
	std::cout<<BIYELLOW<<"Fecha: "<<(this->getFecha())<<RESET<<std::endl;
	std::cout<<BIPURPLE<<"Temperatura: "<<this->getTemperatura()<<RESET<<std::endl;
	std::cout<<BICYAN<<"Humedad: "<<this->getHumedad()<<RESET<<std::endl;
	std::cout<<BIWHITE<<"Velocidad del viento: "<<this->getVelocidadViento()<<RESET<<std::endl;
	std::cout<<BIGREEN<<"Radiacion: "<<this->getRadiacion()<<RESET<<std::endl;
	std::cout<<BIBLUE<<"Precipitación: "<<this->getPrecipitacion()<<RESET<<"\n"<<std::endl;
}

void ed::Medicion::escribirMedicion2(){
	std::cout<<BIPURPLE<<"Temperatura: "<<this->getTemperatura()<<RESET<<std::endl;
	std::cout<<BICYAN<<"Humedad: "<<this->getHumedad()<<RESET<<std::endl;
	std::cout<<BIWHITE<<"Velocidad del viento: "<<this->getVelocidadViento()<<RESET<<std::endl;
	std::cout<<BIGREEN<<"Radiacion: "<<this->getRadiacion()<<RESET<<std::endl;
	std::cout<<BIBLUE<<"Precipitación: "<<this->getPrecipitacion()<<RESET<<"\n"<<std::endl;
}

// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{

	// Sobrecarga del operador de salida
	ostream &operator<<(ostream &stream, ed::Medicion const &medicion){
  		stream << medicion.getFecha();
  		stream << " ";
  		stream << medicion.getTemperatura();
  		stream << " ";
  		stream << medicion.getHumedad();
  		stream << " ";
  		stream << medicion.getVelocidadViento();
  		stream << " ";
  		stream << medicion.getRadiacion();
  		stream << " ";
  		stream << medicion.getPrecipitacion();
  		stream << "\n";

		return stream;
	}

	// Sobrecarga del operador de entrada
	istream &operator>>(istream &stream, ed::Medicion &medicion){
			ed::Fecha fecha;
			std::string f;
			std::getline(stream, f, '-');
			fecha.setDia(atoi(f.c_str()));

			std::getline(stream, f, '-');
			fecha.setMes(atoi(f.c_str()));

			std::getline(stream, f, ' ');
			fecha.setAgno(atoi(f.c_str()));


			medicion.setFecha(fecha);

			std::getline(stream, f, ' ');
			medicion.setTemperatura(atof(f.c_str()));
			

			std::getline(stream, f, ' ');
			if(atof(f.c_str())>=0.0){
				medicion.setHumedad(atof(f.c_str()));
			}else{
				std::cout<<BIRED<<"Error, la humedad tiene que ser mayor o igual que 0.0"<<RESET<<std::endl;
				std::cin.ignore();
			}

			std::getline(stream, f, ' ');
			if(atof(f.c_str())>=0.0){
				medicion.setVelocidadViento(atof(f.c_str()));
			}else{
				std::cout<<BIRED<<"Error, la velocidad del viento tiene que ser mayor o igual que 0.0"<<RESET<<std::endl;
				std::cin.ignore();
			}

			std::getline(stream, f, ' ');
			if(atof(f.c_str())>=0.0){
				medicion.setRadiacion(atof(f.c_str()));
			}else{
				std::cout<<BIRED<<"Error, la radiación tiene que ser mayor o igual que 0.0"<<RESET<<std::endl;
				std::cin.ignore();
			}

			std::getline(stream, f, '\n');
			if(atof(f.c_str())>=0.0){
				medicion.setPrecipitacion(atof(f.c_str()));
			}else{
				std::cout<<BIRED<<"Error, la precipitación tiene que ser mayor o igual que 0.0"<<RESET<<std::endl;
				std::cin.ignore();
			}
		return stream;
	} 
} // Fin del espacio de nombres ed
