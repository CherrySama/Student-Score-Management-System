#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CourseMaxNumber 6
#define NameMaxLen 10

typedef struct student {
    int id;
    char name[NameMaxLen];
    float scores[CourseMaxNumber];
    float sum;    //�Ժ��õ���͵ĵط��ǳ���
    struct student *next;
} STUDENT;


void PrintMenu();

void PrintList(STUDENT *head, int *couAmount);

STUDENT *InputRecord(STUDENT *head, int *stuAmount, int *couAmount);

STUDENT *DeleteRecord(STUDENT *head);

STUDENT *PushRecord(STUDENT *head, int *stuAmount, int *couAmount);

void PrintSum(STUDENT *head, int *couAmount);

void PrintAverage(STUDENT *head, int *stuAmount, int *couAmount);

void SortScore(STUDENT *head,int *stuAmount,int *couAmount,int (*compare)(float a, float b));

int Ascending(float a, float b);

int Descending(float a, float b);

void SortId(STUDENT *head,int *stuAmount,int *couAmount,int (*compare)(float a, float b));

void SortName(STUDENT *head,int *stuAmount,int *couAmount);

void SearchId(STUDENT *head,int *couAmount);

void SearchName(STUDENT *head,int *couAmount);

void StatisticAnalysis(STUDENT *head,int *couAmount,int *stuAmount);

int main() {
    int stuAmount = 0, couAmount = 0, i = 0, n = 0, Selection;
    STUDENT *head = NULL;

    printf("Welcome to Student Scores Management System V5!\n");
    printf("By XiaZhen\n");
    printf("---------------------------------------------\n");

    do {
        PrintMenu();
        scanf("%d", &Selection);
		system("cls");  //�����Ļ
        switch (Selection) {
            case 0:
                exit(0);
            case 1:
                head = InputRecord(head, &stuAmount, &couAmount);
                break;
            case 2:
                head = DeleteRecord(head);
                break;
            case 3:
                head = PushRecord(head, &stuAmount, &couAmount);
                break;
            case 4:
                PrintSum(head, &couAmount);
                PrintAverage(head, &stuAmount, &couAmount);
                break;
            case 5:
                SortScore(head,&stuAmount,&couAmount,Descending);
                PrintList(head, &couAmount);
                break;
            case 6:
                SortScore(head,&stuAmount,&couAmount,Ascending);
                PrintList(head, &couAmount);
                break;
            case 7:
                SortId(head,&stuAmount,&couAmount,Descending);
                PrintList(head, &couAmount);
                break;
            case 8:
                SortName(head,&stuAmount,&couAmount);
                PrintList(head, &couAmount);
                break;
            case 9:
                SortScore(head,&stuAmount,&couAmount,Ascending);
                SearchId(head,&couAmount);
                break;
            case 10:
                SortScore(head,&stuAmount,&couAmount,Ascending);
                SearchName(head,&couAmount);
                break;
            case 11:
                StatisticAnalysis(head,&couAmount,&stuAmount);
                break;
            case 12:
                SortId(head,&stuAmount,&couAmount,Descending);
                printf("\n-- Score List\n");
                PrintList(head, &couAmount);
                PrintSum(head, &couAmount);
                PrintAverage(head, &stuAmount, &couAmount);
                printf("\n-- TOTAL:%d\n", stuAmount);
                printf("\n-- END\n");
                break;
            default:
                printf("\n\n-- Sorry!Please input 0-12!\n");
        };
    } while (Selection != 0);

}

//���ܣ�����˵�
//��Σ���
//���Σ���
void PrintMenu() {
    printf("\n");
	printf("||Menu:\n");
    printf("|1.Input records from beginning\n");
    printf("|2.Delete a record ��\n");
    printf("|3.Push a record ��\n");
    printf("|4.Calculate total and average score of course\n");
    printf("|5.Sort in descending order by score\n");
    printf("|6.Sort in ascending order by score\n");
    printf("|7.Sort in ascending order by number\n");
    printf("|8.Sort in dictionary order by name\n");
    printf("|9.Search by number\n");
    printf("|10.Search by name\n");
    printf("|11.Statistic analysis\n");
    printf("|12.List record\n");
    printf("|0.Exit\n");
    printf("|Please input 0-12 to select function :");
}

//���ܣ�����ɼ��б�
//��Σ������׵�ַ���γ�����
//���Σ���
void PrintList(STUDENT *head, int *couAmount) {
    int m;
    STUDENT *p1 = head;

    printf("\n");
    while (p1 != NULL) {
        printf("%d  ", p1->id);
        fputs(p1->name, stdout);   //puts�����ַ���ĩβ�Զ�����\n fputs����
        for (m = 0; m < *couAmount; m++) {
            printf("  %.1f  ", *(p1->scores + m));
        }
        printf("TOTAL:%.1f\n", p1->sum);
        p1 = p1->next;
    }

}

//���ܣ������������Ļس�ɾ��
//��Σ����������ַ
//���Σ���
void alter(STUDENT *head) {
    int m;
    STUDENT *p1 = head;

    while (p1 != NULL) {
        for (m = 0; m < NameMaxLen; m++) {
            if (*((p1->name) + m) == '\n') {
                *((p1->name) + m) = '\0';
            }
        }
        p1 = p1->next;
    }
}

//���ܣ�����ÿ��ѧ�����ܷ�
//��Σ������׵�ַ���γ�����
//���Σ���
void SumScores(STUDENT *head, int *couAmount) {
    int m;
    float SumTemp;
    STUDENT *p1 = head;

    while (p1 != NULL) {
        SumTemp = 0;
        for (m = 0; m < *couAmount; m++) {
            SumTemp += *(p1->scores + m);
        }
        p1->sum = SumTemp;
        p1 = p1->next;
    }
}

//���ܣ���ͷ����ɼ�
//��Σ������׵�ַ��ѧ���������γ�����
//���Σ������׵�ַ
STUDENT *InputRecord(STUDENT *head, int *stuAmount, int *couAmount) {
    int i = 0,m = 0;
    char inputchar;
    STUDENT *p1;
    printf("\n-- Start to Input Record from beginning\n");
    if (*couAmount == 0) {   //��PushRecord��couAmount�����ѱ���ֵ
        printf("\n-- Please input the number of courses:");
        scanf("%d", couAmount);
        if (*couAmount > CourseMaxNumber) {
            printf("\n-- Sorry! The max of courses amount is 6!:");
            *couAmount = 6;
        }
    }
    *stuAmount = 1;
    head = malloc(sizeof(STUDENT));
    p1 = head;
    do {
        printf("Input NO.%d student`s ID:", i + 1);
        scanf("%d", &(p1->id));
        printf("Input NO.%d student`s Name:", i + 1);
        getchar();
        fgets(p1->name, NameMaxLen + 1, stdin);
        printf("Input NO.%d student`s Scores:\n", i + 1);
        for (m = 0; m < *couAmount; m++) {
            printf("- Input NO.%d student`s NO.%d Course Score:", i + 1, m + 1);
            scanf("%f", p1->scores + m);
        }
        printf("Do you want to continue?(Y/N)");
        scanf(" %c", &inputchar);
        if (inputchar == 'Y' || inputchar == 'y') {  //ֱ����getchar���������дY���ܼ���
            p1->next = malloc(sizeof(STUDENT));
            p1 = p1->next;
            *stuAmount += 1;
            i++;
        } else {
            break;
        }
    } while (1);
	p1->next = NULL;
    alter(head);
    SumScores(head, couAmount);
    printf("\n-- Input Record is over. %d student(s) have saved.\n", *stuAmount);
    return head;
}

//���ܣ�ɾ���ɼ���ͨ��ѧ�ţ�
//��Σ������׵�ַ
//���Σ������׵�ַ

STUDENT *DeleteRecord(STUDENT *head) {
    int inputid;
    STUDENT *p1 = head, *p2;

    printf("\n-- Please input the id you want to delete:");
    scanf("%d", &inputid);
    while (p1 != NULL && p1->id != inputid) {
        p2 = p1;         //p2��һ���ڵ�
        p1 = p1->next;   //p1��һ���ڵ�
    }

    if (p1 == head) {
        head = p1->next;
        free(p1);
        printf("\n-- Success!\n");
    } else if (p1 != NULL) {
        p2->next = p1->next;
        free(p1);
        printf("\n-- Success!\n");
    } else {
        printf("\n-- Do not find this id!\n");
    }
    return head;
}

//���ܣ������µ�ѧ��
//��Σ������׵�ַ��ѧ���������γ�����
//���Σ������׵�ַ
STUDENT *PushRecord(STUDENT *head, int *stuAmount, int *couAmount) {
	int m;
    STUDENT *p1 = head, *input;
    input = malloc(sizeof(STUDENT));

    if (*couAmount == 0) {
        printf("\n-- Please input the number of courses:");
        scanf("%d", couAmount);
        if (*couAmount > CourseMaxNumber) {
            printf("\n-- Sorry! The max of courses amount is 6!:");
            *couAmount = 6;
        }
    }

    //����һ��������
    printf("\n-- Please input the id you want to insert :");
    scanf("%d", &(input->id));
    printf("Input student`s Name:");
    getchar();
    fgets(input->name, NameMaxLen + 1, stdin);
    printf("Input student`s Scores:\n");
    for (m = 0; m < *couAmount; m++) {
        printf("- Input student`s NO.%d Course Score:", m + 1);
        scanf("%f", input->scores + m);
    }
    input->next = NULL;  //Ĭ�Ϸ�����������
    *stuAmount += 1;

    //��������
    if (p1 == NULL) {
        head = input;
    } else {
        while (p1->next != NULL) {
            p1 = p1->next;
        }
        p1->next = input;
    }

    alter(head);
    SumScores(head, couAmount);
    printf("-- Success!\n");
    return head;
}

//���ܣ���ӡÿ�ſγ̵��ܷ�
//��Σ������׵�ַ���γ�����
//���Σ���
void PrintSum(STUDENT *head, int *couAmount) {
    int m;
    float sum = 0;
    STUDENT *p1 = head;
    if (head == NULL) {
        printf("\n-- Please input records first!\n");
        return;
    }
    printf("\n-- SUM:  ");
    for (m = 0; m < *couAmount; m++) {
        sum = 0;
        p1 = head;
        while (p1 != NULL) {
            sum += *(p1->scores + m);
            p1 = p1->next;
        }
        printf("  Course%d:%.2f  ", m + 1, sum);
    }
    printf("\n");
}

//���ܣ���ӡÿ�ſε�ƽ����
//��Σ������׵�ַ���γ�����
//���Σ���
void PrintAverage(STUDENT *head, int *stuAmount, int *couAmount) {
    int m;
    float sum = 0, average = 0;
    STUDENT *p1 = head;
    if (head == NULL) {
        printf("\n-- Please input records first!\n");
        return;
    }
    printf("\n-- AVERAGE:  ");
    for (m = 0; m < *couAmount; m++) {
        sum = 0;
        p1 = head;
        while (p1 != NULL) {
            sum += *(p1->scores + m);
            p1 = p1->next;
        }
        average = sum / *stuAmount;
        printf("  Course%d:%.2f  ", m + 1, average);
    }
    printf("\n");
}

//���ܣ���������
//��Σ�����ָ��1������ָ��2����Ŀ����
//���Σ���
void swap(STUDENT *p1, STUDENT *p2, int *couAmount) {
    int tempInt = 0,m;
    float tempFloat = 0;
    char tempName[NameMaxLen];

    tempInt = p2->id;
    p2->id = p1->id;
    p1->id = tempInt;

    strcpy(tempName, p2->name);
    strcpy(p2->name, p1->name);
    strcpy(p1->name, tempName);

    for (m = 0; m < *couAmount; m++) {
        tempFloat = *(p2->scores+m);
        *(p2->scores+m) = *(p1->scores+m);
        *(p1->scores+m) = tempFloat;
    }

    tempFloat = p2->sum;
    p2->sum = p1->sum;
    p1->sum = tempFloat;
}

//���ܣ�����ɼ�
//��Σ������׵�ַ��ѧ���������γ�������˳����ָ��
//���Σ���
void SortScore(STUDENT *head,int *stuAmount,int *couAmount,int (*compare)(float a, float b)) {
    int i=1,n=0;
    STUDENT *p1,*p2,*p3=head;

    if (head == NULL) {
        printf("\n-- Please input records first!\n");
        return;
    }else if(head->next == NULL){ //ֻ��һ��Ԫ�� ֱ�ӷ���
        return;
    }

    while(p3!=NULL){    //ð������ֱ�ӽ����ṹ��data��
        p1 = head;
        for (n = 0; n < *stuAmount-i; n++) {
            p2=p1;
            p1=p1->next;
            if((*compare)(p2->sum, p1->sum)){
                swap(p2,p1,couAmount);
            }
        }
        i++;
        p3 = p3->next;
    }
}

//���ܣ��ɴ�С����
//��Σ���������
//���Σ�1/0
int Ascending(float a, float b) {
    return a < b;
}

//���ܣ���С��������
//��Σ���������
//���Σ�1/0
int Descending(float a, float b) {
    return a > b;
}

//���ܣ�����ѧ��
//��Σ������׵�ַ��ѧ���������γ�������˳����ָ��
//���Σ���
void SortId(STUDENT *head,int *stuAmount,int *couAmount,int (*compare)(float a, float b)) {
    int i=1,n=0;
    STUDENT *p1,*p2,*p3=head;

    if (head == NULL) {
        printf("\n-- Please input records first!\n");
        return;
    }else if(head->next == NULL){ //ֻ��һ��Ԫ�� ֱ�ӷ���
        return;
    }

    while(p3!=NULL){    //ð������ֱ�ӽ����ṹ��data��
        p1 = head;
        for (n = 0; n < *stuAmount-i; n++) {
            p2=p1;
            p1=p1->next;
            if((*compare)(p2->id, p1->id)){
                swap(p2,p1,couAmount);
            }
        }
        i++;
        p3 = p3->next;
    }
}

//���ܣ���������
//��Σ������׵�ַ��ѧ���������γ�����
//���Σ���
void SortName(STUDENT *head,int *stuAmount,int *couAmount) {
    int i=1,n=0;
    STUDENT *p1,*p2,*p3=head;

    if (head == NULL) {
        printf("\n-- Please input records first!\n");
        return;
    }else if(head->next == NULL){
        return;
    }

    while(p3!=NULL){    //ð������ֱ�ӽ����ṹ��data��
        p1 = head;
        for (n = 0; n < *stuAmount-i; n++) {
            p2=p1;
            p1=p1->next;
            if(strcmp(p2->name,p1->name)>0){
                swap(p2,p1,couAmount);
            }
        }
        i++;
        p3 = p3->next;
    }
}

//���ܣ���ѧ����������ӡ�ɼ�������
//��Σ������׵�ַ,�γ�����
//���Σ���
void SearchId(STUDENT *head,int *couAmount){
    int i=0,m,inputId;
    STUDENT *p1=head;

    if (head == NULL) {
        printf("\n-- Please input records first!\n");
        return;
    }

    printf("\n-- Please input the id you want to search:");
    scanf("%d", &inputId);

    while (p1!=NULL && p1->id!=inputId){
        i++;
        p1 = p1->next;
    }

    if(!p1){
        printf("\n-- Sorry!No result!\n");
        return;
    }else{
        printf("\n-- Rank: %d\n", i + 1);
        printf("-- %d  ", p1->id);
        fputs(p1->name, stdout);   //puts�����ַ���ĩβ�Զ�����\n fputs����
        for (m = 0; m < *couAmount; m++) {
            printf("  %.1f  ", *(p1->scores + m));
        }
        printf("TOTAL:%.1f\n", p1->sum);
    };
}


//���ܣ���������������ӡ�ɼ�������
//��Σ������׵�ַ,�γ�����
//���Σ���
void SearchName(STUDENT *head,int *couAmount){
    int i=0,m;
    char InputName[NameMaxLen];
    STUDENT *p1=head;

    if (head == NULL) {
        printf("\n-- Please input records first!\n");
        return;
    }

    getchar();
    printf("\n-- Please input the name you want to search:");
    fgets(InputName, NameMaxLen + 1, stdin);
    for (m = 0; m < NameMaxLen; m++) {
        if (*(InputName + m) == '\n') {
            *(InputName + m) = '\0';
        }
    }    //ɾ������ʱ�Ļس�

    while (p1!=NULL && strcmp(p1->name,InputName) != 0){
        i++;
        p1 = p1->next;
    }

    if(!p1){
        printf("\n-- Sorry!No result!\n");
        return;
    }else{
        printf("\n-- Rank: %d\n", i + 1);
        printf("-- %d  ", p1->id);
        fputs(p1->name, stdout);   //puts�����ַ���ĩβ�Զ�����\n fputs����
        for (m = 0; m < *couAmount; m++) {
            printf("  %.1f  ", *(p1->scores + m));
        }
        printf("TOTAL:%.1f\n", p1->sum);
    };
}

//���ܣ�������������ѧ��������ռ��
//��Σ�ѧ���������γ��������ɼ������ַ
//���Σ���
void StatisticAnalysis(STUDENT *head,int *couAmount,int *stuAmount) {
    int A = 0, B = 0, C = 0, D = 0, E = 0, m = 0, n = 0;
    STUDENT *p1=head;
    if (head == NULL) {
        printf("\n-- Please input records first!\n");
        return;
    }
    printf("\n-- Statistic Analysis:\n");
    for (m = 0; m < *couAmount; m++) {
        A = 0;
        B = 0;
        C = 0;
        D = 0;
        E = 0;
        p1 = head;
        while (p1 != NULL) {
            if (*(p1->scores+m) >= 90 && *(p1->scores + m) <= 100) {
                A += 1;
            } else if (*(p1->scores + m) >= 80) {
                B += 1;
            } else if (*(p1->scores + m) >= 70) {
                C += 1;
            } else if (*(p1->scores) + m >= 60) {
                D += 1;
            } else {
                E += 1;
            }
            p1 = p1->next;
        }
        printf("Course%d  ", m + 1);
        printf("A(100-90):%d(%.2f%%)  ", A, (float) A / (float) (*stuAmount) * 100);
        printf("B(89-80):%d(%.2f%%)  ", B, (float) B / (float) (*stuAmount) * 100);
        printf("C(79-70):%d(%.2f%%)  ", C, (float) C / (float) (*stuAmount) * 100);
        printf("D(69-60):%d(%.2f%%)  ", D, (float) D / (float) (*stuAmount) * 100);
        printf("E(59-0):%d(%.2f%%)\n", E, (float) E / (float) (*stuAmount) * 100);
    }
}

