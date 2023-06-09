[top]
components : financial_queue@Financial_Q
out : FQ_Out
in : Call_In
in : Release_Next
Link : Call_In Call_In@financial_queue
Link : Release_Next Release_Next@financial_queue
Link : FQ_Out@financial_queue FQ_Out

[financial_queue]
distribution : normal
mean : 4
deviation : 2