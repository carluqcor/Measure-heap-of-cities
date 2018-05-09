/*! 
   \file Medicion.hpp
   \brief Fichero de la clase Medicion: medición de una estación meteorológica 
   \author Carlos Luque Córdoba
   \date   25/04/2018
*/

#ifndef _MEDICION_HPP_
#define _MEDICION_HPP_

// Entrada y salida 
#include <iostream>
// Abs para cotas de error de numeros reales positivos
#include <cmath>

// Para controlar las precondiciones y postcondiciones mediante asertos
#include <cassert>

// Definición de la clase Fecha
#include "Fecha.hpp"


// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación de números reales


// Se incluye la clase Medicion dentro del espacio de nombres de la asigantura: ed
/*!   
   \namespace ed
   \brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed {

//!  Definición de la clase Medicion 
class Medicion
{
  //! \name Atributos privados de la clase Medicion
   private: 

	ed::Fecha _fecha; //!<Fecha de tipo Fecha
	double _precipitacion; //!<Precipitación de tipo double
   double _temperatura; //!<Temperatura de tipo double
   double _humedad; //!<Humedad de tipo double
   double _velViento; //!<Velocidad del viento de tipo double
   double _radiacion; //!<Radiación de tipo double

   //! \name Funciones o métodos públicos de la clase Medicion
   public:

	   //! \name Constructor de la clase Medicion

      /*! 
         \brief     Constructor que crea una Medicion apartir de una fecha de tipo Fecha y una precipitacion de tipo double
         \attention Función sobrecargada 
         \note      Función inline
         \warning   Los parámetros tienen valores por defecto
         \param     fecha: fecha de la medicion; valor por defecto: 1-1-1
         \param     precipitacion: Precipitacion de la medicion; valor por defecto: 0.0
         \param     humedad: Humedad de la medicion; valor por defecto: 0.0
         \param     temperatura: Temperatura de la medicion; valor por defecto: 0.0
         \param     velocidadViento: Velocidad del viento de la medicion; valor por defecto: 0.0
         \param     radiacion: Radiacion de la medicion; valor por defecto: 0.0
         \pre       Ninguna
         \post      La fecha que pasamos como parámetro y la precipitación, deben ser igual a las actuales
         \sa        getFecha(), getPrecipitacion(), setFecha(), setPrecipitacion()
      */
      inline Medicion(ed::Fecha fecha=Fecha(1,1,1), double precipitacion=0.0, double temperatura=0.0, double humedad=0.0, double velocidadViento=0.0, double radiacion=0.0){
         setFecha(fecha);
         setPrecipitacion(precipitacion);
      	setTemperatura(temperatura);
         setHumedad(humedad);
         setVelocidadViento(velocidadViento);
         setRadiacion(radiacion);

         #ifndef NDEBUG
      		assert(getFecha()==fecha);
      	  	assert(std::abs(getPrecipitacion()-precipitacion)<COTA_ERROR);
            assert(std::abs(getTemperatura()-temperatura)<COTA_ERROR);
            assert(std::abs(getHumedad()-humedad)<COTA_ERROR);
            assert(std::abs(getVelocidadViento()-velocidadViento)<COTA_ERROR);
            assert(std::abs(getRadiacion()-radiacion)<COTA_ERROR);
         #endif
      }

      /*! 
         \brief     Constructor que crea una Medicion apartir de una medicion pasada como parámetro constante
         \attention Función sobrecargada 
         \note      Función inline
         \param     medicion: objeto de la clase Medi ion pasado como referencia constante
         \pre       Ninguna
         \post      La fecha que pasamos como parámetro y la precipitación, deben ser igual a las actuales
         \sa        getFecha(), getPrecipitacion(), setFecha(), setPrecipitacion()
      */
   	inline Medicion(Medicion const &medicion){
         setFecha(medicion.getFecha());
         setTemperatura(medicion.getTemperatura());
         setHumedad(medicion.getHumedad());
         setVelocidadViento(medicion.getVelocidadViento());
         setRadiacion(medicion.getRadiacion());
         setPrecipitacion(medicion.getPrecipitacion());
   		#ifndef NDEBUG
   			assert(getFecha()==medicion.getFecha());
   			assert(std::abs(getPrecipitacion()-medicion.getPrecipitacion())<COTA_ERROR);
            assert(std::abs(getTemperatura()-medicion.getTemperatura())<COTA_ERROR);
            assert(std::abs(getHumedad()-getHumedad())<COTA_ERROR);
            assert(std::abs(getVelocidadViento()-getVelocidadViento())<COTA_ERROR);
            assert(std::abs(getRadiacion()-getRadiacion())<COTA_ERROR);
   		#endif
   	}
	

	//! \name Observadores: funciones de consulta de la clase Medicion
      /*! 
         \fn      Fecha getFecha()
         \brief   Función que devuelve una fecha constante
         \note    Función inline de tipo Fecha y constante
         \return  fecha constante de tipo Fecha
         \pre     Ninguna
         \post    Ninguna
      */
   	inline ed::Fecha const getFecha() const {return _fecha;}

      /*! 
         \fn      double getPrecipitacion()
         \brief   Función que devuelve una precipitacion constante
         \note    Función inline de tipo double y constante
         \return  Precipitacion constante de tipo double
         \pre     Ninguna
         \post    Ninguna
      */
   	inline double const getPrecipitacion() const {return _precipitacion;}

	
      /*! 
         \fn      double getTemperatura()
         \brief   Función que devuelve una temperatura constante
         \note    Función inline de tipo double y constante
         \return  Temperatura constante de tipo double
         \pre     Ninguna
         \post    Ninguna
      */
      inline double const getTemperatura() const {return _temperatura;}

      /*! 
         \fn      double getHumedad()
         \brief   Función que devuelve una humedad constante
         \note    Función inline de tipo double y constante
         \return  Humedad constante de tipo double
         \pre     Ninguna
         \post    Ninguna
      */
      inline double const getHumedad() const {return _humedad;}

      /*! 
         \fn      double getVelocidadViento()
         \brief   Función que devuelve una velocidad del viento constante
         \note    Función inline de tipo double y constante
         \return  Velocidad del viento constante de tipo double
         \pre     Ninguna
         \post    Ninguna
      */
      inline double const getVelocidadViento() const {return _velViento;}

      /*! 
         \fn      double getRadiacion()
         \brief   Función que devuelve una radiacion constante
         \note    Función inline de tipo double y constante
         \return  Radiación constante de tipo double
         \pre     Ninguna
         \post    Ninguna
      */
      inline double const getRadiacion() const {return _radiacion;}

	//! \name Funciones de modificación de la clase Medicion
      /*!       
         \fn    void setFecha(Fecha &fecha)
         \brief Función que asigna una nueva fecha a la fecha actual
         \note  Función inline de tipo void
         \param fecha: objeto de la clase Fecha pasado como referencia constante
         \pre   Ninguna
         \post  La fecha pasada como parámetro debe ser igual a la actual
         \sa    getFecha()
      */
   	inline void setFecha(ed::Fecha const &fecha){
   		_fecha=fecha;
   		#ifndef NDEBUG
   			assert(getFecha()==fecha);
   		#endif
   	}
	
      /*!       
         \fn    void setPrecipitacion(double precipitacion)
         \brief Función que asigna una nueva precipitacion a la precipitacion actual
         \note  Función inline de tipo void
         \param precipitacion: precipitacion de tipo double 
         \pre   Ninguna
         \post  La precipitacion pasada como parámetro debe ser igual a la actual
         \sa    getPrecipitacion()
      */
   	inline void setPrecipitacion(double const precipitacion){
   		_precipitacion=precipitacion;
   		#ifndef NDEBUG
   			assert(std::abs(getPrecipitacion()-precipitacion)<COTA_ERROR);
   		#endif
   	}

      /*!       
         \fn    void setTemperatura(double temperatura)
         \brief Función que asigna una nueva temperatura a la temperatura actual
         \note  Función inline de tipo void
         \param temperatura: temperatura de tipo double 
         \pre   Ninguna
         \post  La temperatura pasada como parámetro debe ser igual a la actual
         \sa    getTemperatura()
      */
      inline void setTemperatura(double const temperatura){
         _temperatura=temperatura;
         #ifndef NDEBUG
            assert(std::abs(getTemperatura()-temperatura)<COTA_ERROR);
         #endif
      }

      /*!       
         \fn    void setHumedad(double humedad)
         \brief Función que asigna una nueva humedad a la humedad actual
         \note  Función inline de tipo void
         \param humedad: humedad de tipo double 
         \pre   Ninguna
         \post  La humedad pasada como parámetro debe ser igual a la actual
         \sa    getHumedad()
      */
      inline void setHumedad(double const humedad){
         _humedad=humedad;
         #ifndef NDEBUG
            assert(std::abs(getHumedad()-humedad)<COTA_ERROR);
         #endif
      }

      /*!       
         \fn    void setVelocidadViento(double VelocidadViento)
         \brief Función que asigna una nueva velocidad del viento a la velocidad del viento actual
         \note  Función inline de tipo void
         \param velocidadViento: velocidad del viento de tipo double 
         \pre   Ninguna
         \post  La velocidad del viento pasada como parámetro debe ser igual a la actual
         \sa    getVelocidadViento()
      */
      inline void setVelocidadViento(double const velocidadViento){
         _velViento=velocidadViento;
         #ifndef NDEBUG
            assert(std::abs(getVelocidadViento()-velocidadViento)<COTA_ERROR);
         #endif
      }
      
      /*!       
         \fn    void setRadiacion(double radiacion)
         \brief Función que asigna una nueva radiacion a la radiacion actual
         \note  Función inline de tipo void
         \param radiacion: radiacion de tipo double 
         \pre   Ninguna
         \post  La radiacion pasada como parámetro debe ser igual a la actual
         \sa    getRadiacion()
      */
      inline void setRadiacion(double const radiacion){
         _radiacion=radiacion;
         #ifndef NDEBUG
            assert(std::abs(getRadiacion()-radiacion)<COTA_ERROR);
         #endif
      }
	//! \name Operadores

   /*! 
      \fn        bool operator==(Medicion const &medicion)
      \brief     Operador de igualdad: operador que comprueba si la fecha actual es igual a la fecha de la medicion pasada como parámetro
      \attention Se sobrecarga el operador de asignación "=="
      \note      Función bool de tipo const
      \warning   Se requiere que la funcion de acceso getFecha() tenga el modificador const
      \param     medicion: objeto de la clase Medicion pasado como referencia constante
      \pre       Ninguna
      \post      La fecha actual y la de la medición deben de dar como resultado, lo mismo que el valor bool
      \sa        getFecha()
   */
   bool operator==(ed::Medicion const &medicion)const;
   
   /*! 
      \fn        Medicion &operator=(Medicion const &medicion)
      \brief     Operador de asignación: operador que asigna la medicion pasada como parámetro a la actual
      \attention Se sobrecarga el operador de asignación "="
      \note      Función inline de tipo Medicion
      \warning   Se requiere que la funcion de acceso getPrecipitacion, getTemperatura, getHumedad, getVelocidadViento, getRadiacion tengan el modificador const
      \param     medicion: objeto de la clase Medicion pasado como referencia constante
      \pre       Ninguna
      \post      Ninguna
      \sa        getFecha(), getPrecipitacion(), getTemperatura(), getHumedad(), getVelocidadViento(), getRadiacion(), setFecha(), setPrecipitacion(), setTemperatura(), setHumedad(), setVelocidadViento(), setRadiacion()
   */
   inline Medicion &operator=(ed::Medicion const &medicion){
      setFecha(medicion.getFecha());
      setPrecipitacion(medicion.getPrecipitacion());
      setTemperatura(medicion.getTemperatura());
      setHumedad(medicion.getHumedad());
      setVelocidadViento(medicion.getVelocidadViento());
      setRadiacion(medicion.getRadiacion());
      return (*this);
   }

   /*! 
      \fn        bool &operator<(Medicion const &h)
      \brief     Operador de Menor-Mayor: operador que devuelve true si la precipitacion actual es menor que la pasada por referencia
      \attention Se sobrecarga el operador de asignación "<"
      \note      Función inline de tipo bool constante
      \warning   Se requiere que la funcion de acceso getPrecipitacion tengan el modificador const
      \param     h: objeto de la clase Medicion pasado como referencia constante
      \pre       Ninguna
      \post      Ninguna
      \sa        getPrecipitacion()
   */
   bool operator<(Medicion const &h)const;
   
   /*! 
      \fn        bool &operator>(Medicion const &h)
      \brief     Operador de Mayor-Menor: operador que devuelve true si la precipitacion actual es mayor que la pasada por referencia
      \attention Se sobrecarga el operador de asignación ">"
      \note      Función inline de tipo bool constante
      \warning   Se requiere que la funcion de acceso getPrecipitacion tengan el modificador const
      \param     h: objeto de la clase Medicion pasado como referencia constante
      \pre       Ninguna
      \post      Ninguna
      \sa        getPrecipitacion()
   */
   bool operator>(Medicion const &h)const;


	//! \name Funciones de lectura y escritura de la clase Medicion
   /*!       
         \fn    void leerMedicion()
         \brief Función que lee por pantalla una medicion
         \note  Función de tipo void
         \pre   Ninguna
         \post  Ninguna
         \sa    setFecha(), setPrecipitacion(), setTemperatura(), setHumedad(), setVelocidadViento(), setRadiacion()
   */
   void leerMedicion();
   
   /*!       
         \fn    void leerMedicion2()
         \brief Función que lee por pantalla una medicion sin la fecha
         \note  Función de tipo void
         \pre   Ninguna
         \post  Ninguna
         \sa    setPrecipitacion(), setTemperatura(), setHumedad(), setVelocidadViento(), setRadiacion()
   */
   void leerMedicion2();

   /*!       
         \fn    void escribirMedicion()
         \brief Función que imprime por pantalla una medicion
         \note  Función de tipo void
         \pre   Ninguna
         \post  Ninguna
         \sa    getFecha(), getPrecipitacion(), getTemperatura(), getHumedad(), getVelocidadViento(), getRadiacion()
   */
   void escribirMedicion();

   /*!       
         \fn    void escribirMedicion2()
         \brief Función que imprime por pantalla una medicion sin la fecha
         \note  Función de tipo void
         \pre   Ninguna
         \post  Ninguna
         \sa    getPrecipitacion(), getTemperatura(), getHumedad(), getVelocidadViento(), getRadiacion()
   */
   void escribirMedicion2();
	  



}; // Fin de la definición de la clase Medicion

   //! \name Funciones externas de la clase Medicion: sobrecarga de los operadores de flujo
   /*!
      \brief     Sobrecarga del operador de entrada o lectura ">>"
      \param     stream: Flujo de entrada
      \param     medicion: Medición de tipo Medicion que es pasada por referencia  
      \pre       Ninguna
      \post      Ninguna
      \sa        operator<<()
    */
	istream &operator>>(istream &stream, ed::Medicion &medicion);
   /*!
      \brief     Sobrecarga del operador de salida o escritura "<<"
      \param     stream: Flujo de salida
      \param     medicion: Medición de tipo Medicion que es pasada por referencia constante 
      \pre       Ninguna
      \post      Ninguna
      \sa        operator>>()
   */
	ostream &operator<<(ostream &stream, ed::Medicion const &medicion);

} // \brief Fin de namespace ed.

//  _MEDICION_HPP_
#endif 
