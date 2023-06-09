[top]
components : financial_queue@Financial_Q
components : financial_queue_control@Financial_Q_Control
components : financial_manager
out	: Done
out : Problem
in	: Call_In
Link : Call_In Call_In@financial_queue
Link : FQ_Out@financial_queue Call_In@financial_manager
Link : Problem@financial_manager Problem
Link : Plan_Ok@financial_manager Done
Link : Problem@financial_manager Control_In@financial_queue_control
Link : Plan_Ok@financial_manager Control_In@financial_queue_control
Link : Control_Out@financial_queue_control Release_Next@financial_queue


[financial_queue_control]
distribution : normal
mean : 4
deviation : 2 

[financial_queue]
distribution : normal
mean : 4
deviation : 2 

[financial_manager]
components : coverage_plan_manager@Coverage_Plan_Manager validation@Validation
out : Plan_Ok 
out : Problem
in  : Call_In
Link : Call_In Call_In@coverage_plan_manager
Link : Plan_Ok@coverage_plan_manager Plan_Ok
Link : Problem@coverage_plan_manager Problem
Link : Request_Validation@coverage_plan_manager Request_Validation@validation
Link : Result@validation Validation_Result@coverage_plan_manager



[coverage_plan_manager]
distribution : normal
mean : 4
deviation : 2

[validation]
processing_time : 00:03:00:000
