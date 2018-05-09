/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 3
  \author Carlos Luque Córdoba
  \date  25/04/2018
*/

#ifndef _FuncionesAuxiliares_HPP_
#define _FuncionesAuxiliares_HPP_

#include "MonticuloMediciones.hpp"

/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed
{
	/*! 
		\brief   Muestra el menú del programa principal 
		\return  Devuelve el número de opción elegido
	*/
 	int menu();
	
	/*! 
	    \fn      void insertarM(Medicion &medicion, MonticuloMediciones &monticulo)
	    \brief   Función que inserta una medición en el montículo
	    \note    Función de tipo void
	    \param   medicion: Medicion de tipo medicion pasada como parámetro por referencia
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro por referencia
    	\sa      insert()
    */
	void insertarM(ed::Medicion &medicion, ed::MonticuloMediciones &monticulo);

	/*! 
	    \fn      void cargarMonticuloDeFichero(std::string const & nombreFichero, ed::MonticuloMediciones & monticulo)
	    \brief   Función que carga el montículo con un fichero
	    \note    Función de tipo void
	    \param   nombreFichero: Cadena pasada por referencia constante
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro por referencia
    	\sa      insertM(), print()
    */
	void cargarMonticuloDeFichero(std::string const & nombreFichero, ed::MonticuloMediciones & monticulo); 

	/*! 
	    \fn    	 void grabarMonticuloEnFichero (std::string const & nombreFichero, ed::MonticuloMediciones const & monticulo)
	    \brief   Función que graba el montículo en un fichero
	    \note    Función de tipo void
	    \param   nombreFichero: Cadena pasada por referencia constante
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro por referencia
    	\sa      isEmpty(), top(), remove()
    */
	void grabarMonticuloEnFichero (std::string const & nombreFichero, ed::MonticuloMediciones const & monticulo); 

	/*! 
	    \fn      void Modificar(MonticuloMediciones &monticulo)
	    \brief   Función que modifica la cabeza del montículo
	    \note    Función de tipo void
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro por referencia
    	\sa      size(), leerMedicion2(), modify()
    */
	void Modificar(ed::MonticuloMediciones &monticulo);

	/*! 
	    \fn      void borrarTodo(MonticuloMediciones &monticulo)
	    \brief   Función que elimina todas las mediciones del montículo
	    \note    Función de tipo void
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro por referencia
    	\sa      size(), removeAll()
    */
	void borrarTodo(ed::MonticuloMediciones &monticulo);

	/*! 
	    \fn      void monticuloStats(MonticuloMediciones const &monticulo)
	    \brief   Función que muestra las estádisticas del montículo
	    \note    Función de tipo void
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro constante por referencia
    	\sa      size(), precipitacionTotal(), precipitacionMedia()
    */
	void monticuloStats(ed::MonticuloMediciones const &monticulo);

	/*! 
	    \fn      void mostrarTop(MonticuloMediciones const &monticulo)
	    \brief   Función que muestra la cabeza del montículo
	    \note    Función de tipo void
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro constante por referencia
    	\sa      size(), top(), escribirMedicion()
    */
	void mostrarTop(ed::MonticuloMediciones const &monticulo);

	/*! 
	    \fn      void eliminarCima(MonticuloMediciones &monticulo)
	    \brief   Función que eliminia la cabeza del montículo
	    \note    Función de tipo void
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro constante por referencia
    	\sa      size(), remove()
    */
	void eliminarCima(ed::MonticuloMediciones &monticulo);

	/*! 
	    \fn      void estadisticasFecha(MonticuloMediciones const &monticulo)
	    \brief   Función que muestra las estadísticas de una fecha concreta
	    \note    Función de tipo void
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro constante por referencia
    	\sa      statPorDia()
    */
	void estadisticasFecha(ed::MonticuloMediciones const &monticulo);

	/*! 
	    \fn      void estadisticasMes(MonticuloMediciones const &monticulo)
	    \brief   Función que muestra las estadísticas de un mes concreto
	    \note    Función de tipo void
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro constante por referencia
    	\sa      statPorMes()
    */
	void estadisticasMes(ed::MonticuloMediciones const &monticulo);

	/*! 
	    \fn      void printNew(MonticuloMediciones const &monticulo)
	    \brief   Función que imprime por pantalla en orden por precipitación
	    \note    Función de tipo void
	    \param   monticulo: Montículo de tipo MonticuloMediciones pasada como parámetro constante por referencia
    	\sa      isEmpty(), top(). getFecha(), getTemperatura(), getHumedad(), getVelocidadViento(), getRadiacion(), getPrecipitacion()
    */
	void printNew(ed::MonticuloMediciones const &monticulo);

} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FuncionesAuxiliares_HPP_
#endif

