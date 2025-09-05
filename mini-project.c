#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 1024
#define MSIZE 16777216  // 메모리 버퍼(16메가) 지정

// 202202590 박종현

// 0-index : 비었다? -1로 설정
int *p = NULL;
int max_row = -1;
int max_col = -1;

////////////////////////
// 학생이 구현해야 하는 함수
////////////////////////

// 행번호가 음수이면 무시하고 종료
void copy(int * whtie_paper, int * origin, int length){
    for (int i=0; i<length; i++)
        whtie_paper[i] = origin[i];
    free(origin);
}

void create_row() {
    int row_num;
    scanf("%d", &row_num);
    while(getchar() != '\n'); 

    if (row_num < 0) return;
    // if (p == NULL) {
    //     max_col++;
    //     p = (int*) malloc(sizeof(int) * (max_row+1)); // 한 줄 생성
    // }
    max_row++; //최대 row 갱신
    int tmp_max_row = row_num > max_row ? row_num : max_row; // max_row보다 더 큰 값을 입력할 수도 있음.
    int p_new_length = (tmp_max_row+1) * (max_col + 1);

    int * tmp_p = (int*) malloc(sizeof(int) * p_new_length);
    int index_p = 0;

    for (int i=0; i<p_new_length; i++) {
        int now = ((int)i/(max_col+1));
        if ( (max_row > row_num &&now == row_num) || (row_num >= max_row && now >= max_row) )
            tmp_p[i] = 0;
        else 
            tmp_p[i] = p[index_p++];   
    }

    max_row = tmp_max_row;

    // copy and free
    p = (int*) malloc(sizeof(int) * p_new_length);
    copy(p, tmp_p, p_new_length);
}

void create_col() {
    int col_num;
    scanf("%d", &col_num);
    while(getchar() != '\n');
    
    if (col_num < 0) return;
    // if (p == NULL) {
    //     max_row++;
    //     p = (int*) malloc(sizeof(int) * (max_row+1));
    // }

    max_col++; //최대 col 갱신
    int tmp_max_col = col_num > max_col ? col_num : max_col; // max_col보다 더 큰 값을 입력할 수도 있음.
    int p_new_length = (max_row+1) * (tmp_max_col + 1);

    int * tmp_p = (int*) malloc(sizeof(int) * p_new_length);
    int index_p = 0;
    
    for (int i=0; i<p_new_length; i++) {
        int now = i%(tmp_max_col+1);
        if ((col_num<max_col && now == col_num) || (col_num >= max_col && now >= max_col))
            tmp_p[i] = 0;
        else
            tmp_p[i] = p[index_p++];
    }

    max_col = tmp_max_col; //최대값 갱신

    // copy and free
    p = (int*) malloc(sizeof(int) * p_new_length);
    copy(p, tmp_p, p_new_length);
}

long sum() {
    long ret = 0;
    for (int i=0; i<max_row+1; i++)
        for (int j=0; j<max_col+1; j++)
            ret += p[i + ((max_row+1) * j)];
        
    return ret;
}
double avg() {
    long s = sum();
    double ss = (double) s;
    double q = (double) ((max_row+1)*(max_col+1));
    return (ss/q);
}

void update_cell() {
    int row, col, data;
    scanf("%d %d %d", &row, &col, &data);
    getchar();
    // p 안에 있는 값 변경
    int index = col + (max_col+1)*row;
    if (row > max_row ||
        col > max_col ||
        index >= 1024) return;

    p[index] = data;
}

void delete_row() {
    int row_num;
    scanf("%d", &row_num); getchar();
    if (row_num > max_row || p == NULL) return;

    int* tmp = (int *) malloc(sizeof(int) * ((max_row) * (max_col+1)));
    
    int p_length = (max_row+1) * (max_col+1);
    int tmp_idx = 0;
    for (int i=0; i<p_length; i++) {
        int row = ((int)i/(max_col+1));
        if (row == row_num) {continue;}
        tmp[tmp_idx++] = p[i];
    }
    int new_length = (max_row) * (max_col+1);
    // copy and free
    p = (int*) malloc(sizeof(int) * new_length);
    copy(p, tmp, new_length);

    max_row--;
}

void delete_col() {
    int col_num;
    scanf("%d", &col_num); getchar();
    if (col_num > max_col || p == NULL) return;

    int* tmp = (int *) malloc(sizeof(int) * ((max_row+1) * (max_col)));
    
    int p_length = (max_row+1) * (max_col+1);
    int tmp_idx = 0;
    for (int i=0; i<p_length; i++) {
        int col = ((int)i%(max_col+1));
        if (col == col_num) {continue;}
        tmp[tmp_idx++] = p[i];
    }
    int new_length = (max_row+1) * (max_col);
    // copy and free
    p = (int*) malloc(sizeof(int) * new_length);
    copy(p, tmp, new_length);

    max_col--;
}

void save() {
    char file_name[100];
    scanf("%s", file_name);
    getchar();
    
    char folder[1000] = "";
    // "/home/jonghp1128/CP03/assignments/termproject/mini1_files/";
    // "assignments/termproject/202202590_PJH_mini1_files/";
    char * file_path = strcat(strcat(folder, file_name), ".csv");
    FILE *fp = fopen(file_path, "w");

    if (fp == NULL){return;}
    

    for (int i=1; i<(max_row+1) * (max_col+1) +1; i++){
        if (i%(max_col + 1)==0){
            fprintf(fp, "%d", p[i-1]);
            fprintf(fp, "%c", '\n');
        } else {
            fprintf(fp, "%d,", p[i-1]); // 배열의 각 값을 한 줄에 하나씩 출력
        }
    }
    fclose(fp);
}

///////////////////////////////
// 아래 코드는 기존에 주어진 코드
///////////////////////////////

void create_obj() {
    printf("create new (r)ow | (c)olumn\n");
    printf("input your command: \n");
    char c;
    scanf("%c", &c);
    while(getchar() !='\n');
    switch (c)
    {
    case 'r':
        printf("input row num: ");
        create_row();
        break;
    case 'c':
        printf("input column num: ");
        create_col();
        break;
    default:
        printf("wrong command...\n");
    }
}

void functions() {
    printf("apply function (a)verage | (s)um\n");
    printf("input your command: \n");
    char c;
    scanf("%c", &c);
    while(getchar() !='\n');
    switch (c)
    {
    case 'a':
        printf("average: %f\n", avg());
        break;
    case 's':
        printf("sum: %ld", sum());
        break;
    default:
        printf("wrong command...\n");
    }
}

void delete_obj() {
    printf("delete (r)ow | (c)olumn\n");
    printf("input your command: \n");
    char c;
    scanf("%c", &c);
    while(getchar() !='\n');
    switch (c)
    {
    case 'r':
        printf("input row num: ");
        delete_row();
        break;
    case 'c':
        printf("input column num: ");
        delete_col();
        break;
    default:
        printf("wrong command...\n");
    }
}

void print_obj() {
    if (max_row==-1 || max_col==-1) return;
    printf("           ");
    for (int i=0; i<max_col+1; i++) {
        printf(" %11d", i);
    }
    printf("\n           ");
    for (int i=0; i<max_col+1; i++) {
        printf("------------");
    }
    printf("-\n");
    for (int i=0; i<max_row+1; i++) {
        printf("%11d", i);
        for (int j=0; j<max_col+1; j++) {
            printf("|%11d", *(p + ((max_col+1)*i) + j));
        }
        printf("|\n");
    }
    printf("           ");
    for (int i=0; i<max_col+1; i++) {
        printf("------------");
    }
    printf("-\n");
}

void print_intro() {
    printf("#################################################\n");
    printf("#\t\t2025 CP3 mini project\t\t#\n");
    printf("#################################################\n");
    printf("\n");
    printf("(c)reate | (f)unction | (u)pdate | (d)elete | (s)ave | (p)rint | (q)uit\n");
    printf("input your command: \n");
}

int main() {
    int loop = 1;
    while (loop) {
        print_intro();
        
        char c;
        scanf("%c", &c);
        while(getchar() !='\n');
        
        switch (c)
        {
        case 'c':
            create_obj();
            break;
        case 'f':
            functions();
            break;
        case 'u':
            printf("input row and column num & data: ");
            update_cell();
            break;
        case 'd':
            delete_obj();
            break;
        case 's':
            printf("input filename: ");
            save();
            break;
        case 'q':
            loop = 0;
            break;
        case 'p':
            print_obj();
            break;
        default:
            printf("wrong command...\n");
        }
        printf("\n\n\n\n");
    }

    return 0;
}

