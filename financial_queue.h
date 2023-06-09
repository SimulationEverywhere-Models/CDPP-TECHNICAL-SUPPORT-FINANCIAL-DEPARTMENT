/*******************************************************************
*
*  DESCRIPTION: Atomic Model Financial Q
*
*  AUTHOR: Yasser Jafer
*
*  EMAIL: mailto://yjafe089@uottawa.ca
*
*  DATE: 20/10/2010
*
*******************************************************************/

#ifndef _FINANCIAL_Q_H
#define _FINANCIAL_Q_H


#include "atomic.h"     // class Atomic

/** forward declarations **/
class Distribution ;

class Financial_Q : public Atomic
{
public:
	Financial_Q( const string & name = "Financial_Q" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	typedef list<int> itemList;
	itemList	callList;
	
	const Port & Call_In;
	const Port & Release_Next;
	Port & FQ_Out;
	Distribution *dist ;
	
	Distribution &distribution()
	{return *dist;}
};	// class Financial Q

// ** inline ** // 
inline
string Financial_Q::className() const
{
	return "Financial_Q" ;
}

#endif   // _Financial_Q_H
