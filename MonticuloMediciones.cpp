/*!
	\file MonticuloMediciones.cpp
	\brief Fichero que contiene el código de las funciones de la clase MonticuloMediciones.
    \author Carlos Luque Córdoba
    \date   25/04/2018
*/

//#include <vector>

#include <cassert>

#include <fstream>

#include "Medicion.hpp"

#include "MonticuloMediciones.hpp"

#include "macros.hpp"

// Abs para cotas de error de numeros reales positivos
#include <cmath>

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación de números reales

//! Modificadores privados
void ed::MonticuloMediciones::shiftUp(unsigned int i){
	#ifndef NDEBUG
		assert(i>0 && i<size());
	#endif
	if(i>0 && (getElement(i)>getElement(getParent(i)))==true){
  		ed::Medicion medicion;
		medicion=getElement(i);
		setElement(i, getElement(getParent(i)));
		setElement(getParent(i), medicion);
		if(getParent(i)!=0)
  			shiftUp(getParent(i));
  	}
  	#ifndef NDEBUG
  		if(i!=0)
  			assert(getElement(i)<getElement(getParent(i)) || (std::abs((getElement(i).getPrecipitacion())-(getElement(getParent(i)).getPrecipitacion()))<COTA_ERROR));
  		if(getLeftChild(i)<size())
  			assert(getElement(i)>getElement(getLeftChild(i)) || (std::abs((getElement(i).getPrecipitacion())-(getElement(getLeftChild(i)).getPrecipitacion()))<COTA_ERROR));
  		if(getRightChild(i)<size())
  			assert(getElement(i)>getElement(getRightChild(i)) || (std::abs((getElement(i).getPrecipitacion())-(getElement(getRightChild(i)).getPrecipitacion()))<COTA_ERROR));
	#endif
}


void ed::MonticuloMediciones::shiftDown(unsigned int i){
	#ifndef NDEBUG
		assert(i>=0 && i<size());
	#endif
	unsigned int n=i;
  	unsigned int LeftChild=getLeftChild(i);
  	unsigned int RightChild=getRightChild(i);
  	
  	if(RightChild<size()){ //Si tiene hijo derecho, tambien tiene hijo izquierdo y se deberá comprobar cual es mayor para subirlo
  		if(getElement(LeftChild)>getElement(i) || getElement(RightChild)>getElement(i)){ //Si el hijo derecho o izquierdo es mayor que su padre
	  		if(getElement(LeftChild)>getElement(i)){ //Si el hijo izquierdo es mayor que su padre, guardará el indice en n para cambiarse por el padre
	  			n=LeftChild;
	  			ed::Medicion medicion=getElement(n);
	  			setElement(n, getElement(i));
				setElement(i, medicion);
				shiftDown(n);
	  		}
			if(getElement(RightChild)>getElement(i) && getElement(RightChild)>getElement(LeftChild)){ //Si el hijo derecho es mayor que su padre y mayor que la precipitacion del hijo izquierdo, guardará el indice en n para cambiarse por el padre
				n=RightChild;
				ed::Medicion medicion=getElement(n);
				setElement(n, getElement(i));
				setElement(i, medicion);
				shiftDown(n);
			}
		}
	}else if(LeftChild<size()){ //Si tiene un hijo, solo va a ser el izquierdo
		if(getElement(LeftChild)>getElement(i)){
			n=LeftChild;
			ed::Medicion medicion=getElement(n);
			setElement(n, getElement(i));
			setElement(i, medicion);
		
		}
	}else //Si no tiene hijo izquierdo, no va a tener derecho, por lo tonto no hay que hacer nada
		return;	

	#ifndef NDEBUG
  		if(i!=0)
  			assert(getElement(i)<getElement(getParent(i)) || (std::abs((getElement(i).getPrecipitacion())-(getElement(getParent(i)).getPrecipitacion()))<COTA_ERROR));
  		
  		if(getLeftChild(i)<size())
  			assert(getElement(i)>getElement(getLeftChild(i)) || (std::abs((getElement(i).getPrecipitacion())-(getElement(getLeftChild(i)).getPrecipitacion()))<COTA_ERROR));
  		
  		if(getRightChild(i)<size())
  			assert(getElement(i)>getElement(getRightChild(i)) || (std::abs((getElement(i).getPrecipitacion())-(getElement(getRightChild(i)).getPrecipitacion()))<COTA_ERROR));
  	#endif
}


bool ed::MonticuloMediciones::has(ed::Medicion const &medicion)const{
	unsigned int i;
	bool val=false;
	for(i=0;i<size();i++){
		if(medicion==getElement(i))
			return true;
	}
	return val;
}

/////////////////////////////////////////////////////////////////////////////////7

// Métodos públicos de la clase MonticuloMediciones
//!Observadores públicos
void ed::MonticuloMediciones::statPorDia()const{
	unsigned int i;
	ed::Fecha fecha;
	ed::Medicion medicion;
	std::cout<<BIBLUE<<"Introduzca la fecha a buscar"<<RESET<<std::endl;
	fecha.leerFecha();
	medicion.setFecha(fecha);
	if(has(medicion)){
		for(i=0; i<(size());i++){
			if(medicion.getFecha()==getElement(i).getFecha())
				medicion=getElement(i);
		}
		double temperatura=0;
		double temperaturaAux=(medicion.getTemperatura());
		double humedad=(medicion.getHumedad());
		double vel=0;
		double precipitacion=(medicion.getPrecipitacion());
		double PR=0;
		double altura=0;
		double humedadAux=(pow((humedad/100),(1/8)))-0.02;
		double temperaturaAux1=(112+(0.9*temperaturaAux));
		double temperaturaAux2=(0.1*temperaturaAux);
		double sensacionTermina=0;
	

		temperatura=((1.8*(temperaturaAux)+32));
		std::cout<<BIYELLOW<<"La temperatura en grados F para el "<<fecha<<" es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
		precipitacion=((precipitacion)/24.5);
		std::cout<<BIYELLOW<<"La precipitacion en pulgadas para el "<<fecha<<" es: "<<BIBLUE<<precipitacion<<" pulgadas"<<RESET<<"\n"<<std::endl;
		vel=(((medicion.getVelocidadViento())*3600)/1000);
		std::cout<<BIYELLOW<<"La velocidad del viento en km/h para el "<<fecha<<" es: "<<BIWHITE<<vel<<" km/h"<<RESET<<"\n"<<std::endl;
		PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
		std::cout<<BIYELLOW<<"El Punto de Rocío para el "<<fecha<<" es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
		altura=(((temperaturaAux-PR)*1000)/8.02);
		if(altura<50){
				std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
		}else{
			std::cout<<BIYELLOW<<"La altura de las nubes para el "<<fecha<<" es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
		}
		
		sensacionTermina=(13.12+(0.6215*temperaturaAux)-(11.37*(pow(vel,0.16)))+(0.3965*temperaturaAux*(pow(vel,0.16))));
		std::cout<<BIYELLOW<<"La sensación terminca para el "<<fecha<<" es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
		
		
		std::cin.ignore();

	}else
		std::cout<<BIRED<<"La fecha introducida no se encuentra en el monticulo"<<std::endl;
}

void ed::MonticuloMediciones::statPorMes()const{
	unsigned int i;
	int opcion=0;
	unsigned int j=0;
	int agno=0;
	bool val=false;
	ed::Fecha fecha;
	ed::Medicion medicion;
	std::cout<<BIYELLOW<<"Introduzca el año: "<<BIBLUE;
	std::cin>>agno;
	std::cout<<RESET<<std::endl;
	fecha.setAgno(agno);
	double temperatura=0;
	double temperaturaAux=0;
	double humedad=0;
	double vel=0;
	double precipitacion=0;
	double PR=0;
	double altura=0;
	double humedadAux=0;
	double temperaturaAux1=0;
	double temperaturaAux2=0;
	double temperaturaAux3=0;
	double sensacionTermina=0;
	double precipitacionAux=0;
	double humedadAux2=0;
	double preci=0;
	double velAux=0;
	double vel1=0;

	for(i=0;i<size();i++){
		if((getElement(i).getFecha().getAgno())==agno){
			std::cout<<BIYELLOW<<"Introduzca el mes por numero: "<<BIBLUE;
			std::cin>>opcion;
			std::cout<<RESET<<std::endl;
			val=true;
		}
		if(!val){
			std::cout<<BIRED<<"Error, el año "<<agno<<" introducido no está en el monticulo"<<RESET<<"\n"<<std::endl;
			std::cin.ignore();
			return;
		}
			
		if(opcion>0 && opcion<13){
			switch(opcion){

				case 1: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Enero del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Enero del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;
			
				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Enero del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Enero del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Enero del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Enero del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
					
					
				std::cin.ignore();
				break;

				case 2: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Febrero del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Febrero del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Febrero del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Febrero del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Febrero del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Febrero del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;	
					
				std::cin.ignore();
				break;

				case 3: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Marzo del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Marzo del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Marzo del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Marzo del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Marzo del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Marzo del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
					
				std::cin.ignore();
				break;

				case 4: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Abril del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Abril del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Abril del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Abril del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Abril del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Abril del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
					
				std::cin.ignore();
				break;

				case 5: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Mayo del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Mayo del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Mayo del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Mayo del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Mayo del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Mayo del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;	
					
				std::cin.ignore();
				break;

				case 6: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Junio del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Junio del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Junio del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Junio del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Junio del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Junio del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;	
					
				std::cin.ignore();
				break;

				case 7: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Julio del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Julio del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Julio del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Julio del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Julio del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Julio del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;	
					
				std::cin.ignore();
				break;

				case 8: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Agosto del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Agosto del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Agosto del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Agosto del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Agosto del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Agosto del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;	
					
				std::cin.ignore();
				break;

				case 9: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Septiembre del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Septiembre del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Septiembre del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Septiembre del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Septiembre del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Septiembre del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;	
					
				std::cin.ignore();
				break;

				case 10: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Octubre del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Octubre del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Octubre del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Octubre del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Octubre del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Octubre del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;	
					
				std::cin.ignore();
				break;

				case 11: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Noviembre del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Noviembre del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Noviembre del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Noviembre del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Noviembre del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Noviembre del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;	
					
				std::cin.ignore();
				break;

				case 12: 
					PLACE(2,1);
					std::cout << CLEAR_SCREEN;
					for(i=0;i<size();i++){
						if((getElement(i).getFecha().getMes())==opcion){
							medicion=getElement(i);
							temperaturaAux+=(medicion.getTemperatura());
							humedad+=(medicion.getHumedad());
							precipitacion+=(medicion.getPrecipitacion());
							vel+=(medicion.getVelocidadViento());
							j++;
						}
					}
				if(j==0){
					std::cout<<BIRED<<"Error, el mes "<<opcion<<" introducido del "<<agno<<" no está en el monticulo"<<RESET<<"\n"<<std::endl;
					std::cin.ignore();
				}
				temperaturaAux3=temperaturaAux/j;
				humedadAux2=humedad/j;
				precipitacionAux=precipitacion/j;
				vel1=vel/j;

				humedadAux=(pow((humedadAux2/100),(1/8)))-0.02;
				temperaturaAux1=(112+(0.9*temperaturaAux3));
				temperaturaAux2=(0.1*temperaturaAux3);

				temperatura=((1.8*(temperaturaAux3)+32));
				std::cout<<BIYELLOW<<"La temperatura en grados F para Diciembre del año "<<agno<< " es: "<<BIPURPLE<<temperatura<<" F"<<RESET<<"\n"<<std::endl;
				
				preci=((precipitacionAux)/24.5);
				std::cout<<BIYELLOW<<"La precipitacion en pulgadas para Diciembre del año "<<agno<<" es: "<<BIBLUE<<preci<<" pulgadas"<<RESET<<"\n"<<std::endl;

				velAux=((vel1*3600)/1000);
				std::cout<<BIYELLOW<<"La velocidad del viento en km/h para Diciembre del año "<<agno<< " es: "<<BIWHITE<<velAux<<" km/h"<<RESET<<"\n"<<std::endl;
				
				PR=(((humedadAux)*(temperaturaAux1))+(temperaturaAux2-112));
				std::cout<<BIYELLOW<<"El Punto de Rocío para Diciembre del año "<<agno<< " es: "<<ICYAN<<PR<<" grados Centigrados"<<RESET<<"\n"<<std::endl;
				
				altura=(((temperaturaAux3-PR)*1000)/8.02);
				if(altura<50){
						std::cout<<BIYELLOW<<"El dia "<<fecha<<BICYAN<<" hubo mucha niebla"<<RESET<<"\n"<<std::endl;
				}else{
					std::cout<<BIYELLOW<<"La altura de las nubes para Diciembre del año "<<agno<< " es: "<<BICYAN<<altura<<" pies"<<RESET<<"\n"<<std::endl;
				}
				
				sensacionTermina=(13.12+(0.6215*temperaturaAux3)-(11.37*(pow(velAux,0.16)))+(0.3965*temperaturaAux3*(pow(velAux,0.16))));
				std::cout<<BIYELLOW<<"La sensación terminca para Diciembre del año "<<agno<< " es: "<<BIRED<<sensacionTermina<<" grados Centigrados"<<RESET<<"\n"<<std::endl;	
					
				std::cin.ignore();
				break;
			}
		}else
			std::cout<<BIRED<<"Has introducido mal el mes"<<RESET<<std::endl;
	}
}

double ed::MonticuloMediciones::precipitacionTotal()const{
	double suma=0;
	unsigned int i;
	for(i=0; i<(size());i++){
 			suma+=(getElement(i).getPrecipitacion());
 	}
 	return suma;
}

double ed::MonticuloMediciones::precipitacionMedia()const{
	unsigned int i;
	int j=0;
	ed::Medicion medicion;
	for(i=0; i<(size());i++){
		medicion=getElement(i);
 		if((medicion.getPrecipitacion())!=0.0)
 			j++;
 	}
 	return j;
}

double ed::MonticuloMediciones::hayMedicion2(ed::Medicion const &medicion)const{
	if(has(medicion)){
		return medicion.getPrecipitacion();
	}else
		return -2;
}

void ed::MonticuloMediciones::insert(ed::Medicion const &medicion){
	if(has(medicion)==false){
		_vectorPrecipitaciones.push_back(medicion);
		if((size()-1)>0)
			shiftUp(size()-1);
	}else{
		std::cout<<BIRED<<"La fecha "<<medicion.getFecha()<<" ya está insertada"<<RESET<<std::endl;
		std::cin.ignore();
	}
}

void ed::MonticuloMediciones::remove(){ 
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif
	ed::Medicion medicion=_vectorPrecipitaciones[size()-1];
	_vectorPrecipitaciones[size()-1]=_vectorPrecipitaciones[0];
	_vectorPrecipitaciones[0]=medicion;
	_vectorPrecipitaciones.erase(_vectorPrecipitaciones.end());
	if(size()>2){
		if(!isEmpty()){	
			shiftDown(0);
		}
	}
}

void ed::MonticuloMediciones::modify(ed::Medicion &medicion){
	#ifndef NDEBUG
		assert(isEmpty()==false);	
	#endif
		medicion.setFecha(getElement(0).getFecha());
		setElement(0, medicion);
		if((size()-1)>0)
			shiftDown(0);
	#ifndef NDEBUG
		assert(has(medicion)==true);
	#endif
}

//! Operadores públicos
ed::MonticuloMediciones & ed::MonticuloMediciones::operator=(ed::MonticuloMediciones &m){
	#ifndef NDEBUG
		assert(*this!=m);
	#endif
		return *this=m;

}

bool ed::MonticuloMediciones::operator!=(ed::MonticuloMediciones &m) const {
	if(*this!=m)
		return true;
	else
		return false;
}

//! Funciones de Escritura
void ed::MonticuloMediciones::print(){
	unsigned int i;
	int parar=0;
	for(i=0; i<size();i++){	
		if(parar==22){
			PLACE(1,1);
			std::cout<<BIYELLOW<<"Fecha"<<"\t"<<BIPURPLE<<"        Temp"<<"\t"<<BICYAN<<"Hum"<<"\t"<<BIWHITE<<"Viento"<<"\t"<<BIGREEN<<"Rad"<<"\t"<<BIBLUE<<"Prec"<<std::endl;	
			PLACE(25,1);
			std::cout << "Pulse ";
			std::cout << BIGREEN;
			std::cout << "ENTER";
			std::cout << RESET;
			std::cout << " para mostrar la siguiente ";
			std::cout << INVERSE;
			std::cout << "página"; 
			std::cout << RESET;

			// Pausa
			std::cin.ignore();
			PLACE(2,1);
			std::cout << CLEAR_SCREEN;
			parar=0;
		}else{
			std::cout<<BIYELLOW<<_vectorPrecipitaciones[i].getFecha()<<RESET<<" ";
			std::cout<<"\t"<<BIPURPLE<<_vectorPrecipitaciones[i].getTemperatura()<<RESET<<" ";			
			std::cout<<"\t"<<BICYAN<<_vectorPrecipitaciones[i].getHumedad()<<RESET<<" ";
			std::cout<<"\t"<<BIWHITE<<_vectorPrecipitaciones[i].getVelocidadViento()<<RESET<<" ";
			std::cout<<"\t"<<BIGREEN<<_vectorPrecipitaciones[i].getRadiacion()<<RESET<<" ";
			std::cout<<"\t"<<BIBLUE<<_vectorPrecipitaciones[i].getPrecipitacion()<<RESET<<std::endl;
			parar++;
		}
	}
}
