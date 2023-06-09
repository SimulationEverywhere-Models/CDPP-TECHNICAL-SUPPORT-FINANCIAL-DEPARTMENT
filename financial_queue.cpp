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

/** include files **/
#include "financial_queue.h"      // class Financial Q
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "distri.h"        // class Distribution
#include "strutil.h"       // str2float( ... )

/** public functions **/

/*******************************************************************
* Function Name: Queue
* Description: 
********************************************************************/
Financial_Q::Financial_Q( const string & name )
: Atomic( name )
, Call_In( addInputPort( "Call_In" ) )
, Release_Next( addInputPort( "Release_Next" ) )
, FQ_Out( addOutputPort( "FQ_Out" ) )
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
* Function Name: initFunction
* Description: Initialize the model
********************************************************************/
Model & Financial_Q::initFunction()
{

	callList.erase(callList.begin(),callList.end());
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model & Financial_Q::externalFunction( const ExternalMessage & msg )
{
	if (msg.port() == Call_In && msg.value() != 0)
	{
		if (callList.empty() && this->state() == active)
			holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
		
			callList.push_back(msg.value());	
	}
	
	if (msg.port() == Release_Next && msg.value() ==1 && this->state() == passive) 
	{
		
		if ( callList.empty() )
			holdIn(active, Time::Inf);
		else
			holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
	}
	

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model & Financial_Q::internalFunction( const InternalMessage & )
{	
	if ( this->state() == active) 
	{
		callList.pop_front();
		this->passivate();
	}

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model & Financial_Q::outputFunction( const InternalMessage &msg )
{	
	if (!callList.empty())
	{
		sendOutput(msg.time(), FQ_Out, callList.front());
	}
	 
	return *this ;
}
