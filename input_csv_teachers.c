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
    char name[20];
    char employeeID[10];
    char gender[10];
    int age;
    char state[25];
    char email[30];
    long long int mobileno;
};

struct teachers teacher[max_teachers];
int numteachers = 0;

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
void addteacher()
{
    if (numteachers < max_teachers)
    {
        printf("Enter your name: ");
        getchar();
        gets(teacher[numteachers].name);
        strupr(teacher[numteachers].name);

        printf("Enter your Employee ID : ");
    here0:
        scanf("%s", teacher[numteachers].employeeID);
        getchar();
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
        scanf("%c", &gender);
        getchar();
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
        scanf("%d", &teacher[numteachers].age);

        printf("Enter your state: ");
        scanf("%s", teacher[numteachers].state);
        strupr(teacher[numteachers].state);
        getchar();

        printf("Enter your E-mail ID : ");
        scanf("%s", teacher[numteachers].email);
        getchar();

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
void removeteacher()
{
    viewteacher();
    if (numteachers == 0)
    {
        return;
    }
x:
    printf("Enter the S.no of the teacher to be removed\n");
    FILE *file = fopen(FILENAMETEACHERS, "w");
    int remove;
    scanf("%d", &remove);
    if(remove<1 || remove>=numteachers){
        printf("Invalid Input, Please retry\n");
        goto x;
    }
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
void searchbyteachername(char str[])
{
    int n = strlen(str);
    int check =0;
    for (int i = 0; i < numteachers; i++)
    {
        if (strncmp(str, teacher[i].name,n) == 0)
        {
            printf("%-20s%-10s%-10s%-10d%-20s%-28s%-10lld\n", teacher[i].name, teacher[i].employeeID, teacher[i].gender, teacher[i].age, teacher[i].state, teacher[i].email, teacher[i].mobileno);
            check++;
        }
    }
    if(check ==0)
    {
        printf("Teacher was not found.\n");
    }
}
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
void teachers_main()
{
    loadteacherdatafromfile();
    printf("Welcome to Classvault\n");
    int choice, choice2;

    do
    {
        printf("\nTeacher-list Menu\n");
        printf("0. Exit\n");
        printf("1. Add Teacher\n");
        printf("2. View Teachers\n");
        printf("3. Remove Teacher\n");
        printf("4. Search Teacher\n");
        printf("5. Group Teachers\n");
        printf("6. Show Feedback\n");
        printf("Enter your choice(pls enter the number): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            printf("Exiting Classvault. Goodbye!\n");
            break;
        case 1:
            addteacher();
            break;
        case 2:
            viewteacher();
            break;
        case 3:
            removeteacher();
            break;
        case 4:
        {
            do
            {
                printf("\nTeacher-search Menu\n");
                printf("0. Exit\n");
                printf("1. Search by name.\n");
                printf("2. Search by mobile number.\n");
                printf("Enter your choice(pls enter the number): ");
                scanf("%d", &choice2);
                getchar();

                switch (choice2)
                {
                case 0:
                    printf("Exiting Teacher-search.\n");
                    sleep(1);
                    break;
                case 1:
                {
                    char teacher_name[50];
                    printf("Enter the name : ");
                    scanf("%s", &teacher_name);
                    strupr(teacher_name);
                    searchbyteachername(teacher_name);
                    break;
                }
                case 2:
                {
                    long long int mob_num;
                    printf("Enter your mobile no.: ");
                    while (1)
                    {
                        scanf("%lld", &mob_num);
                        long long int temp = mob_num;
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
                    searchbyteachermobno(mob_num);
                    break;
                }
                }
            } while (choice2 != 0);
            break;
        }
        case 5:
        {
            do
            {
                printf("\nStudent-Group Menu\n");
                printf("0. Exit\n");
                printf("1. Group by gender.\n");
                printf("Enter your choice(pls enter the number): ");
                scanf("%d", &choice2);
                getchar();

                switch (choice2)
                {
                case 0:
                    printf("Exiting student-group\n");
                    sleep(1);
                    break;
                case 1:
                {
                    char gender;
                    char teacher_gender[10];
                    printf("Enter your gender.\n");
                there:
                    printf("M for male and F for female.\n");
                    scanf("%c", &gender);
                    getchar();
                    if (gender == 'M' || gender == 'm')
                    {
                        strcpy(teacher_gender, "MALE");
                    }
                    else if (gender == 'F' || gender == 'f')
                    {
                        strcpy(teacher_gender, "FEMALE");
                    }
                    else
                    {
                        printf("Enter correct gender : ");
                        goto there;
                    }
                    groupbyteachergender(teacher_gender);
                    break;
                }
                }
            } while (choice2 != 0);
            break;
        }
        case 6:
            showfeedback();
            break;
        default:
            printf("Invalid choice. Exiting application.\n");
            return;
        }
        sleep(1);
    } while (choice != 0);

    return;
}
