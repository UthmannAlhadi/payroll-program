
START
	OPENFILE "UserDetails.txt", FOR APPEND 
	
	FOR q = 1, q < 16, q++  	
		DISPLAY "-"
		DISPLAY "+"
	END FOR
	
	DISPLAY "SIMPLE PAYROLL SYSTEM"
	
	FOR q = 1, q < 16, q++ 	
		DISPLAY "-"
		DISPLAY "+"
	END FOR
	
	
	DISPLAY "Enter System:  1. Yes   2. No", holder
	answer = (int)holder 
	
	SWITCH(answer)
		case 1:
			DISPLAY "Welcome!"
			break;
		case 2:
			DISPLAY "Exiting The Program..."
			exit(0)  
	END SWITCH
	

    DISPLAY "Number of Employee to process: " 
    READ EmpNum
    
    account_s account[EmpNum]    
    memset account, 0, sizeof account 
    
    EmployeeDetails(EmpNum, account)  
    SetTax(EmpNum, account)
    SetNetSalary(EmpNum, account)
    
	ave_salary = Get_ave_salery(EmpNum, account)
    ave_insurance = Get_ave_insurance(EmpNum, account)
    ave_tax = Get_ave_tax(EmpNum, account)
    ave_net_sal = Get_ave_net(EmpNum, account)
    
    DISPLAY "Payroll:"
	DISPLAY "Name", "ID", "Age", "insurance", "Tax", "GrossSalary", "NetSalary"
	
	FOR i = 0, i < EmpNum, i++
		DISPLAY account[i].EmpName, account[i].EmpID, account[i].EmpAge
		DISPLAY account[i].insurance, account[i].tax, account[i].gross_salary, account[i].net_salary
	END FOR
	
	DISPLAY "Average", ave_insurance, ave_tax, ave_salary, ave_net_sal
	
	WRITEFILE, "UserDetails.txt", "Payroll:"
	WRITEFILE, "UserDetails.txt", "Name", "ID", "Age", "insurance", "Tax", "GrossSalary", "NetSalary"
	
	FOR i = 0, i < EmpNum, i++
		DISPLAY account[i].EmpName, account[i].EmpID, account[i].EmpAge
		DISPLAY account[i].insurance, account[i].tax, account[i].gross_salary, account[i].net_salary
	END FOR
	
	WRITEFILE, "UserDetails.txt", "Average", ave_insurance, ave_tax, ave_salary, ave_net_sal
	
	CLOSEFILE "UserDetails.txt" 
END

FUNCTION EmployeeDetails(count, account_s record[count])
	
	
    EmployeeName
    FOR i = 0, i < count, i++			
        
		DISPLAY "Enter employee name: "
        READ record[i].EmpName
        
        FOR j = 0, j < strlen(record[i].EmpName, j++     
        	
        	ch = record[i].EmpName[j]
		
		IF  ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z'   

			EmployeeID
        	IF  strlen record[i].EmpName <= 50  
        	
        		DISPLAY "Enter employee ID: " 
        		READ record[i].EmpID
        	
				EmployeeAge
				IF  record[i].EmpID >= 1000 && record[i].EmpID <= 9999   
        		
					DISPLAY "Enter employee Age: " 
        			READ record[i].EmpAge
        	
					EmployeeSalary
					IF  record[i].EmpAge >= 18 && record[i].EmpAge <= 99
        			
						DISPLAY "Enter employee Salary: " 
        				READ record[i].gross_salary)
        			
						IF  record[i].gross_salary >= 0.0 && record[i].gross_salary <= 9999.99
        				
        					SetInsurance(&record[i])
							SetTaxRate(&record[i])  	 
						
						ELSE
							DISPLAY "Invalid Input! Salary must be positive number"
							GOTO EmployeeSalary
						END IF
						
					END IF
					DISPLAY "Invalid Input!\nEmployee Age Is Between 18 To 99"
					GOTO EmployeeAge
					
				END IF
				DISPLAY "Invalid Input!\nEmployee ID Number is Between 1000 To 9999"
				GOTO EmployeeID
				
			END IF
			DISPLAY "Invalid Input! Max Character is 50"
			GOTO EmployeeName
				
		END IF
		DISPLAY "Invalid Input! Special Characters Not Allowed "
		GOTO EmployeeName
		END FOR	
		
    END FOR
    
END FUNCTION

FUNCTION SetInsurance(account_s *record)    

    IF record->EmpAge <= 35
        record->insurance = 110
    ELSE IF record->EmpAge >= 36 && record->EmpAge <= 65
        record->insurance = 160
    ELSE IF record->EmpAge > 65
        record->insurance = 250
    ELSE
        DISPLAY "Under Age!"
    END IF
        
    DISPLAY "Insurance: ", record->insurance
    
END FUNCTION

FUNCTION SetTaxRate(account_s *track)     
	
	IF track->gross_salary <- 999.99
		track->tax_rate = 0.0
	ELSE IF track->gross_salary >= 1000 && track->gross_salary <= 2999.99
		track->tax_rate = 2.5
	ELSE IF track->gross_salary > 3000
		track->tax_rate = 5.0
	ELSE
		DISPLAY "Invalid Input!"
	END IF
	
	DISPLAY "Income Tax Rate: ", track->tax_rate
	
END FUNCTION

FUNCTION SetTax(a, account_s *track2)    
	
	do 
		IF track2[i].tax_rate == 0.0
			track2[i].tax = track2[i].gross_salary - 0.0   
		ELSE IF track2[i].tax_rate == 2.5
			track2[i].tax = track2[i].gross_salary * (2.5 / 100) 
		ELSE IF track2[i].tax_rate == 5.0
			track2[i].tax = track2[i].gross_salary * (5.0 / 100)
		END IF
	while i < a
	
END FUNCTION

FUNCTION SetTotalInsurance(m, account_s *data)     
	
	FOR i = 0, i < m, i++
		data[i].total_insurance =+ data[i].insurance
		sum = data[i].total_insurance
	END FOR
	
	RETURN sum
	
END FUNCTION

FUNCTION SetTotalTax(t, account_s *data2)     
	
	FOR i = 0, i < t, i++
		data2[i].total_tax =+ data2[i].tax
		sum = data2[i].total_tax
	END FOR
	
	RETURN sum
	
END FUNCTION

FUNCTION SetNetSalary(k, account_s *account2)    

	while i < k
		account2[i].net_salary = account2[i].gross_salary - account2[i].insurance - account2[i].tax     
		total = account2[i].net_salary
		i++
	END WHILE
	
	RETURN total
	
END FUNCTION

FUNCTION Get_ave_salery(c, account_s *account)   

    FOR i = 0, i < c, i++
        sum += account[i].gross_salary
    END FOR
        
    RETURN sum/c

END FUNCTION

FUNCTION Get_ave_insurance(d, account_s *account3)     

    FOR i = 0, i < d, i++
        sum += account3[i].insurance
    END FOR
        
    RETURN sum/d; 

END FUNCTION

FUNCTION Get_ave_tax(f, account_s *account4)     

    FOR i = 0, i < f, i++
        sum += account4[i].tax
    END FOR
        
    RETURN sum/f

END FUNCTION

FUNCTION Get_ave_net(g, account_s *account5)      

    FOR i = 0, i < g, i++
        sum += account5[i].net_salary
    END FOR
        
    RETURN sum/g

END FUNCTION


