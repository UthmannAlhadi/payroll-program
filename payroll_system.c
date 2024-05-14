#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{ /* struct to keep employee details */
	char EmpName[50];
	int EmpID;
	int EmpAge;
	double gross_salary;
	double net_salary;
	double insurance;
	double tax;
	double tax_rate;
} account_s;

/* Function prototypes */
void EmployeeDetails(int count, account_s *record);
void SetInsurance(account_s *p1);
void SetTaxRate(account_s *p2);
void SetTax(int a, account_s *p3);
double SetTotalInsurance(int m, account_s *data);
double SetTotalTax(int t, account_s *data2);
double SetNetSalary(int k, account_s *account);
double Get_ave_salary(int c, account_s *account2);
double Get_ave_insurance(int d, account_s *account3);
double Get_ave_tax(int f, account_s *account4);
double Get_ave_net(int g, account_s *account5);

int main(void) /* Main function */
{
	int i, q, answer, EmpNum = 0; /* Variable declaration */
	float holder;
	double ave_insurance, ave_tax, ave_net_sal, ave_salary;

	FILE *file;
	file = fopen("UserDetails.txt", "ab"); /* Open an external file */

	for (q = 1; q < 16; q++)
	{ /* Title section */
		printf("-");
		printf("+");
	}

	printf("\n\nSIMPLE PAYROLL SYSTEM\n\n");

	for (q = 1; q < 16; q++)
	{ /* Title section */
		printf("-");
		printf("+");
	}

	printf("\nEnter System: \n\n 1. Yes   2. No\n\n");
	scanf("%f", &holder);
	answer = (int)holder; /* Typecast from float to int */

	switch (answer)
	{
	case 1:
		printf("\nWelcome!\n");
		break;
	case 2:
		printf("\nExiting The Program...\n");
		exit(0); // Used to exit the program
	}

	printf("\n\nNumber of Employee to process: "); /* Start of code */
	scanf("%d", &EmpNum);
	account_s *account = malloc(EmpNum * sizeof(account_s)); /* Dynamically allocate array of instances of account_s */
	memset(account, 0, EmpNum * sizeof(account_s));			 /* Initializes array */

	EmployeeDetails(EmpNum, account); /* Function call */
	SetTax(EmpNum, account);
	SetNetSalary(EmpNum, account);

	ave_salary = Get_ave_salary(EmpNum, account);
	ave_insurance = Get_ave_insurance(EmpNum, account);
	ave_tax = Get_ave_tax(EmpNum, account);
	ave_net_sal = Get_ave_net(EmpNum, account);

	printf("\n\nPayroll:\n");
	printf("%-15s %-8s %-5s %-17s %-17s %-18s %-17s\n", "Name", "ID", "Age", "insurance", "Tax", "GrossSalary", "NetSalary");

	for (i = 0; i < EmpNum; i++)
	{
		/* Print employee details */
		printf("%-15s %-8d %-5d ", account[i].EmpName, account[i].EmpID, account[i].EmpAge);
		printf("RM%-15.2f RM%-15.2f RM%-16.2f RM%-15.2f\n", account[i].insurance, account[i].tax, account[i].gross_salary, account[i].net_salary);
	}
	/* Print Average */
	printf("\n%-31s RM%-15.2f RM%-15.2f RM%-16.2f RM%-16.2f\n", "\nAverage", ave_insurance, ave_tax, ave_salary, ave_net_sal);

	/* Print output in external file */
	fprintf(file, "\n\nPayroll:\n");
	fprintf(file, "%-15s %-8s %-5s %-17s %-17s %-18s %-17s\n", "Name", "ID", "Age", "insurance", "Tax", "GrossSalary", "NetSalary");

	for (i = 0; i < EmpNum; i++)
	{
		/* Print employee details */
		fprintf(file, "%-15s %-8d %-5d ", account[i].EmpName, account[i].EmpID, account[i].EmpAge);
		fprintf(file, "RM%-15.2f RM%-15.2f RM%-16.2f RM%-15.2f\n", account[i].insurance, account[i].tax, account[i].gross_salary, account[i].net_salary);
	}

	/* Print Average */
	fprintf(file, "%-31s RM%-15.2f RM%-15.2f RM%-16.2f RM%-16.2f\n", "Average", ave_insurance, ave_tax, ave_salary, ave_net_sal);

	fclose(file);  /* Close external file */
	free(account); /* Free allocated memory */
	return 0;
}

void EmployeeDetails(int count, account_s *record)
{ /* Function to get employee details */

	int i;
	char ch;
	for (i = 0; i < count; i++)
	{ /* Read in information for each account */

		printf("\nEnter employee name: ");
		scanf("%s", record[i].EmpName);

		for (unsigned int j = 0; j < strlen(record[i].EmpName); j++)
		{ /* Set ch to employee name */
			ch = record[i].EmpName[j];
		}

		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		{ /* check special characters in employee name */

			if (strlen(record[i].EmpName) <= 50)
			{

				printf("\nEnter employee ID: ");
				scanf("%d", &record[i].EmpID);

				if (record[i].EmpID >= 1000 && record[i].EmpID <= 9999)
				{

					printf("\nEnter employee Age: ");
					scanf("%d", &record[i].EmpAge);

					if (record[i].EmpAge >= 18 && record[i].EmpAge <= 99)
					{

						printf("\nEnter employee Salary: ");
						scanf("%lf", &record[i].gross_salary);

						if (record[i].gross_salary >= 0.0 && record[i].gross_salary <= 9999.99)
						{

							SetInsurance(&record[i]);
							SetTaxRate(&record[i]); /* Function to set insurance & taxrate via function argument */
						}
						else
						{
							printf("Invalid Input!\nSalary must be positive number and contain in 4 digits\n");
							i--;
							continue;
						}
					}
					else
					{
						printf("\nInvalid Input!\nEmployee Age Is Between 18 To 99\n");
						i--;
						continue;
					}
				}
				else
				{
					printf("\nInvalid Input!\nEmployee ID Number is Between 1000 To 9999\n");
					i--;
					continue;
				}
			}
			else
			{
				printf("\nInvalid Input!\nMax Character is 50\n");
				i--;
				continue;
			}
		}
		else
		{
			printf("\nInvalid Input!\nSpecial Characters Not Allowed\n");
			i--;
			continue;
		}
	}
}

void SetInsurance(account_s *p1)
{ /* Function to set insurance on each employee */

	if (p1->EmpAge <= 35)
		p1->insurance = 110;
	else if (p1->EmpAge >= 36 && p1->EmpAge <= 65)
		p1->insurance = 160;
	else if (p1->EmpAge > 65)
		p1->insurance = 250;
	else
		printf("Under Age!");

	printf("\nInsurance: %.2f\n", p1->insurance);
}

void SetTaxRate(account_s *p2)
{ /* Function to set tax rate on each employee */

	if (p2->gross_salary <= 999.99)
		p2->tax_rate = 0.0;
	else if (p2->gross_salary >= 1000 && p2->gross_salary <= 2999.99)
		p2->tax_rate = 2.5;
	else if (p2->gross_salary > 3000)
		p2->tax_rate = 5.0;
	else
		printf("Invalid Input!");
	printf("Income Tax Rate: %.2f\n", p2->tax_rate);
}

void SetTax(int a, account_s *p3)
{ /* Function to set tax on each employee */

	int i = 0;
	do
	{
		if (p3[i].tax_rate == 0.0)
			p3[i].tax = 0.0; // Calculate tax based on tax rate
		else if (p3[i].tax_rate == 2.5)
			p3[i].tax = p3[i].gross_salary * (2.5 / 100);
		else if (p3[i].tax_rate == 5.0)
			p3[i].tax = p3[i].gross_salary * (5.0 / 100);
		i++;
	} while (i < a);
}

double SetTotalInsurance(int m, account_s *data)
{ /* Function to count total insurance */

	int i;
	double sum = 0.0;
	for (i = 0; i < m; i++)
	{
		sum += data[i].insurance;
	}

	return sum;
}

double SetTotalTax(int t, account_s *data2)
{ /* Function to count total tax */

	int i;
	double sum = 0.0;
	for (i = 0; i < t; i++)
	{
		sum += data2[i].tax;
	}

	return sum;
}

double SetNetSalary(int k, account_s *account)
{ /* Function to set net salary on each employee */

	int i = 0;
	double total;
	while (i < k)
	{
		account[i].net_salary = account[i].gross_salary - account[i].insurance - account[i].tax; /* Calculate net salary */
		i++;
	}
	return total;
}

double Get_ave_salary(int c, account_s *account2)
{ /* Function to get average salary */

	double sum = 0.0;
	int i;
	for (i = 0; i < c; i++)
	{
		sum += account2[i].gross_salary;
	}

	return sum / c;
}

double Get_ave_insurance(int d, account_s *account3)
{ /* Function to get average insurance */

	double sum = 0.0;
	int i;
	for (i = 0; i < d; i++)
	{
		sum += account3[i].insurance;
	}

	return sum / d;
}

double Get_ave_tax(int f, account_s *account4)
{ /* Function to get average tax */

	double sum = 0.0;
	int i;
	for (i = 0; i < f; i++)
	{
		sum += account4[i].tax;
	}

	return sum / f;
}

double Get_ave_net(int g, account_s *account5)
{ /* Function to get average net salary */

	double sum = 0.0;
	int i;
	for (i = 0; i < g; i++)
	{
		sum += account5[i].net_salary;
	}

	return sum / g;
}
