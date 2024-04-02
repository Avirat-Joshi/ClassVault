#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define max_students 5000
int number1 = 0;
int i1 = 0;
void check_existence();
void get_password();
void check_password();
void reset_password();
void print_data();
struct student_credentials_password_change
{
    char rollno[10];
    char old_password[7];
    char new_password[50];
};
struct student_credentials_password_change stud_cred_password_change;
struct student_credentials_password_change existing_stud_cred[max_students];
void get_existing_credential_data()
{
    FILE *file_1 = fopen("credentials.csv", "a");
    fclose(file_1);
    FILE *file_2 = fopen("credentials.csv", "r");
    if (file_2 == NULL)
    {
        perror("Error in opening the file\n");
        return;
    }
    while (fscanf(file_2, "%[^,],%[^,],\n", &existing_stud_cred[number1].rollno, &existing_stud_cred[number1].old_password) == 2)
    {
        number1++;
        if (number1 >= max_students)
        {
            break;
        }
    }
    fclose(file_2);
}
void check_existence()
{
    printf("Enter roll number: ");
    gets(stud_cred_password_change.rollno);
    for (i1 = 0; i1 < number1; i1++)
    {
        if (strcmp(existing_stud_cred[i1].rollno, stud_cred_password_change.rollno) == 0)
        {
            get_password();
            return;
        }
    }
    printf("The roll number does not exist in the credentials database ");

}
void get_password()
{
    printf("Enter old password ");
    gets(stud_cred_password_change.old_password);
    check_password();
}
void check_password()
{
    if (strcmp(existing_stud_cred[i1].old_password, stud_cred_password_change.old_password) == 0)
    {
        reset_password();
    }
    else
    {
        printf("The password doesnt match ");
        get_password();
    }
}
void reset_password()
{
    char new[50];
re_enter:
    printf("Enter new password ");
    gets(stud_cred_password_change.new_password);
    printf("Re-Enter password");
    gets(new);
    if (strcmp(new, stud_cred_password_change.new_password) == 0)
    {
        printf("Password reset successfully ");
        strcpy(existing_stud_cred[i1].old_password, new);
        print_data();
    }
    else
    {
        printf("Password does not match ");
        goto re_enter;
    }
}
void print_data()
{
    FILE *file2 = fopen("credentials.csv", "w");
    if (file2 == NULL)
    {
        perror("Error opening file for writing\n");
        return;
    }
    for (int i1 = 0; i1 < number1; i1++)
        fprintf(file2, "%s,%s,\n", existing_stud_cred[i1].rollno, existing_stud_cred[i1].old_password);
    fclose(file2);
}
void password_change_main()
{
    get_existing_credential_data();
    check_existence();
}