/******************************************************************
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "financial_queue.h"        // class Financial_Q
#include "financial_queue_control.h"        // class Financial_Q_Control
#include "Coverage_Plan_Manager.h"   // class Coverage Plan Manager
#include "validation.h"         // class Validation

void MainSimulator::registerNewAtomics()
{
 	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Financial_Q>(), "Financial_Q" ) ;   
 	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Financial_Q_Control>(), "Financial_Q_Control" ) ;  
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Coverage_Plan_Manager>(), "Coverage_Plan_Manager" ) ;   
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Validation>(), "Validation" ) ;   
}