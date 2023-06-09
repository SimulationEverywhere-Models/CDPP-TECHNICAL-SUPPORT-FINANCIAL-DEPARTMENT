/*******************************************************************
*
*  DESCRIPTION: Atomic Model Financial Q Control
*
*  AUTHOR: Yasser Jafer
*
*  EMAIL: mailto://yjafe089@uottawa.ca
*
*  DATE: 20/10/2010
*
*******************************************************************/

#ifndef _FINANCIALQCONTROL_H
#define _FINANCIALQCONTROL_H

/** forward declarations **/
class Distribution ;

#include "atomic.h"     // class Atomic

class Financial_Q_Control : public Atomic
{
public:
	Financial_Q_Control( const string & name = "Financial_Q_Control" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	const Port &Control_In;
	const Port &Control_Out;
	Distribution *dist ;
	
	Distribution &distribution()
	{return *dist;}
	
};	// class Financial Q Control

// ** inline ** // 
inline
string Financial_Q_Control::className() const
{
	return "Financial_Q_Control" ;
}

#endif   // _FINANCIALQCONTROL_H
