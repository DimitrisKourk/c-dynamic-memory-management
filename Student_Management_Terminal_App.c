#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct  {
	char *name; // Name of the course
	int grade; // grade 0-10
}Course;

typedef struct {
	Course *arr;
	int numCourses;
}CourseSet;

typedef struct  {
	int id; // id is incrementally assigned upon a new entry for every student
	char *surname; // Surname
	char *name; // Name
	int age;
	CourseSet courses; // set of courses for a student
	int numCourses; // Number of courses
}Student;

typedef struct  {
	Student *students; // Dynamic array to store students
	int num_students; // Number of students – Number of elements in the array
}StudentSet;

int ImportDataFromFile(StudentSet *MyStudentSet); // pointer to struct using -> to reference the members of MyStudentSet
int InsertStudent(StudentSet *MyStudentSet);  
void InsertCourse(Student *MyStudent); 
Student* FindStudentByID(StudentSet *MyStudentSet,int id); // returning pointer to student with given id 
Student* FindStudentByFullName(StudentSet *MyStudentSet,char *name,char *surname); //  returning pointer to student with given Full Name 
void printStudentInfo(Student *MyStudent);
int CheckStudentHasNoCourse(StudentSet *MyStydentSet);
void CalculateAverageGrade(Student *MyStudent);
void DeleteCourse(Student *MyStudent);
void WriteToFile(StudentSet *MyStydentSet);
void FreeStudentSet(StudentSet *MyStudentSet); // frees all dynamically allocated memory before exit
int LinearComp(const void *a,const void *b); // compare function for linear search used in lfind
int Comp(const void *a,const void *b); // compare function for sorting used in qsort and for binary search in bsearch

int main(){
	
   StudentSet MyStudentSet;
   int a = ImportDataFromFile(&MyStudentSet); // passing MyStudentSet by reference !!!
   
   if(a==-1){
   	printf("Source file was empty\n");
   	MyStudentSet.num_students=0;
   }
   else {
   	printf("Data imported successfully from file\n");
   }
   
   if(MyStudentSet.num_students>1){
   	
   		qsort(MyStudentSet.students,MyStudentSet.num_students,sizeof(Student),Comp);
   		printf("---Students sorted---\n");
   		int i;
   		for(i=0;i<MyStudentSet.num_students;i++){
			printf("---Students[%d]=%s %s\n",i,MyStudentSet.students[i].surname,MyStudentSet.students[i].name);

		}
   }
    
   // menu infinite loop
   int choice, id,i;
   Student *found;
   char name[25],surname[25];
   while(1){
   		
   		printf("\n1)Insert Student\n2)Insert Course\n3)Search Student by ID\n4)Search Student by Surname + Name\n5)Calculate Student Average Grade\n6)Delete Student\n7)Delete Course\n8)Save and Exit\n\n");
   		printf("Type the number of the operation you want to run: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				a=InsertStudent(&MyStudentSet);	
				if(MyStudentSet.num_students>1){
   					
					qsort(MyStudentSet.students,MyStudentSet.num_students,sizeof(Student),Comp);
					//printf("---Students sorted---\n");
					for(i=0;i<MyStudentSet.num_students;i++){
						printf("---Students[%d]=%s %s\n",i,MyStudentSet.students[i].surname,MyStudentSet.students[i].name);
					}
   				}
				break;
			case 2:
				printf("1)Search Student by id\n");
				printf("2)Search Student by Surname + Name\n");
				fflush(stdin);
				
				printf("Choice: "); 
				scanf("%d", &choice);
				
				if(choice==1){
					printf("\nGive id: ");
					scanf("%d",&id);
					found = FindStudentByID(&MyStudentSet,id);
					if(found==NULL){
						printf("---No Student matched the given id---\n");
					}
					else{
						printf("---Student matched the given id---\n");
						InsertCourse(found); // Not passing &found because found is a pointer
					}
				}
				else if (choice==2){
					printf("\nGive Surame: ");
					scanf("%s",surname);
					
					printf("\nGive Name: ");
					scanf("%s",name);
					found = FindStudentByFullName(&MyStudentSet,name,surname);
					if(found==NULL){
						printf("---No Student matched the given Name---\n");
					}
					else{
						printf("---Student matched the given Name---\n");
						InsertCourse(found); // Not passing &found because found is a pointer
					}
				}
				else {
					printf("---Invalid Choice Input---\n");
				}
				
				break;
				
			case 3:	
				printf("\nGive id: ");
				scanf("%d",&id);
				found = FindStudentByID(&MyStudentSet,id);
				if(found==NULL){
					printf("---No Student matched the given id---");
				}
				else{
					printf("---Student matched the given id---");
					printStudentInfo(found); // Not passing &found because found is a pointer
				}
				break;
			case 4:
				printf("\nGive Surame: ");
				scanf("%s",surname);
				
				printf("\nGive Name: ");
				scanf("%s",name);
				found = FindStudentByFullName(&MyStudentSet,name,surname);
				if(found==NULL){
					printf("---No Student matched the given Name---");
				}
				else{
					printf("---Student matched the given Name---");
					printStudentInfo(found); // Not passing &found because found is a pointer
				}
				break;
			case 5:
				printf("1)Search Student by id\n");
				printf("2)Search Student by Surname + Name\n");
				fflush(stdin);
				
				printf("Choice: "); 
				scanf("%d", &choice);
				
				if(choice==1){
					printf("\nGive id: ");
					scanf("%d",&id);
					found = FindStudentByID(&MyStudentSet,id);
					if(found==NULL){
						printf("---No Student matched the given id---\n");
					}
					else{
						printf("---Student matched the given id---\n");
						CalculateAverageGrade(found); // Not passing &found because found is a pointer
					}
				}
				else if (choice==2){
					printf("\nGive Surame: ");
					scanf("%s",surname);
					
					printf("\nGive Name: ");
					scanf("%s",name);
					found = FindStudentByFullName(&MyStudentSet,name,surname);
					if(found==NULL){
						printf("---No Student matched the given Name---\n");
					}
					else{
						printf("---Student matched the given Name---\n");
						CalculateAverageGrade(found); // Not passing &found because found is a pointer
				}
				}
				else {
					printf("---Invalid Choice Input---\n");
				}
				
				break;
			case 6:
				printf("1)Search Student by id\n");
				printf("2)Search Student by Surname + Name\n");
				fflush(stdin);
				
				printf("Choice: "); 
				scanf("%d", &choice);
				
				if(choice==1){
					printf("\nGive id: ");
					scanf("%d",&id);
					found = FindStudentByID(&MyStudentSet,id);
					if(found==NULL){
						printf("---No Student matched the given id---\n");
						break;
					}
					else{
						printf("---Student matched the given id---\n");					}
				}
				else if (choice==2){
					printf("\nGive Surame: ");
					scanf("%s",surname);
					
					printf("\nGive Name: ");
					scanf("%s",name);
					found = FindStudentByFullName(&MyStudentSet,name,surname);
					if(found==NULL){
						printf("---No Student matched the given Name---\n");
						break;
					}
					else{
						printf("---Student matched the given Name---\n");
					}
				}
				else {
					printf("---Invalid Choice Input---\n");
					break;
				}
				printStudentInfo(found); // Not passing &found because found is a pointer
				fflush(stdin);
				printf("Confirm Delete Student??\n");
				printf("1)Confirm \n2)Cancel\n");
			
				printf("Choice: "); 
				scanf("%d", &choice);
					
				if(choice==1){
					int N=MyStudentSet.num_students;
					if(N>1){
						char *replace="ZZZZ";
						free(found->surname);
						found->surname=(char*)malloc(strlen(replace) + 1);
						strcpy(found->surname,replace); // replace name with ZZZZ
						qsort(MyStudentSet.students,MyStudentSet.num_students,sizeof(Student),Comp);// sort array so student with ZZZZ is the last element in the array
						
						free(MyStudentSet.students[N-1].name);			
						free(MyStudentSet.students[N-1].surname);
						
						int i,K=MyStudentSet.students[N-1].numCourses;						
						for(i=0;i<K;i++){
							//printf("Freed course name\n");
							free(MyStudentSet.students[N-1].courses.arr[i].name); // free name of every course
						}
						
						free(MyStudentSet.students[N-1].courses.arr);
					
					
						MyStudentSet.num_students--; // decrease student count by 1
						int StudentNumber=MyStudentSet.num_students;
						MyStudentSet.students= (Student*)realloc(MyStudentSet.students,StudentNumber*sizeof(Student)); //reallocare array with 1 less element.
								printf("Student Deleted Successfully\n");
					}
					else if (N==1){
							
						free(MyStudentSet.students[0].name);
						free(MyStudentSet.students[0].surname);
							
						int i,K=MyStudentSet.students[0].numCourses;
						if(K>0){
							for(i=0;i<K;i++){
								//printf("Freed course name\n");
								free(MyStudentSet.students[0].courses.arr[i].name); // free name of every course
							}
					
							free(MyStudentSet.students[0].courses.arr);
						}
						
						MyStudentSet.num_students--;
						printf("Student Deleted Successfully\n");
						free(MyStudentSet.students);
					}
				}
				else if(choice==2){
					printf("Canceling Delete operation...\n"); 
				}
				else {
					printf("---Invalid Input---\n"); 
				}	
				break;
			case 7:
				printf("1)Search Student by id\n");
				printf("2)Search Student by Surname + Name\n");
				fflush(stdin);
				
				printf("Choice: "); 
				scanf("%d", &choice);
				
				if(choice==1){
					printf("\nGive id: ");
					scanf("%d",&id);
					found = FindStudentByID(&MyStudentSet,id);
					if(found==NULL){
						printf("---No Student matched the given id---\n");
					}
					else{
						printf("---Student matched the given id---\n");
						DeleteCourse(found); // Not passing &found because found is a pointer
					}
				}
				else if (choice==2){
					printf("\nGive Surame: ");
					scanf("%s",surname);
					
					printf("\nGive Name: ");
					scanf("%s",name);
					found = FindStudentByFullName(&MyStudentSet,name,surname);
					if(found==NULL){
						printf("---No Student matched the given Name---\n");
					}
					else{
						printf("---Student matched the given Name---\n");
						DeleteCourse(found); // Not passing &found because found is a pointer
					}
				}
				else {
					printf("---Invalid Choice Input---\n");
				}
				
				break;
				
			case 8:
				if(CheckStudentHasNoCourse(&MyStudentSet)){
					printf("---Found Student With NO Courses!!! Unable to SAVE and EXIT---\n");
					break;
				}
				else{
					WriteToFile(&MyStudentSet);
					FreeStudentSet(&MyStudentSet);
					printf("---Saved Successfully and Exit---\n");
					return 0;
				}
				
			default:
				printf("Invalid Input!!! Enter valid menu choice number\n");
				fflush(stdin);
				break;
		}
   }
	
	return 0;
}

int ImportDataFromFile(StudentSet *MyStudentSet){
	FILE *fp; 		// declaring file pointer
    char str[100];	// line buffer

   /* opening file for reading */
   
   fp = fopen("students.txt" , "r");
   
   if(fp == NULL) {
      perror("Error opening file");
      return(-1);
   }
   
   int StudentNumber;
   
   if( fgets (str, sizeof(str), fp)) {
      /* writing content to stdout */
      StudentNumber=atoi(str);
      printf("Student.num_students=%d\n",StudentNumber);
	}
	else{
		fclose(fp);
		return -1;
		} // return -1 when file is empty
	
	
	MyStudentSet->students = (Student *)malloc(StudentNumber * sizeof(Student)); // allocating memory for StudentSet
	
	printf("StudentSet memmory allocated\n");

	MyStudentSet->num_students=StudentNumber; // setting to value from the file
	
	int i; // loop for every student
	
	for(i=0;i<StudentNumber;i++){

		MyStudentSet->students[i].id=i;
		
		fgets (str, sizeof(str), fp);
		// removing \n trailing character from fgets
		int len = strlen(str);
  		if (len > 0 && str[len-1] == '\n') {
    	str[--len] = '\0';
  		}
  		
   		char *token;
 		token = strtok(str, " "); // tokenizing using space as delimiter to get name
   		MyStudentSet->students[i].name = (char*)malloc(strlen(token) + 1);
   		strcpy(MyStudentSet->students[i].name,token);
   		printf("Student.students[%d].name=%s\n",i,MyStudentSet->students[i].name);
		
		int k;
		
		      // walking through the tokens to get surname
      	token = strtok(NULL, " ");
      	MyStudentSet->students[i].surname = (char*)malloc(strlen(token) + 1);
      	strcpy(MyStudentSet->students[i].surname,token);
		token = strtok(NULL, " ");
		printf("Student.students[%d].surname=%s\n",i,MyStudentSet->students[i].surname);
   		
   		
		fgets (str, sizeof(str), fp);
   		MyStudentSet->students[i].age=atoi(str); // getting age from file
   		printf("Student.students[%d].age=%d\n",i,MyStudentSet->students[i].age);
   		
   		
		fgets (str, sizeof(str), fp);
   		int CourseNumber=atoi(str);
   		MyStudentSet->students[i].numCourses=CourseNumber; // getting num of courses from file
   		MyStudentSet->students[i].courses.numCourses=CourseNumber;
   		printf("Student.students[%d].numCourses=%d\n",i,MyStudentSet->students[i].numCourses);
		
		fgets (str, sizeof(str), fp);
		// removing \n trailing character from fgets
		len = strlen(str);
  		if (len > 0 && str[len-1] == '\n') {
    	str[--len] = '\0';
  		}
  		
		MyStudentSet->students[i].courses.arr=(Course*)malloc(CourseNumber*sizeof(Course)); // allocating memory for Course
		
   		token = strtok(str, ","); // tokenizing using comma "," as delimiter to get each course
   		MyStudentSet->students[i].courses.arr[0].name=(char*)malloc(strlen(token) + 1); // allocating memory for course name
   		strcpy(MyStudentSet->students[i].courses.arr[0].name,token);
   		printf("Student.students[%d].courses.arr[0].name=%s\n",i,MyStudentSet->students[i].courses.arr[0].name);

		int j=1;
   		while( token != NULL ) {      // walking through the tokens to get course name
			
			token = strtok(NULL, ",");
			if(token != NULL){
				int len=strlen(token);
				MyStudentSet->students[i].courses.arr[j].name=(char*)malloc(len + 1);
   				strcpy(MyStudentSet->students[i].courses.arr[j].name,token);
   				printf("Student.students[%d].courses.arr[%d].name=%s\n",i,j,MyStudentSet->students[i].courses.arr[j].name);
   				j++;
			}
				
	    }
		   
   		fgets (str, sizeof(str), fp);
   		
   		token = strtok(str, ","); // tokenizing using comma "," as delimiter to get each Grade
   		
   		MyStudentSet->students[i].courses.arr[0].grade=atoi(token);
		printf("Student.students[%d].courses.arr[0].grade=%d\n",i,MyStudentSet->students[i].courses.arr[0].grade);

   		j=1;
   		while( token != NULL ) {      // walking through the tokens to get all grades
      		token = strtok(NULL, ",");
			if(token != NULL){
				MyStudentSet->students[i].courses.arr[j].grade=atoi(token);
				printf("Student.students[%d].courses.arr[%d].grade=%d\n",i,j,MyStudentSet->students[i].courses.arr[j].grade);
   				j++;
   			}
		}
	}
	fclose(fp);
	return 0;
}

int InsertStudent(StudentSet *MyStudentSet){
	char buffer[25]; // buffer to store user input
	
	int StudentNumber=MyStudentSet->num_students;
	
	if(StudentNumber>0){
		MyStudentSet->num_students++;
		StudentNumber=MyStudentSet->num_students;
		//reallocating memory for new student (Means adding more bytes of memory to dynamic array)
		MyStudentSet->students= (Student*)realloc(MyStudentSet->students,StudentNumber*sizeof(Student)); 
	}
	else if(StudentNumber==0){
			MyStudentSet->num_students++;
			StudentNumber=MyStudentSet->num_students;
			MyStudentSet->students= (Student*)malloc(StudentNumber*sizeof(Student));
	}
		
		StudentNumber=MyStudentSet->num_students; // StudentNumber represent current + new student
		printf("\nGive Student Name: ");
		scanf("%s",buffer);
		
		MyStudentSet->students[StudentNumber-1].name=(char*)malloc(strlen(buffer) + 1);
		strcpy(MyStudentSet->students[StudentNumber-1].name,buffer);
		fflush(stdin);
		
		printf("\nGive Student Surname: ");
		scanf("%s",buffer);
		
		MyStudentSet->students[StudentNumber-1].surname=(char*)malloc(strlen(buffer) + 1);
		strcpy(MyStudentSet->students[StudentNumber-1].surname,buffer);
	
		int age;
		printf("\nGive Student Age: ");
		scanf("%d",&age);
		while(age<18){
			printf("Invalid Age!!!\nGive Student Age: ");
			scanf("%d",&age);
		}
		MyStudentSet->students[StudentNumber-1].age=age;
		// new id = highest existing id + 1, so ids stay unique even after deletions
		int k,new_id=0;
		for(k=0;k<StudentNumber-1;k++){
			if(MyStudentSet->students[k].id>=new_id) new_id=MyStudentSet->students[k].id+1;
		}
		MyStudentSet->students[StudentNumber-1].id=new_id;
		MyStudentSet->students[StudentNumber-1].numCourses=0;
		return 0;
}

void InsertCourse(Student *MyStudent){
	int num,i,grade;
	char buffer[25]; // buffer to store user input
	printf("Number of Courses to add: ");
	scanf("%d",&num);
	
	if(MyStudent->numCourses==0){
		MyStudent->numCourses=num;
		MyStudent->courses.numCourses=num;
		MyStudent->courses.arr=(Course*)malloc(num*sizeof(Course)); // allocating memory for Course
		
		for(i=0;i<num;i++){
			printf("\nGive Course Name: ");
			scanf("%s",buffer);
			MyStudent->courses.arr[i].name=(char*)malloc(strlen(buffer) + 1);
			strcpy(MyStudent->courses.arr[i].name,buffer);
			fflush(stdin);
			
			printf("\nGive Course Grade: ");
			scanf("%d",&grade);
			while(grade<0 || grade >10){
				printf("Invalid Grade!!!\nGive Course Grade: ");
				scanf("%d",&grade);
			}
			MyStudent->courses.arr[i].grade=grade;
			fflush(stdin);
		}
	}
	else if(MyStudent->numCourses>0){
		int pos=MyStudent->numCourses;
		MyStudent->numCourses=pos+num;  // adding existing plus added courses
		MyStudent->courses.numCourses=pos+num;
		int N=MyStudent->numCourses;
		
		MyStudent->courses.arr=(Course*)realloc(MyStudent->courses.arr,N*sizeof(Course)); // allocating memory for Course
		
		for(i=0;i<num;i++){
			printf("\nGive Course Name: ");
			scanf("%s",buffer);
			
			MyStudent->courses.arr[pos].name=(char*)malloc(strlen(buffer) + 1);
			strcpy(MyStudent->courses.arr[pos].name,buffer);
			fflush(stdin);
			
			printf("\nGive Course Grade: ");
			scanf("%d",&grade);
				while(grade<0 || grade >10){
				printf("Invalid Grade!!!\nGive Course Grade: ");
				scanf("%d",&grade);
			}
			MyStudent->courses.arr[pos].grade=grade;
			fflush(stdin);
			pos++;
		}
	}
	
}


Student* FindStudentByID(StudentSet *MyStudentSet, int id){
	int N=MyStudentSet->num_students;
	Student *ptr,find;
	find.id=id;
	
	// uintptr_t cast was needed when casting int->void* and void*->int
	ptr=(Student *)(uintptr_t)lfind(&find,MyStudentSet->students,&N,sizeof(Student),LinearComp);
	
	if(ptr==NULL){
		return NULL;
	}
	else{
		return ptr;
	}
}

Student* FindStudentByFullName(StudentSet *MyStudentSet,char *name,char *surname){
	int N=MyStudentSet->num_students;
	Student *ptr,find;
	find.name=(char*)malloc(strlen(name) + 1); // allocating memory for name
	find.surname=(char*)malloc(strlen(surname) + 1); // allocating memory for surname
	strcpy(find.name,name);
	strcpy(find.surname,surname);
	
	// uintptr_t cast was needed when casting int->void* and void*->int
	ptr=(Student *)(uintptr_t)bsearch(&find,MyStudentSet->students,(size_t)N,sizeof(Student),Comp); //same comp function as qsort
	
	free(find.name);
	free(find.surname);
	
	if(ptr==NULL){
		return NULL;
	}
	else{
		return ptr;
	}
}
int LinearComp(const void *a,const void *b){
	Student *s1,*s2;
	s1=(Student *)a;
	s2=(Student *)b;
	if(s1->id==s2->id){
		return 0;
	}
	else {
		return 1;
	}
}
int Comp(const void *a,const void *b){
	Student *s1,*s2;
	s1=(Student *)a;
	s2=(Student *)b;
	
	int res;
	
	res=strcmp(s1->surname,s2->surname);	
	if(res!=0){
		return res; //sorting by surname 
	}
	
	res=strcmp(s1->name,s2->name);
	if(res!=0){
		return res; // sorting by name when surnames match
	}
	
	return 0;
}
void CalculateAverageGrade(Student *MyStudent){
	int N=MyStudent->numCourses;
	
	if(N>1){
		int i,sum=0;
		for(i=0;i<N;i++){
			sum=sum+MyStudent->courses.arr[i].grade;
		}
		//printf("sum=%d\n",sum);
		float avg=(float)sum/N; // cast so the division isn't done in integers
		printf("Average Grade=%.2f\n",avg);
	}
	else if(N==1){
		printf("Average Grade=%d\n",MyStudent->courses.arr[0].grade);
	}
	else{
		printf("---Student has NO COURSES!!!---");
	}
}

void DeleteCourse(Student *MyStudent){
	char buffer[25];
	printf("\nDelete Course with Name: ");
	scanf("%s",buffer);
	fflush(stdin);
	
	int N=MyStudent->numCourses;
	
	if(N>1){ // if student has more than 1 course
		int i;
		for(i=0;i<N;i++){
			int comp=strcmp(MyStudent->courses.arr[i].name,buffer);
			if(comp==0){
				//overwritting the Course we want to delete with the last course in the array and reallocating with 1 less Course
				free(MyStudent->courses.arr[i].name);
				MyStudent->courses.arr[i].name=(char*)malloc(strlen(MyStudent->courses.arr[N-1].name) + 1);
				strcpy(MyStudent->courses.arr[i].name,MyStudent->courses.arr[N-1].name);
				MyStudent->courses.arr[i].grade=MyStudent->courses.arr[N-1].grade;
				MyStudent->courses.numCourses--;
				MyStudent->numCourses--;
				free(MyStudent->courses.arr[N-1].name);// free memory of name of the last array element
				N--;
				MyStudent->courses.arr=(Course*)realloc(MyStudent->courses.arr,N*sizeof(Course)); // reallocating memory to remove last Course element

				printf("\nCourse Found and Deleted\n");
				break;
			}
		}
	}
	else if(N==1){ // if student has only 1 course
		
			int comp=strcmp(MyStudent->courses.arr[0].name,buffer);
			if(comp==0){
	
				MyStudent->courses.numCourses--;
				MyStudent->numCourses--;
				free(MyStudent->courses.arr[0].name);// free memory of name of the last array element
				free(MyStudent->courses.arr);
				printf("\nCourse Found and Deleted--No Courses remain in the array\n");
			}
	}
	
	else{
		printf("\nStudent has NO Course to delete\n");
		}	
	
}
int CheckStudentHasNoCourse(StudentSet *MyStydentSet){
	int i, StudentNumber=MyStydentSet->num_students;
	for(i=0;i<StudentNumber;i++){
		int CourseNumber=MyStydentSet->students[i].numCourses;
		if(CourseNumber==0){
			return 1;
		}
	}
	return 0;
}
void WriteToFile(StudentSet *MyStydentSet){
	
	FILE *fp;
	fp=fopen("students.txt", "w"); // opening with write mode overwrites the existing file 
	
	int i, StudentNumber=MyStydentSet->num_students;
	char buffer[25];
	
	if(StudentNumber>0){
		fputs(itoa(StudentNumber,buffer,10),fp);
		fputs("\n",fp);
	}
	
	for(i=0;i<StudentNumber;i++){
		
		fputs(MyStydentSet->students[i].name,fp);
		fputs(" ",fp);
		fputs(MyStydentSet->students[i].surname,fp);
		fputs("\n",fp);
		
		
		fputs(itoa(MyStydentSet->students[i].age,buffer,10),fp);
		fputs("\n",fp);
		fputs(itoa(MyStydentSet->students[i].numCourses,buffer,10),fp);
		fputs("\n",fp);
		int j,CourseNumber=MyStydentSet->students[i].numCourses;
		
		if(CourseNumber>0){
			fputs(MyStydentSet->students[i].courses.arr[0].name,fp);
			for(j=1;j<CourseNumber;j++){
				fputs(",",fp);
				fputs(MyStydentSet->students[i].courses.arr[j].name,fp);
			
			}
			fputs("\n",fp);
			fputs(itoa(MyStydentSet->students[i].courses.arr[0].grade,buffer,10),fp);
			for(j=1;j<CourseNumber;j++){
				fputs(",",fp);
				fputs(itoa(MyStydentSet->students[i].courses.arr[j].grade,buffer,10),fp);
			}
			fputs("\n",fp);
		}
		else continue;
	}
	fclose(fp);
}
void printStudentInfo(Student *MyStudent){
	printf("\nid=%d\n",MyStudent->id);
	printf("Name=%s\n",MyStudent->name);
	printf("Surname=%s\n",MyStudent->surname);
	printf("Age=%d\n",MyStudent->age);
	printf("Number of Courses=%d\n",MyStudent->numCourses);
	
	int N=MyStudent->numCourses;
	
	if(N>0){
		int i;
		for(i=0;i<N;i++){
			printf("Course=%s\n",MyStudent->courses.arr[i].name);
			printf("Grade=%d\n",MyStudent->courses.arr[i].grade);
		}
	}
	
}

void FreeStudentSet(StudentSet *MyStudentSet){
	int i,j;
	int StudentNumber=MyStudentSet->num_students;
	
	if(StudentNumber<=0){
		return; // nothing allocated (empty file) or already freed when the last student was deleted
	}
	
	for(i=0;i<StudentNumber;i++){
		Student *s=&MyStudentSet->students[i];
		free(s->name);
		free(s->surname);
		
		if(s->numCourses>0){ // course array only exists when the student has courses
			for(j=0;j<s->numCourses;j++){
				free(s->courses.arr[j].name); // free name of every course
			}
			free(s->courses.arr);
		}
	}
	
	free(MyStudentSet->students);
	MyStudentSet->students=NULL;
	MyStudentSet->num_students=0;
}
