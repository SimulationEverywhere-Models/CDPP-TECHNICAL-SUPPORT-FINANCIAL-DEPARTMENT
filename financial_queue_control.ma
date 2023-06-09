[top]
components : financial_queue_control@Financial_Q_Control
out : Control_Out
in : Control_In
Link : Control_In Control_In@financial_queue_control
Link : Control_Out@financial_queue_control Control_Out


[financial_queue_control]
distribution : normal
mean : 4
deviation : 2 