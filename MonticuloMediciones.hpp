/*!
	\file MonticuloMediciones.hpp
	\brief Se define el TAD MonticuloMediciones.
    \author Carlos Luque Córdoba
    \date   25/04/2018
*/

#ifndef _MONTICULO_MEDICIONES_HPP
#define _MONTICULO_MEDICIONES_HPP

#include <vector>

#include <cassert>

#include "Medicion.hpp"

#include "MonticuloMedicionesInterfaz.hpp"

/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed{
	//!  Definición de la clase MonticuloMediciones que hereda públicamente de montículoMedicionesInterfaz
	class MonticuloMediciones : public ed::MonticuloMedicionesInterfaz{
////////////////////////////////////////////////////////////////////

// Métodos privados de la clase MonticuloMediciones
	private:
		//! Atributos privados
		std::vector<Medicion> _vectorPrecipitaciones; //! Atributo privado de la clase Monticulo Mediciones

		//! Observadores privados
		/*! 
	         \fn      Medicion getElement(unsigned int const i)
	         \brief   Función que devuelve una medicion constante
	         \note    Función inline de tipo Medicion y constante
	         \param   i: entero positivo
	         \return  Medicion constante
	         \pre     i>=0 e i<size()
	         \post    Ninguna
      	*/
		inline ed::Medicion const &getElement(unsigned int const i)const{
			#ifndef NDEBUG
				assert(i>=0 && i<size());
			#endif
				return _vectorPrecipitaciones[i];
		}

		/*! 
	         \fn      unsigned int getLeftChild(unsigned int const i)
	         \brief   Función que devuelve el indice del hijo izquierdo del nodo actual
	         \note    Función inline de tipo entero positivo y constante
	         \param   i: entero positivo
	         \return  Indice entero positivo del hijo izquierdo
	         \pre     i>=0
	         \post    valorDevuelto==((2*i)+1)
      	*/
		inline unsigned int getLeftChild(unsigned int const i) const {
			#ifndef NDEBUG
				assert(i>=0);
			#endif
			
			unsigned int indice=((2*i)+1);

			#ifndef NDEBUG
				assert(indice=((2*i)+1));
			#endif

			return indice;
		}

		/*! 
	         \fn      unsigned int getRightChild(unsigned int const i)
	         \brief   Función que devuelve el indice del hijo derecho del nodo actual
	         \note    Función inline de tipo entero positivo y constante
	         \param   i: entero positivo
	         \return  Indice entero positivo del hijo derecho
	         \pre     i>=0
	         \post    valorDevuelto==((2*i)+2)
      	*/
		inline unsigned int getRightChild(unsigned int const i) const {
			#ifndef NDEBUG
				assert(i>=0);
			#endif
			
			unsigned int indice=((2*i)+2);

			#ifndef NDEBUG
				assert(indice=((2*i)+2));
			#endif

			return indice;
		}

		/*! 
	         \fn      unsigned int getParent(unsigned int const i)
	         \brief   Función que devuelve el indice del padre del nodo actual
	         \note    Función inline de tipo entero positivo y constante
	         \param   i: entero positivo
	         \return  Indice entero positivo del padre del nodo
	         \pre     i>=1
	         \post    valorDevuelto==((i-1)/2)
      	*/
		inline unsigned int getParent(unsigned int const i) const{
			#ifndef NDEBUG
				assert(i>=1);
			#endif
			
			unsigned int indice=((i-1)/2);

			#ifndef NDEBUG
				assert(indice==((i-1)/2));
			#endif

			return indice;
		}
		
		/*! 
	         \fn      bool has(Medicion const &medicion)
	         \brief   Función que devuelve true si el montículo tiene la fecha de la medicion ya dentro de el
	         \note    Función inline de tipo bool y constante
	         \param   medicion: Medicion de tipo constante pasada como referencia
	         \return  true o false
	         \pre     Ninguna
	         \post    Ninguna
      	*/
		bool has(ed::Medicion const &medicion) const;

		//! Modificadores privados
		/*! 
	         \fn      void setElement(unsigned int const i, Medicion const &medicion)
	         \brief   Función que asigna el indice y medicion pasado como parámetro a la medición actual
	         \note    Función inline de tipo void
	         \param   i: entero positivo
	         \param   medicion: Medicion de tipo constante pasada como referencia
	         \return  Ninguna
	         \pre     i>=0 e i<size()
	         \post    getElement(i)==medicion
      	*/
		inline void setElement(unsigned int const i, ed::Medicion const &medicion){
			#ifndef NDEBUG
				assert(i>=0 && i<size());
			#endif
				(_vectorPrecipitaciones[i])=medicion;
			#ifndef NDEBUG
				assert(getElement(i)==medicion);
			#endif
		}

		/*! 
	         \fn      void shiftUp(unsigned int const i)
	         \brief   Función que hace que el nodo con indice i, flote hacia arriba si es necesario en el insert
	         \note    Función de tipo void
	         \param   i: entero positivo
	         \return  Ninguna
	         \pre     i>0 e i<size()
	         \post    Si no es la cima, el elemento actual es menor o igual que su padre, di tiene hijo izquierdo, el elemento actual es mayor o igual que él y, además, si tiene hijo derecho, es mayor o igual que él.
        	 \sa      getPrecipitacion(), getElement(), setElement(), getParent()      	
      	*/
		void shiftUp(unsigned int const i); 

		/*! 
	         \fn      void shiftDown(unsigned int const i)
	         \brief   Función que hace que el nodo con indice i, se hunda en los metodos remove y modify
	         \note    Función de tipo void
	         \param   i: entero positivo
	         \return  Ninguna
	         \pre     i>=0 e i<size()
	         \post    Si no es la cima, el elemento actual es menor o igual que su padre, di tiene hijo izquierdo, el elemento actual es mayor o igual que él y, además, si tiene hijo derecho, es mayor o igual que él.
        	 \sa      getPrecipitacion(), getElement(), setElement(), getParent() 

      	*/
		void shiftDown(unsigned int const i);		

////////////////////////////////////////////////////////////////////////////////////7

// Métodos públicos de la clase MonticuloMediciones

	public:
		//! Constructores publicos
		/*! 
         \brief     Constructor vacio que crea un monticulo de mediciones
         \attention Función sobrecargada 
         \note      Función inline
         \warning   No hay parámetros
         \pre       Ninguna
         \post      El monticulo creado debe estar vacio
         \sa        isEmpty()
      */
		inline MonticuloMediciones(){
			#ifndef NDEBUG
				assert(isEmpty()==true);
			#endif
		}

		//! Observadores Publicos
		/*! 
	         \fn      inline bool isEmpty()
	         \brief   Función que comprueba si el monticulo está vacio
	         \note    Función de tipo bool e inline
	         \return  True si el montículo está vacío
	         \pre     Ninguna
	         \post    valorDevuelto==(size()==0))
        	 \sa      size()

      	*/
		inline bool isEmpty() const {
			bool val=false;
			if(_vectorPrecipitaciones.empty())
				val=true;
			#ifndef NDEBUG
				assert(val==(size()==0));
			#endif
				return val;
		}

		/*! 
	         \fn      inline unsigned int i size()
	         \brief   Función que devuelve el tamaño del montículo
	         \note    Función de tipo entero positivo e inline
	         \return  Tamaño del montículo
	         \pre     Ninguna
	         \post    Ninguna
        	 \sa      size()

      	*/
		inline unsigned int size() const {
			return _vectorPrecipitaciones.size();
		}

		/*! 
	         \fn      inline Medicion top()
	         \brief   Función que devuelve la cima del montículo
	         \note    Función de tipo Medicion e inline
	         \return  La cima del montículo
	         \pre     Que el monículo no esté vacío
	         \post    La medicion devuelta sea la cima
        	 \sa      isEmpty()

      	*/
		inline ed::Medicion top() const {
			#ifndef NDEBUG
				assert(isEmpty()==false);
			#endif
				Medicion medicionDevuelto=_vectorPrecipitaciones.front();
			#ifndef NDEBUG
				assert(medicionDevuelto==_vectorPrecipitaciones.front());
			#endif

			return medicionDevuelto;
		}

		/*! 
	         \fn      void statPorDia()
	         \brief   Función que calcula ciertas estádisticas de una fecha del montículo
	         \note    Función de tipo void
	         \pre     Ninguna
	         \post    Ninguna
    		 \sa      getFecha(), getPrecipitacion(), getTemperatura(), getHumedad(), getVelocidadViento(), getRadiacion(), setFecha(), setPrecipitacion(), setTemperatura(), setHumedad(), setVelocidadViento(), setRadiacion()
      	*/
		void statPorDia()const;

		/*! 
	         \fn      void statPorMes()
	         \brief   Función que calcula ciertas estádisticas por mes de un año que esté ya en el montículo
	         \note    Función de tipo void
	         \pre     Ninguna
	         \post    Ninguna
    		 \sa      getFecha(), getPrecipitacion(), getTemperatura(), getHumedad(), getVelocidadViento(), getRadiacion(), setFecha(), setPrecipitacion(), setTemperatura(), setHumedad(), setVelocidadViento(), setRadiacion()
      	*/
		void statPorMes()const;

		/*! 
	         \fn      double precipitacionTotal()
	         \brief   Función que calcula la precipitación total del montículo
	         \note    Función de tipo double
	         \pre     Ninguna
	         \post    Ninguna
    		 \sa      getFecha(), getPrecipitacion(), setFecha(), setPrecipitacion()
      	*/
		double precipitacionTotal()const;

		/*! 
	         \fn      double hayMedicion2(Medicion const &medicion)
	         \brief   Función que devuelve la precipitación de una fecha
	         \note    Función de tipo double
	         \param   medicion: Medicion de tipo medicion constante pasada como parámetro por referencia
	         \pre     Ninguna
	         \post    Ninguna
    		 \sa      getFecha(), getPrecipitacion(), setFecha(), setPrecipitacion()
      	*/
		double hayMedicion2(ed::Medicion const &medicion)const;

		/*! 
	         \fn      double precipitacionMedia()
	         \brief   Función que calcula la precipitación media del montículo
	         \note    Función de tipo double
	         \pre     Ninguna
	         \post    Ninguna
    		 \sa      getFecha(), getPrecipitacion(), setFecha(), setPrecipitacion()
      	*/
		double precipitacionMedia()const;

		//! Modificadores públicos
		/*! 
	         \fn      void insert(Medicion const &medicion)
	         \brief   Función que inserta una medición en el montículo y la coloca en su lugar según la precipitación
	         \note    Función de tipo void
	         \param   medicion: Medicion de tipo medicion constante pasada como parámetro por referencia
	         \pre     Ninguna
	         \post    Ninguna
    		 \sa      size(), has(), shiftUp()
      	*/
		void insert(ed::Medicion const &medicion);

		/*! 
	         \fn      void remove()
	         \brief   Función que borra la cima del montículo
	         \note    Función de tipo void
	         \pre     El montículo no debe estar vacío
	         \post    Ninguna
    		 \sa      size(), isEmpty(), shiftDown()
      	*/
		void remove();
		
		/*! 
	         \fn      inline void removeAll()
	         \brief   Función que borra todo el montículo
	         \note    Función de tipo void e inline
	         \pre     Ninguna
	         \post    El montículo debe estar vacío
    		 \sa      isEmpty()
      	*/
		inline void removeAll(){
			_vectorPrecipitaciones.clear();
			#ifndef NDEBUG
				assert(isEmpty()==true);
			#endif
		}

		/*! 
	         \fn      void modify()
	         \brief   Función que modifica la cima del montículo
	         \note    Función de tipo void
	         \param   medicion: Medicion de tipo medicion pasada como parámetro por referencia
	         \pre     El montículo no debe estar vacío
	         \post    El montículo'debe tener esa medición
    		 \sa      size(), isEmpty(), shiftDown(), has()
      	*/
		void modify(ed::Medicion &medicion);

		//! Operadores públicos

		/*! 
		    \fn        Medicion &operator=(MonticuloMediciones &m)
		    \brief     Operador de asignación: operador que asigna un montículo a otro
		    \attention Se sobrecarga el operador de asignación "="
		    \note      Función de tipo MonticuloMediciones
		    \param     m: objeto de la clase montículoMediciones pasado como referencia constante
		    \pre       El monticulo actual debe diferente igual al pasado como referencia
		    \post      Ninguna
  		*/
		MonticuloMediciones &operator=(MonticuloMediciones &m);

		/*! 
		    \fn        bool operator!=(MonticuloMediciones &m)
		    \brief     Operador de negación: operador que niega la igualdad de dos montículos
		    \attention Se sobrecarga el operador de asignación "!="
		    \note      Función de tipo bool
		    \param     m: objeto de la clase montículoMediciones pasado como referencia constante
		    \return    Devuelve true si son diferentes, si no devuelve false
		    \pre       Ninguna
		    \post      Ninguna
  		*/
		bool operator!=(MonticuloMediciones &m)const;


		//! Funciones de Escritura
		/*! 
	         \fn      void print()
	         \brief   Función que imprime por pantalla el estado actual del heap
	         \note    Función de tipo void
	         \pre     Ninguna
	         \post    Ninguna
    		 \sa      getFecha(), getPrecipitacion(), getTemperatura(), getHumedad(), getVelocidadViento(), getRadiacion()
      	*/
		void print();

	};//Se cierra la clase MonticuloMediciones
}//Se cierra el espacio de nombres ed

#endif // _MONTICULO_MEDICIONES_HPP
