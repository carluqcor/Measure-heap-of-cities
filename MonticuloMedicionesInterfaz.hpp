/*!
	\file MonticuloMedicionesInterfaz.hpp
	\brief Se define la interfaz del TAD MonticuloMediciones.
    \author Carlos Luque Córdoba
    \date   25/04/2018
*/

#ifndef _MONTICULO_MEDICIONES_INTERFAZ_HPP
#define _MONTICULO_MEDICIONES_INTERFAZ_HPP

#include "Medicion.hpp"

/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed
{
	//!  Definición de la clase MonticuloMedicionesInterfaz
	class MonticuloMedicionesInterfaz
	{
		public:			
		//!Observadores Públicos
		 /*!
        	\brief  Comprueba si el monticulo está vacía
			\note   Función virtual pura, que deberá ser redefinida en la clase heredera
	        \note   Función de tipo "const": no puede modificar al objeto actual
        	\return true, si la lista está vacía; false, en caso contrario
    	*/
		virtual bool isEmpty() const = 0;

		/*!
	        \brief  Devuelve la medición situada en la cima
			\note   Función virtual pura, que deberá ser redefinida en la clase heredera
	        \note   Función de tipo "const": no puede modificar al objeto actual
	        \return Devuelve una medición del tipo Medicion
    	*/
		virtual ed::Medicion top() const = 0;

		//!Modificadores Públicos
		/*!
	        \brief  Inserta una medición que no esté ya dentro del montículo
			\note   Función virtual pura, que deberá ser redefinida en la clase heredera
	        \note   Modificar al objeto actual
	        \param  medicion: medicion de tipo Medicion constante pasada como parámetro
    	*/
		virtual void insert(ed::Medicion const &medicion) = 0;

		/*!
	        \brief  Elimina la medición situada en la cima
			\note   Función virtual pura, que deberá ser redefinida en la clase heredera
	        \note   Modificar al objeto actual
    	*/
		virtual void remove() = 0;

	}; // Clase MonticuloMedicionesInterfaz

} // Espacio de nombres ed

#endif //  _MONTICULO_MEDICIONES_INTERFAZ_HPP
