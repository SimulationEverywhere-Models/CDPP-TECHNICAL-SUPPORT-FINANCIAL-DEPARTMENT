/*******************************************************************
*
*  DESCRIPTION: Atomic Model Coverage Plan Manager
*
*  AUTHOR: Yasser Jafer
*
*  EMAIL: yjafe089@uottawa.ca
*
*
*  DATE: 18/10/2002
*
*******************************************************************/
#ifndef __COVERAGEPLANMANAGER_H
#define __COVERAGEPLANMANAGER_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class Coverage_Plan_Manager: public Atomic
{
public:
	Coverage_Plan_Manager( const string &name = "Coverage_Plan_Manager" ) ;	 // Default constructor

	~Coverage_Plan_Manager();					// Destructor

	virtual string className() const
		{return "Coverage_Plan_Manager";}

protected:
	Model &initFunction()
		{    Plan_Valid = 0;
			 Need_Validation =0;
			 CC_Valid = 0;
			 call_in_port = 0;
			 validation_result_port = 0;
                      return *this;}

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	const Port &Call_In ;
	Port &Plan_Ok ;
    Port &Request_Validation;
    Port &Validation_Result;
    Port &Problem;
    int   Plan_Valid;
    int	  CC_Valid;
    int   Need_Validation;
    int	  call_in_port;
    int   validation_result_port;
	Distribution *dist ;
    double call_in;
    double result;
    double randnumber;

	Distribution &distribution()
			{return *dist;}
};	// class Coverage_Plan_Manager


#endif    //__COVERAGEPLANMANAGER_H
