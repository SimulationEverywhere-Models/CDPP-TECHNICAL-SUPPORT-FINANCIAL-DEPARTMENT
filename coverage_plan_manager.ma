[top]
components : coverage_plan_manager@Coverage_Plan_Manager
out : Plan_Ok
out : Request_Validation
out : Problem
in : Call_In
in : Validation_Result
Link : Call_In Call_In@coverage_plan_manager
Link : Validation_Result Validation_Result@coverage_plan_manager
Link : Plan_Ok@coverage_plan_manager Plan_Ok
Link : Problem@coverage_plan_manager Problem
Link : Request_Validation@coverage_plan_manager Request_Validation

[coverage_plan_manager]
distribution : normal
mean : 4
deviation : 2 
