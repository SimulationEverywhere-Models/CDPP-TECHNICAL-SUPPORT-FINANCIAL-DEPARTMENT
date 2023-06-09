/*******************************************************************
*
*  DESCRIPTION: Atomic Validation
*
*  AUTHOR: Yasser Jafer
*
*  EMAIL: mailto://yjafe089@uottawa.ca
*
*
*  DATE: 20/10/2010
*
*******************************************************************/

/** include files **/
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "randlib.h"         // Random numbers library
#include "validation.h"    // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Validation
* Description: constructor
********************************************************************/
Validation::Validation( const string &name )
: Atomic( name )
, Request_Validation( addInputPort( "Request_Validation" ) )
, Result( addOutputPort( "Result" ) )
, processingTime( 0, 3, 0, 0 )
{	
	string time( MainSimulator::Instance().getParameter( description(), "processing_time" ) ) ;

	if( time != "" )
		processingTime = time ;
}


/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Validation::externalFunction( const ExternalMessage &msg )
{
  if ( this->state() == passive)
   {
	holdIn(active,processingTime);
    //call_in = msg.value();
    // According to CD++ manual, random() fn should return a number
    // between 0 and 1. But this doesn't happen and it returns a number
    // of 10 digits.
    //randnumber = random()/1e+10;

    randnumber = (double)rand()/(double)RAND_MAX;
    if ( randnumber <= 0.50)
        validation_result = 1;
    else
        validation_result = 0;
   
	return *this ;
}
}
/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Validation::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}
/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Validation::outputFunction( const InternalMessage &msg )
{
    
         sendOutput( msg.time(), Result, validation_result );
    
	return *this;
}

