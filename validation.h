/*******************************************************************
*
*  DESCRIPTION: Validation
*
*  AUTHOR: Yasser Jafer
*
*  EMAIL: yjafe089@uottawa.ca
*
*
*  DATE: 18/10/2002
*
*******************************************************************/
#ifndef __VALIDATION_H
#define __VALIDATION_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class Validation: public Atomic
{
public:
	Validation( const string &name = "Validation" ) ;	 // Default constructor

	virtual string className() const
		{return "Validation";}

protected:
	Model &initFunction()
		{    validation_result= 0;
                      return *this;}

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	const Port &Request_Validation ;
	Port &Result ;
    int  validation_result;
    double randnumber;
	Time processingTime;
};	// class Validation


#endif    //__VALIDATION_H
