#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define max_teachers 100
#define max_students 5000
#define max_feedbacks (max_students * max_teachers)
#define FILENAMETEACHERS "teachers.csv"
struct teachers
{
    char name[50];
    char employeeID[10];
    char gender[10];
    int age;
    char state[25];
    char email[30];
    long long int mobileno;
};

struct teachers teacher[max_teachers];
int numteachers = 0;

// made teacher array to store data of teacher and numteachers is a variable to keep track of teacher array

void saveTeacherToFile(struct teachers *teacher);
void loadteacherdatafromfile();
void addteacher();
void viewteacher();
void removeteacher();
void searchbyteachername(char str[]);
void searchbyteachermobno(long long int number);
void groupbyteachergender(char str[]);
void showfeedback();
void teachers_main();

// saving teacher to a CSV file
void saveTeacherToFile(struct teachers *teacher)
{
    FILE *file = fopen(FILENAMETEACHERS, "a");
    if (file == NULL)
    {
        perror("Error: ");
        return;
    }
    fprintf(file, "%s,%s,%s,%d,%s,%s,%lld\n", teacher->name, teacher->employeeID, teacher->gender, teacher->age, teacher->state, teacher->email, teacher->mobileno);
    fclose(file);
}

// scaning and loading data in teacher array from CSV file

void loadteacherdatafromfile()
{
    FILE *file1 = fopen(FILENAMETEACHERS, "a");
    fclose(file1);
    FILE *file = fopen(FILENAMETEACHERS, "r");
    if (file == NULL)
    {
        perror("Error");
        return;
    }
    while (fscanf(file, "%[^,],%[^,],%[^,],%d,%[^,],%[^,],%lld\n", &teacher[numteachers].name, &teacher[numteachers].employeeID, &teacher[numteachers].gender, &teacher[numteachers].age, &teacher[numteachers].state, &teacher[numteachers].email, &teacher[numteachers].mobileno) == 7)
    {
        numteachers++;
        if (numteachers >= max_teachers)
        {
            break;
        }
    }
    fclose(file);
}

// adding teacher details in array
void addteacher()
{
    if (numteachers < max_teachers)
    {
        printf("Enter name: ");
        fflush(stdin);
        gets(teacher[numteachers].name);
        strupr(teacher[numteachers].name);

        printf("Enter your Employee ID : ");
    here0:
        fflush(stdin);
        scanf("%s", teacher[numteachers].employeeID);
        int index = 0;
        for (int i = 0; i < numteachers; i++)
        {
            if (strcmp(teacher[numteachers].employeeID, teacher[i].employeeID) == 0)
            {
                index = 1;
            }
        }
        if (index)
        {
            printf("Enter the correct Employee ID :");
            goto here0;
        }
        strupr(teacher[numteachers].employeeID);

        char gender;
        printf("Enter your gender.\n");
    here:
        printf("M for male and F for female.\n");
        fflush(stdin);
        scanf("%c", &gender);
        if (gender == 'M' || gender == 'm')
        {
            strcpy((teacher[numteachers].gender), "MALE");
        }
        else if (gender == 'F' || gender == 'f')
        {
            strcpy((teacher[numteachers].gender), "FEMALE");
        }
        else
        {
            printf("Enter correct gender : ");
            goto here;
        }
        printf("Enter your age: ");
        fflush(stdin);
        scanf("%d", &teacher[numteachers].age);

        printf("Enter your state: ");
        fflush(stdin);
        gets(teacher[numteachers].state);
        strupr(teacher[numteachers].state);

        printf("Enter your E-mail ID : ");
        fflush(stdin);
        scanf("%s", teacher[numteachers].email);

        printf("Enter your mobile no.: ");
        while (1)
        {
            scanf("%lld", &teacher[numteachers].mobileno);
            long long int temp = teacher[numteachers].mobileno;
            int count = 0;
            while (temp)
            {
                temp /= 10;
                count++;
            }
            if (count == 10)
            {
                break;
            }
            else
                printf("Enter a valid phone number\n");
        }

        saveTeacherToFile(&teacher[numteachers]);
        printf("Teacher details added successfully!\n");
        numteachers++;
    }
    else
        printf("Teachers-list is Full.Cannot add more teachers.\n");
}

// showing teacher's data
void viewteacher()
{
    if (numteachers > 0)
    {
        printf("\nTeacherslist\n");
        printf("\n");
        printf("%-7s%-20s%-10s%-10s%-10s%-20s%-28s%-10s\n", "Sr no.", "name", "Employee ID", "gender", "Age", "state", "E-Mail ID", "Mobile no");
        printf("\n");
        for (int i = 0; i < numteachers; i++)
        {
            printf("%-5d: %-20s%-10s%-10s%-10d%-20s%-28s%-10lld\n", i + 1, teacher[i].name, teacher[i].employeeID, teacher[i].gender, teacher[i].age, teacher[i].state, teacher[i].email, teacher[i].mobileno);
        }
    }
    else
        printf("No Teachers to display\n");
}

//remove teacher from database
void removeteacher()
{
    FILE *file = fopen(FILENAMETEACHERS, "w");
    viewteacher();
    if (numteachers == 0)
    {
        return;
    }
    int remove;
    printf("Enter the S.no of the teacher to be removed\n");
    scanf("%d", &remove);
    for (int i = remove - 1; i < numteachers - 1; i++)
    {
        teacher[i] = teacher[i + 1];
    }
    printf("Teacher removed\n");
    numteachers--;
    for (int i = 0; i < numteachers; i++)
    {
        saveTeacherToFile(&teacher[i]);
    }
    fclose(file);
}

//search teacher by name
void searchbyteachername(char str[])
{
    int n = strlen(str);
    int check = 0;
    for (int i = 0; i < numteachers; i++)
    {
        if (strncmp(str, teacher[i].name, n) == 0)
        {
            printf("%-20s%-10s%-10s%-10d%-20s%-28s%-10lld\n", teacher[i].name, teacher[i].employeeID, teacher[i].gender, teacher[i].age, teacher[i].state, teacher[i].email, teacher[i].mobileno);
            check++;
        }
    }
    if (check == 0)
    {
        printf("Teacher was not found.\n");
    }
}

//search teacher by mobile number
void searchbyteachermobno(long long int number)
{
    int index = -1;
    for (int i = 0; i < numteachers; i++)
    {
        if (number == teacher[i].mobileno)
        {
            index = i;
        }
    }
    if (index != -1)
    {
        printf("Teacher Found.\n");
        printf("%-20s%-10s%-10s%-10d%-20s%-28s%-10lld\n", teacher[index].name, teacher[index].employeeID, teacher[index].gender, teacher[index].age, teacher[index].state, teacher[index].email, teacher[index].mobileno);
    }
    else
    {
        printf("Teacher was not found.\n");
    }
}

//group teachers by gender
void groupbyteachergender(char str[])
{
    int indices[numteachers];
    int index = 0;
    for (int i = 0; i < numteachers; i++)
    {
        if (strcmp(str, teacher[i].gender) == 0)
        {
            indices[index] = i;
            index++;
        }
    }
    for (int i = 0; i < index; i++)
    {
        printf("%-20s%-10s%-10s%-10d%-20s%-28s%-10lld\n", teacher[indices[i]].name, teacher[indices[i]].employeeID, teacher[indices[i]].gender, teacher[indices[i]].age, teacher[indices[i]].state, teacher[indices[i]].email, teacher[indices[i]].mobileno);
    }
}
