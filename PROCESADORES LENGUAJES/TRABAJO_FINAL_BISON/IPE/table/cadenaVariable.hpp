/*!	
	\file    cadenaVariable.hpp
	\brief   Declaration of cadenaVariable class
	\author  
	\date    2017-12-1
	\version 1.0
*/

#ifndef _CADENAVARIABLE_HPP_
#define _CADENAVARIABLE_HPP_

#include <string>
#include <iostream>

#include "variable.hpp"
using namespace std;
/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class cadenaVariable
  \brief Definition of atributes and methods of cadenaVariable class
  \note  cadenaVariable Class publicly inherits from Variable class
*/
class cadenaVariable:public lp::Variable
{
/*!		
\name Private atributes of cadenaVariable class
*/
	private:
		string      _value;   //!< \brief cadena value of the cadenaVariable

/*!		
\name Public methods of cadenaVariable class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Variable's constructor as members initializer
	\param name: name of the cadenaVariable
	\param token: token of the cadenaVariable
	\param type: type of the cadenaVariable
	\param value: string value of the cadenaVariable
	\pre   None
	\post  A new cadenaVariable is created with the values of the parameters
	\sa   setName, setValue
*/
	inline cadenaVariable(std::string name="", int token = 0, int type = 0, string value=""): 
 	Variable(name,token,type)
	{
		this->setValue(value);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param n: object of cadenaVariable class
	\pre   None
	\post  A new cadenaVariable is created with the values of an existent cadenaVariable
	\sa    setName, setValue
*/
	cadenaVariable(const cadenaVariable & n)
	{
		// Inherited methods
		this->setName(n.getName());

		this->setToken(n.getToken());

		this->setType(n.getType());
		
		// Own method
		this->setValue(n.getValue());
	}


/*!	
	\name Observer
*/
	
/*!	
	\brief  Public method that returns the value of the cadenaVariable
	\note   Función inline
	\pre    None
	\post   None
    \return Value of the cadenaVariable
	\sa		getValue
*/
	inline string getValue() const
	{
		return this->_value;
	}



/*!	
	\name Modifier
*/
		
/*!	
	\brief   This functions modifies the value of the cadenaVariable
	\note    Inline function
	\param   value: new value of the cadenaVariable
	\pre     None
	\post    The value of the cadenaVariable is equal to the parameter 
	\return  void
	\sa 	 setValue
*/
	inline void setValue(const string & value)
	{
	    this->_value = value;
	}



		
/*!	
	\name I/O Functions
*/
		
/*!		
	\brief Read a cadenaVariable
	\pre   None
	\post  The atributes of the cadenaVariable are modified with the read values
    \sa    write
*/
	void read();

	
/*!		
	\brief Write a cadenaVariable
	\pre   None
	\post  None
    \sa    read
*/
	void write() const;


/*!	
	\name Operators
*/
	
/*!		
	\brief  Assignment Operator
	\param  n: objectoof cadenaVariable class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	cadenaVariable &operator=(const cadenaVariable &n);
	

 //! \name Friend functions
/*!		
	\brief  Insertion operator
	\param  i: input stream
	\param  n: object of cadenaVariable class
	\pre    nome
	\post   The atributes of the cadenaVariable are modified with the inserted values from the input stream
	\return The input stream
*/
	friend std::istream &operator>>(std::istream &i, cadenaVariable &n);

/*!		
	\brief  Extraction operator
	\param  o: output stream
	\param  n: object of cadenaVariable class
	\pre    nome
	\post   The atributes of the cadenaVariable are written in the output stream
	\return The output stream
*/
	friend std::ostream &operator<<(std::ostream &o, cadenaVariable const &n);
	
// End of cadenaVariable class
};

// End of name space lp
}

// End of _CADENAVARIABLE_HPP_
#endif
