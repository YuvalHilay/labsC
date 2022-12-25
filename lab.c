#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define x
typedef struct Item //define Item struct
{
	int num;
	struct Item* next;
}Item;

typedef struct List //define List struct
{
	struct Item* head;
	struct Item* tail;
	int count;

}List;

void Error_Msg(char*);  //prototypes
void AddAsFirst(Item*, List*);
void AddAsLast(Item*, List*);
void MoveToAnotherList(List*, List*, List*);
void CreateList(List*, FILE*);
void PrintItem(Item*);
void PrintList(List*, char*);
void DeleteList(List*);

#ifdef x2
int main()
{
	List L, Posit, Negat;
	FILE* in = fopen("ThreeLists.txt", "rt");
	if (in == NULL)
		Error_Msg("input file is wrong");
	L.head = NULL;
	L.tail = NULL;
	L.count = 0;

	Posit.head = NULL;
	Posit.tail = NULL;
	Posit.count = 0;

	Negat.head = NULL;
	Negat.tail = NULL;
	Negat.count = 0;

	CreateList(&L, in);
	PrintList(&L, "\nMy List:\n");
	MoveToAnotherList(&L, &Posit, &Negat);
	PrintList(&Posit, "\n\nThe Positive List:\n");
	PrintList(&Negat, "\n\nThe Negative List:\n\n");

	fclose(in);
	DeleteList(&Posit);
	DeleteList(&Negat);
	return 0;
}
void Error_Msg(char* msg)//fun for print Error massege
{
	printf("\n%s", msg);
	exit(1);
}
void AddAsFirst(Item* node, List* l)//fun add node to first place in list
{
	node->next = l->head;
	l->head = node;
	l->count++;
}
void AddAsLast(Item* node, List* l)//fun add node to last place in list
{
	node->next = NULL;
	if (l->head == NULL)//in case the list empty
	{
		l->head = node;
	}
	else
	{
		l->tail->next = node;
	}
	l->tail = node;
	l->count++;
}
void DeleteList(List* l)//fun delete the list
{
	Item* temp;
	while (l->head != NULL)
	{
		temp = l->head;
		l->head = (l->head)->next;
		free(temp);
	}
}
void MoveToAnotherList(List* l, List* posit, List* neg)//fun create 2 lists one for positive numbers and one for negative numbers
{
	Item* temp;
	while (l->head != NULL)
	{
		temp = l->head; 
		l->head = l->head->next;
		if (temp->num > 0)// add temp to positive list or negative list
		{
			AddAsLast(temp, posit);
		}
		else
		{
			AddAsFirst(temp, neg);
		}
	}
	l->tail = NULL;
	l->count = 0;
}
void CreateList(List* L, FILE* f)//fun that take input from file and create list
{
	int value;
	Item* temp;
	while (fscanf(f, "%d", &value) == 1)
	{
		temp = (Item*)malloc(sizeof(struct Item));
		if (temp == NULL)
		{
			DeleteList(L);
			Error_Msg("Memmory!");
		}

		temp->num = value;
		temp->next = NULL;
		if (L->head == NULL)
			L->head = temp;
		else
			L->tail->next = temp;
		L->tail = temp;
		L->count++;
	}
}
void PrintItem(Item* node)// fun that print node
{
	printf("%d--> ", node->num);
}
void PrintList(List* L, char* title)// fun that print the list
{
	Item* temp = L->head;
	printf("%s", title);
	while (temp)
	{
		PrintItem(temp);
		temp = temp->next;
	}
	printf("\nThere are %d items in the list", L->count);
}

#endif // x
///////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define N 5
#define x
typedef struct Item //define Item struct
{
	int num;
	struct Item* next;
}*PItem;

void Error_Msg(char*); //prototypes
void CreateListFromArray(PItem*, PItem*, int*);
void DeleteList(PItem*);
void ListDisplay(PItem);
int ListLength(PItem);

#ifdef x
int main()
{
	int Arr[N] = { 3,4,1,0,8 };

	PItem list = NULL, tail = NULL;

	CreateListFromArray(&list, &tail, Arr);
	printf("The length of the list is %d members\n", ListLength(list));
	printf("\nThe list is:\n");
	ListDisplay(list);

	DeleteList(&list);
	tail = NULL;
	return 0;
}

void Error_Msg(char* msg)//fun for print Error massege
{
	printf("\n%s", msg);
	exit(1);
}

int ListLength(PItem head)//fun calc recursively List Length
{
	if (head == NULL)
		return 0;
	return 1 + ListLength(head->next);
}
void ListDisplay(PItem head)//fun print recursively the List 
{
	if (head == NULL)
		return 0;
	printf("%d--> ", head->num);
	ListDisplay(head->next);
}
void CreateListFromArray(PItem* head, PItem* tail, int* Arr)//fun convert list to array
{
	int i;
	PItem temp;
	for (i = 0; i < N; i++)
	{
		temp = (PItem)malloc(sizeof(struct Item));
		if (temp == NULL)
		{
			DeleteList(head);
			Error_Msg("Memmory!");
		}
		temp->num = Arr[i];
		temp->next = NULL;
		if (*head == NULL)
			*head = temp;
		else
			(*tail)->next = temp;
		*tail = temp;
	}
}
void DeleteList(PItem* head)//fun delete the list
{
	PItem tmp = *head;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

#endif // x

///////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2
#define x
typedef struct //define struct Item
{
	int code;
	char name[11];
	struct Item* next;
}Item;
#ifdef x2
int main()
{
	int i, j;  //define variables
	Item* Head = NULL, * temp;
	for (i = 1; i <= N; i++)
	{
		temp = (Item*)malloc(sizeof(Item));// dynamic allocation
		if (temp == NULL) //check dynamic allocation succeed
		{
			for (j = 1; j < i; j++)//free the dynamic allocations
			{
				temp = Head;
				Head = Head->next;
				free(temp);
			}
			printf("Not enough memory");
			exit(1);
		}
		temp->next = Head;//insert temp to the start of the list
		Head = temp;
		printf("Enter a new code and name: ");//take input
		scanf("%d %s", &temp->code, temp->name);
	}
	printf("\nThe List is:  ");
	temp = Head;
	while (temp != NULL)//print the list
	{
		printf("%d,%s --> ", temp->code, temp->name);
		temp = temp->next;
	}
	while (Head != NULL)//delete list
	{
		temp = Head;
		Head = Head->next;
		free(temp);

	}
	return 0;
}
#endif // x
////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define x
typedef struct node //define struct std
{
	char code[11];
	char* name;
	char Dep[4];
	int marks[3];
	float avg;
	struct node* next;
}std;

void Error_Msg(char* str); //prototypes
std* FromFileToList(std* head, FILE* in);
std* Delete_Stud(std* toDel, std* head);
std* DeleteList(std* head);
void PrintList(std* head);
std* FindMax(std* head);

#ifdef x
int main()
{
	int i;
	FILE* f;
	std* Head = NULL, * temp;
	if ((f = fopen("List.txt", "rt")) == NULL)
		Error_Msg("input error");
	Head = FromFileToList(Head, f);
	if (Head == NULL)
		Error_Msg("The input file is empty");
	fclose(f);
	printf("The list is:\n");
	PrintList(Head);
	temp = FindMax(Head);
	printf("\nthe student with max average:\n");
	printf("%s %s %s ", temp->code, temp->name, temp->Dep);
	for (i = 0; i < 3; i++)
		printf(" %d ", temp->marks[i]);
	printf("\n\nThe list after change:\n");
	Head = Delete_Stud(FindMax(Head), Head);
	PrintList(Head);
	Head = DeleteList(Head);   /*Head = NULL */
	return 0;
}
void Error_Msg(char* str)
{
	printf("\n%s", str);
	exit(1);
}
std* FromFileToList(std* head, FILE* in)//fun get pointer to file and pointer to std and take unput from file and create a list
{
	int i,j, count = 1;//define variables
	char name[256];
	std* temp = NULL,*p = NULL;
	temp = (std*)malloc(sizeof(std));//dynamic allocation temp
	if (temp == NULL)//check dynamic allocation succeed
	{
		printf("allocation didint succeed");
		exit(1);
	}
	while (fscanf(in, "%s %s %s %d %d %d", temp->code, name, temp->Dep, &temp->marks[0], &temp->marks[1], &temp->marks[2]) != EOF)//take input until end of file
	{
		temp->avg = (float)(temp->marks[0] + temp->marks[1] + temp->marks[2]) / 3;//calc avg
		temp->name = (char*)malloc((strlen(name)) + 1); //dynamic allocation for name in
		if ((temp->name) == NULL)//check dynamic allocation succeed
		{
			p = head;
			for ( j = 0; j < count-1; j++)
			{
				temp = p;
				p = p->next; 
				free(temp->name);
			}
			for (i = 0; i < count; i++)//free dynamic allocations
			{
				temp = head;
				head = head->next;
				free(temp);
			}
			printf("Not enough memory");
			exit(1);
		}
		strcpy(temp->name, name);//copy name to arr
		temp->next = head;//inset temp to start of the list
		head = temp;
		temp = (std*)malloc(sizeof(std));//another dynamic allocation temp
		if (temp == NULL) // check dynamic allocation succeed
		{
			for (i = 0; i < count; i++)//free dynamic allocations
			{
				temp = head;
				head = head->next;
				free(temp->name);
				free(temp);
			}
			printf("allocation didint succeed");
			exit(1);
		}
		count++;
	}
	return head;//return the list
}
void PrintList(std* head)//fun get pointer to std and print list
{
	std* temp = NULL;
	temp = head;
	while (temp != NULL)
	{
		printf("%s %s %s %d %d %d\n", temp->code, temp->name, temp->Dep, temp->marks[0], temp->marks[1], temp->marks[2]);
		temp = temp->next;
	}
}
std* FindMax(std* head)//fun get pointer to std find node with maxavg
{
	int i;
	float maxavg = 0;
	std* p = NULL, * pmax = NULL;
	p = head;
	pmax = head;
	while (p != NULL)//run on list
	{
		if (p->avg > maxavg)//check avg
		{
			pmax = p;
			maxavg = p->avg;
		}
		p = p->next;
	}
	return pmax;
}
std* Delete_Stud(std* toDel, std* head)//fun get pointer to std and pointer to node to delete and delete him
{
	std* temp = NULL, * p = NULL;
	if (head == NULL)
		return NULL;
	temp = (std*)malloc(sizeof(std)); // dynamic allocation
	if (temp == NULL) // check dynamic allocation succeed
	{
		printf("allocation didint succeed");
		exit(1);
	}
	if (toDel == head)//if the node is first orgin in list delete him
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	else//delete if the node isnt first in list
	{
		p = head;
		while (p->next != toDel)
		{
			p = p->next;
		}
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return head;
}
std* DeleteList(std* head)//fun get pointer to std and delete list
{
	std* temp = NULL;
	temp = (std*)malloc(sizeof(std));//dynamic allocation
	if (temp == NULL)// check dynamic allocation succeed
	{
		printf("allocation didint succeed");
		exit(1);
	}
	while (head != NULL)//delete list
	{
		temp = head;
		head = head->next;
		free(temp);

	}
}

#endif // x

//////////////
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define x
void Error_Msg(char* str);//prototype
void copy_Comp_stud(FILE* in, FILE* out);
#ifdef x2
int main()
{
	FILE* in, * out;
	if ((in = fopen("Students.txt", "r")) == NULL)//open  in  for read and check open file succeed
		Error_Msg("The input file is wrong");
	if ((out = fopen("StudentsNew.txt", "w")) == NULL)//open  out  for write and check open file succeed
		Error_Msg("The output file is wrong");
	copy_Comp_stud(in, out);//call copy_Comp_stud
	fclose(in);//close files
	fclose(out);
	return 0;
}
void copy_Comp_stud(FILE* in, FILE* out)
{
	char name[7], unit[5], grade1[4], grade2[4];//define variables
	int sum = 0, grade3, grade4;
	while (fgets(name, 7, in) != NULL)//take input until the end of file
	{
		fgets(unit, 5, in);	//input the unit and compare to "Comp"
		if (strcmp(unit, "Comp") == 0)
		{
			fgets(grade1, 4, in);//input the grade and convert to integer
			fgets(grade2, 4, in);
			grade3 = atoi(grade1);
			grade4 = atoi(grade2);
			fprintf(out, "%s %.2f\n", name, (float)(grade3 + grade4) / 2);//print to file the data
		}
		else
		{
			fgets(grade1, 4, in);////input the grade if we didint in Comp unit
			fgets(grade2, 4, in);
		}

	}
}
void Error_Msg(char* str)
{
	printf("\n%s", str);
	exit(1);
}


#endif // x


////////////
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX 256
#define x
typedef struct //define struct Book
{
	char code[11];
	char* name;
}Book;
typedef struct //define struct Library
{
	char name[MAX];
	int num_book;
	Book* books;
}Library;
void input_book(Book* B, FILE* in);//prototypes
void input_library(Library* L, FILE* in);
void output_book(Book* B, FILE* out);
void output_library(Library* L, FILE* out);
#ifdef x2
int main()
{
	FILE* in, * out;//define variables
	Library Libr;
	int i;
	if ((in = fopen("input.txt", "r")) == NULL)//open  in  for read and check open file succeed
		printf("The input file is wrong");
	input_library(&Libr, in);//call input_library
	fclose(in);
	if ((out = fopen("output.txt", "w")) == NULL)//open  out  for write and check open file succeed
		printf("The input file is wrong");
	output_library(&Libr, out);//call output_library
	fclose(out);
	for (i = 0; i < Libr.num_book; i++)/* free the memory!!!*/
	{
		free(Libr.books[i].name);
	}
	free(Libr.books);
	return 0;
}
void input_library(Library* L, FILE* in)//fun get address to Library and pointer to file and take input
{
	int i;
	fscanf(in, "%s", L->name);//input Library name and number of books
	fscanf(in, "%d", &L->num_book);
	L->books=(Book*)malloc(L->num_book*sizeof(Book));//dynamic allocation for books
	if ((L->books) == NULL)//check dynamic allocation succeed
	{
		printf("Not enough memory");
		exit(1);
	}
	for (i = 0; i < L->num_book; i++)//run on number of books
	{
		input_book(&L->books[i], in);//call input_book for input a book 
	}
}
void input_book(Book* B, FILE* in)//fun get address to Book and pointer to file and take input
{
	char name[MAX];
	fscanf(in, "%s", B->code);//input code and name
	fscanf(in, "%s", name);
	B->name = (char*)malloc((strlen(name)) + 1);//dynamic allocation fo name in B
	if ((B->name) == NULL)//check dynamic allocation succeed
	{
		printf("Not enough memory");
		exit(1);
	}
	strcpy(B->name, name);//copy name to array	
}
void output_library(Library* L, FILE* out)//fun get address to Library and pointer to file and print output
{
	int i;
	fprintf(out, "%s\n", L->name);//print name
	for (i = 0; i < L->num_book; i++)//run on number of books
	{
		output_book(&L->books[i], out);//call output_book 
	}
}
void output_book(Book* B, FILE* out)//fun get address to Book and pointer to file and print output
{
	fprintf(out, "%s\t%s\n", B->code, B->name);//print the code and name
}
#endif // x

/////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define x2
int Bit_Count(unsigned int x);//prototypes
void Bin_Print(unsigned int x);
#ifdef x3
int main()
{
	unsigned int x;
	printf("Enter a number: ");
	scanf("%u", &x);
	printf("There are %d bits equal to one in %d\n", Bit_Count(x), x);//print use Bit_Count
	printf("The binary representation of %d is ", x);
	Bin_Print(x);//print number use Bin_Print
	return 0;
}
int Bit_Count(unsigned int x)//fun get unsigned int and return number of 1
{
	int i, count = 0, unity = 1;
	int n = 8 * sizeof(unsigned int);//n is the amount of bite
	for (i = 0; i < n - 1; i++)//run on n
	{
		if ((x & (unity << i)) != 0)//check if bite is 1 and count
			count++;
	}
	return count;
}
void Bin_Print(unsigned int x)//fun get unsigned int and print him
{
	int i, unity = 1, num = 0;
	int n = 8 * sizeof(unsigned int);//n is the amount of bite
	for (i = n - 1; i >= 0; i--)//run from rhe end
	{
		if ((x & (unity << i)) != 0)//check if bite is 1 or 0 and print using num
		{
			num = 1;
		}
		printf("%d", num);
		num = 0;
	}
}
#endif // x
////////////

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define x
void BinPrint(unsigned char ch);//prototypes
unsigned char check_ms(unsigned char num);
unsigned char change_bit(unsigned char num, int number);
#ifdef x
int main()
{
	unsigned char num1 = 102, num2 = 58;
	int n;
	printf("\nThe first part :");//prints inputs and call for functions
	printf("\nThe number is %d   ", num1);
	BinPrint(num1);
	num1 = check_ms(num1);
	printf("\nThe new number is: %d   ", num1);
	BinPrint(num1);
	printf("\n\nThe second part :");
	printf("\nThe number is %d   ", num2);
	BinPrint(num2);
	printf("\nEnter a number of the bit to change(1-8): ");
	scanf("%d", &n);
	num2 = change_bit(num2, n);
	printf("\nThe new number is: %d   ", num2);
	BinPrint(num2);
	return 0;
}
unsigned char check_ms(unsigned char num)//fun get unsigned char and change left bit to 1
{
	int unity = 1;
	int n = 8 * sizeof(unsigned char);//n is the amount of bite
	if (num & (unity << (n - 1)) != 0)//check left bite and change to 1
	{
		return num;
	}
	return num | unity << n - 1;
}
unsigned char change_bit(unsigned char num, int number)//fun get unsigned char and number and change the required bite to 1 or 0
{
	unsigned char unity = 1, num1=num;
	unity = unity << (8*sizeof(unsigned char) -number);//unity mask with 1 in required bite
	if ((num & unity) != 0)//check if bite is 0 or 1 and change him
		num1= num & ~(unity);
	else
		num1 = num | unity;
	return num1;
}
void BinPrint(unsigned char ch)//fun get unsigned char and print him
{
	int i, unity = 1, num = 0;
	int n = 8 * sizeof(unsigned char);//n is the amount of bite
	for (i = n - 1; i >= 0; i--)//run from rhe end
	{
		if ((ch & (unity << i)) != 0)//check if bite is 1 or 0 and print using num
		{
			num = 1;
		}
		printf("%d", num);
		num = 0;
	}
}
#endif // x

//////////
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define x2
typedef struct Person //define struct Person
{
	char ID[10];
	char F_name[11];
	char L_name[16];
	int Age;
	char Addr[51];
}Person;
void Error_Msg(char*);//prototype
#ifdef x
int main()
{
	Person temp;
	FILE* in, * out;
	in = fopen("the_first.txt", "r");//open  in  for read
	if (in == NULL)//check open file succeed
	{
		Error_Msg("open file didnt succeed");
	}
	out = fopen("the_second.txt", "w"); // open  out  for write
	if (out == NULL)//check open file succeed
	{
		Error_Msg("open file didnt succeed");
	}
	fscanf(in, "%s%s%s%d%s", temp.ID, temp.F_name, temp.L_name, &temp.Age, temp.Addr);//scanf from file
	fprintf(out, "ID: %s\nFull name: %s %s\nAge: %d\nAddress: %s", temp.ID, temp.F_name, temp.L_name, temp.Age, temp.Addr);//print to file
	fclose(in);//close files
	fclose(out);
	return 0;
}
void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);    /*Exit() closes any open files in the program*/
}
#endif // x
//////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define x
#ifdef x2
typedef struct //define struct studnet
{
    char name[20];
    int grades[3];
}student;
void Error_Msg(char*);//prototypes
int InputData(student**, FILE*);
void OutputData(int, student*, FILE*);

int main()
{
    FILE* fp;
    student* arr;
    int size;
    if ((fp = fopen("Students.txt", "r")) == NULL)//open  fp  for read and check open file succeed
        Error_Msg("The input file is wrong");
    size = InputData(&arr, fp);//call InputData
    fclose(fp);
    if ((fp = fopen("Students.txt", "w")) == NULL)//open  fp  for write and check open file succeed
    {
        free(arr);
        Error_Msg("The output file is wrong");
    }
    OutputData(size, arr, fp);//call OutputData
    fclose(fp);//close file
    free(arr);
    return 0;
}

int InputData(student** p_array, FILE* fp)//fun get studnet array and file and scanf from the file and return number of students
{
    student* arr,*temp;
    int i = 1;
    arr = (student*)malloc(sizeof(student)); //dynamic allocation for arr
    if (arr == NULL)//check dynamic allocation succeed
    {
        Error_Msg("Not enough memory");
        exit(1);
    }
    while (fscanf(fp, "%s %d %d %d", arr[i - 1].name, &arr[i - 1].grades[0], &arr[i - 1].grades[1], &arr[i - 1].grades[2]) != EOF)//scanf from the file into the arr
    {
        temp = (student*)realloc(arr, (i + 1) * sizeof(student));//extend arr by 1
        if (temp != NULL)//check realloc succeed
            arr = temp;
        else
        {
            free(arr);
            exit(1);
        }
        i++;
    }
    *p_array = arr;
    return  i - 1; /*return the number of students*/


}
void OutputData(int arr_size, student* arr, FILE* fp)//fun get studnet arr his size and file
{
    int i,j,maxgrade;
    for (i = 0; i < arr_size; i++)//run on arr size
    {
        maxgrade = arr[i].grades[0];
        for ( j = 1; j < 3; j++)//calc max grade for student
        {
            if (arr[i].grades[j] > maxgrade)
            {
                maxgrade = arr[i].grades[j];
            }
        }
        fprintf(fp,"%s %d\n", arr[i].name, maxgrade);//print studnet with his max grade
    }

}
void Error_Msg(char* msg)
{
    printf("\n%s", msg);
    exit(1);
}
#endif // x


///////////

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 4
#define X
typedef struct Complex //define struct Complex
{
	float r;
	float i;
}Complex;

float CRadius(Complex);//prototypes
void Error_Msg(char* str);
void InputAndWriteToFile(FILE* f);
int CheckFile(FILE* f, float m);
#ifdef X2
int main()
{
	FILE* f;
	f = fopen("complex.txt", "w");//open  f for write and check open file succeed
	if (f == NULL)
	{
		Error_Msg("open file didnt succeed");
		exit(1);
	}
	InputAndWriteToFile(f);//call InputAndWriteToFile
	fclose(f);//close file
	f = fopen("complex.txt", "r");//open  f for read and check open file succeed
	if (f == NULL)
	{
		Error_Msg("open file didnt succeed");
		exit(1);
	}
	printf("\nThere are %d big numbers\n", CheckFile(f, 4));//print thw amount of numbers vigger than m use CheckFile
	fclose(f);//close file
	return 0;
}
float CRadius(Complex num)//fun get Complex number and return his radius
{
	float radius;
	radius = sqrt(pow(num.r, 2) + pow(num.i, 2));
	return radius;
}
void InputAndWriteToFile(FILE* f)//fun get file and print to him complex nuber and radius
{
	Complex a;
	int i;
	printf("Enter %d complex numbers:\n", N);//input N complex nuber 
	for (i = 0; i < N; i++)
	{
		scanf("%f%f", &a.r, &a.i);//input complex numbers
		fprintf(f, "%.1f %.1f %.1f\n", a.r, a.i, CRadius(a));//print to file
	}

}
int CheckFile(FILE* f, float m)//fun get file and number and return the number of complex number bigger than m
{
	int i, counter = 0;
	float num;
	while (fscanf(f, "%f%f%f", &num, &num, &num) != EOF)//input radius from file
	{
		if (num > m)//check the condition
		{
			counter++;
		}
	}
	return counter;
}
void Error_Msg(char* str)
{
	printf("\n%s", str);
	exit(1);
}
#endif // X

////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define x
#ifdef x2
void set_2d(float** a, int m, int n);//prototypes
void print_2d(float** a, int m, int n);
int main()
{
    int m, n, i;
    float** a;
    printf("enter m and n, for m*n array: \n");
    scanf("%d %d", &m, &n);
    a = (float**)malloc(m* sizeof(float*));//dynamic allocation for a
    if (a == NULL)//check dynamic allocation succeed
    {
        printf("Not enough memory");
        exit(1);
    }
    for (i = 0; i < m; i++)//dynamic allocation for all a[i]
    {
        a[i] = (float*)malloc(n * sizeof(float));
    }
    set_2d(a, m, n);
    print_2d(a, m, n);
    for (i = 0; i < m; i++)//free all dynamic allocation
    {
        free(a[i]);
    }
    free(a);
	return 0;
}
void set_2d(float** a, int m, int n) //fun get a and his size and make his origins 1 2 3...
{
    int i, j, k = 1;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            a[i][j] = k++;
}
void print_2d(float** a, int m, int n)//fun get a and his size and print him
{
    int i, j,counter=0;//counter to know when get line down
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
        {
            if (counter % n == 0)
            {
                printf("\n");   
            }
            counter++;
            printf("%8.1f", a[i][j]);
        }
            
}
   


#endif // x

/////////////

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define x
#define numElems 7
char* findMin(char** arrP, int arrSize);//prototype
#ifdef x
int main()
{
	char* a[] = { "Amos","Nir","Alona","Yosef","alice","Amina","bob" };
	int i;
	for (i = 0; i < numElems; i++)//print the a origins
		printf("%s\n", a[i]);
	printf("\n%s", findMin(a, numElems));//print and call findMin
	return 0;
}
char* findMin(char** arrP, int arrSize)//fun get arrP and his size and return the min origin
{
	int i,minindex=0;
	char minstr[20] = { 0 };
	strcpy(minstr, arrP[0]);//copy to minstr the arrP[0] 
	for ( i = 1; i < arrSize; i++) //run on size and  compare every origin to minstr and if he smaller he swap them and save the index
	{
		if (strcmp(arrP[i], minstr) < 0)
		{
			strcpy(minstr, arrP[i]);
			minindex = i;
		}	
	}
	return arrP[minindex];
}
#endif // x

///////////
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define x
#ifdef x2
float func1(int a);//prototypes
float func2(int a);
double sum_square(int m, int n, float(*f)(int a));
int main()
{
	
	printf("The sum of func2: %.5lf\n", sum_square(2, 13,func2 ));//print and call sum_square
	printf("The sum of func1: %.5lf\n ", sum_square(1, 10000, func1));

	return 0;
}
float func1(int a)
{
	return 1.0 / a;
}
float func2(int a)
{
	return a/ 5.0;
}
double sum_square(int m, int n, float(*f)(int a))
{
	int i;
	double sum = 0;
	for (i = m; i <= n; i++)//run frim m to n and do calc by func1 or func2
	{
		sum += pow(f(i),2);
	}
	return sum;

}
#endif // x



/////////////

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define x
#define N 5
typedef  enum { FALSE, TRUE } BOOL;
BOOL Int_Sum(void*, void*, void*);//prototypes
BOOL Float_Sum(void*, void*, void*);
BOOL Sum(BOOL(*f)(void*, void*, void*), void** p_num, void* number);
#ifdef x
int main()
{
	int num[] = { 3,5,23,5,6 }, i, value;
	float  fnum[] = { 3.5,5.0,2.3,5.8,6.2 }, fvalue;
	void* p_num[N];
	for ( i = 0; i < N; i++)//put in p_num the adresses of all num numbers
	{
		p_num[i] = &num[i];
	}
	printf("Please enter an integer number ");
	scanf("%d", &value);
	if (Sum(Int_Sum,p_num,&value) == TRUE)
		printf("There is such sum\n");
	else
		printf("There is no such sum\n");
	for (i = 0; i < N; i++)//put in p_num the adresses of all fnum numbers
	{
		p_num[i] = &fnum[i];
	}
	printf("\nPlease enter a float number ");
	scanf("%f", &fvalue);
	if (Sum(Float_Sum, p_num, &fvalue) == TRUE)
		printf("There is such sum\n");
	else
		printf("There is no such sum\n");
	return 0;

}
BOOL Int_Sum(void* a, void* b, void* c)//fun that check the condition for int
{
	if (*(int*)a + *(int*)b == *(int*)c)
		return TRUE;
	return FALSE;
}
BOOL Float_Sum(void* a, void* b, void* c)//fun that check the condition for float
{
	if (*(float*)a + *(float*)b == *(float*)c)
		return TRUE;
	return FALSE;
}
BOOL Sum(BOOL(*f)(void*, void*, void*), void** p_num, void* number)//fun that get pointer for fun, array of addresses and pointer to number and check the condition
{
	int i,j, flag=0;
	for (i = 0; i < N; i++)//run on all orgins in array and check the condition
	{
		for ( j = 0; j < N; j++)
		{
			if (f(p_num[i], p_num[j], number) == TRUE && i != j)
			{
				flag = 1;
				break;
			}
			
		}
		if (flag == 1)
			break;
	}
	if (flag == 1)
		return TRUE;
	return FALSE;
}

#endif // x


//////////////////

#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#define X
#ifdef X2
typedef struct point //define struct point
{
	double x;
	double y;

}point;
typedef struct circle //define struct circle
{
	point o;
	double r;
}circle;
int in_circle(point z, circle t); //prototype
int main()
{
	point z; //define variables
	circle t;
	printf("Enter the coordinates of your point:"); //inputs
	scanf("%lf%lf", &z.x, &z.y); 
	printf("Enter the radius and the center of your circle:");
	scanf("%lf%lf%lf", &t.r, &t.o.x, &t.o.y);
	if (in_circle(z, t) == 1)//call in_circle and print message
		printf("The point is included in the circle");
	else
		printf("The point is not included in the circle");
	return 0;
}
int in_circle(point z, circle t)//fun get point and circle and return if the point in the circle 
{
	double dist;
	dist = sqrt(pow((z.x - t.o.x), 2) + pow((z.y - t.o.y), 2)); //calc distance
	if (dist < t.r)//check if the point in the circle
		return 1;
	return 0;
}
#endif // X
//////////////////

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define x2
typedef struct stud //define student struct
{
    char* name;
    int marks[4];
    float avg;
}student;

/*functions declaration*/
student* Create_Class(int size);
void Print_One(student*);
void Avg_Mark(student*);

#ifdef x3
int main()
{
    int size, i;
    student* arr;
    printf("Enter the number of students:");
    scanf("%d", &size);
    arr = Create_Class(size);//call Create_Class fun
    for (i = 0; i < size; i++)//run on arr and print all students with avg above 85 using Print_One
    {
        if (arr[i].avg > 85)
            Print_One(&arr[i]);
    }
    for (i = 0; i < size; i++)//free all dynamic allocation
    {
        free(arr[i].name);
    }
    free(arr);
    return 0;
}
void Print_One(student* arr)//fun get pointer to student in arr and prints his name and his avg
{
    printf("\nThe average of %s is %.1f", arr->name, arr->avg);
}
void Avg_Mark(student* arr)//fun get pointer to student and calc his avg and update the arr
{
    float sum = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        sum += arr->marks[i];
    }
    arr->avg = sum / 4;

}
student* Create_Class(int size)//fun get size of arr and create and return him
{
    int i;
    char name[50];//name for help dynamic allocation later
    student* arr;
    arr = (student*)malloc(size * sizeof(student));//dynamic allocation for arr
    if (arr == NULL)//check dynamic allocation succeed
    {
        printf("Not enough memory");
        exit(1);
    }

    for (i = 0; i < size; i++)//run on arr
    {
        printf("Enter your name: ");
        scanf("%s", name);//input name
        arr[i].name = (char*)malloc((strlen(name)) + 1);//dynamic allocation for name in arr 
        if ((arr[i].name) == NULL)//check dynamic allocation succeed
        {
            printf("Not enough memory");
            free(arr);//if we didint succeed free arr
            exit(1);
        }
        strcpy(arr[i].name, name);//copy name to arr
        printf("Enter your marks: ");//input matks
        scanf("%d%d%d%d", &arr[i].marks[0], &arr[i].marks[1], &arr[i].marks[2], &arr[i].marks[3]);
        Avg_Mark(&arr[i]);//update avg using Avg_Mark
    }

    return arr;
}
#endif // x
//////////////////

#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#define NUM 3//define NUM for number of complex number 
#define x
#ifdef x2
typedef struct Complex //define struct Complex
{
	double r;
	double i;
}Complex;
double CRadius(Complex num);//prototypes
Complex* Cmax(Complex arr[]);
int main()
{
	Complex arr[NUM],*max;//define arr of Complex and max for save pointer for the max complex number
	int i,counter=0;
	printf("Enter %d complex numbers:\n",NUM);//input NUM complex nuber into arr
	for (i = 0; i < NUM; i++)
	{
		scanf("%lf%lf", &arr[i].r, &arr[i].i);
		if (arr[i].r == 0 && arr[i].i == 0)//check that the input not all zero
			counter++;
	}
	if (counter == NUM)
	{
		printf("all numbers are zero!, please enter at least one number that not zero");
		exit(1);
	}
	max = Cmax(arr);//call Cmax and save in max the address of maximum complex number
	printf("The max complex number is %.2lf+%.2lfi\n", max->r, max->i);
	printf("The radius of the max number is %.2lf", CRadius(*max));
	return 0;
}
double CRadius(Complex num)//fun get Complex number and return his radius
{
	double radius;
	radius = sqrt(pow(num.r, 2) + pow(num.i, 2));
	return radius;
}
Complex* Cmax(Complex arr[]) // fun get Complex array and return address of maximum complex number
{
	int maxr=CRadius(arr[0]); //maxr save radius of first complex number in the array
	int i,imax;//save the index of maximun complex number in the array
	for (i = 1; i < sizeof(arr)-1; i++)
	{
		if (CRadius(arr[i]) > maxr)//check every number
		{
			maxr = CRadius(arr[i]);
			imax=i; //save the index
		}
	}
	return &arr[imax];//return the address of maximum complex number
}
#endif // x
////////////////////
#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#define N 5 //define N for row
#define M 4 //define N for col
#define x
#ifdef x2
double average(int Matrix[][M], int Rows, int Cols, int r, int c); //prototypes
int is_legal(int Rows, int Cols, int r, int c);
int main()
{
	int inedxr,indexc,r,c, arr[N][M] = { {11,12,13,14},{0,-7,18,7},{1,2,-1,-2},{6,-9,-19,9},{300,149,267,10} }; //create arr 
	double avg;
	printf("Enter index in the matrix: ");
	scanf("%d%d", &r, &c);
	if (r < 0 || r>4 || c < 0 || c>3)//check input is in matrix
	{
		printf("invalid index the matrix is 5x4");
		exit(1);
	}    
	avg = average(arr, N, M, r, c);//call average and save the average of the neighbors in avg
	printf("The average neighbors of cell (%d,%d) is: %.2lf", r, c, avg);//print the result for required option
	return 0;
}
double average(int Matrix[][M], int Rows, int Cols, int r, int c)//fun get matrix her nubers of row and cols and an index in the matrix
{
	int i, j, sum = 0, count = 0; //define variables: count and sum for calc the avg
	for (i = r - 1; i <= r + 1; i++)// run one row before and after the index 
	{
		for (j = c - 1; j <= c + 1; j++)// run one col before and after the index 
		{
			if (is_legal(Rows, Cols, i, j) == 1)//by is_legal check that the index is valid
			{
				if (i == r && j == c)//skip in the calc the index himself
					continue;
				else
					sum += Matrix[i][j];
				count++;
			}
		}
	}
	return (double)sum / count;//return average
}
int is_legal(int Rows, int Cols, int r, int c)//fun get number of rows and cols in matrix and index and return if the index is valid
{
	if (r < 0 || r >= Rows || c < 0 || c >= Cols)
	{
		return 0;
	}
	return 1;
}
#endif // x2
//////////////////

#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#include <stdlib.h>
#define x
#ifdef x2
double* inputArithmetic(double* a1, double* d, int* n); //prototypes
double setArithmetic(double a1, double d, double* arr, int n);
int main()
{
	double a1, d,*arr,sum; //define variables
	int n,i,counter=0; //counter for for get down a line in the print
	arr = inputArithmetic(&a1, &d, &n); //call inputArithmetic
	while (n > 0)
	{
		sum = setArithmetic(a1, d, arr, n); //call setArithmetic and save the sum
		for (i = 0; i < n; i++)
		{
			if (counter % 5 == 0)//after 5 prints get down a line
				printf("\n");
			printf("%10lf  ", arr[i]);
			counter++;
		}
		printf("\nThe sum of the sequence is: %lf", sum);
		free(arr);
		counter = 0;
		printf("\n");
		arr = inputArithmetic(&a1, &d, &n);//input new arr
	}
	printf("Thank you for exploring arithmetic sequences and dynamic allocations of arrays");
	return 0;
}
double* inputArithmetic(double* a1, double* d, int* n)//fun get pointers for a1 d and n, take input for them and make dynamic allocation and return the adress 
{
	double* arr;
	printf("Enter a1, d, and n respectively, please: ");
	scanf("%lf%lf%d", a1, d, n); //take input
	if (*n <= 0)
		return NULL;
	arr = (double*)malloc(*n * sizeof(double));//make dynamic allocation for arr
	if (arr == NULL) //check dynamic allocation succeed 
	{
		printf("The allocation didint succeed, please try again");
		exit(1);
	}
	return arr;
}
double setArithmetic(double a1, double d, double* arr, int n)//fun get a1 d arr and n and fill arr and rrturn the sum
{
	double sum = a1;
	int i;
	arr[0] = a1;
	for (i = 1; i < n; i++)
	{
		arr[i] = arr[i - 1] + d;
		sum += arr[i];
	}
	return sum;
}
#endif // x
/////////////
#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#define Length 10 // define length to be 10
#define x
#ifdef x2
double avg(double arr[], int len);
int main()
{
	int k, i, sum = 0; // set the int's
	double arr[Length], average; //set the arr with length 10 and average as double values
	printf("Enter times, please: ");
	for (k = 0; k < Length; k++)// scan 10 results of runners
	{
		scanf("%lf", &arr[k]);
	}
	average = avg(arr, Length);// set the average by calling to function average
	for (i = 0; i < Length; i++)// runing over all the reuslts
	{
		if (arr[i] < average)// if the result lower then avg
		{
			sum++;//add for sum 1
		}
	}
	printf("The number of runners, running below the average time is %d.", sum);
	return 0;//defult return for main function
}
double avg(double arr[], int len)
{
	int i;
	double sum = 0;
	for (i = 0; i < len; i++)//runing over the array
	{
		sum += arr[i];//make a some of all the results
	}
	return (sum / len);// return the average
}
#endif // x
/////////////

#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
#include <time.h>
#define N 7
#define x
#ifdef x2
int first_index(int arr1[], int arr2[], int len);
void print_array(int arr[]);
int main()
{
	int arr1[N], arr2[N], i, j, maxval, index;
	for (i = 0; i < N; i++)// runing over 0 until 7
	{
		printf("Enter arr[%d]: ", i);
		scanf("%d", &arr1[i]);// user enter values to arr1
	}
	printf("Enter max value greater than zero: ");
	do
	{
		scanf("%d", &maxval);//user enter max
		if (maxval <= 0)//if the input <= 0 (the max)
		{
			printf("input invalid, try again please: ");
		}
	} while (maxval <= 0);
	srand(time(NULL));// initialization random for the debugger
	for (j = 0; j < N; j++)
	{
		arr2[j] = (rand() % maxval) + 1;//set arr2 in j place as  random value (+1 to be more than zero)
	}
	printf("Array 1: ");
	print_array(arr1);
	printf("Array 2: ");
	print_array(arr2);
	index = first_index(arr1, arr2, N);//set index to be the result by calling first_index function
	if (index != -1)// if the index returned from the function not equal -1
		printf("The index is %d(numbers %d and %d)", index, arr1[index], arr2[index]);
	else//if it is -1
		printf("No!!!");
	return 0;
}
int first_index(int arr1[], int arr2[], int len)
{
	int i, index = -1;
	for (i = 0; i < N; i++)
	{
		if (arr1[i] > arr2[i])// if the value of arr1 in index i bigger than the value of arr2 in index i
		{
			index = i;//set the index to be i
			break;
		}
	}
	return index;
}
void print_array(int arr[])
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%d ", arr[i]);//printing each value of the arr
	}
	printf("\n");
}
#endif // x
//////////////////


#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#include <string.h>
#define Len 100 //define max len for input
#define x
#ifdef x2
void replaceSubstring(char* str, char* substr); //prototypes
int main()
{
	char str[Len], substr[Len];
	printf("Enter text: "); //take input
	fgets(str, Len, stdin);
	if (str[0] == '\n')//finish if str is empty
	{
		printf("finish");
		exit(1);
	}
	printf("Enter substring: ");
	fgets(substr, Len, stdin);
	if (str[strlen(str) - 1] == '\n') //remove \n from the end of the string
		str[strlen(str) - 1] = '\0';
	if (substr[strlen(substr) - 1] == '\n')
		substr[strlen(substr) - 1] = '\0';
	while (*str != '\0' && *substr != '\0') //keep take input until one of the strings empty
	{
		replaceSubstring(str, substr);
		printf("%s\n", str);
		printf("Enter text: ");
		fgets(str, Len, stdin);
		if (str[0] == '\n')//finish if str is empty
			break;
		printf("Enter substring: ");
		fgets(substr, Len, stdin);
		if (str[strlen(str) - 1] == '\n')
			str[strlen(str) - 1] = '\0';
		if (substr[strlen(substr) - 1] == '\n')
			substr[strlen(substr) - 1] = '\0';
	}
	printf("finish");


	

	return 0;
}
void replaceSubstring(char* str, char* substr)//fun get str and substr and replace in the str all substr with big letters
{

	int i, j, k, index, sum = 0, subin; //define variables: i,j,k for the fors, index save the index where str[i]==substr[0], sum checks that all letter in str equals to substr, subin take care to take substr to begging
	for (i = 0; i < strlen(str); i++) //run in len if str
	{
		if (str[i] == substr[0]) //checks if str[i] == substr[0]
		{
			index = i;
			subin = 0;
			for (j = i; j < strlen(substr) + i; j++) //continue checking that every letter in substr equals to acorrding letter in str
			{
				if (str[j] == substr[subin])
				{
					sum++;
					subin++;
				}
			}
			if (sum == strlen(substr)) //check that all the letters wsa equals 
			{
				for (k = 0; k < strlen(substr); k++)//run on len of substr
				{
					if (str[index] >= 'a' && str[index] <= 'z')//if it small letter it becomes a upper letter
						str[index] -= 32;
					index++;
				}
			}

		}
		sum = 0;
	}

}
#endif // x


/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
void replaceSubstring(char* str, char* subStr);
void main()
{
	char str[N], substr[N];
	printf("Enter text: "); //take input
	fgets(str, 100, stdin);
	printf("Enter substring: ");
	fgets(substr, N, stdin);
	if (str[strlen(str) - 1] == '\n') //remove \n from the end of the string
		str[strlen(str) - 1] = '\0';
	if (substr[strlen(substr) - 1] == '\n')
		substr[strlen(substr) - 1] = '\0';
	while (*str != '\0' && *substr != '\0') //keep take input until one of the strings empty
	{
		replaceSubstring(str, substr);
		printf("%s\n", str);
		printf("Enter text: ");
		fgets(str, N, stdin);
		printf("Enter substring: ");
		fgets(substr, N, stdin);
		if (str[strlen(str) - 1] == '\n')
			str[strlen(str) - 1] = '\0';
		if (substr[strlen(substr) - 1] == '\n')
			substr[strlen(substr) - 1] = '\0';
	}
	printf("finish");
}

void replaceSubstring(char* str, char* SubStr)
{
	int  i, j, upper = 0;
	char* tmp;
	for (j = 0; j < strlen(str); j++)
	{
		if (str[j] >= 'a' && str[j] <= 'z')
		{
			upper = 1;
		}
	}

	while ((tmp = strstr(str, SubStr)) != NULL && upper == 1)
	{
		for (i = 0; i < strlen(SubStr); i++)
		{
			tmp[i] -= 32;
		}
	}
}
*/
/////////////////

#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#define x
#ifdef x2
void Set_Mid(double x1, double y1, double x2, double y2, double* p_midx, double* p_midy); //prototypes
int main()
{
	double midx, midy, x1, y1, x2, y2; //define variables
	printf("Enter first coordinate (x,y): ");
	scanf("%lf%lf", &x1, &y1); //take input for first coordinate 
	printf("Enter second coordinate (x,y): ");
	scanf("%lf%lf", &x2, &y2); //take input for second coordinate 
	Set_Mid(x1, y1, x2, y2, &midx, &midy); //call for Set_Mid
	printf("The middle coordinate is: (%.3lf,%.3lf)", midx, midy); //print the middle coordinate

	return 0;
}
void Set_Mid(double x1, double y1, double x2, double y2, double* p_midx, double* p_midy)//function that get two coordinates and calc the middle coordinate
{
	*p_midx = (x1 + x2) / 2;
	*p_midy = (y1 + y2) / 2;
}
#endif // x

//////////////

#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#define x
#ifdef x2
int InputThree(int* p1, int* p2, int* p3); //prototypes
void SortTwo(int* p1, int* p2);
void SortThree(int* q1, int* q2, int* q3);
int main()
{
	int p1, p2, p3; //define variables
	while (InputThree(&p1, &p2, &p3) == 1) //call InputThree and run while the input is proper
	{
		SortThree(&p1, &p2, &p3); //call SortThree
		printf("Sorted values:%d, %d, %d \n", p1, p2, p3); //print variables after short
	}
	printf("Finish");
	return 0;
}
int InputThree(int* p1, int* p2, int* p3) //function that take input for all three variables and make sure the input is valid 
{
	printf("Input three integers values: ");
	if (scanf("%d%d%d", p1, p2, p3) != 3)
	{
		return 0;
	}
	return 1;
}
void SortTwo(int* p1, int* p2) //function that short two variables 
{
	int temp;
	if (*p1 > *p2)
	{
		temp = *p1;
		*p1 = *p2;
		*p2 = temp;
	}
}
void SortThree(int* q1, int* q2, int* q3) //function that short three variables using SortTwo
{
	SortTwo(q1, q2);
	SortTwo(q1, q3);
	SortTwo(q2, q3);
}

#endif // x
/////////////

#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#define X
#ifdef X2
int main()
{
	int weight, height; //define variables as int
	float bmi, meter; //define variables as float
	printf("Please enter weight (in kg) and height (in cm), respectively: "); //print message
	scanf("%d%d", &weight, &height);//input weight and height
	meter = ((float)height) / 100; // convert height to meter
	bmi = weight / pow(meter, 2); // calc bmi
	if (bmi < 18.5) //check bmi and print message
		printf("Underweight");
	else if (bmi >= 18.5 && bmi < 25)
		printf("Normal weight");
	else if (bmi >= 25 && bmi < 30)
		printf("Increased weight");
	else if (bmi >= 30 && bmi < 40)
		printf("Obese");
	else
		printf("Very high obese");

	return 0;
}
#endif // !1


////

#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#define X
#ifdef X1
int main()
{
	int num, i, count = 0; //define variables as int
	printf("Enter an integer number, please: "); //print message
	scanf("%d", &num); //input num
	if (num == 0) //check if num is 0 and print message
	{
		printf("Infinity");
		return;
	}
	if (num < 0) //check if num is <0 and print message
	{
		num = num * -1;
		for (i = 1; i <= num; i++)
		{
			if (num % i == 0)
			{
				printf("%d ", i);
				count++;
			}
		}
	}
	else // num is >0 and print message
	{
		for (i = 1; i < num; i++)
		{
			if (num % i == 0)
			{
				printf("%d ", i);
				count++;
			}
		}

	}
	printf("\ncount=%d", count); //print count
	return 0;
}

#endif // X

////
#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#define X1
void triangle(char a, int num) //fun that print triangle
{
	int i, g, snum; //define variables as int
	snum = num; //snum save num
	for (i = 0; i < num; i++) //print triangle
	{
		for (g = 0; g < snum; g++)
		{
			printf("%c", a);
		}
		snum -= 1;
		printf("\n");
	}
}
#ifdef X
int main()
{
	char letter;
	int num;
	printf("Enter a character and an integer, please: "); //print message
	scanf("%c%d", &letter, &num); //input num and letter
	triangle(letter, num); //call triangle
	return 0;
}

#endif // X

//////

#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <math.h>
#define X
#ifdef X1
int main()
{
	char a; //define variables
	int num1, num2, i;
	float avg, pow;
	printf("please enter charcter: "); //print message
	scanf("%c", &a); //input a
	while (a != 'q' && a != 'Q')
	{
		switch (a) //check cases on a
		{
		case'a':case'A': //case for average
		{
			printf("Enter 2 integers, please: ");
			scanf("%d%d", &num1, &num2);
			avg = ((float)num1 + num2) / 2;
			printf("the average of %d and %d is: %.2f\n", num1, num2, avg);
			break;
		}
		case'*': // case for multiply
		{
			printf("Enter 2 integers, please: ");
			scanf("%d%d", &num1, &num2);
			printf("the multiply of %d and %d is: %d\n", num1, num2, num1 * num2);
			break;
		}
		case'm': //case for minimum
		{
			printf("Enter 2 integers, please: ");
			scanf("%d%d", &num1, &num2);
			if (num1 > num2)
			{
				printf("the minimum number between %d and %d is: %d\n", num1, num2, num2);
			}
			else
				printf("the minimum number between %d and %d is: %d\n", num1, num2, num1);
			break;
		}
		case'M': //case for maximum
		{
			printf("Enter 2 integers, please: ");
			scanf("%d%d", &num1, &num2);
			if (num1 > num2)
			{
				printf("the maximum number between %d and %d is %d\n", num1, num2, num1);
			}
			else
				printf("the maximum number between %d and %d is %d\n", num1, num2, num2);
			break;
		}
		case'^': //case for power
			printf("Enter 2 integers first base second exponent, please: ");
			scanf("%d%d", &num1, &num2);
			if (num1 == 0 && num2 < 0) //check divide by 0
			{
				printf("check your input, cant divide by 0!\n");
				break;
			}
			else if (num2 > 0) //calc if the exponent is positive
			{
				pow = 1;
				for (i = 0; i < num2; i++)
				{
					pow *= num1;
				}
			}
			else //calc if the exponent is negitave
			{
				pow = 1;
				num2 = num2 * -1;
				for (i = 0; i < num2; i++)
				{
					pow *= num1;
				}
				pow = 1 / pow;
			}
			printf("The power of base %d in exponent %d is %g\n", num1, num2, pow);
			break;
		default:
			printf("error\n");
			break;

		}
		rewind(stdin); //clean the buffer
		printf("please enter charcter: "); ////print message for another input
		scanf("%c", &a);

	}
	printf("finish");
	return 0;
}

#endif // X
