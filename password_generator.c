#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define max_students 5000
#define max_employees 5000
#define FILENAME "students.csv"
struct students_password_generator
{
    char name[50];
    char rollno[10];
    char gender[10];
    char dateofBirth[11];
    char bloodgroup[4];
    char category[10];
    char branch[20];
    char state[25];
    char address[60];
    char email[30];
    int annualincome;
    long long int mobileno;
    int totalfee;
    int tutionfee;
    float cgpa;
};
struct existing_students
{
    char rollno[10];
    char password[7];
};
struct student_credentials
{
    char rollno[10];
    char password[7];
};
struct employees
{
    char name[20];
    char employeeID[10];
    char gender[10];
    int age;
    char state[25];
    char email[30];
    long long int mobileno;
};
struct existing_employees
{
    char employeeID[20];
    char password[7];
};
struct employee_credentials
{
    char employeeID[20];
    char password[7];
};
struct student_credentials stud_cred[max_students];
struct students_password_generator student1[max_students];
struct existing_students exist[max_students];
struct employee_credentials emp_cred[max_employees];
struct employees teacher_password_generator[max_employees];
struct existing_employees existing[max_employees];
int numstudents_password_generator = 0;
int number_student = 0;
int numteachers1 = 0;
int number_employee = 0;
const int password_length = 6;
char password1[7];
/*generates a random string of various characters defined in charset[].
Uses the rand() function to generates a pseudo random number and srand() function to seed the random number generator and set its initial state*/
char *random_generate()
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@";

    int length = 6;
    const int charset_length = sizeof(charset) - 1;

    for (int i = 0; i < length; ++i)
    {
        password1[i] = charset[rand() % charset_length];
    }
    return password1;
}
//generates a password for every student
void password_generator_student()
{
    for (int i = 0; i < numstudents_password_generator; i++)
    {
        char *temp_passs = (random_generate());
        strcpy(stud_cred[i].password, temp_passs);
        strcpy(stud_cred[i].rollno, student1[i].rollno);
    }
}

//generates a password for every employee
void password_generator_employee()
{
    for (int i = 0; i < numteachers1; i++)
    {
        char *temp_passt = (random_generate());
        strcpy(emp_cred[i].password, temp_passt);
        strcpy(emp_cred[i].employeeID, teacher_password_generator[i].employeeID);
    }
}
//checks if student credentials exist
//if already existing then they are not updated
int check_student(char *to_be_checkeds)
{
    for (int i = 0; i < number_student; i++)
    {
        if (strcmp(to_be_checkeds, exist[i].rollno) == 0)
            return 0;
    }
    return 1;
}
//checks if employee credentials exist
//if already existing then they are not updated
int check_employee(char *to_be_checkedt)
{
    for (int i = 0; i < number_employee; i++)
    {
        if (strcmp(to_be_checkedt, existing[i].employeeID) == 0)
        {
            return 0;
        }
    }
    return 1;
}
//gets existing credentials data from credentials_student.csv
void get_credentials_student()
{
    FILE *file_s1 = fopen("credentials_student.csv", "a");
    fclose(file_s1);
    FILE *file_s2 = fopen("credentials_student.csv", "r");
    if (file_s2 == NULL)
    {
        perror("Error in opening the file\n");
        return;
    }
    while (fscanf(file_s2, "%[^,],%[^,],\n", &exist[number_student].rollno, &exist[number_student].password) == 2)
    {
        number_student++;
        if (number_student >= max_students)
        {
            break;
        }
    }
    fclose(file_s2);
}
//gets existing credentials data from credentials_employee.csv
void get_credentials_employee()
{
    FILE *file_e1 = fopen("credentials_employee.csv", "a");
    fclose(file_e1);
    FILE *file_e2 = fopen("credentials_employee.csv", "r");
    if (file_e2 == NULL)
    {
        perror("Error in opening the file\n");
        return;
    }
    while (fscanf(file_e2, "%[^,],%[^,],\n", &existing[number_employee].employeeID, &exist[number_employee].password) == 2)
    {
        number_employee++;
        if (number_employee >= max_employees)
        {
            break;
        }
    }
    fclose(file_e2);
}
//fetches existing credential data from students.csv
void get_data_student()
{
    FILE *files1 = fopen("students.csv", "a");
    fclose(files1);
    FILE *files = fopen("students.csv", "r");
    if (files == NULL)
    {
        perror("Error in opening the file\n");
        return;
    }

    while (fscanf(files, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%lld,%f,%d,%d\n", &student1[numstudents_password_generator].name, &student1[numstudents_password_generator].rollno, &student1[numstudents_password_generator].gender, &student1[numstudents_password_generator].dateofBirth,&student1[numstudents_password_generator].bloodgroup,&student1[numstudents_password_generator].category, &student1[numstudents_password_generator].branch, &student1[numstudents_password_generator].state,&student1[numstudents_password_generator].address, &student1[numstudents_password_generator].email,&student1[numstudents_password_generator].annualincome, &student1[numstudents_password_generator].mobileno,&student1[numstudents_password_generator].cgpa,&student1[numstudents_password_generator].totalfee,&student1[numstudents_password_generator].tutionfee) == 15)
    {
        numstudents_password_generator++;
        if (numstudents_password_generator >= max_students)
        {
            break;
        }
    } 
}
//fetches existing credential data from teachers.csv
void get_data_employee()
{
    FILE *filet1 = fopen("teachers.csv", "a");
    fclose(filet1);
    FILE *filet = fopen("teachers.csv", "r");
    if (filet == NULL)
    {
        perror("Error in opening the file\n");
        return;
    }

    while (fscanf(filet, "%[^,],%[^,],%[^,],%d,%[^,],%[^,],%lld\n", &teacher_password_generator[numteachers1].name, &teacher_password_generator[numteachers1].employeeID, &teacher_password_generator[numteachers1].gender, &teacher_password_generator[numteachers1].age, &teacher_password_generator[numteachers1].state, &teacher_password_generator[numteachers1].email, &teacher_password_generator[numteachers1].mobileno) == 7)
    {
        numteachers1++;
        if (numteachers1 >= max_employees)
        {
            break;
        }
    }
    fclose(filet);
}
//prints student credentials data to credentials_student.csv
void print_data_student()
{
    FILE *files2 = fopen("credentials_student.csv", "a");
    if (files2 == NULL)
    {
        perror("Error opening file for writing\n");
        return;
    }
    for (int i = 0; i < numstudents_password_generator; i++)
        if (check_student(stud_cred[i].rollno))
            fprintf(files2, "%s,%s,\n", stud_cred[i].rollno, stud_cred[i].password);
    fclose(files2);
}
//prints employee credentials data to credentials_employee.csv
void print_data_employee()
{
    FILE *filet2 = fopen("credentials_employee.csv", "a");
    if (filet2 == NULL)
    {
        perror("Error opening file for writing\n");
        return;
    }
    for (int i = 0; i < numteachers1; i++)
        if (check_employee(emp_cred[i].employeeID))
            fprintf(filet2, "%s,%s,\n", emp_cred[i].employeeID, emp_cred[i].password);
    fclose(filet2);
}
//function to call from driver.c
void password_generator_main()
{
    get_credentials_student();
    get_data_student();
    srand((unsigned int)time(NULL)); //sets seed value for random number generator
    //time(NULL) returns the time in seconds elapsed since UNIX EPOCH i.e. January 1,1970
    password_generator_student();
    print_data_student();
    get_credentials_employee();
    get_data_employee();
    srand((unsigned int)time(NULL));
    //srand() functions are called in main to 
    password_generator_employee();
    print_data_employee();

}
