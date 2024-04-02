// subjects sub1 sub2 sub3 sub4 sub5
// numstudents variable ko vishwas wali files se uthaana h
// #include"vishwas.h"
// k is number of students and 500 is max number of students
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// global declarations
int k = 0;
int k1 = 0;
struct marks
{
    char rollno[10];
    float marks[5];
    int grade_weightage[5];
    float cgpa;
    char grade[5][3];
};
struct existing_students
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
struct existing_students es[5000];
struct marks array[5000];
int index__[5000];
int credit[5];

// functions

void loaddata1()
{
    FILE *ptr = fopen("marks.csv", "a");
    fclose(ptr);
    ptr = fopen("marks.csv", "r");

    char titles[6][20];
    // fscanf(ptr, "%s %s %s %s %s %s", &titles[0], &titles[1], &titles[2], &titles[3], &titles[4], &titles[5]);

    while (fscanf(ptr, "%[^,],%f,%f,%f,%f,%f", &array[k].rollno, &array[k].marks[0], &array[k].marks[1], &array[k].marks[2], &array[k].marks[3], &array[k].marks[4]) == 6)
    {
        k++;
        if (k >= 5000)
        {
            break;
        }
    }
    // if(k==0)
    // {
    //     fprintf(ptr,"Roll_no      Sub1     Sub2     Sub3     Sub4     Sub5");
    // }
    fclose(ptr);
}

void loaddata2()
{
    FILE *ptr = fopen("cg.csv", "a");
    fclose(ptr);
    ptr = fopen("cg.csv", "r");

    char titles[7][20];
    fscanf(ptr, "%[^,] %[^,] %[^,] %[^,] %[^,] %[^,] %[^,]", &titles[0], &titles[1], &titles[2], &titles[3], &titles[4], &titles[5], &titles[6]);

    while (fscanf(ptr, "%[^,] %f %[^,] %[^,] %[^,] %[^,] %[^,]", &array[k1].rollno, &array[k1].cgpa, &array[k1].grade[0], &array[k1].grade[1], &array[k1].grade[2], &array[k1].grade[3], &array[k1].grade[4]) == 7)
    {

        k1++;
        for (int i = 0; i < 5; i++)
        {
            if (strcmp(array[k1 - 1].grade[i], "Ex") == 0)
                array[k1 - 1].grade_weightage[i] = 10;
            if (strcmp(array[k1 - 1].grade[i], "A") == 0)
                array[k1 - 1].grade_weightage[i] = 9;
            if (strcmp(array[k1 - 1].grade[i], "B") == 0)
                array[k1 - 1].grade_weightage[i] = 8;
            if (strcmp(array[k1 - 1].grade[i], "C") == 0)
                array[k1 - 1].grade_weightage[i] = 7;
            if (strcmp(array[k1 - 1].grade[i], "D") == 0)
                array[k1 - 1].grade_weightage[i] = 6;
            if (strcmp(array[k1 - 1].grade[i], "P") == 0)
                array[k1 - 1].grade_weightage[i] = 5;
            if (strcmp(array[k1 - 1].grade[i], "F") == 0)
                array[k1 - 1].grade_weightage[i] = 0;
        }

        if (k1 >= 5000)
        {
            break;
        }
    }

    fclose(ptr);
}

void creditinput()
{

    for (int i = 1; i <= 5; i++)
    {
        printf("enter the credits corresponding to subject %d\n", i);
        scanf("%d", &credit[i - 1]);
    }
}

void marksinput()
{

    FILE *ptr = fopen("marks.csv", "a");

    printf("Enter roll number of student: ");
here3:
    scanf("%s", &array[k].rollno);
    strupr(array[k].rollno);

    for (int i = 0; i < k; i++)
    {
        if (strcmp(array[i].rollno, array[k].rollno) == 0)
        {
            printf("Enter a Valid roll number :\n");
            goto here3;
        }
    }

    fprintf(ptr, "%s,", array[k].rollno);

    for (int i = 1; i <= 5; i++)
    {
    here:
        printf("enter the marks out of 100 corresponding to subject %d\n", i);
        scanf("%f", &array[k].marks[i - 1]);
        if (array[k].marks[i - 1] >= 0 && array[k].marks[i - 1] <= 100)
            fprintf(ptr, "%.2f,", array[k].marks[i - 1]);
        else
        {
            printf("please enter a value between 0 to 100\n");
            goto here;
        }
    }
    fprintf(ptr, "\n");
    printf("marks added successfully\n");
    k++;
    fclose(ptr);
    int a;
    printf("-> Enter 1 for adding marks of a student\n-> Enter 2 for calculating grades and cgpa of students\n");
    scanf("%d", &a);
    switch (a)
    {
    case 1:
        goto here3;
        break;
    case 2:
        printf("grades and cgpa can be seen from the files created . thanks!");
        break;
    }
}
void subjectsorted(struct marks array[], int subjectnumber, FILE *ptr)
{
    float max = 0, large = 0;
    int m = 0, maxcount = 0;
    for (int i = 0; i < k; i++)
    {
        if (array[i].marks[subjectnumber] > max)
        {
            max = array[i].marks[subjectnumber];
            m = i;
        }
    }
    index__[maxcount] = m;
    maxcount++;

    fprintf(ptr, "%s,%f,\n", array[index__[maxcount - 1]].rollno, array[index__[maxcount - 1]].marks[subjectnumber]);

    for (int p = 0; p < (k - 1); p++)
    {
        for (int i = 0; i < k; i++)
        {
            int j;
            for (j = 0; j < maxcount; j++)
            {
                if (i == index__[j])
                {
                    break;
                }
            }
            if (j != maxcount)
            {
                continue;
            }
            if (array[i].marks[subjectnumber] <= max && array[i].marks[subjectnumber] >= large)
            {
                large = array[i].marks[subjectnumber];
                m = i;
            }
        }
        index__[maxcount] = m;
        maxcount++;

        fprintf(ptr, "%s,%f,\n", array[index__[maxcount - 1]].rollno, array[index__[maxcount - 1]].marks[subjectnumber]);
        max = large;
        large = 0;
    }
}

void gradingsystem(struct marks array[], int index[], FILE *ptr, int subject_number)
{
    // ex=k/10  a =3k/10 b=3k/10 c=15/100 d=5k/100 pass=5k/100 fail=5k/100
    int no_ex, no_a, no_b, no_c, no_d, no_p, no_f;
    no_ex = ceil(k / 10);
    no_a = ceil(3 * k / 10);
    no_b = ceil(3 * k / 10);
    no_c = ceil(15 * k / 100);
    no_d = ceil(5 * k / 100);
    no_p = ceil(5 * k / 100);
    no_f = k - no_ex - no_a - no_b - no_c - no_d - no_p;

    for (int i = 0; i <= no_ex; i++)
    {
        char grade[] = "ex";
        fprintf(ptr, "%s,%s,\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 10;
    }
    for (int i = no_ex + 1; i <= no_ex + no_a; i++)
    {
        char grade[] = "A";
        fprintf(ptr, "%s,%s,\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 9;
    }
    for (int i = no_ex + no_a + 1; i <= no_ex + no_a + no_b; i++)
    {
        char grade[] = "B";
        fprintf(ptr, "%s,%s,\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 8;
    }
    for (int i = no_ex + no_a + no_b + 1; i <= no_ex + no_a + no_b + no_c; i++)
    {
        char grade[] = "C";
        fprintf(ptr, "%s,%s,\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 7;
    }
    for (int i = no_ex + no_a + no_b + no_c + 1; i <= no_ex + no_a + no_b + no_c + no_d; i++)
    {
        char grade[] = "D";
        fprintf(ptr, "%s,%s,\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 6;
    }
    for (int i = no_ex + no_a + no_b + no_c + no_d + 1; i <= no_ex + no_a + no_b + no_c + no_d + no_p; i++)
    {
        char grade[] = "P";
        fprintf(ptr, "%s,%s,\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 5;
    }
    for (int i = no_ex + no_a + no_b + no_c + no_d + no_p + 1; i < no_ex + no_a + no_b + no_c + no_d + no_p + no_f; i++)
    {
        char grade[] = "F";
        fprintf(ptr, "%s,%s,\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 0;
    }
}

void cg(int credit[], struct marks array[])
{
    FILE *ptr = fopen("cg.csv", "w");
    // index wale se index u tha ke us hisaab se ex=10 a=9 b=8 c=7 d=6 p=5 f=0..... credit*weightage/total credit
    int total_credits = 0;
    for (int i = 0; i < 5; i++)
    {
        total_credits += credit[i];
    }
    fprintf(ptr, "Roll_no.,CGPA,Sub1,Sub2,Sub3,Sub4,Sub5,\n");
    for (int i = 0; i < k; i++)
    {
        array[i].cgpa = 0;
        for (int j = 0; j < 5; j++)
        {
            array[i].cgpa += (array[i].grade_weightage[j] * credit[j]) / (float)total_credits;
        }
        fprintf(ptr, "%s,%f,", array[i].rollno, array[i].cgpa);
        for (int j = 0; j < 5; j++)
        {
            switch (array[i].grade_weightage[j])
            {
            case 10:
                fprintf(ptr, "Ex,");
                break;
            case 9:
                fprintf(ptr, "A,");
                break;
            case 8:
                fprintf(ptr, "B,");
                break;
            case 7:
                fprintf(ptr, "C,");
                break;
            case 6:
                fprintf(ptr, "D,");
                break;
            case 5:
                fprintf(ptr, "P,");
                break;
            case 0:
                fprintf(ptr, "F,");
                break;
            }
        }
        fprintf(ptr, "\n");
    }
}

void viewstudents(struct marks array[], FILE *ptr)
{
    char roll[9];
    printf("enter the roll number of student: ");
    scanf("%s", &roll);
    strupr(roll);
    int i, flag = 0;
    for (i = 0; i < k1; i++)
    {
        if (strcmp(array[i].rollno, roll) == 0)
        {
            flag++;
            printf("%s,%f,", array[i].rollno, array[i].cgpa);
            for (int j = 0; j < 5; j++)
            {
                switch (array[i].grade_weightage[j])
                {
                case 10:
                    printf("Ex,");
                    break;
                case 9:
                    printf("A,");
                    break;
                case 8:
                    printf("B,");
                    break;
                case 7:
                    printf("C,");
                    break;
                case 6:
                    printf("D,");
                    break;
                case 5:
                    printf("P,");
                    break;
                case 0:
                    printf("F,");
                    break;
                }
            }
        }
    }
    if (i == k1 && flag == 0)
    {
        printf("This roll number does not exist");
    }
}
void save_students_csv()
{
    FILE *file1 = fopen("students.csv", "a");
    fclose(file1);
    FILE *file = fopen("students.csv", "r");
    if (file == NULL)
    {
        perror("Error :");
        return;
    }
    int num_ss=0;
    
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%lld,%f,%d,%d\n", &es[num_ss].name, &es[num_ss].rollno, &es[num_ss].gender, &es[num_ss].dateofBirth, &es[num_ss].bloodgroup, &es[num_ss].category, &es[num_ss].branch, &es[num_ss].state, &es[num_ss].address, &es[num_ss].email, &es[num_ss].annualincome, &es[num_ss].mobileno, &es[num_ss].cgpa, &es[num_ss].totalfee, &es[num_ss].tutionfee) == 15)
    {
        num_ss++;
        if (num_ss >= 5000)
        {
            break;
        }
    }
    fclose(file);

    for(int arr_var=0;arr_var<k;arr_var++)
    {
        for(int es_var=0;es_var<num_ss;es_var++)
        {
            if(strcmp(array[arr_var].rollno,es[es_var].rollno)==0)
                es[es_var].cgpa=array[arr_var].cgpa;
        }  
    }

    FILE *file_ss = fopen("students.csv", "w");
    if (file_ss == NULL)
    {
        perror("Error :");
        return;
    }

    for (int i = 0; i < num_ss; i++)
    {
        fprintf(file_ss, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%lld,%f,%d,%d\n", es[num_ss].name, es[num_ss].rollno, es[num_ss].gender, es[num_ss].dateofBirth, es[num_ss].bloodgroup, es[num_ss].category, es[num_ss].branch, es[num_ss].state, es[num_ss].address, es[num_ss].email, es[num_ss].annualincome, es[num_ss].mobileno, es[num_ss].cgpa, es[num_ss].totalfee, es[num_ss].tutionfee);
    }
    fclose(file_ss);
}
int main()
{
    int a;
    loaddata1();
    loaddata2();
    // printf("%d %d",k,k1);
    printf("->enter 1 for displaying CG and grades of a student\n->enter 2 for adding student data\n");
    scanf("%d", &a);
    switch (a)
    {
    case 1:
    {
        FILE *ptr_ = fopen("cg.csv", "r");
        viewstudents(array, ptr_);
        break;
    }
    case 2:
        creditinput();
        system("cls");
        marksinput();

        // i think 5 subject ke corresponding jo sorting h indivisual subject me, vo krni zaruri h kyuki harek teacher ko apne subject se matlab h to vo teacher uss file me se apne subject ka data dekh skte h sorted fom me.

        FILE *ptr = fopen("subject0sort.csv", "w");
        subjectsorted(array, 0, ptr);
        gradingsystem(array, index__, ptr, 0);
        fclose(ptr);

        FILE *ptr1 = fopen("subject1sort.csv", "w");
        subjectsorted(array, 1, ptr1);
        gradingsystem(array, index__, ptr, 1);
        fclose(ptr1);

        FILE *ptr2 = fopen("subject2sort.csv", "w");
        subjectsorted(array, 2, ptr2);
        gradingsystem(array, index__, ptr, 2);
        fclose(ptr2);

        FILE *ptr3 = fopen("subject3sort.csv", "w");
        subjectsorted(array, 3, ptr3);
        gradingsystem(array, index__, ptr, 3);
        fclose(ptr3);

        FILE *ptr4 = fopen("subject4sort.csv", "w");
        subjectsorted(array, 4, ptr4);
        gradingsystem(array, index__, ptr, 4);
        fclose(ptr4);

        cg(credit, array);
        break;
    }
    save_students_csv();
}
