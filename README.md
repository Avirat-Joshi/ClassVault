# CAPSTONE PROJECT ::: ClassVault

This is the final capstone project of our first-year PDS LAB
We have tried to make a student database management system 
using C language.

## Appendix :: Information
The motivation behind making a database management system is to learn about database management systems, file handling, algorithms, and various data structures. 
The aim is to effectively organize, display, edit, and process data. 
This system can be integrated with other software used such as learning management systems, scheduling software, or administration tools.  

## KEY FEATURES
Some key features which are part of the project are listed here:
- Merge Sort
  Instead of using the standard bubble sort algorithms, merge sort was used which decreased the worst-case time complexity from O(n^2) to O(n * log n)
- Random Password Generator
  Since users require a password to access the system, assigning passwords at random was required. For this, we used the time() function from the header file time.h, rand() function from header file stdlib.h and srand() function.
- Use of .CSV(Comma separated values) file
  This format was chosen over .txt and other database management formats due to its simplicity, portability, and ease of integration.

## Roadmap
We distributed the subparts of our code within our(group of 4)
- input data
- store data
- password generator
- password change
- CGPA calculation
- sort data
- Search by various parameters
- branch change
- fee details
- feedback system

## Tech
**-Use of C language only**
- using VScode
- using gcc MinGW compiler

## Database
- We have used a student database of our batch for demo purposes.
- The teacher database on the other hand is a list of some of our professors.
- The address of students is a randomly generated city out of 16 cities.
- The marks in marks.csv are randomly generated and do not belong to any student.

## 🔗 Github Links
- https://github.com/Avirat-Joshi
- https://github.com/Vishwasdabhi37
- https://github.com/Naitik1034
- https://github.com/skshmgrg9

## Deployment

To deploy this project run
- download the complete GitHub repository
- extract all files in the same folder
- open a new terminal and run the code 

```bash
  gcc driver.c
  ./a.exe
```

## Screenshots

- Initial User Interface:: <br><br>

For students
  ![Screenshot 2024-04-04 211727](https://github.com/Avirat-Joshi/PDS_PROJECT/assets/157312327/a12f463e-6a79-4a43-a92f-6d94a33ab63a)

For teachers
  ![Screenshot 2024-04-04 211956](https://github.com/Avirat-Joshi/PDS_PROJECT/assets/157312327/f5fa847f-8908-47d9-ac50-8eee774eb1e6)

View Students
  ![image](https://github.com/Avirat-Joshi/PDS_PROJECT/assets/157312327/c1155a5b-bed8-4d6c-93db-dd0e41b8efbb)


## Demo Video

  https://drive.google.com/file/d/160J2PqTGbt0NtQBoWIkv6l5-lN99QzjU/view?usp=sharing


