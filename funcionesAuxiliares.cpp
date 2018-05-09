/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares para el programa principal de la práctica 3
  \author Carlos Luque Córdoba
  \date   25/04/2018
*/


#include <iostream>

#include <fstream>

#include <string>

#include <stdlib.h>

#include <vector>

#include "funcionesAuxiliares.hpp"
          
#include "MonticuloMediciones.hpp"

#include "Medicion.hpp"

#include "macros.hpp"

#include <cmath>

int ed::menu()
{
	int opcion;
	int posicion;

	// Se muestran las opciones del menú
	posicion=2;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	PLACE(1,10);
	std::cout << BIBLUE;
	std::cout << "Programa principial | Opciones del menú";
	std::cout << RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,12);
	std::cout <<BICYAN<< "[1] Comprobar si el montículo tiene mediciones"<<RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,12);
	std::cout <<BIYELLOW<< "[2] Cargar el montículo desde un fichero"<<RESET;

	PLACE(posicion++,12);
	std::cout <<BIYELLOW<< "[3] Grabar el montículo en un fichero"<<RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;
 
	PLACE(posicion++,12);
	std::cout <<BIGREEN<< "[4] Consultar datos del montículo"<<RESET;

	PLACE(posicion++,12);
	std::cout <<BIGREEN<<"[5] Mostrar mediciones ordenadas por precipitación del montículo"<<RESET;

	PLACE(posicion++,12);
	std::cout <<BIGREEN<<"[6] Mostrar estadisticas de una fecha"<<RESET;

	PLACE(posicion++,12);
	std::cout <<BIGREEN<<"[7] Mostrar estadisticas de un mes"<<RESET;

	PLACE(posicion++,12);
	std::cout <<BIGREEN<<"[8] Borrar todas las mediciones del montículo"<<RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,12);
	std::cout <<BIBLUE<< "[9] Consultar el top"<<RESET;

	PLACE(posicion++,12);
	std::cout <<BIBLUE<<"[10] Insertar una medición"<<RESET;

	PLACE(posicion++,12);
	std::cout <<BIBLUE<< "[11] Modificar la cima"<<RESET;

	PLACE(posicion++,12);
	std::cout <<BIBLUE<< "[12] Eliminar la cima"<<RESET;

	
	posicion++;

	PLACE(posicion++,11);
	std::cout << BIRED << "[0] Salir";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,11);
	std::cout << BIGREEN;
	std::cout << "Opción: ";
	std::cout << RESET;

	// Se lee el número de opción
	std::cin >> opcion;

    // Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();

	return opcion;
}


//////////////////////////////////////////////////////////////////////////////


void ed::insertarM(ed::Medicion &medicion, ed::MonticuloMediciones &monticulo){
	monticulo.insert(medicion);
}

void ed::cargarMonticuloDeFichero(std::string const & nombreFichero, ed::MonticuloMediciones & monticulo){
	std::cout<<BIYELLOW<<"Se va a mostrar el heap\n"<<RESET<<std::endl;
	std::ifstream med;
	bool value;
	ed::Medicion medicion;
	ed::Fecha fecha;
	med.open(nombreFichero.c_str());
	std::string f;
	if(med.is_open()){
		while(!med.eof()){
 			med>>medicion;
  			if(!med.eof())
				insertarM(medicion, monticulo);
 		}
	
 	monticulo.print();
 	med.close();
 	value=true;
 	}else
 		value=false;
 	
 	if(value)
		std::cout<<BIGREEN<<"El fichero ha sido cargado con exito"<<RESET<<std::endl;
	else
		std::cout<<BIRED<<"Error al cargar el fichero"<<RESET<<std::endl;
}

void ed::grabarMonticuloEnFichero(std::string const & nombreFichero, ed::MonticuloMediciones const & monticulo){
	std::ofstream med;
	med.open(nombreFichero.c_str());
	ed::MonticuloMediciones monticuloAux=monticulo;
	bool value;
	if(med.is_open()){
		while(!(monticuloAux.isEmpty())){
 			med<<monticuloAux.top();
 			monticuloAux.remove();
		}
	med.close();
	value=true;
	}else
		value=false;
 	if(value)
		std::cout<<BIGREEN<<"El fichero ha sido cargado con exito"<<RESET<<std::endl;
	else
		std::cout<<BIRED<<"Error al cargar el fichero"<<RESET<<std::endl;

}

void ed::Modificar(ed::MonticuloMediciones &monticulo){
	if(monticulo.size()>0){
		ed::Medicion medicion;
		medicion.leerMedicion2();
		monticulo.modify(medicion);
	}else
		std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede modificar una cima inexistente"<<RESET<<std::endl;
}

void ed::borrarTodo(ed::MonticuloMediciones &monticulo){
	if(monticulo.size()>0){
		std::cout<<BIBLUE<<"El monticulo antes del borrado tiene: "<<monticulo.size()<<" mediciones"<<RESET<<std::endl;
		monticulo.removeAll();
		std::cout<<BIGREEN<<"Se han borrado todas las mediciones correctamente"<<RESET<<std::endl;
		std::cout<<BIBLUE<<"El monticulo después del borrado tiene: "<<monticulo.size()<<" mediciones"<<RESET<<std::endl;
		std::cout<<BIGREEN<<"Se ha borrado el monticulo correctamente"<<RESET<<std::endl;
	}
	else
		std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede borrar nada"<<RESET<<std::endl;

}

 void ed::monticuloStats(ed::MonticuloMediciones const &monticulo){
 	if(monticulo.size()>0){
 		double suma=0;
 		double sumaMedia=0;
	 	std::cout<<BIGREEN<<"La máxima precipitación del montículo es: "<<BIBLUE<<monticulo.top().getPrecipitacion()<<RESET<<std::endl;
	 	std::cout<<BIGREEN<<"El tamaño del montículo es: "<<BIBLUE<<monticulo.size()<<RESET<<std::endl;
 		suma=(monticulo.precipitacionTotal());
 		sumaMedia=suma/monticulo.precipitacionMedia();
 		std::cout<<BIGREEN<<"La precipitacion media de las mediciones con al menos 0.1 mm es de: "<<sumaMedia<<RESET<<std::endl;
 		if(suma<400)
 			std::cout<<BIRED<<suma<<" mm no es suficiente por lo tanto habrá sequía"<<RESET<<std::endl;
 		else
 			std::cout<<BIYELLOW<<suma<<" mm es suficiente por lo tanto se podrán regar los huertos"<<RESET<<std::endl;
	}else
		std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede mostrar los stats"<<RESET<<std::endl;
}

void ed::mostrarTop(ed::MonticuloMediciones const &monticulo){
	if(monticulo.size()>0)
		monticulo.top().escribirMedicion();
	else
		std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede mostrar el top"<<RESET<<std::endl;
}


void ed::eliminarCima(ed::MonticuloMediciones &monticulo){
	if(monticulo.size()>0){
		std::cout<<BIGREEN<<"Se va a proceder a la eliminación de la cima y a la actualizacion del heap"<<RESET<<std::endl;
		monticulo.remove();
	}
}

void ed::estadisticasFecha(ed::MonticuloMediciones const &monticulo){
	monticulo.statPorDia();
}

void ed::estadisticasMes(ed::MonticuloMediciones const &monticulo){
	monticulo.statPorMes();
}

void ed::printNew(ed::MonticuloMediciones const &monticulo){
	ed::MonticuloMediciones monticuloAux=monticulo;
	int parar=0;
	while(!(monticuloAux.isEmpty())){
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
			std::cout<<BIYELLOW<<monticuloAux.top().getFecha()<<RESET<<" ";
			std::cout<<"\t"<<BIPURPLE<<monticuloAux.top().getTemperatura()<<RESET<<" ";			
			std::cout<<"\t"<<BICYAN<<monticuloAux.top().getHumedad()<<RESET<<" ";
			std::cout<<"\t"<<BIWHITE<<monticuloAux.top().getVelocidadViento()<<RESET<<" ";
			std::cout<<"\t"<<BIGREEN<<monticuloAux.top().getRadiacion()<<RESET<<" ";
			std::cout<<"\t"<<BIBLUE<<monticuloAux.top().getPrecipitacion()<<RESET<<std::endl;
			parar++;
			monticuloAux.remove();
		}
	}
}