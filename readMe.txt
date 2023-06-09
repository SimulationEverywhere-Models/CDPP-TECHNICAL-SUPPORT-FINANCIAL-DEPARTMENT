The model includes the following couple models:

	Technical Support Financial Dept
and	Financial Manager

The atomic models are:
	Financial Q
	Financial Q Control
	Coverage Plan Manager
	Validation

This folder contains the files necessary to execute and test the Technical Support Financial Dept model.
The model consists of four atomic models and two coupled ones:

* Financial_Q (atomic)
* Financial_Q_Control (atomic)
* Coverage_Plan_Manager (atomic)
* Validation (atomic)
* Technical_Support_FD (coupled)
* Financial_Manager (coupled)

Here is a brief description of each of the files associated with the model:

- financial_queue.cpp, financial_queue.h     -> financial_queue model definition and implementation
- financial_queue.ev                         -> financial_queue events input file
- financial_queue.ma                         -> financial_queue coupled model definition used to test the financial_queue model separately
- financial_queue.bat                        -> financial_queue batch file used to execute the model
- financial_queue.log                        -> financial_queue simulation log file

- validation.cpp, validation.h         	 -> validation model definition and implementation
- validation.ev                  	  -> validation events input file
- validation.ma                  	  -> validation coupled model definition used to test the validation model separately
- validation.bat                	   -> validation batch file used to execute the model
- validation.log                	   -> validation simulation log file

- financial_queue_control.ev                   -> financial_queue_control events input file
- financial_queue_control.ma                   -> financial_queue_control coupled model definition used to test the financial_queue_controls model separately
- financial_queue_control.bat                  -> financial_queue_control batch file used to execute the model
- financial_queue_control.log                  -> financial_queue_control simulation log file

- coverage_plan_manager.ev                  -> coverage_plan_manager events input file
- coverage_plan_manager.ma                  -> coverage_plan_manager coupled model definition used to test the coverage_plan_manager model 
- coverage_plan_manager.bat                 -> coverage_plan_manager batch file used to execute the model
- coverage_plan_manager.log                 -> coverage_plan_manager simulation log file


- register.cpp		               -> used to register the atomic models with the CD++ simulator

		
				