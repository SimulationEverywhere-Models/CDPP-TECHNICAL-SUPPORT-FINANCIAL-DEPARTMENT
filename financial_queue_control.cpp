/*******************************************************************
*
*  DESCRIPTION: Atomic Model Financial Q Control
*
*  AUTHOR: Yasser Jafer
*
*  EMAIL: mailto://yjafer@uottawa.ca
*
*  DATE: 20/10/2010
*
*******************************************************************/

/** include files **/
#include "financial_queue_control.h"      // class Controller
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "distri.h"        // class Distribution
#include "strutil.h"       // str2float( ... )

/** public functions **/

/*******************************************************************
* Function Name: Financial Q Control
* Description: 
********************************************************************/
Financial_Q_Control::Financial_Q_Control( const string & name )
: Atomic( name )
, Control_In( addInputPort( "Control_In" ) )
, Control_Out( addOutputPort("Control_Out"))

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
Model & Financial_Q_Control::initFunction()
{
		
	holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model & Financial_Q_Control::externalFunction( const ExternalMessage & msg )
{
	if (msg.port() == Control_In && this->state() == passive )
	{
		holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
	}
	
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model & Financial_Q_Control::internalFunction( const InternalMessage & )
{	
	if ( this->state() == active) 
	{
		this->passivate();
	}

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model & Financial_Q_Control::outputFunction( const InternalMessage &msg )
{	
	if (this->state() == active)
	{
		sendOutput(msg.time(), Control_Out, 1);
	}
	 
	return *this ;
}
