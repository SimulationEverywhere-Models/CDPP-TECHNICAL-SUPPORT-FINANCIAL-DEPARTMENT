/*******************************************************************
*
*  DESCRIPTION: Atomic Coverage Plan Manager
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
#include "Coverage_Plan_Manager.h"  // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Coverage_Plan_Manager
* Description: constructor
********************************************************************/
Coverage_Plan_Manager::Coverage_Plan_Manager( const string &name )
: Atomic( name )
, Call_In( addInputPort( "Call_In" ) )
, Validation_Result( addInputPort( "Validation_Result" ) )
, Plan_Ok( addOutputPort( "Plan_Ok" ) )
, Problem( addOutputPort( "Problem" ) )
, Request_Validation( addOutputPort( "Request_Validation" ) )
{
	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

		MASSERT( dist );

		for ( register int i = 0 ; i < dist->varCount() ; i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
			dist->setVar( i, str2float( parameter ) ) ;
		}
	} catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch( MException &e )
	{
		MTHROW( e ) ;
	}
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Coverage_Plan_Manager::externalFunction( const ExternalMessage &msg )
{
  if ( this->state() == passive)
   {
	holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
   // call_in = msg.value();
    // According to CD++ manual, random() fn should return a number
    // between 0 and 1. But this doesn't happen and it returns a number
    // of 10 digits.
    //randnumber = random()/1e+10;
		if(msg.port() == Call_In){
			call_in = msg.value();
			call_in_port = 1;
			validation_result_port = 0;
   			randnumber = (double)rand()/(double)RAND_MAX;
   		 	if ( randnumber <= 0.4){
    	  		 Plan_Valid = 1;
   		 	}else {
     	 		  Need_Validation = 1;
   		 	}
		} else {
			if(msg.port() == Validation_Result){
			result = msg.value();
			call_in_port = 0;
			validation_result_port = 1;
			if (result == 1)
				CC_Valid = 1;
			else
				CC_Valid = 0;
			}
		}
	return *this ;
}
}
/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Coverage_Plan_Manager::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}
/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Coverage_Plan_Manager::outputFunction( const InternalMessage &msg )
{
	
      if (call_in_port == 1){
      	if ( Plan_Valid == 1 ){
         	sendOutput( msg.time(), Plan_Ok,call_in);
      		} else
     	 if (Need_Validation == 1){
        	 sendOutput( msg.time(), Request_Validation, call_in);
     		 }
      }
      if (validation_result_port == 1){
    	  if (CC_Valid == 1){
      		 sendOutput( msg.time(), Plan_Ok, call_in );
     	 } else
     	 if (CC_Valid == 0){
      	  sendOutput( msg.time(), Problem, call_in );
     	 }
      }	
	return *this;
}

Coverage_Plan_Manager::~Coverage_Plan_Manager()
{
	delete dist;
}
