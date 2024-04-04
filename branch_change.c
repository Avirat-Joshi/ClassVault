#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define FILENAME "students.csv"
#define max_students 5000
int numstudents1 = 0;
int number = 0;
float top_1_percent_cg;
int i = 0;
int number_branch_change_students = 0;
struct student_details_depC
{
    char rollno[10];
    float cgpa;
    char branch_choice_number1[3];
    char branch_choice_number2[3];
    char branch_choice_number3[3];
    char current_branch[3];
    char approve[10];
};
struct existing_student_details
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
struct existing_student_credentials
{
    char rollno[10];
    char password[7];
};
int num_ce = 0;
int num_cs = 0;
int num_ec = 0;
int num_ee = 0;
int num_me = 0;
int num_mm = 0;
struct student_details_depC depC[max_students];
struct student_details_depC depC_details;
struct existing_student_credentials student_credentials[max_students];
struct existing_student_details student_branch_change[max_students];
void get_existing_student_details();
void get_credentials();
void get_details_from_user();
void get_current_branch();
void ask_branch_choice();
void confirmation_choice();
void branch_change_admin_verify();
void get_depC_student_data();
void allot_depC_to_top1perc();
void count_branch_wise_students();
void allot_depC_to_remaining();
void sort_depC_according_to_cg();
void update_data();
void show_result();
void get_existing_student_details()
{
    FILE *file1 = fopen(FILENAME, "a");
    fclose(file1);
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        perror("Error in opening the file\n");
        return;
    }
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%lld,%f,%d,%d\n", &student_branch_change[numstudents1].name, &student_branch_change[numstudents1].rollno, &student_branch_change[numstudents1].gender, &student_branch_change[numstudents1].dateofBirth, &student_branch_change[numstudents1].bloodgroup, &student_branch_change[numstudents1].category, &student_branch_change[numstudents1].branch, &student_branch_change[numstudents1].state, &student_branch_change[numstudents1].address, &student_branch_change[numstudents1].email, &student_branch_change[numstudents1].annualincome, &student_branch_change[numstudents1].mobileno, &student_branch_change[numstudents1].cgpa, &student_branch_change[numstudents1].totalfee, &student_branch_change[numstudents1].tutionfee) == 15)
    {
        numstudents1++;
        if (numstudents1 >= max_students)
        {
            break;
        }
    }
    printf("Total students %d\n", numstudents1);
    fclose(file);
}
void get_credentials()
{
    FILE *file_1 = fopen("credentials_student.csv", "a");
    fclose(file_1);
    FILE *file_2 = fopen("credentials_student.csv", "r");
    if (file_2 == NULL)
    {
        perror("Error in opening the file\n");
        return;
    }
    while (fscanf(file_2, "%[^,],%[^,],\n", &student_credentials[number].rollno, &student_credentials[number].password) == 2)
    {
        number++;
        if (number >= max_students)
        {
            break;
        }
    }
    fclose(file_2);
}
void get_details_from_user()
{
    printf("Welcome to Branch change forum\n");
    int choice = 1;
again:
    printf("Do you want to apply for branch change\n");
    printf("1. Yes\n2. No\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Enter roll number : ");
        scanf("%s", depC_details.rollno);
        strupr(depC_details.rollno);
        get_current_branch();
        break;
    case 2:
        break;
    default:
        printf("Wrong input, please retry \n");
        goto again;
    }
}
int i;
void get_current_branch()
{
    int index = -1;
    for (i = 0; i < numstudents1; i++)
    {
        if (strcmp(student_branch_change[i].rollno, depC_details.rollno) == 0)
        {
            index = 1;
        }
        if (index == 1)
            break;
    }
    if (index != 1)
    {
        printf("Student not found in database \n");
        return;
    }
    if (student_branch_change[i].cgpa < 8.5)
    {
        printf("Minimum CG requirement not met \n");
        return;
    }
    printf("Current branch is %s\n", student_branch_change[i].branch);
    strcpy(depC_details.current_branch, student_branch_change[i].branch);
    strcpy(depC_details.approve, "NOT YET");
    depC_details.cgpa = student_branch_change[i].cgpa;
    ask_branch_choice();
}
void ask_branch_choice()
{
    printf("Branches available are:\n1.CE\n2.CS\n3.ECE\n4.EE\n5.ME\n6.MM\n");
c1:
    printf("Enter branch choice number 1: ");
    scanf("%s", depC_details.branch_choice_number1);
    if (strcmp(depC_details.branch_choice_number1, student_branch_change[i].branch) == 0)
    {
        printf("Current branch and choice cannot be same. Re-enter your choice \n");
        goto c1;
    }
c2:
    printf("Enter branch choice number 2: ");
    scanf("%s", depC_details.branch_choice_number2);
    if (strcmp(depC_details.branch_choice_number2, student_branch_change[i].branch) == 0)
    {
        printf("Current branch and choice cannot be same. Re-enter your choice \n");
        goto c2;
    }
    if (strcmp(depC_details.branch_choice_number2, depC_details.branch_choice_number1) == 0)
    {
        printf("Two choices cannot be the same \n");
        goto c2;
    }
c3:
    printf("Enter branch choice number 3: ");
    scanf("%s", depC_details.branch_choice_number3);
    if (strcmp(depC_details.branch_choice_number3, student_branch_change[i].branch) == 0)
    {
        printf("Current branch and choice cannot be same. Re-enter your choice \n");
        goto c3;
    }
    if (strcmp(depC_details.branch_choice_number2, depC_details.branch_choice_number3) == 0)
    {
        printf("Two choices cannot be the same \n");
        goto c3;
    }
    if (strcmp(depC_details.branch_choice_number1, depC_details.branch_choice_number3) == 0)
    {
        printf("Two choices cannot be the same \n");
        goto c3;
    }
    confirmation_choice();
}
void save_details_to_file()
{
    FILE *file3 = fopen("dep_c.csv", "a");
    if (file3 == NULL)
    {
        perror("Error opening file for writing.\n");
        return;
    }
    char temp1[10];
    sprintf(temp1, "%f", depC_details.cgpa);
    fprintf(file3, "%s,%s,%s,%s,%s,%s,%s,\n", depC_details.rollno, temp1, depC_details.branch_choice_number1, depC_details.branch_choice_number2, depC_details.branch_choice_number3, depC_details.current_branch, depC_details.approve);
    fclose(file3);
}
void confirmation_choice()
{
    char password[10];
    printf("Here are your choices ");
    printf("1.%c%c\n", depC_details.branch_choice_number1[0], depC_details.branch_choice_number1[1]);
    printf("2.%c%c\n", depC_details.branch_choice_number2[0], depC_details.branch_choice_number2[1]);
    printf("3.%c%c\n", depC_details.branch_choice_number3[0], depC_details.branch_choice_number3[1]);
    printf("1. OK\n2.Edit\n");
    printf("Enter your choice \n");
    int n;
    scanf("%d", &n);
    getchar();
    switch (n)
    {
    case 1:
    retry:
        printf("Enter password: ");
        fflush(stdin);
        gets(password);
        for (int k = 0; k < numstudents1; k++)
        {
            if (strcmp(depC_details.rollno, student_credentials[k].rollno) == 0)
            {
                if (strcmp(password, student_credentials[k].password) == 0)
                {
                    printf("Your choices are recorded \n");
                    break;
                }
                else
                {
                    printf("Wrong password. Please retry\n");
                    goto retry;
                }
            }
        }
        break;
    case 2:
        printf("Your choices won't be recorded \n");
        break;
    default:
        printf("Please enter correct choice \n");
        confirmation_choice();
    }
    save_details_to_file();
}
void merge1(float arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    float L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void merge_sort(float arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge1(arr, l, m, r);
    }
}
void calculate_top_1_percent()
{
    float cg[numstudents1];
    for (int j = 0; j < numstudents1; j++)
        cg[j] = student_branch_change[j].cgpa;
    merge_sort(cg, 0, numstudents1 - 1);
    int temp = ceil(0.1 * numstudents1);
    top_1_percent_cg = cg[numstudents1 - temp - 1];
}
void branch_change_admin_verify()
{
    getchar();
    printf("Enter admin credentials: ");
    char id[10];
    gets(id);
    printf("Enter admin verification password: ");
    char pass[100];
    gets(pass);
    if (strcmp(id, "ADMIN") == 0 && strcmp(pass, "ADMIN@IITBBS") == 0)
        get_depC_student_data();
}
void get_depC_student_data()
{
    FILE *file4 = fopen("dep_c.csv", "a");
    fclose(file4);
    FILE *file5 = fopen("dep_c.csv", "r");
    if (file5 == NULL)
    {
        perror("Error in opening the file\n");
        return;
    }
    int temp = 0;
    char temporary[11];
    while (fscanf(file5, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],\n", depC[temp].rollno, temporary, depC[temp].branch_choice_number1, depC[temp].branch_choice_number2, depC[temp].branch_choice_number3, depC[temp].current_branch, depC[temp].approve) == 7)
    {
        depC[temp].cgpa = strtod(temporary, NULL);
        temp++;
    }
    fclose(file5);
    number_branch_change_students = temp;
    calculate_top_1_percent();
    allot_depC_to_top1perc();
    count_branch_wise_students();
    allot_depC_to_remaining();
}
void allot_depC_to_top1perc()
{
    for (int j = 0; j < number_branch_change_students; j++)
    {
        if (depC[j].cgpa > top_1_percent_cg)
        {
            strcpy(depC[j].approve, "YES\0");
            for (int k = 0; k < numstudents1; k++)
            {
                if (strcmp(student_branch_change[k].rollno, depC[j].rollno) == 0)
                {
                    strcpy(student_branch_change[k].branch, depC[j].branch_choice_number1);
                    strcpy(depC[j].current_branch, depC[j].branch_choice_number1);
                }
            }
        }
    }
}
void count_branch_wise_students()
{
    for (int j = 0; j < numstudents1; j++)
    {
        if (strcmp(student_branch_change[j].branch, "CE"))
            num_ce++;
        if (strcmp(student_branch_change[j].branch, "CS"))
            num_cs++;
        if (strcmp(student_branch_change[j].branch, "EC"))
            num_ec++;
        if (strcmp(student_branch_change[j].branch, "EE"))
            num_ee++;
        if (strcmp(student_branch_change[j].branch, "ME"))
            num_me++;
        if (strcmp(student_branch_change[j].branch, "MM"))
            num_mm++;
    }
}
void sort_depC_according_to_cg()
{
    for (int m = 0; m < number_branch_change_students - 1; m++)
    {
        for (int n = m + 1; n < number_branch_change_students; n++)
        {
            if (depC[m].cgpa >= depC[n].cgpa)
            {
                struct student_details_depC temp = depC[m];
                depC[m] = depC[n];
                depC[n] = temp;
            }
        }
    }
}
void allot_depC_to_remaining()
{
    int max_cs = ceil(1.1 * num_cs);
    int max_ce = ceil(1.1 * num_ce);
    int max_ee = ceil(1.1 * num_ee);
    int max_ec = ceil(1.1 * num_ec);
    int max_mm = ceil(1.1 * num_mm);
    int max_me = ceil(1.1 * num_me);
    sort_depC_according_to_cg();
    for (int j = 0; j < number_branch_change_students; j++)
    {
        if (strcmp(depC[j].approve, "NOT YET") == 0)
        {
            if (strcmp(depC[j].branch_choice_number1, "CE") == 0)
            {
                if (num_ce + 1 <= max_ce)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "CE");
                    num_ce++;
                }
            }
            if (strcmp(depC[j].branch_choice_number1, "CS") == 0)
            {
                if (num_cs + 1 <= max_cs)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "CS");
                    num_cs++;
                }
            }
            if (strcmp(depC[j].branch_choice_number1, "EC") == 0)
            {
                if (num_ec + 1 <= max_ec)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "EC");
                    num_ec++;
                }
            }
            if (strcmp(depC[j].branch_choice_number1, "EE") == 0)
            {
                if (num_ee + 1 <= max_ee)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "EE");
                    num_ee++;
                }
            }
            if (strcmp(depC[j].branch_choice_number1, "ME") == 0)
            {
                if (num_me + 1 <= max_me)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "ME");
                    num_me++;
                }
            }
            if (strcmp(depC[j].branch_choice_number1, "MM") == 0)
            {
                if (num_mm + 1 <= max_mm)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "MM");
                    num_mm++;
                }
            }
        }
    }
    for (int j = 0; j < number_branch_change_students; j++)
    {
        if (strcmp(depC[j].approve, "NOT YET") == 0)
        {
            if (strcmp(depC[j].branch_choice_number2, "CE") == 0)
            {
                if (num_ce + 1 <= max_ce)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "CE");
                    num_ce++;
                }
            }
            if (strcmp(depC[j].branch_choice_number2, "CS") == 0)
            {
                if (num_cs + 1 <= max_cs)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "CS");
                    num_cs++;
                }
            }
            if (strcmp(depC[j].branch_choice_number2, "EC") == 0)
            {
                if (num_ec + 1 <= max_ec)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "EC");
                    num_ec++;
                }
            }
            if (strcmp(depC[j].branch_choice_number2, "EE") == 0)
            {
                if (num_ee + 1 <= max_ee)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "EE");
                    num_ee++;
                }
            }
            if (strcmp(depC[j].branch_choice_number2, "ME") == 0)
            {
                if (num_me + 1 <= max_me)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "ME");
                    num_me++;
                }
            }
            if (strcmp(depC[j].branch_choice_number2, "MM") == 0)
            {
                if (num_mm + 1 <= max_mm)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "MM");
                    num_mm++;
                }
            }
        }
    }
    for (int j = 0; j < number_branch_change_students; j++)
    {
        if (strcmp(depC[j].approve, "NOT YET") == 0)
        {
            if (strcmp(depC[j].branch_choice_number3, "CE") == 0)
            {
                if (num_ce + 1 <= max_ce)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "CE");
                    num_ce++;
                }
            }
            if (strcmp(depC[j].branch_choice_number3, "CS") == 0)
            {
                if (num_cs + 1 <= max_cs)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "CS");
                    num_cs++;
                }
            }
            if (strcmp(depC[j].branch_choice_number3, "EC") == 0)
            {
                if (num_ec + 1 <= max_ec)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "EC");
                    num_ec++;
                }
            }
            if (strcmp(depC[j].branch_choice_number3, "EE") == 0)
            {
                if (num_ee + 1 <= max_ee)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "EE");
                    num_ee++;
                }
            }
            if (strcmp(depC[j].branch_choice_number3, "ME") == 0)
            {
                if (num_me + 1 <= max_me)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "ME");
                    num_me++;
                }
            }
            if (strcmp(depC[j].branch_choice_number3, "MM") == 0)
            {
                if (num_mm + 1 <= max_mm)
                {
                    strcpy(depC[j].approve, "YES");
                    strcpy(depC[j].current_branch, "MM");
                    num_mm++;
                }
            }
        }
    }
    for (int k = 0; k < number_branch_change_students; k++)
    {
        if (strcmp(depC[k].approve, "NOT YET") == 0)
            strcpy(depC[k].approve, "NO");
    }
    for (int k = 0; k < number_branch_change_students; k++)
    {
        if (strcmp(depC[k].approve, "YES") == 0)
        {
            for (int j = 0; j < numstudents1; j++)
            {
                if (strcmp(depC[k].rollno, student_branch_change[j].rollno) == 0)
                    strcpy(student_branch_change[j].branch, depC[k].current_branch);
            }
        }
    }
    update_data();
}
void show_result()
{
    printf("Following students have been alloted new branches \n");
    for (int j = 0; j < number_branch_change_students; j++)
    {
        if (strcmp(depC[j].approve, "YES") == 0)
        {
            printf("Roll number: %s\t", depC[j].rollno);
            printf("New Branch: %s\n", depC[j].current_branch);
        }
    }
}
void update_data()
{
    FILE *file = fopen("students.csv", "w");
    if (file == NULL)
    {
        perror("Error opening file for writing\n");
        return;
    }   
    for (int i = 0; i < numstudents1; i++)
    {
        char temp1[12], temp2[10];
        sprintf(temp1, "%lld", student_branch_change[i].mobileno);
        sprintf(temp2, "%f", student_branch_change[i].cgpa);
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%lld,%f,%d,%d\n", student_branch_change[i].name, student_branch_change[i].rollno, student_branch_change[i].gender, student_branch_change[i].dateofBirth, student_branch_change[i].bloodgroup, student_branch_change[i].category, student_branch_change[i].branch, student_branch_change[i].state, student_branch_change[i].address, student_branch_change[i].email, student_branch_change[i].annualincome, student_branch_change[i].mobileno, student_branch_change[i].cgpa, student_branch_change[i].totalfee, student_branch_change[i].tutionfee);
    }
    fclose(file);
}
void branch_change_student_main()
{
    get_existing_student_details();
    get_credentials();
    get_details_from_user();
}
void branch_change_admin_verify_main()
{
    get_existing_student_details();
    get_credentials();
    branch_change_admin_verify();
    show_result();
}
