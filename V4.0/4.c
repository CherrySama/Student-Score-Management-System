#include <stdio.h>
#include <string.h>

#define StuMaxNumber 30
#define CourseMaxNumber 6
#define NameMaxLen 10

void PrintMenu();

void PrintList(int *stuAmount, int *couAmount, int *sorts, int *id, char (*names)[NameMaxLen],
               float (*scores)[CourseMaxNumber], float *ScoresTotal);

void FormatSorts(int *sorts);

void SumScores(float (*score)[CourseMaxNumber], int *stuAmount, int *couAmount, float *ScoresTotal);

void InputRecord(float (*scores)[CourseMaxNumber], int *id, char (*names)[NameMaxLen], int *stuAmount, int *couAmount);

void PrintSum(float (*scores)[CourseMaxNumber], int *stuAmount, int *couAmount);

void PrintAverage(float (*scores)[CourseMaxNumber], int *stuAmount, int *couAmount);

void SortScore(int *sorts, float *ScoresTotal, int *stuAmount, int (*compare)(float a, float b));

int Ascending(float a, float b);

int Descending(float a, float b);

void SortId(int *id, int *sorts, int *stuAmount);

void SortName(char (*names)[NameMaxLen], int *sorts, int *stuAmount);

void SearchId(int *stuAmount, int *couAmount, int *sorts, int *id, char (*names)[NameMaxLen],
              float (*scores)[CourseMaxNumber], float *ScoresTotal);

void SearchName(int *stuAmount, int *couAmount, int *sorts, int *id, char (*names)[NameMaxLen],
                float (*scores)[CourseMaxNumber], float *ScoresTotal);

void StatisticAnalysis(int *stuAmount, int *couAmount, float (*scores)[CourseMaxNumber]);



int main() {
    int id[StuMaxNumber] = {0}, StudentsTotal = 0, CourseTotal = 0, i=0, n=0, Selection;
    int sorts[StuMaxNumber];   //һά���� ��������
    float scores[StuMaxNumber][CourseMaxNumber] = {0};  //�ɼ�����;�Ϊfloat
    float ScoresTotal[StuMaxNumber] = {0};
    char names[StuMaxNumber][NameMaxLen];


    printf("Welcome to Student Scores Management System V4!\n");
    printf("By XiaZhen\n");
    printf("---------------------------------------------\n\n");

    do {
        PrintMenu();
        scanf("%d", &Selection);
//		printf("\n%d\n",Selection);
        FormatSorts(sorts);
        switch (Selection) {
            case 0:
                break;
            case 1:
                InputRecord(scores, id, names, &StudentsTotal, &CourseTotal);
                SumScores(scores, &StudentsTotal, &CourseTotal, ScoresTotal);
                break;
            case 2:
                PrintSum(scores, &StudentsTotal, &CourseTotal);
                PrintAverage(scores, &StudentsTotal, &CourseTotal);
                break;
            case 3:
                SortScore(sorts, ScoresTotal, &StudentsTotal, Descending);
                PrintList(&StudentsTotal, &CourseTotal, sorts, id, names, scores, ScoresTotal);
                break;
            case 4:
                SortScore(sorts, ScoresTotal, &StudentsTotal, Ascending);
                PrintList(&StudentsTotal, &CourseTotal, sorts, id, names, scores, ScoresTotal);
                break;
            case 5:
                SortId(id, sorts, &StudentsTotal);
                PrintList(&StudentsTotal, &CourseTotal, sorts, id, names, scores, ScoresTotal);
                break;
            case 6:
                SortName(names, sorts, &StudentsTotal);
                PrintList(&StudentsTotal, &CourseTotal, sorts, id, names, scores, ScoresTotal);
                break;
            case 7:
                SortScore(sorts, ScoresTotal, &StudentsTotal, Ascending);
                SearchId(&StudentsTotal, &CourseTotal, sorts, id, names, scores, ScoresTotal);
                break;
            case 8:
                SortScore(sorts, ScoresTotal, &StudentsTotal, Ascending);
                SearchName(&StudentsTotal, &CourseTotal, sorts, id, names, scores, ScoresTotal);
                break;
            case 9:
                StatisticAnalysis(&StudentsTotal, &CourseTotal, scores);
                break;
            case 10:
                SortId(id, sorts, &StudentsTotal);
                printf("\n-- Score List\n");
                PrintList(&StudentsTotal, &CourseTotal, sorts, id, names, scores, ScoresTotal);
                PrintSum(scores, &StudentsTotal, &CourseTotal);
                PrintAverage(scores, &StudentsTotal, &CourseTotal);
                printf("\nTOTAL:%d\n", StudentsTotal);
                printf("-- END\n");
                break;
            default:
                printf("\n\n-- Sorry!Please input 0-10!\n");
        };
    } while (Selection != 0);
}

//���ܣ�����˵�
//��Σ���
//���Σ���
void PrintMenu() {
    printf("\n");
    printf("|1.Input record\n");
    printf("|2.Calculate total and average score of course\n");
    printf("|3.Sort in descending order by score\n");
    printf("|4.Sort in ascending order by score\n");
    printf("|5.Sort in ascending order by number\n");
    printf("|6.Sort in dictionary order by name\n");
    printf("|7.Search by number\n");
    printf("|8.Search by name\n");
    printf("|9.Statistic analysis\n");
    printf("|10.List record\n");
    printf("|0.Exit\n");
    printf("|Please input 0-10 to select function :");
}


//���ܣ�����ɼ��б�
//��Σ�ѧ���������γ����������������ַ��ѧ�������ַ�����������ַ���ɼ������ַ���ܳɼ������ַ
//���Σ���
void PrintList(int *stuAmount, int *couAmount, int *sorts, int *id, char (*names)[NameMaxLen],
               float (*scores)[CourseMaxNumber], float *ScoresTotal) {
    int i,n;
    printf("\n");
    for (i = 0; i < *stuAmount; i++) {
        printf("%d  ", *(id + *(sorts + i)));  // i -> *(sorts+i)
        fputs(*(names + *(sorts + i)),stdout);  //puts�����ַ���ĩβ�Զ�����\n fputs����
        for (n = 0; n < *couAmount; n++) {
            printf("  %.1f  ", *(*(scores + *(sorts + i)) + n));
        };
        printf("TOTAL:%.1f\n", *(ScoresTotal + *(sorts + i)));
    }
}

//���ܣ������������ʽ��
//��Σ����������ַ
//���Σ���
void FormatSorts(int *sorts) {
    int i;
    for (i = 0; i <= StuMaxNumber; i++) {
        *(sorts + i) = i;
    }
}


//���ܣ������������Ļس�ɾ��
//��Σ����������ַ
//���Σ���
void alter(char (*names)[NameMaxLen]) {
    int i, m;
    for (i = 0; i < StuMaxNumber; i++) {
        for (m = 0; m < NameMaxLen; m++) {
            if (*(*(names + i) + m) == '\n') {
                *(*(names + i) + m) = '\0';
            }
        }
    }
}

//���ܣ�����ÿ��ѧ�����ܷ�
//��Σ��ɼ������ַ
//���Σ���
void SumScores(float (*score)[CourseMaxNumber], int *stuAmount, int *couAmount, float *ScoresTotal) {
    int i, n;
	float SumTemp;
    for (i = 0; i < *stuAmount; i++) {
        SumTemp = 0;
        for (n = 0; n < *couAmount; n++) {
            SumTemp += *(*(score + i) + n);
        }
        *(ScoresTotal + i) = SumTemp;
    }
}


//���ܣ�����ɼ�
//��Σ��ɼ������ַ��ѧ�������ַ,��������
//���Σ�ѧ��������int��
void InputRecord(float (*scores)[CourseMaxNumber], int *id, char (*names)[NameMaxLen], int *stuAmount, int *couAmount) {
    int i, m;
    printf("\n-- Start to Input Record\n");
    printf("\n-- Please input the number of courses:");
    scanf("%d", couAmount);
    if (*couAmount > CourseMaxNumber) {
        printf("\n-- Sorry! The max of courses amount is 6!:");
        *couAmount = 6;
    }
    printf("- You can stop inputting with a negative number \n\n");
    for (i = 0; i < StuMaxNumber; i++) {
        printf("Input NO.%d student`s ID:", i + 1);    //ID һά����
        scanf("%d", id + i);
        if (*(id + i) < 0) {
            printf("\n-- Input Record is Over\n");
            *stuAmount = i;
            alter(names);
            return;
        }
        printf("Input NO.%d student`s Name:", i + 1);    //name ��ά������ָ��
        getchar();
        fgets(*(names + i), NameMaxLen + 1, stdin);
        if (**(names + i) == '-') {
            printf("\n-- Input Record is Over\n");
            *stuAmount = i;
            alter(names);
            return;
        }
        printf("Input NO.%d student`s Score:\n", i + 1);   //scores ��ά������ָ��
        for (m = 0; m < *couAmount; m++) {
            printf("- Input NO.%d student`s NO.%d Course Scores:", i + 1, m + 1);
            scanf("%f", *(scores + i) + m);
            if (*(*(scores + i) + m) < 0) {
                printf("\n-- Input Record is Over\n");
                *stuAmount = i;
                alter(names);
                return;
            }
        }
    };
    *stuAmount = StuMaxNumber;
    printf("\n-- The MAX number of students is StuMaxNumber.Input Record is over.\n");
}

//���ܣ���ӡÿ�ſγ̵��ܷ�
//��Σ��ɼ������ַ��ѧ������
//���Σ���
void PrintSum(float (*scores)[CourseMaxNumber], int *stuAmount, int *couAmount) {
    int i, m;
    float sum = 0;
    if (*stuAmount == 0) {
        printf("\n-- Please input record first!\n");
        return;
    }
    printf("\n-- SUM:  ");
    for (m = 0; m < *couAmount; m++) {
        sum = 0;
        for (i = 0; i < *stuAmount; i++) {
            sum += *(*(scores + i) + m);
        }
        printf("  Course%d:%.2f  ", m + 1, sum);
    }
    printf("\n");
}

//���ܣ���ӡÿ�ſε�ƽ����
//��Σ��ɼ������ַ��ѧ������
//���Σ���
void PrintAverage(float (*scores)[CourseMaxNumber], int *stuAmount, int *couAmount) {
    int i, m;
    float sum = 0, average = 0;
    if (*stuAmount == 0) {
        printf("\n-- Please input record first!\n");   /* �ɼ�Ϊ0�����ж��Ƿ�������ɼ�*/
        return;
    }
    printf("\n-- AVERAGE:  ");
    for (m = 0; m < *couAmount; m++) {
        sum = 0;
        for (i = 0; i < *stuAmount; i++) {
            sum += *(*(scores + i) + m);
        }
        average = sum / *stuAmount;
        printf("  Course%d:%.2f  ", m + 1, average);
    }
    printf("\n");
}

//���ܣ������ܳɼ������ҷ���
//��Σ����������ַ���ܳɼ������ַ��ѧ��������ַ����������ָ��
//���Σ���
void SortScore(int *sorts, float *ScoresTotal, int *stuAmount, int (*compare)(float a, float b)) {
    int m, n, flag = 0, SortTemp;
    if (*stuAmount == 0) {
        printf("\n-- Please input record first!\n");
        return;
    }
    for (m = 0; m < *stuAmount - 1; m++) {  //�����ܳɼ�������бȽ�
        flag = m;
        for (n = m + 1; n < *stuAmount; n++) {
            if ((*compare)(*(ScoresTotal + m), *(ScoresTotal + n))) {
                flag = n;
            }
        }
        SortTemp = *(sorts + m);      //������������б仯
        *(sorts + m) = *(sorts + flag);
        *(sorts + flag) = SortTemp;
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

//���ܣ���С��������ѧ�ţ����ҷ���
//��Σ�ѧ�������ַ�����������ַ��ѧ������
//���Σ���
void SortId(int *id, int *sorts, int *stuAmount) {
    int m, n, flag = 0, SortTemp;
    if (*stuAmount == 0) {
        printf("\n-- Please input record first!\n");
        return;
    }
    for (m = 0; m < *stuAmount - 1; m++) {  //�����ܳɼ�������бȽ�
        flag = m;
        for (n = m + 1; n < *stuAmount; n++) {
            if (*(id + m) > *(id + n)) {
                flag = n;
            }
        }
        SortTemp = *(sorts + m);      //������������б仯
        *(sorts + m) = *(sorts + flag);
        *(sorts + flag) = SortTemp;
    }
}

//���ܣ����ֵ����������֣����ҷ���
//��Σ����������ַ�����������ַ��ѧ������
//���Σ���
void SortName(char (*names)[NameMaxLen], int *sorts, int *stuAmount) {
    int m, n, flag = 0, SortTemp;
    if (*stuAmount == 0) {
        printf("\n-- Please input record first!\n");
        return;
    }
    for (m = 0; m < *stuAmount - 1; m++) {  //�����ܳɼ�������бȽ�
        flag = m;
        for (n = m + 1; n < *stuAmount; n++) {
            if (strcmp(*(names + m), *(names + n)) > 0) {  //maybe bug:  *(names+n)
                flag = n;
            }
        }
        SortTemp = *(sorts + m);      //������������б仯
        *(sorts + m) = *(sorts + flag);
        *(sorts + flag) = SortTemp;
    }
}


//���ܣ���ѧ����������ӡ�ɼ�������
//��Σ�ѧ���������γ����������������ַ��ѧ�������ַ�����������ַ���ɼ������ַ���ܳɼ������ַ
//���Σ���
void SearchId(int *stuAmount, int *couAmount, int *sorts, int *id, char (*names)[NameMaxLen],
              float (*scores)[CourseMaxNumber],
              float *ScoresTotal) {
    int InputId, m, n, find = 0;
    if (*stuAmount == 0) {
        printf("\n-- Please input record first!\n");
        return;
    }
    printf("\n-- Please input the id you want to search:");
    scanf("%d", &InputId);
    for (m = 0; m < *stuAmount; m++) {          //ʹ�ö��ַ�����ʹ��˳��
        if (InputId == *(id + *(sorts + m))) {
            find = 1;
            break;
        }
    }
    if (!find) {
        printf("\n-- Sorry!No result!\n");
        return;
    } else {
        printf("\nRank: %d\n", m + 1);
        printf("%d  ", *(id + *(sorts + m)));
        fputs(*(names + *(sorts + m)),stdout);
        for (n = 0; n < *couAmount; n++) {
            printf("  %.1f  ", *(*(scores + *(sorts + m)) + n));
        };
        printf("TOTAL:%.1f\n", *(ScoresTotal + *(sorts + m)));
    }
}


//���ܣ���ѧ����������ӡ�ɼ�������
//��Σ�ѧ���������γ����������������ַ��ѧ�������ַ�����������ַ���ɼ������ַ���ܳɼ������ַ
//���Σ���
void SearchName(int *stuAmount, int *couAmount, int *sorts, int *id, char (*names)[NameMaxLen],
                float (*scores)[CourseMaxNumber], float *ScoresTotal) {
    int m, n, find = 0;
    char InputName[NameMaxLen];
    if (*stuAmount == 0) {
        printf("\n-- Please input record first!\n");
        return;
    }
    getchar();
    printf("\n-- Please input the name you want to search:");
    fgets(InputName, NameMaxLen + 1, stdin);
    for (m = 0; m < NameMaxLen; m++) {
        if (*(InputName + m) == '\n') {
            *(InputName + m) = '\0';
        }
    }
    for (m = 0; m < *stuAmount; m++) {          //ʹ�ö��ַ�����ʹ��˳��
        if (strcmp(*(names + *(sorts + m)), InputName) == 0) {
            find = 1;
            break;
        }
    }
    if (!find) {
        printf("\n-- Sorry!No result!\n");
        return;
    } else {
        printf("\nRank: %d\n", m + 1);
        printf("%d  ", *(id + *(sorts + m)));
        fputs(*(names + *(sorts + m)),stdout);
        for (n = 0; n < *couAmount; n++) {
            printf("  %.1f  ", *(*(scores + *(sorts + m)) + n));
        };
        printf("TOTAL:%.1f\n", *(ScoresTotal + *(sorts + m)));
    }
}

//���ܣ�������������ѧ��������ռ��
//��Σ�ѧ���������γ��������ɼ������ַ
//���Σ���
void StatisticAnalysis(int *stuAmount, int *couAmount, float (*scores)[CourseMaxNumber]) {
    int A = 0, B = 0, C = 0, D = 0, E = 0, m, n;
    if (*stuAmount == 0) {
        printf("\n-- Please input record first!\n");
        return;
    }
    printf("\n-- Statistic Analysis:\n");
    for (m = 0; m < *couAmount; m++) {
        A = 0;
        B = 0;
        C = 0;
        D = 0;
        E = 0;
        for (n = 0; n < *stuAmount; n++) {
            if (*(*(scores + n) + m) >= 90 && *(*(scores + n) + m) <= 100) {
                A += 1;
            } else if (*(*(scores + n) + m) >= 80) {
                B += 1;
            } else if (*(*(scores + n) + m) >= 70) {
                C += 1;
            } else if (*(*(scores + n) + m) >= 60) {
                D += 1;
            } else {
                E += 1;
            }
        }
        printf("Course%d  ", m + 1);
        printf("A(100-90):%d(%.2f%%)  ", A, (float) A / (float) (*stuAmount) * 100);
        printf("B(89-80):%d(%.2f%%)  ", B, (float) B / (float) (*stuAmount) * 100);
        printf("C(79-70):%d(%.2f%%)  ", C, (float) C / (float) (*stuAmount) * 100);
        printf("D(69-60):%d(%.2f%%)  ", D, (float) D / (float) (*stuAmount) * 100);
        printf("E(59-0):%d(%.2f%%)\n", E, (float) E / (float) (*stuAmount) * 100);
    }
}

