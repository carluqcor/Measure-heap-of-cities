/*!
	\file principalMenuMonticulo.cpp
	\brief Programa principal de la práctica 3 de ED: montículo de maximos
	\author Carlos Luque Córdoba
  	\date   25/04/2018
	\version 1.0
*/

/*!
 \mainpage Implementación de un montículo de máximos
 \author   Carlos Luque Córdoba
 \date     25/04/2018
 \version  1.0
*/

// Para los flujos de entrada y salida y para usar locale
#include <iostream>
#include <string>

#include "Fecha.hpp"
#include "Medicion.hpp"
#include "MonticuloMediciones.hpp"

#include "funcionesAuxiliares.hpp"
#include "macros.hpp"



/*! 
	\brief   Programa principal de la práctica 3: Monticulo de mediciones(Fecha y Precipitaciones)
	\return  int
*/
int main(){

	ed::Medicion medicion;
	ed::MonticuloMediciones monticulo;
	std::string cad;

	int opcion;

	do{
		// Se elige la opción del menún
		opcion = ed::menu();		

		std::cout << CLEAR_SCREEN;
		PLACE(3,1);

		// Se ejecuta la opción del menú elegida
		switch(opcion)
		{
			case 0: 
					std::cout << INVERSE;
					std::cout << "Fin del programa" << std::endl;
					std::cout << RESET;
			break;

		   ///////////////////////////////////////////////////////////////////

			case 1: 
					std::cout<<BIPURPLE<< "[1] Comprobar si el montículo está vacío"<<RESET<< std::endl;
					if(monticulo.size()==0)
						std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío"<<RESET<<std::endl;
					else
						std::cout<<BIGREEN<<"Al menos hay una medición en el montículo"<<RESET<<std::endl;
					break;

			//////////////////////////////////////////////////////////////////////////////
			case 2: 
					std::cout <<BIPURPLE<< "[2] Cargar el montículo desde un fichero" <<RESET<< std::endl;
					std::cout<<BIBLUE<<"Introduce el nombre del fichero: "<<RESET<<BIYELLOW;
					std::getline(std::cin,cad);
					std::cout <<RESET<<BIBLUE<< "\nSe cargan las mediciones desde el fichero "<<RESET<<BIYELLOW<<cad<<RESET<<"\n"<< std::endl;
					ed::cargarMonticuloDeFichero(cad,monticulo);
					std::cout <<BIGREEN<<"Tamaño del montículo " << monticulo.size() <<RESET<< std::endl;

				break;

			case 3: 
					std::cout <<BIPURPLE<< "[3] Grabar el montículo en un fichero" <<RESET<< std::endl;
					if((monticulo.size())>0){
						std::cout<<BIGREEN<<"Introduce el nombre del fichero: "<<RESET<<BIYELLOW;
						std::getline(std::cin,cad);
						std::cout <<RESET<<BIBLUE<< "\nSe graba el montículo en el fichero "<<RESET<<BIYELLOW<<cad<<RESET<< std::endl;
						ed::grabarMonticuloEnFichero(cad,monticulo);
					}else
						std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede grabar en el fichero"<<RESET<<std::endl;

					break;

			//////////////////////////////////////////////////////////////////////////////
			case 4: 
				  	std::cout<<BIPURPLE<< "[4] Consultar datos del montículo: " <<RESET<< std::endl; 
				  	if((monticulo.size())>0)
				  		ed::monticuloStats(monticulo);
				  	else
						std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede consultar sus datos"<<RESET<<std::endl;
					break;

			case 5: 
				  	//std::cout<<BIPURPLE<< "[5] Mostrar las mediciones del montículo: " <<RESET<< std::endl;
				  	if((monticulo.size())>0){
				  		ed::printNew(monticulo);
				  	}
				  	else
				  		std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede consultar sus mediciones"<<RESET<<std::endl;

					break;


			//////////////////////////////////////////////////////////////////////////////
			case 6: 
					std::cout <<BIPURPLE<< "[6] Mostrar estadisticas de una fecha"<<RESET<< std::endl;
					if((monticulo.size())>0)
						ed::estadisticasFecha(monticulo);
					else
						std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede consultar la estadistica de la fecha"<<RESET<<std::endl;
					break;

			case 7: 
					std::cout <<BIPURPLE<< "[7] Mostrar estadisticas de un mes"<<RESET<< std::endl;
					if((monticulo.size())>0)
						ed::estadisticasMes(monticulo);
					else
						std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede consultar la estadistica de un mes"<<RESET<<std::endl;
					break;


			case 8: 
					std::cout <<BIPURPLE<< "[8] Borrar todas las mediciones del montículo" <<RESET<<std::endl;
					if((monticulo.size())>0)
						ed::borrarTodo(monticulo);
					else
						std::cout<<ONIRED<<BIYELLOW<<"El montículo ya está vacío"<<RESET<<std::endl;
					break;

			//////////////////////////////////////////////////////////////////////////////
			case 9: 
					std::cout <<BIPURPLE<< "[9] Consultar el top\n" <<RESET<< std::endl;
					if((monticulo.size())>0)
						ed::mostrarTop(monticulo);
					else
						std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede consultar la estadistica de la fecha"<<RESET<<std::endl;
					break;

			case 10: 
					std::cout <<BIPURPLE<< "[10] Insertar una medición" <<RESET<< std::endl;
					medicion.leerMedicion();
					ed::insertarM(medicion, monticulo);
					break;

			case 11: 
					std::cout <<BIPURPLE<< "[11] Modificar la cima" <<RESET<<std::endl;
					if((monticulo.size())>0)
						ed::Modificar(monticulo);
					else
						std::cout<<ONIRED<<BIYELLOW<<"El montículo está vacío y no se puede modificar la cima"<<RESET<<std::endl;
					break;
			case 12: 
					std::cout <<BIPURPLE<< "[12] Eliminar la cima" <<RESET<<std::endl;
					if((monticulo.size())>0)
						ed::eliminarCima(monticulo);
					else
						std::cout<<ONIRED<<BIYELLOW<<"El montículo ya está vacío"<<RESET<<std::endl;
					break;
			//////////////////////////////////////////////////////////////////////////////
			default:
				std::cout << BIRED;
				std::cout << "Opción incorrecta ";
				std::cout << RESET;
				std::cout << "--> ";
			  	std::cout << ONIRED;
				std::cout << opcion << std::endl;
				std::cout << RESET;
     }
  
    if (opcion !=0)
    {
		PLACE(25,1);
		std::cout << "Pulse ";
		std::cout << BIGREEN;
		std::cout << "ENTER";
		std::cout << RESET;
		std::cout << " para mostrar el ";
		std::cout << INVERSE;
		std::cout << "menú"; 
		std::cout << RESET;

		// Pausa
		std::cin.ignore();

		std::cout << CLEAR_SCREEN;
    }
	  }while(opcion!=0);

	return 0;
}


