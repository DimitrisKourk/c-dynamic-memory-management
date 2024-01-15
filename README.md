# Student Management Terminal App (C)

A menu-driven terminal application for managing students and their course grades, written in C as an exercise in **dynamic memory management**.

Every collection in the program grows and shrinks at runtime with `malloc`, `realloc` and `free`: the list of students, each student's list of courses, and every name string. The data is loaded from and saved back to a plain text file.

## Features

| Menu option | What it does |
|---|---|
| 1. Insert Student | Adds a student (name, surname, age ≥ 18). The student list grows with `realloc` and is re-sorted. |
| 2. Insert Course | Adds one or more courses with grades (0–10) to a student found by ID or full name |
| 3. Search by ID | Linear search with `lfind` |
| 4. Search by Surname + Name | Binary search with `bsearch` on the sorted list |
| 5. Average Grade | Computes a student's average across their courses |
| 6. Delete Student | Asks for confirmation, frees all of the student's memory and shrinks the list |
| 7. Delete Course | Removes a course by name and shrinks the course array |
| 8. Save and Exit | Writes everything back to `students.txt`. Refuses to save while any student has no courses. |

## Design

### Data structures

```c
typedef struct { char *name; int grade; } Course;
typedef struct { Course *arr; int numCourses; } CourseSet;
typedef struct { int id; char *surname; char *name; int age;
                 CourseSet courses; int numCourses; } Student;
typedef struct { Student *students; int num_students; } StudentSet;
```

All strings and arrays are heap-allocated to exactly the size needed, rather than using fixed-size buffers inside the structs.

### Notable techniques

- **Sorted storage.** Students are kept sorted by surname, then name, with `qsort`. That allows `bsearch` lookups by full name, and the same comparison function serves both.
- **Deleting a student.** The student's surname is replaced with `"ZZZZ"` and the array is re-sorted, which moves them to the end. Their memory is then freed and the array shrunk by one with `realloc`.
- **Deleting a course.** The last course is copied over the deleted one, and the array is shrunk by one. This is O(1) but doesn't preserve order.

## Data file format

`students.txt` holds the number of students, followed by five lines per student:

```
2                  ← number of students
Rafas Lakas        ← name surname
20                 ← age
1                  ← number of courses
Compilers          ← course names, comma-separated
7                  ← grades, comma-separated, in the same order
Nikos Mpikas
19
2
Anal1,Prog1
6,8
```

## Build and run

The program was written on **Windows**. It uses `itoa`, a non-standard function available with MinGW/MSVC, so it compiles there but not with GCC on Linux or macOS as-is.

```bash
gcc -o student_app Student_Management_Terminal_App.c
student_app.exe
```

Run it from the folder containing `students.txt`. The file is read on startup and overwritten on *Save and Exit*.
