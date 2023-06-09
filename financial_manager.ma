[top]
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