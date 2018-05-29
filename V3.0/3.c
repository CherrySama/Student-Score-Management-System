#include <stdio.h>
#include <string.h>

#define StuMaxNumber 30
#define NameMaxLen 10

void PrintMenu();

int InputRecord(float scores[], int id[],char names[][NameMaxLen]);

void alter(char names[][NameMaxLen]);

float PrintSum(float scores[], int StudentsTotal);

float PrintAverage(float scores[], int StudentsTotal);

void SortScore(float scores[], int id[], char names[][NameMaxLen], int StudentsTotal,int (*compare)(float a,float b) );

int Ascending(float a,float b);

int Descending(float a,float b);

void SortId(float scores[], int id[], char names[][NameMaxLen], int StudentsTotal);

void SortName(float scores[], int id[], char names[][NameMaxLen],int StudentsTotal);

void SearchId(float scores[], int id[], char names[][NameMaxLen], int StudentsTotal);

void SearchName(float scores[], int id[], char names[][NameMaxLen], int StudentsTotal);

void StatisticAnalysis(float scores[], int id[], char names[][NameMaxLen], int StudentsTotal);

void PrintScoreList(float scores[], int id[], char names[][NameMaxLen], int StudentsTotal);

int main() {
    int id[StuMaxNumber] = {0}, StudentsTotal = 0, i, Selection;
    float scores[StuMaxNumber] = {0};
    char names[StuMaxNumber][NameMaxLen];

    printf("Welcome to Student Scores Management System!\n");
    printf("By XiaZhen\n");
    printf("---------------------------------------------\n\n");

    do {
        PrintMenu();
        scanf("%d", &Selection);
		printf("\n%d\n",Selection);
        switch (Selection) {
            case 0:
                break;
            case 1:
                StudentsTotal = InputRecord(scores, id, names);
                break;
            case 2:
                PrintSum(scores, StudentsTotal);
                PrintAverage(scores, StudentsTotal);
                break;
            case 3:
                SortScore(scores, id,names, StudentsTotal,Descending);
                for (i = 0; i < StudentsTotal; i++) {
                    printf("%d  ", id[i]);
                    puts(names[i]);
                    printf("%.1f\n", scores[i]);
                }
                break;
            case 4:
                SortScore(scores, id,names, StudentsTotal,Ascending);
                for (i = 0; i < StudentsTotal; i++) {
                    printf("%d  ", id[i]);
                    puts(names[i]);
                    printf("%.1f\n", scores[i]);
                }
                break;
            case 5:
                SortId(scores, id,names, StudentsTotal);
                for (i = 0; i < StudentsTotal; i++) {
                    printf("%d  ", id[i]);
                    puts(names[i]);
                    printf("%.1f\n", scores[i]);
                }
                break;
            case 6:
                SortName(scores, id,names, StudentsTotal);
                for (i = 0; i < StudentsTotal; i++) {
                    printf("%d  ", id[i]);
                    puts(names[i]);
                    printf("%.1f\n", scores[i]);
                }
                break;
            case 7:
                SearchId(scores, id,names, StudentsTotal);
                break;
            case 8:
                SearchName(scores, id,names, StudentsTotal);
                break;
            case 9:
                StatisticAnalysis(scores, id,names, StudentsTotal);
                break;
            case 10:
                PrintScoreList(scores, id,names, StudentsTotal);
                break;
            default:
                printf("\n\n-- Sorry!Please input 0-7!\n");
        };
    } while (Selection != '0');
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
    printf("|Please input 0-7 to select function :");
}

//���ܣ������������Ļس�ɾ��
//��Σ���������
//���Σ���
void alter(char names[][NameMaxLen]){
    int i,m;
    for(i=0;i< StuMaxNumber;i++){
        for(m=0;m<NameMaxLen;m++){
            if(names[i][m] == '\n'){
                names[i][m] = '\0';
            }
        }
    }
}

//���ܣ�����ɼ�
//��Σ��ɼ������ַ��ѧ�������ַ,��������
//���Σ�ѧ��������int��
int InputRecord(float scores[], int id[],char names[][NameMaxLen]) {
    int  i;
    printf("\n-- Start to Input Record\n");
    printf("- You can stop inputting with a negative number \n\n");
    for (i = 0; i < StuMaxNumber; i++) {
        printf("Input NO.%d student`s ID:", i + 1);
        scanf("%d", &id[i]);
        if (id[i] < 0) {
            printf("\n-- Input Record is Over\n");
            alter(names);
            return i;
        }
        printf("Input NO.%d student`s Name:", i + 1);
        getchar();
        fgets(names[i],NameMaxLen+1,stdin);
        if (names[i][0] == '-') {
            printf("\n-- Input Record is Over\n");
            alter(names);
            return i;
        }
        printf("Input NO.%d student`s Score:", i + 1);
        scanf("%f", &scores[i]);
        if (scores[i] < 0) {
            printf("\n-- Input Record is Over\n");
            alter(names);
            return i;
        }
    };

    printf("\n-- The MAX number of students is StuMaxNumber.Input Record is over.\n");
    return StuMaxNumber;
}


//���ܣ�����ɼ��ܺ�
//��Σ��ɼ������ַ��ѧ������
//���Σ������Ӻͣ�float��
float PrintSum(float scores[], int StudentsTotal) {
    int i;
    float sum = 0;
    if (StudentsTotal == 0) {      
        printf("\n-- Please input record first!\n");
        return 0;
    }
    for (i = 0; i < StudentsTotal; i++) {
        sum += scores[i];
    }
    printf("\nSUM:%.2f\n", sum);
    return sum;
}

//���ܣ�����ɼ�ƽ����
//��Σ��ɼ������ַ��ѧ������
//���Σ�����ƽ������float��
float PrintAverage(float scores[], int StudentsTotal) {
    int i;
    float sum = 0, average = 0;
    if (StudentsTotal == 0) {   /* �ɼ�Ϊ0�����ж��Ƿ�������ɼ�*/
        return 0;
    }
    for (i = 0; i < StudentsTotal; i++) {
        sum += scores[i];
    }
    average = sum / StudentsTotal;
    printf("\nAVERAGE:%.2f\n", average);
    return average;
}

//���ܣ�����ɼ������ҷ���
//��Σ��ɼ������ַ��ѧ�������ַ�����������ַ��ѧ������
//���Σ���
void SortScore(float scores[], int id[], char names[][NameMaxLen],int StudentsTotal, int (*compare)(float a,float b) ){
    int m, n, flag = 0, IdTemp;
    float ScoreTemp;
    char NameTemp[NameMaxLen];
	if (StudentsTotal == 0) {      
        printf("\n-- Please input record first!\n");
        return;
    }
    for (m = 0; m < StudentsTotal - 1; m++) {
        flag = m;
        for (n = m + 1; n < StudentsTotal; n++) {
            if ((*compare)(scores[m],scores[n])) {
                flag = n;
            }
        }
        ScoreTemp = scores[m];
        scores[m] = scores[flag];
        scores[flag] = ScoreTemp;
        IdTemp = id[m];
        id[m] = id[flag];
        id[flag] = IdTemp;
        strcpy(NameTemp,names[m]);
        strcpy(names[m],names[flag]);
        strcpy(names[flag],NameTemp);
    }
}

//���ܣ��ɴ�С����
//��Σ���������
//���Σ�1/0
int Ascending(float a,float b){
    return a < b;
}

//���ܣ���С��������
//��Σ���������
//���Σ�1/0
int Descending(float a,float b){
    return a > b;
}


//���ܣ���С��������ѧ�ţ����ҷ���
//��Σ��ɼ������ַ��ѧ�������ַ�����������ַ��ѧ������
//���Σ���
void SortId(float scores[], int id[], char names[][NameMaxLen],int StudentsTotal){
    int m, n, flag = 0, IdTemp;
    float ScoreTemp;
    char NameTemp[NameMaxLen];
	if (StudentsTotal == 0) {      
        printf("\n-- Please input record first!\n");
        return;
    }
    for (m = 0; m < StudentsTotal - 1; m++) {
        flag = m;
        for (n = m + 1; n < StudentsTotal; n++) {
            if (id[m] > id[n]) {
                flag = n;
            }
        }
        ScoreTemp = scores[m];
        scores[m] = scores[flag];
        scores[flag] = ScoreTemp;
        IdTemp = id[m];
        id[m] = id[flag];
        id[flag] = IdTemp;
        strcpy(NameTemp,names[m]);
        strcpy(names[m],names[flag]);
        strcpy(names[flag],NameTemp);
    }
}


//���ܣ����ֵ����������֣����ҷ���
//��Σ��ɼ������ַ��ѧ�������ַ�����������ַ��ѧ������
//���Σ���
void SortName(float scores[], int id[], char names[][NameMaxLen],int StudentsTotal){
    int m, n, flag = 0, IdTemp;
    float ScoreTemp;
    char NameTemp[NameMaxLen];
    if (StudentsTotal == 0) {
        printf("\n-- Please input record first!\n");
        return;
    }
    for (m = 0; m < StudentsTotal - 1; m++) {
        flag = m;
        for (n = m + 1; n < StudentsTotal; n++) {
            if (strcmp(names[m],names[n]) > 0) {
                flag = n;
            }
        }
        ScoreTemp = scores[m];
        scores[m] = scores[flag];
        scores[flag] = ScoreTemp;
        IdTemp = id[m];
        id[m] = id[flag];
        id[flag] = IdTemp;
        strcpy(NameTemp,names[m]);
        strcpy(names[m],names[flag]);
        strcpy(names[flag],NameTemp);
    }
}

//���ܣ���ѧ����������ӡ�ɼ�������
//��Σ��ɼ������ַ��ѧ�������ַ�����������ַ��ѧ������
//���Σ���
void SearchId(float scores[], int id[], char names[][NameMaxLen], int StudentsTotal){
    int InputId,m,find=0;
	if (StudentsTotal == 0) {      
        printf("\n-- Please input record first!\n");
        return;
    }
    printf("\n-- Please input the id you want to search:");
    scanf("%d",&InputId);
    SortScore(scores,id,names,StudentsTotal,Ascending);
    for(m=0;m<StudentsTotal;m++){          //ʹ�ö��ַ�����ʹ��˳��
        if(InputId == id[m]){
            find = 1;
            break;
        }
    }
    if(!find){
        printf("\n-- Sorry!No result!\n");
        return;
    }else{
        printf("\nRank: %d\n",m+1);
        puts(names[m]);
        printf("\nScore: %.1f\n",scores[m]);
    }
}

//���ܣ���ѧ����������ӡ�ɼ�������
//��Σ��ɼ������ַ��ѧ�������ַ�����������ַ��ѧ������
//���Σ���
void SearchName(float scores[], int id[], char names[][NameMaxLen], int StudentsTotal){
    int m,find=0;
    char InputName[NameMaxLen];
    if (StudentsTotal == 0) {
        printf("\n-- Please input record first!\n");
        return;
    }
    getchar();
    printf("\n-- Please input the name you want to search:");
    fgets(InputName,NameMaxLen+1,stdin);
    SortScore(scores,id,names,StudentsTotal,Ascending);
    for(m=0;m<StudentsTotal;m++){          //ʹ�ö��ַ�����ʹ��˳��
        if(strcmp(names[m],InputName) == 0){
            find = 1;
            break;
        }
    }
    if(!find){
        printf("\n-- Sorry!No result!\n");
        return;
    }else{
        printf("\nRank: %d\n",m+1);
        puts(names[m]);
        printf("\nScore: %.1f\n",scores[m]);
    }
}



//���ܣ�������������ѧ��������ռ��
//��Σ��ɼ������ַ��ѧ�������ַ�����������ַ��ѧ������
//���Σ���
void StatisticAnalysis(float scores[], int id[], char names[][NameMaxLen], int StudentsTotal){
    int A=0,B=0,C=0,D=0,E=0,m;
	if (StudentsTotal == 0) {      
        printf("\n-- Please input record first!\n");
        return;
    }
    SortScore(scores,id,names,StudentsTotal,Ascending);
    for(m=0;m<StudentsTotal;m++){
        if(scores[m] >= 90 && scores[m] <= 100){
            A += 1;
        }else if(scores[m] >= 80){
            B += 1;
        }else if(scores[m] >= 70){
            C += 1;
        }else if(scores[m] >= 60){
            D += 1;
        }else{
            E += 1;
        }
    }
    printf("\n-- Statistic Analysis:\n");
    printf("A(100-90):%d(%.2f%%)\n",A,(float)A/(float)StudentsTotal*100);
    printf("B(89-80):%d(%.2f%%)\n",B,(float)B/(float)StudentsTotal*100);
    printf("C(79-70):%d(%.2f%%)\n",C,(float)C/(float)StudentsTotal*100);
    printf("D(69-60):%d(%.2f%%)\n",D,(float)D/(float)StudentsTotal*100);
    printf("E(59-0):%d(%.2f%%)\n",E,(float)E/(float)StudentsTotal*100);
}

//���ܣ�����ɼ�ͳ�Ʊ�
//��Σ��ɼ������ַ��ѧ�������ַ�����������ַ��ѧ������
//���Σ���
void PrintScoreList(float scores[], int id[], char names[][NameMaxLen], int StudentsTotal){
    int m;
	if (StudentsTotal == 0) {      
        printf("\n-- Please input record first!\n");
        return;
    }
    SortId(scores,id,names,StudentsTotal);
    printf("\n-- Score List\n");
    for(m=0;m<StudentsTotal;m++){
        printf("No.%d   %d  %s  %.1f\n",m+1,id[m],names[m],scores[m]);
    }
    PrintSum(scores,StudentsTotal);
    PrintAverage(scores,StudentsTotal);
    printf("\nTOTAL:%d\n",StudentsTotal);
    printf("-- END\n");
}