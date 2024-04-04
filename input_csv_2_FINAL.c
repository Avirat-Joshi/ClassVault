#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "input_csv_teachers.c"
#include "marks_final.c"
#define FILENAME "students.csv"
#define FILENAMEFEEDBACK "feedback.csv"
struct students
{
    char name[50];
    char rollno[10];
    char gender[10];
    char dateofBirth[11];
    char bloodgroup[4];
    char category[10];
    char branch[3];
    char state[25];
    char address[60];
    char email[30];
    int annualincome;
    long long int mobileno;
    float cgpa;
    int totalfee;
    int tutionfee;
};
struct students student[max_students];
int numstudents = 0;
struct feedbacks
{
    char employeeid[10];
    char feedback[500];
};
struct feedbacks stud_feedback[max_feedbacks];
int numfeedbacks = 0;

void saveStudentToFile(struct students *student);
void saveAllstudents();
void loaddatafromfile();
void merge(int low, int mid, int high);
void sortstudent(int l, int r);
void addstudent();
void editstudent(char str[]);
void viewstudent_for_teacher();
void viewstudent_for_student(char str[]);
void removestudent();
void searchbyname(char str[]);
void searchbymobno(long long int number);
void searchbyrollno(char str[]);
void groupbybranch(char str[]);
void groupbystate(char str[]);
void groupbygender(char str[]);
void show_fees(char str[]);
void assignCGPA();
void Calculate_fees();
void savefeedbacktoFile(struct feedbacks *stud_feedback);
void loadfeedbackfromfile();
void givefeedback();
void showfeedback();

void saveStudentToFile(struct students *student)
{
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL)
    {
        perror("Error :");
        return;
    }
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%lld,%.2f,%d,%d\n", student->name, student->rollno, student->gender, student->dateofBirth, student->bloodgroup, student->category, student->branch, student->state, student->address, student->email, student->annualincome, student->mobileno, student->cgpa, student->totalfee, student->tutionfee);
    fclose(file);
}
void saveAllstudents()
{
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL)
    {
        perror("Error :");
        return;
    }

    for (int i = 0; i < numstudents; i++)
    {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%lld,%f,%d,%d\n", student[i].name, student[i].rollno, student[i].gender, student[i].dateofBirth, student[i].bloodgroup, student[i].category, student[i].branch, student[i].state, student[i].address, student[i].email, student[i].annualincome, student[i].mobileno, student[i].cgpa, student[i].totalfee, student[i].tutionfee);
    }
    fclose(file);
}
void loaddatafromfile()
{
    FILE *file1 = fopen(FILENAME, "a");
    fclose(file1);
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error :");
        return;
    }
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%lld,%f,%d,%d\n", &student[numstudents].name, &student[numstudents].rollno, &student[numstudents].gender, &student[numstudents].dateofBirth, &student[numstudents].bloodgroup, &student[numstudents].category, &student[numstudents].branch, &student[numstudents].state, &student[numstudents].address, &student[numstudents].email, &student[numstudents].annualincome, &student[numstudents].mobileno, &student[numstudents].cgpa, &student[numstudents].totalfee, &student[numstudents].tutionfee) == 15)
    {
        numstudents++;
        if (numstudents >= max_students)
        {
            break;
        }
    }
    fclose(file);
}
void merge(int low, int mid, int high)
{
    struct students student_temp[high + 1];
    int i, j, k;
    i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
    {
        if (strcmp(student[i].rollno, student[j].rollno) == -1)
        {
            student_temp[k] = student[i];
            i++;
            k++;
        }
        else
        {
            student_temp[k] = student[j];
            j++;
            k++;
        }
    }
    while (i <= mid)
    {
        student_temp[k] = student[i];
        i++;
        k++;
    }
    while (j <= high)
    {
        student_temp[k] = student[j];
        j++;
        k++;
    }
    for (int i = low; i <= high; i++)
    {
        student[i] = student_temp[i];
    }
}
void sortstudent(int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        sortstudent(l, mid);
        sortstudent(mid + 1, r);

        merge(l, mid, r);
    }
    saveAllstudents();
}
void addstudent()
{
    if (numstudents < max_students)
    {
        printf("Enter your name: ");
        gets(student[numstudents].name);
        strupr(student[numstudents].name);

        printf("Enter your roll number : ");
    here0:
        scanf("%s", student[numstudents].rollno);
        strupr(student[numstudents].rollno);
        fflush(stdin);
        int index = -1;
        for (int i = 0; i < numstudents; i++)
        {
            if (strcmp(student[numstudents].rollno, student[i].rollno) == 0)
            {
                index = 1;
            }
        }
        if (index != -1)
        {
            printf("Enter the correct roll no. :");
            goto here0;
        }

        char gender;
        printf("Enter your gender.\n");
    here:
        printf("M for male and F for female.\n");
        scanf("%c", &gender);
        fflush(stdin);
        if (gender == 'M' || gender == 'm')
        {
            strcpy((student[numstudents].gender), "MALE");
        }
        else if (gender == 'F' || gender == 'f')
        {
            strcpy((student[numstudents].gender), "FEMALE");
        }
        else
        {
            printf("Enter correct gender : ");
            goto here;
        }

        printf("Enter your date of birth(dd/mm/yyyy) : ");
        scanf("%s", student[numstudents].dateofBirth);
        fflush(stdin);

        int choice_bg;
        printf("Enter your blood group :\n");
        printf("1.A+\n2.A-\n3.B+\n4.B-\n5.O+\n6.O-\n7.AB+\n8.AB-\n");
    here2:
        scanf("%d", &choice_bg);
        switch (choice_bg)
        {
        case 1:
            strcpy(student[numstudents].bloodgroup, "A+");
            break;
        case 2:
            strcpy(student[numstudents].bloodgroup, "A-");
            break;
        case 3:
            strcpy(student[numstudents].bloodgroup, "B+");
            break;
        case 4:
            strcpy(student[numstudents].bloodgroup, "B-");
            break;
        case 5:
            strcpy(student[numstudents].bloodgroup, "O+");
            break;
        case 6:
            strcpy(student[numstudents].bloodgroup, "O-");
            break;
        case 7:
            strcpy(student[numstudents].bloodgroup, "AB+");
            break;
        case 8:
            strcpy(student[numstudents].bloodgroup, "AB-");
            break;
        default:
            printf("Enter correct number:\n");
            goto here2;
            break;
        }

        int choice_cat;
        printf("Enter your Category :\n");
        printf("1.General\n2.EWS\n3.OBC\n4.SC\n5.ST\n6.PWD\n");
    here3:
        scanf("%d", &choice_cat);
        switch (choice_cat)
        {
        case 1:
            strcpy(student[numstudents].category, "GENERAL");
            break;
        case 2:
            strcpy(student[numstudents].category, "EWS");
            break;
        case 3:
            strcpy(student[numstudents].category, "OBC");
            break;
        case 4:
            strcpy(student[numstudents].category, "SC");
            break;
        case 5:
            strcpy(student[numstudents].category, "ST");
            break;
        case 6:
            strcpy(student[numstudents].category, "PWD");
            break;
        default:
            printf("Enter correct number:\n");
            goto here3;
            break;
        }

        int choice_br;
        printf("Enter your branch:\n");
        printf("1.CE\n2.CS\n3.EE\n4.MM\n5.EC\n6.ME\n");
    here4:
        scanf("%d", &choice_br);
        switch (choice_br)
        {
        case 1:
            strcpy(student[numstudents].branch, "CE");
            break;
        case 2:
            strcpy(student[numstudents].branch, "CS");
            break;
        case 3:
            strcpy(student[numstudents].branch, "EE");
            break;
        case 4:
            strcpy(student[numstudents].branch, "MM");
            break;
        case 5:
            strcpy(student[numstudents].branch, "EC");
            break;
        case 6:
            strcpy(student[numstudents].branch, "ME");
            break;
        default:
            printf("Enter correct number:\n");
            goto here4;
            break;
        }

        printf("Enter your state: ");
        scanf("%s", student[numstudents].state);
        strupr(student[numstudents].state);
        fflush(stdin);

        printf("Enter your Address: ");
        scanf("%s", student[numstudents].address);
        strupr(student[numstudents].address);
        fflush(stdin);

        printf("Enter your E-mail ID : ");
        scanf("%s", student[numstudents].email);
        fflush(stdin);

        printf("Enter your Annual Income : ");
        scanf("%d", &student[numstudents].annualincome);
        fflush(stdin);

        printf("Enter your mobile no.: ");
        while (1)
        {
            scanf("%lld", &student[numstudents].mobileno);
            long long int temp = student[numstudents].mobileno;
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
        marks_main();
        for (int i = 0; i < numstudents; i++)
        {
            if (strcmp(student[numstudents].rollno, mark[i].rollno) == 0)
            {
                student[numstudents].cgpa = mark[i].cgpa;
            }
            else
                student[numstudents].cgpa = 0;
        }
        saveStudentToFile(&student[numstudents]);
        printf("Student details added successfully!\n");
        numstudents++;
    }
    else
        printf("Student-list is Full.Cannot add more students.\n");
}
void editstudent(char str[])
{
    int edit_index = -1;
    for (int i = 0; i < numstudents; i++)
    {
        if (strcmp(str, student[i].rollno) == 0)
        {
            edit_index = i;
        }
    }
    if (edit_index == -1)
    {
        printf("Student with given roll no. not found.\n");
        return;
    }

    int choice_edit;
    printf("\nStudent Edit menu\n");
    printf("0.Exit\n1.name\n2.Roll no.\n3.Gender\n4. Date of birth\n5.blood group\n6.category\n7.branch\n8.state\n9.address\n10.email\n11.annual income\n12.mobile no.\n");
herechoice:
    scanf("%d", &choice_edit);
    switch (choice_edit)
    {
    case 0:
    {
        printf("Exiting Student Edit\n");
        break;
    }
    case 1:
        printf("Enter your name: ");
        fflush(stdin);
        gets(student[edit_index].name);
        strupr(student[edit_index].name);
        break;

    case 2:
    {
        printf("Enter your roll number : ");
    here0:
        scanf("%s", student[edit_index].rollno);
        fflush(stdin);
        int index = 0;
        for (int i = 0; i < numstudents; i++)
        {
            if (strcmp(student[edit_index].rollno, student[i].rollno) == 0)
            {
                index = 1;
            }
        }
        if (index)
        {
            printf("Enter the correct roll no. :");
            goto here0;
        }
        strupr(student[edit_index].rollno);
        break;
    }
    case 3:
    {
        char gender;
        printf("Enter your gender.\n");
    here:
        printf("M for male and F for female.\n");
        scanf("%c", &gender);
        fflush(stdin);
        if (gender == 'M' || gender == 'm')
        {
            strcpy((student[edit_index].gender), "MALE");
        }
        else if (gender == 'F' || gender == 'f')
        {
            strcpy((student[edit_index].gender), "FEMALE");
        }
        else
        {
            printf("Enter correct gender : ");
            goto here;
        }
        break;
    }

    case 4:
    {
        printf("Enter your date of birth(dd/mm/yyyy) : ");
        scanf("%s", student[edit_index].dateofBirth);
        fflush(stdin);
        break;
    }
    case 5:
    {
        int choice_bg;
        printf("Enter your blood group :\n");
        printf("1.A+\n2.A-\n3.B+\n4.B-\n5.O+\n6.O-\n7.AB+\n8.AB-\n");
    here2:
        scanf("%d", &choice_bg);
        switch (choice_bg)
        {
        case 1:
            strcpy(student[edit_index].bloodgroup, "A+");
            break;
        case 2:
            strcpy(student[edit_index].bloodgroup, "A-");
            break;
        case 3:
            strcpy(student[edit_index].bloodgroup, "B+");
            break;
        case 4:
            strcpy(student[edit_index].bloodgroup, "B-");
            break;
        case 5:
            strcpy(student[edit_index].bloodgroup, "O+");
            break;
        case 6:
            strcpy(student[edit_index].bloodgroup, "O-");
            break;
        case 7:
            strcpy(student[edit_index].bloodgroup, "AB+");
            break;
        case 8:
            strcpy(student[edit_index].bloodgroup, "AB-");
            break;
        default:
            printf("Enter correct number:\n");
            goto here2;
            break;
        }
        break;
    }
    case 6:
    {
        int choice_cat;
        printf("Enter your Category :\n");
        printf("1.General\n2.EWS\n3.OBC\n4.SC\n5.ST\n6.PWD\n");
    here3:
        scanf("%d", &choice_cat);
        switch (choice_cat)
        {
        case 1:
            strcpy(student[edit_index].category, "GENERAL");
            break;
        case 2:
            strcpy(student[edit_index].category, "EWS");
            break;
        case 3:
            strcpy(student[edit_index].category, "OBC");
            break;
        case 4:
            strcpy(student[edit_index].category, "SC");
            break;
        case 5:
            strcpy(student[edit_index].category, "ST");
            break;
        case 6:
            strcpy(student[edit_index].category, "PWD");
            break;
        default:
            printf("Enter correct number:\n");
            goto here3;
            break;
        }
        break;
    }
    case 7:
    {
        int choice_br;
        printf("Enter your branch:\n");
        printf("1.CE\n2.CS\n3.EE\n4.MM\n5.EC\n6.ME\n");
    here4:
        scanf("%d", &choice_br);
        switch (choice_br)
        {
        case 1:
            strcpy(student[edit_index].branch, "CE");
            break;
        case 2:
            strcpy(student[edit_index].branch, "CS");
            break;
        case 3:
            strcpy(student[edit_index].branch, "EE");
            break;
        case 4:
            strcpy(student[edit_index].branch, "MM");
            break;
        case 5:
            strcpy(student[edit_index].branch, "EC");
            break;
        case 6:
            strcpy(student[edit_index].branch, "ME");
            break;
        default:
            printf("Enter correct number:\n");
            goto here4;
            break;
        }
        break;
    }
    case 8:
    {
        printf("Enter your state: ");
        scanf("%s", student[edit_index].state);
        strupr(student[edit_index].state);
        fflush(stdin);
        break;
    }
    case 9:
    {
        printf("Enter your Address: ");
        scanf("%s", student[edit_index].address);
        strupr(student[edit_index].address);
        fflush(stdin);
        break;
    }
    case 10:
    {
        printf("Enter your E-mail ID : ");
        scanf("%s", student[edit_index].email);
        fflush(stdin);
        break;
    }
    case 11:
    {
        printf("Enter your Annual Income : ");
        scanf("%d", &student[edit_index].annualincome);
        fflush(stdin);
        break;
    }
    case 12:
    {
        printf("Enter your mobile no.: ");
        while (1)
        {
            scanf("%lld", &student[edit_index].mobileno);
            long long int temp = student[edit_index].mobileno;
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
        break;
    }
    default:
    {
        printf("Enter correct number : \n");
        goto herechoice;
        break;
    }
    }
    printf("Student details updated successfully!\n");
    saveStudentToFile(&student[edit_index]);
}
void viewstudent_for_student(char str[])
{
    if (numstudents > 0)
    {
        int index = -1;
        for (int i = 0; i < numstudents; i++)
        {
            if (strcmp(str, student[i].rollno) == 0)
            {
                index = i;
            }
        }
        if (index != -1)
        {
            printf("%-30s%-15s%-15s%-35s%-15s%-10s\n", "name", "roll no.", "branch", "E-Mail ID", "Gender", "CGPA");
            printf("%-30s%-15s%-15s%-35s%-15s%-10.2f\n\n", student[index].name, student[index].rollno, student[index].branch, student[index].email, student[index].gender, student[index].cgpa);
            printf("Contact Details:\n");
            printf("Address:%s \n", student[index].address);
            printf("Phone No.:%lld\n", student[index].mobileno);
        }
        else
            printf("Student not found!");
    }
    else
        printf("No students to display\n");
}
void viewstudent_for_teacher()
{
    if (numstudents > 0)
    {
        printf("\nStudentslist\n");
        printf("\n");
        printf("%-7s%-30s%-15s%-15s%-35s%-15s%-10s\n", "Sr no.", "name", "roll no.", "branch", "E-Mail ID", "Gender", "CGPA");
        printf("\n");
        for (int i = 0; i < numstudents; i++)
        {
            printf("%-5d: %-30s%-15s%-15s%-35s%-15s%-10.2f\n", i + 1, student[i].name, student[i].rollno, student[i].branch, student[i].email, student[i].gender, student[i].cgpa);
        }
    }
    else
        printf("No students to display\n");
}
void removestudent()
{
    viewstudent_for_teacher();
    if (numstudents == 0)
    {
        return;
    }
    printf("Enter the S.no of the student to be removed\n");
    FILE *file = fopen(FILENAME, "w");
    int remove;
    scanf("%d", &remove);
    for (int i = remove - 1; i < numstudents - 1; i++)
    {
        student[i] = student[i + 1];
    }
    printf("Student removed\n");
    numstudents--;
    for (int i = 0; i < numstudents; i++)
    {
        saveStudentToFile(&student[i]);
    }
    fclose(file);
}
void searchbyname(char str[])
{
    int n = strlen(str);
    int check = 0;
    for (int i = 0; i < numstudents; i++)
    {
        if (strncmp(str, student[i].name, n) == 0)
        {
            printf("%-30s%-15s%-15s%-35s%-15s\n", student[i].name, student[i].rollno, student[i].branch, student[i].email, student[i].gender);
            check++;
        }
    }
    if (check == 0)
    {
        printf("Student was not found.\n");
    }
}
void searchbymobno(long long int number)
{
    int index = -1;
    for (int i = 0; i < numstudents; i++)
    {
        if (number == student[i].mobileno)
        {
            index = i;
        }
    }
    if (index != -1)
    {
        printf("Student Found.\n");
        printf("%-30s%-15s%-15s%-35s%-15s\n", student[index].name, student[index].rollno, student[index].branch, student[index].email, student[index].gender);
    }
    else
    {
        printf("Student was not found.\n");
    }
}
void searchbyrollno(char str[])
{
    int n = strlen(str);
    int check = 0;
    for (int i = 0; i < numstudents; i++)
    {
        if (strncmp(str, student[i].rollno, n) == 0)
        {
            printf("%-30s%-15s%-15s%-35s%-15s\n", student[i].name, student[i].rollno, student[i].branch, student[i].email, student[i].gender);
            check++;
        }
    }
    if (check == 0)
    {
        printf("Student was not found.\n");
    }
}
void groupbybranch(char str[])
{
    int indices[numstudents];
    int index = 0;
    for (int i = 0; i < numstudents; i++)
    {
        if (strcmp(str, student[i].branch) == 0)
        {
            indices[index] = i;
            index++;
        }
    }
    for (int i = 0; i < index; i++)
    {
        printf("%-30s%-15s%-15s%-35s%-15s\n", student[indices[i]].name, student[indices[i]].rollno, student[indices[i]].branch, student[indices[i]].email, student[indices[i]].gender);
    }
}
void groupbystate(char str[])
{
    int indices[numstudents];
    int index = 0;
    for (int i = 0; i < numstudents; i++)
    {
        if (strcmp(str, student[i].state) == 0)
        {
            indices[index] = i;
            index++;
        }
    }
    for (int i = 0; i < index; i++)
    {
        printf("%-30s%-15s%-15s%-35s%-15s\n", student[indices[i]].name, student[indices[i]].rollno, student[indices[i]].branch, student[indices[i]].email, student[indices[i]].gender);
    }
}
void groupbygender(char str[])
{
    int indices[numstudents];
    int index = 0;
    for (int i = 0; i < numstudents; i++)
    {
        if (strcmp(str, student[i].gender) == 0)
        {
            indices[index] = i;
            index++;
        }
    }
    for (int i = 0; i < index; i++)
    {
        printf("%-30s%-15s%-15s%-35s%-15s\n", student[indices[i]].name, student[indices[i]].rollno, student[indices[i]].branch, student[indices[i]].email, student[indices[i]].gender);
    }
}
void Calculate_fees()
{
    int messfee = 18000;
    int tutfee = 100000;
    int otherfee = 15000;

    for (int i = 0; i < numstudents; i++)
    {
        if (strcmp(student[i].category, "PWD") == 0 || strcmp(student[i].category, "SC") == 0 || strcmp(student[i].category, "ST") == 0 || (student[i].annualincome < 100000))
        {
            student[i].tutionfee = tutfee * 0;
        }
        else if (student[i].annualincome < 500000)
        {
            student[i].tutionfee = (tutfee * 1) / 3;
        }
        else
        {
            student[i].tutionfee = tutfee;
        }

        student[i].totalfee = messfee + otherfee + student[i].tutionfee;
    }
    saveAllstudents();
}
void show_fees(char str[])
{
    int messfee = 18000;
    int tutfee = 100000;
    int otherfee = 15000;
    printf("%-25s%-15s%-15s%-15s%-15s%-15s\n", "name", "roll no.", "branch", "Tution Fee", "Mess+Other", "Total Fee");
    printf("\n");

    int index = -1;
    for (int i = 0; i < numstudents; i++)
    {
        if (strcmp(str, student[i].rollno) == 0)
        {
            index = i;
        }
    }
    if (index != -1)
    {

        printf("%-25s%-15s%-15s%-15d%-15d%-15d\n", student[index].name, student[index].rollno, student[index].branch, student[index].tutionfee, (messfee + otherfee), student[index].totalfee);
    }
}
void assignCGPA()
{
    marks_main();
    for (int i = 0; i < numstudents; i++)
    {
        for (int j = 0; j < numstudents; i++)
        {
            if (strcmp(student[i].rollno, mark[j].rollno) == 0)
            {
                student[i].cgpa = mark[j].cgpa;
                break;
            }
        }
    }
}
void savefeedbacktoFile(struct feedbacks *stud_feedback)
{
    FILE *file = fopen(FILENAMEFEEDBACK, "a");
    if (file == NULL)
    {
        perror("Error :");
        return;
    }
    fprintf(file, "%s,%s\n", stud_feedback->employeeid, stud_feedback->feedback);
}
void loadfeedbackfromfile()
{
    FILE *file1 = fopen(FILENAMEFEEDBACK, "a");
    fclose(file1);
    FILE *file = fopen(FILENAMEFEEDBACK, "r");
    if (file == NULL)
    {
        perror("Error :");
        return;
    }
    while (fscanf(file, "%[^,],%[^\n]\n", &stud_feedback[numfeedbacks].employeeid, &stud_feedback[numfeedbacks].feedback) == 2)
    {
        numfeedbacks++;
        if (numfeedbacks >= max_feedbacks)
        {
            break;
        }
    }
    fclose(file);
}
void givefeedback()
{
    // authentication process
    FILE *feedbackptr = fopen(FILENAMEFEEDBACK, "a");
    char teachername[20];
    char teacherid[10];
    printf("Enter the name of the employee :");
    fflush(stdin);
    gets(teachername);
    strupr(teachername);
    int index = -1;
    for (int i = 0; i < numteachers; i++)
    {
        if (strcmp(teachername, teacher[i].name) == 0)
        {
            index = i;
        }
    }
    if (index != -1)
    {
        strcpy(teacherid, teacher[index].employeeID);
        strcpy(stud_feedback[numfeedbacks].employeeid, teacherid);
        printf("Feedback :");
        gets(stud_feedback[numfeedbacks].feedback);
        fprintf(feedbackptr, "%s,\"%s\"\n", teacherid, stud_feedback[numfeedbacks].feedback);
        savefeedbacktoFile(&stud_feedback[numfeedbacks]);
        printf("Feedback added successfully!\n");
        numfeedbacks++;
    }
    else
        printf("Employee not found!.\n");
    fclose(feedbackptr);
}
void showfeedback()
{
    FILE *feedback = fopen(FILENAMEFEEDBACK, "a");
    char teachername[20];
    char teacherid[10];
    printf("Enter the name of the employee :");
    fflush(stdin);
    gets(teachername);
    strupr(teachername);
    int index = -1;
    for (int i = 0; i < numteachers; i++)
    {
        if (strcmp(teachername, teacher[i].name) == 0)
        {
            index = i;
        }
    }
    if (index != -1)
    {
        int num = 1;
        strcpy(teacherid, teacher[index].employeeID);
        for (int i = 0; i < numfeedbacks; i++)
        {
            if (strcmp(teacherid, stud_feedback[i].employeeid) == 0)
            {
                printf("%d :", num);
                puts(stud_feedback[i].feedback);
                num++;
            }
        }
    }
    fclose(feedback);
}
