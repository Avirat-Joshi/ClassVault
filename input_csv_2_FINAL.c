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
    char branch[20];
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
void viewstudent();
void removestudent();
void searchbyname(char str[]);
void searchbymobno(long long int number);
void searchbyrollno(char str[]);
void groupbybranch(char str[]);
void groupbystate(char str[]);
void groupbygender(char str[]);
void fees();
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
        getchar();
        gets(student[numstudents].name);
        strupr(student[numstudents].name);

        printf("Enter your roll number : ");
    here0:
        scanf("%s", student[numstudents].rollno);
        strupr(student[numstudents].rollno);
        getchar();
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
        getchar();
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
        getchar();

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
        printf("1.CE\n2.CSE\n3.EE\n4.MM\n5.EC\n6.ME\n");
    here4:
        scanf("%d", &choice_br);
        switch (choice_br)
        {
        case 1:
            strcpy(student[numstudents].branch, "CE");
            break;
        case 2:
            strcpy(student[numstudents].branch, "CSE");
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
        getchar();

        printf("Enter your Address: ");
        scanf("%s", student[numstudents].address);
        strupr(student[numstudents].address);
        getchar();

        printf("Enter your E-mail ID : ");
        scanf("%s", student[numstudents].email);
        getchar();

        printf("Enter your Annual Income : ");
        scanf("%d", &student[numstudents].annualincome);
        getchar();

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
    case 1:
        printf("Enter your name: ");
        getchar();
        gets(student[edit_index].name);
        strupr(student[edit_index].name);
        break;

    case 2:
    {
        printf("Enter your roll number : ");
    here0:
        scanf("%s", student[edit_index].rollno);
        getchar();
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
        getchar();
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
        getchar();
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
        printf("1.CE\n2.CSE\n3.EE\n4.MM\n5.EC\n6.ME\n");
    here4:
        scanf("%d", &choice_br);
        switch (choice_br)
        {
        case 1:
            strcpy(student[edit_index].branch, "CE");
            break;
        case 2:
            strcpy(student[edit_index].branch, "CSE");
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
        getchar();
        break;
    }
    case 9:
    {
        printf("Enter your Address: ");
        scanf("%s", student[edit_index].address);
        strupr(student[edit_index].address);
        getchar();
        break;
    }
    case 10:
    {
        printf("Enter your E-mail ID : ");
        scanf("%s", student[edit_index].email);
        getchar();
        break;
    }
    case 11:
    {
        printf("Enter your Annual Income : ");
        scanf("%d", &student[edit_index].annualincome);
        getchar();
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
void viewstudent()
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
    viewstudent();
    if (numstudents == 0)
    {
        return;
    }
x:
    printf("Enter the S.no of the student to be removed\n");
    FILE *file = fopen(FILENAME, "w");
    int remove;
    scanf("%d", &remove);
    if(remove<1 || remove>=numstudents){
        printf("Invalid Input, Please retry\n");
        goto x;
    }
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
void fees()
{
    int messfee = 18000;
    int tutfee = 100000;
    int otherfee = 15000;

    for (int i; i < numstudents; i++)
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
    printf("%-7s%-25s%-15s%-15s%-15s%-15s%-15s\n", "Sr no.", "name", "roll no.", "branch", "Tution Fee", "Mess+Other", "Total Fee");
    printf("\n");

    for (int i = 0; i < numstudents; i++)
    {
        printf("%-5d: %-25s%-15s%-15s%-15d%-15d%-15d\n", i + 1, student[i].name, student[i].rollno, student[i].branch, student[i].tutionfee, (messfee + otherfee), student[i].totalfee);
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
    getchar();
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
    // authentication
    FILE *feedback = fopen(FILENAMEFEEDBACK, "a");
    char teachername[20];
    char teacherid[10];
    printf("Enter the name of the employee :");
    getchar();
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
void input_csv_2_final_main()
{
//     loaddatafromfile();
//     loadfeedbackfromfile();
//     loadteacherdatafromfile();
//     printf("Welcome to Classvault\n");
//     int login = 0;
//     printf("Use Classvalue as a :\n1. Student\n2. Teacher\n");
// goto1:
//     scanf("%d", &login);
//     switch (login)
//     {
//     case 1:
//     {
//         int choice, choice2;
//         do
//         {
//             printf("\nStudent-list Menu\n");
//             printf("0. Exit\n");
//             printf("1. Add Student\n");
//             printf("2. View Student\n");
//             printf("3. Remove Student\n");
//             printf("4. Edit Student\n");
//             printf("5. Search Student\n");
//             printf("6. Group Student\n");
//             printf("7. Give Feedback\n");
//             printf("8. Fee Details\n");
//             printf("Enter your choice(pls enter the number): ");
//         gotohere:
//             scanf("%d", &choice);

//             switch (choice)
//             {
//             case 0:
//                 printf("Exiting Classvault. Goodbye!\n");
//                 break;
//             case 1:
//                 addstudent();
//                 break;
//             case 2:
//                 viewstudent();
//                 break;
//             case 3:
//                 removestudent();
//                 break;
//             case 4:
//             {
//                 char roll_num[10];
//                 printf("Enter the Roll no. of the student you want to edit : ");
//                 scanf("%s", &roll_num);
//                 getchar();
//                 strupr(roll_num);
//                 editstudent(roll_num);
//                 break;
//             }
//             case 5:
//             {
//                 do
//                 {
//                     printf("\nStudent-search Menu\n");
//                     printf("0. Exit\n");
//                     printf("1. Search by name.\n");
//                     printf("2. Search by mobile number.\n");
//                     printf("3. Search by Roll no.\n");
//                     printf("Enter your choice(pls enter the number): ");
//                 goto2:
//                     scanf("%d", &choice2);
//                     getchar();

//                     switch (choice2)
//                     {
//                     case 0:
//                         printf("Exiting student-search.\n");
//                         sleep(1);
//                         break;
//                     case 1:
//                     {
//                         char stud_name[50];
//                         printf("Enter the name : ");
//                         scanf("%s", &stud_name);
//                         strupr(stud_name);
//                         searchbyname(stud_name);
//                         break;
//                     }
//                     case 2:
//                     {
//                         long long int mob_num;
//                         printf("Enter your mobile no.: ");
//                         while (1)
//                         {
//                             scanf("%lld", &mob_num);
//                             long long int temp = mob_num;
//                             int count = 0;
//                             while (temp)
//                             {
//                                 temp /= 10;
//                                 count++;
//                             }
//                             if (count == 10)
//                             {
//                                 break;
//                             }
//                             else
//                                 printf("Enter a valid phone number\n");
//                         }
//                         searchbymobno(mob_num);
//                         break;
//                     }
//                     case 3:
//                     {
//                         char roll_num[10];
//                         printf("Enter the Roll no. : ");
//                         scanf("%s", &roll_num);
//                         getchar();
//                         strupr(roll_num);
//                         searchbyrollno(roll_num);
//                         break;
//                     }
//                     default:
//                         printf("Enter Correct number :");
//                         goto goto2;
//                         break;
//                     }
//                 } while (choice2 != 0);
//                 break;
//             }
//             case 6:
//             {
//                 do
//                 {
//                     printf("\nStudent-Group Menu\n");
//                     printf("0. Exit\n");
//                     printf("1. Group by branch.\n");
//                     printf("2. Group by state.\n");
//                     printf("3. Group by gender.\n");
//                     printf("Enter your choice(pls enter the number): ");
//                 goto3:
//                     scanf("%d", &choice2);
//                     getchar();

//                     switch (choice2)
//                     {
//                     case 0:
//                         printf("Exiting student-group\n");
//                         sleep(1);
//                         break;
//                     case 1:
//                     {
//                         char stud_branch[4];
//                         int choice;
//                         printf("Enter the branch:\n");
//                         printf("1 for CE.\n2 for CSE.\n3 for EE.\n4 for MM.\n5 for EC.\n6 for ME.\n");
//                     here3:
//                         scanf("%d", &choice);
//                         switch (choice)
//                         {
//                         case 1:
//                             strcpy(stud_branch, "CE");
//                             break;
//                         case 2:
//                             strcpy(stud_branch, "CSE");
//                             break;
//                         case 3:
//                             strcpy(stud_branch, "EE");
//                             break;
//                         case 4:
//                             strcpy(stud_branch, "MM");
//                             break;
//                         case 5:
//                             strcpy(stud_branch, "EC");
//                             break;
//                         case 6:
//                             strcpy(stud_branch, "ME");
//                             break;
//                         default:
//                             printf("Enter correct number:");
//                             goto here3;
//                             break;
//                         }
//                         groupbybranch(stud_branch);
//                         break;
//                     }
//                     case 2:
//                     {
//                         char stud_state[15];
//                         printf("Enter the state : ");
//                         scanf("%s", &stud_state);
//                         strupr(stud_state);
//                         groupbystate(stud_state);
//                         break;
//                     }
//                     case 3:
//                     {
//                         char gender;
//                         char stud_gender[10];
//                         printf("Enter your gender.\n");
//                     there:
//                         printf("M for male and F for female.\n");
//                         scanf("%c", &gender);
//                         getchar();
//                         if (gender == 'M' || gender == 'm')
//                         {
//                             strcpy(stud_gender, "MALE");
//                         }
//                         else if (gender == 'F' || gender == 'f')
//                         {
//                             strcpy(stud_gender, "FEMALE");
//                         }
//                         else
//                         {
//                             printf("Enter correct gender : ");
//                             goto there;
//                         }
//                         groupbygender(stud_gender);
//                         break;
//                     }
//                     default:
//                         printf("Enter Correct number :");
//                         goto goto2;
//                         break;
//                     }
//                 } while (choice2 != 0);
//                 break;
//             }
//             case 7:
//                 givefeedback();
//                 break;
//             case 8:
//                 fees();
//                 break;
//             default:
//                 printf("Enter Correct number :");
//                 goto gotohere;
//                 break;
//             }
//             sleep(1);
//         } while (choice != 0);
//         break;
//     }
//     case 2:
//         teachers_main();
//         break;
//     default:
//         printf("Enter Correct number :");
//         goto goto1;
//         break;
//     }
//     return ;
}
