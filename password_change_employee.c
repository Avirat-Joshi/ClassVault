#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int number2 = 0;
int i2 = 0;
void check_existence_emp();
void get_password_emp();
void check_password_emp();
void reset_password_emp();
void print_data_emp();
struct employee_credentials_password_change
{
    char employeeID[10];
    char old_password[7];
    char new_password[50];
};
struct employee_credentials_password_change emp_cred_password_change;
struct employee_credentials_password_change existing_emp_cred[100];
void get_existing_employee_credential_data()
{
    FILE *file_1_e = fopen("credentials_employee.csv", "a");
    fclose(file_1_e);
    FILE *file_2_e = fopen("credentials_employee.csv", "r");
    if (file_2_e == NULL)
    {
        perror("Error in opening the file\n");
        return;
    }
    while (fscanf(file_2_e, "%[^,],%[^,],\n", &existing_emp_cred[number2].employeeID, &existing_emp_cred[number2].old_password) == 2)
    {
        number2++;
        if (number2 >= 100)
        {
            break;
        }
    }
    fclose(file_2_e);
}
void check_existence_emp()
{
    printf("Enter Employee ID: ");
    fflush(stdin);
    gets(emp_cred_password_change.employeeID);
    for (i2 = 0; i2 < number2; i2++)
    {
        if (strcmp(existing_emp_cred[i2].employeeID, emp_cred_password_change.employeeID) == 0)
        {
            get_password_emp();
            return;
        }
    }
    printf("The roll number does not exist in the credentials database ");
}
void get_password_emp()
{
    printf("Enter old password: ");
    fflush(stdin);
    gets(emp_cred_password_change.old_password);
    check_password_emp();
}
void check_password_emp()
{
    if (strcmp(existing_emp_cred[i2].old_password, emp_cred_password_change.old_password) == 0)
    {
        reset_password_emp();
    }
    else
    {
        printf("The password doesnt match ");
        get_password_emp();
    }
}
void reset_password_emp()
{
    char new_emp[50];
re_enter_emp:
    printf("Enter new password: ");
    gets(emp_cred_password_change.new_password);
    printf("Re-Enter password: ");
    gets(new_emp);
    if (strcmp(new_emp, emp_cred_password_change.new_password) == 0)
    {
        printf("Password reset successfully ");
        strcpy(existing_emp_cred[i2].old_password, new_emp);
        print_data_emp();
    }
    else
    {
        printf("Password does not match ");
        goto re_enter_emp;
    }
}
void print_data_emp()
{
    FILE *file2 = fopen("credentials_employee.csv", "w");
    if (file2 == NULL)
    {
        perror("Error opening file for writing\n");
        return;
    }
    for (int i2 = 0; i2 < number2; i2++)
        fprintf(file2, "%s,%s,\n", existing_emp_cred[i2].employeeID, existing_emp_cred[i2].old_password);
    fclose(file2);
}
void password_change_employee_main()
{
    get_existing_employee_credential_data();
    check_existence_emp();
}
