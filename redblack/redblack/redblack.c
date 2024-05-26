#include <stdio.h>
#include <stdlib.h>


struct node {
    int color; // red = 1, black = 0
    int data; // data 값 key 값
    struct node* p, * left, * right;
};

typedef struct rbtree {//root와 nil구조체
    struct node* root;
    struct node* nil;
} rbtree;


struct node* create_node(rbtree* T, int data, int color) {//노드만 드는 구간
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data = data;//데이터 값 
    n->color = color;//색
    n->p = T->nil;//기본적으로 만들어진 노드는 nil을 가리킨다
    n->left = T->nil; //기본적으로 만들어진 노드는 nil을 가리킨다
    n->right = T->nil; //기본적으로 만들어진 노드는 nil을 가리킨다 나중에 연결해줌
    return n;
}


void LeftR(rbtree* T, struct node* x) {//좌회전 함수
    struct node* y = x->right;//y는 x의 오른쪽 쉽게 말해서 x가 위에 있다는 뜻
    x->right = y->left;//x오른쪽은 y의 왼쪽 (좌회전 준비를 위해 y의 왼쪽을 x의 오른쪽 값에 삽입)
    if (y->left != T->nil) {//y의 왼쪽이 T->nill이 아니면 (아무것도 없지 않으면) 
        y->left->p = x;//y의 왼쪽의 부모는 (원래 y를 가리키던 값은) x를 가리킨다
    }
    y->p = x->p;//y의 부모는 x의 부모가 된다 이제 y가 더 위에 있게 됨
    if (x->p == T->nil) {//x의 부모가 nill이면
        T->root = y;//이제 y는 루트노드가 된다
    }
    else if (x == x->p->left) {//만약 x와 x의 부모의 왼쪽이 같으면
        x->p->left = y;//x의 부모의 왼쪽은 y이다
    }
    else {
        x->p->right = y;//x의 부모의 오른쪽은 y이다
    }
    y->left = x;//y의 왼쪽값은 x가 도고
    x->p = y;//마지막으로 x의 부모는 y로 연결한다
}


void RightR(rbtree* T, struct node* y) {//우회전 함수
    struct node* x = y->left;//x는 y의 왼쪽 쉽게 말해서 y가 위에 있다는 뜻
    y->left = x->right;//y왼쪽은 x의 오른쪽 (우회전 준비를 위해 x의 오른쪽을 y의왼쪽 값에 삽입)
    if (x->right != T->nil) {//x의 오른쪽이 T->nill이 아니면 (아무것도 없지 않으면) 
        x->right->p = y;//x의 오른쪽의 부모는 (원래 x를 가리키던 값은) y를 가리킨다
    }
    x->p = y->p;//x의 부모는 y의 부모가 된다 이제 x가 더 위에 있게 됨
    if (y->p == T->nil) {//y의 부모가 nill이면
        T->root = x;//이제 x는 루트노드가 된다
    }
    else if (y == y->p->right) {//만약 y와 y의 부모의 오른쪽이 같으면
        y->p->right = x;//y의 부모의 왼쪽은 x이다
    }
    else {
        y->p->left = x;//y의 부모의 오른쪽은 y이다
    }
    x->right = y;//x의 오른쪽값은 y가 도고
    y->p = x;//마지막으로 y의 부모는 x로 연결한다
}


void RBInsertFixup(rbtree* T, struct node* z) {//RBinsertFixup함수
    while (z->p->color == 1) { //선택한 노드의 부모가 색이 빨강일때 ( 왜냐면 무조건 빨강으로 노드가 들어가기 때문에 이때 오류가 생김)
        if (z->p == z->p->p->left) {//z의 부모가 z의 부모의 부모의 왼쪽 일 경우 
            struct node* y = z->p->p->right; //y를 만들고 y는 z의 부모의 보모의 오른쪽 (삼촌?)
            if (y->color == 1) { // 삼촌의 색이 빨강일 경우
                z->p->color = 0; //z의 부모의 생은 검정으로 바꾸고
                y->color = 0;//삼촌의 색또한 검정으로 바꿈
                z->p->p->color = 1;//z의 부모의 부모의 색은 빨강으로 바꿈
                z = z->p->p;//이제 아래쪽에선 문제가 해결되었으므로 z의 조부모를 z로 만들고 반복문을 다시 시작한다
            }
            else {
                if (z == z->p->right) { //z는 z의 부모의 오른쪽일경우
                    z = z->p;// z는 z의 부모가 된다
                    LeftR(T, z);// 좌회전 
                }
                z->p->color = 0;//z의 부모의 색은 검정이 됨
                z->p->p->color = 1;//z의 부모의 부모의 색은 빨강이 된다
                RightR(T, z->p->p);//z의 부모의 부모를 우회전
            }
        }
        else {
            struct node* y = z->p->p->left; //z의 부모의 부모의 왼쪽은 y라는 노드 생성
            if (y->color == 1) { //y의 색은 빨강
                z->p->color = 0;//z의 부모의 색은 검정
                y->color = 0;//y의 색은 검정
                z->p->p->color = 1;//z의 부모의 부모의 색은 빨강
                z = z->p->p;//이제 아래쪽에선 문제가 해결되었으므로 z의 조부모를 z로 만들고 반복문을 다시 시작한다
            }
            else {
                if (z == z->p->left) { //z는 z의 부모의 왼쪽
                    z = z->p;//z는 z의 부모로 바꿈
                    RightR(T, z); //좌회전
                }
                z->p->color = 0;//z의 부모의 색은 검정 
                z->p->p->color = 1;//z의 부모의 부모의 색은 빨강
                LeftR(T, z->p->p);//z의 부모의 부모를 좌회전
            }
        }
    }
    T->root->color = 0; //RBTREE의 루트의 생을 검정으로 바꿈
}
////////////////////////////////////////나머지는 내일  하자
// 
// 
// 
// 
// 레드-블랙 트리에 노드를 삽입하는 함수
void RBInsert(rbtree* T, struct node* z) {
    struct node* y = T->nil; // y를 nil로 초기화
    struct node* x = T->root; // x를 루트 노드로 초기화
    while (x != T->nil) { // x가 nil이 아닌 동안 반복
        y = x; // y를 x로 설정
        if (z->data < x->data) { // z의 데이터가 x의 데이터보다 작으면
            x = x->left; // x를 왼쪽 자식으로 설정
        }
        else {
            x = x->right; // x를 오른쪽 자식으로 설정
        }
    }
    z->p = y; // z의 부모를 y로 설정
    if (y == T->nil) { // y가 nil이면
        T->root = z; // z를 루트 노드로 설정
    }
    else if (z->data < y->data) { // z의 데이터가 y의 데이터보다 작으면
        y->left = z; // y의 왼쪽 자식을 z로 설정
    }
    else {
        y->right = z; // y의 오른쪽 자식을 z로 설정
    }
    z->left = T->nil; // z의 왼쪽 자식을 nil로 설정
    z->right = T->nil; // z의 오른쪽 자식을 nil로 설정
    z->color = 1; // z를 빨간색으로 설정
    RBInsertFixup(T, z); // 삽입 후 속성 복구 함수 호출
}

//교체 함수
void RBTransplant(rbtree* T, struct node* u, struct node* v) {
    if (u->p == T->nil) { // u의 부모가 nil이면
        T->root = v; // v를 루트 노드로 설정
    }
    else if (u == u->p->left) { // u가 부모의 왼쪽 자식이면
        u->p->left = v; // 부모의 왼쪽 자식을 v로 설정
    }
    else {
        u->p->right = v; // 부모의 오른쪽 자식을 v로 설정
    }
    v->p = u->p; // v의 부모를 u의 부모로 설정
}

// 서브트리에서 최소값을 찾는 함수
struct node* TreeMinimum(rbtree* T, struct node* x) {
    while (x->left != T->nil) { // x의 왼쪽 자식이 nil이 아닐 동안 반복
        x = x->left; // x를 왼쪽 자식으로 설정
    }
    return x; // 최소값 노드 반환
}
struct node* TreeMaximum(rbtree* T, struct node* x) {
    while (x->right != T->nil) { // x의 왼쪽 자식이 nil이 아닐 동안 반복
        x = x->right; // x를 왼쪽 자식으로 설정
    }
    return x; // 최대값 노드 반환
}

struct node* SearchRBtree(rbtree* T, int value) {
    struct node* x = T->root;//루트부터 찾을 예정
    while (x != T->nil && x->data != value) {//x가 nil이 아니고 x가 value 즉 찾지 않았을때
        if (x->data < value) {//크면
            x = x->right;//오른쪽으로
        }
        else {
            x = x->left;//아니면 왼쪽으로
        }
    }
    if (x != T->nil) {//찾았으면 그 node 리턴
        return x;
    }
    else {//없으면 NULL
        return NULL;
    }
}

// 레드-블랙 트리 삭제 후 속성 복구 함수
void RBDeleteFixup(rbtree* T, struct node* x) {
    while (x != T->root && x->color == 0) { // x가 루트가 아니고 검은색인 동안 반복
        if (x == x->p->left) { // x가 부모의 왼쪽 자식이면
            struct node* w = x->p->right; // w는 x의 형제 노드
            if (w->color == 1) { // 형제 노드가 빨간색이면
                w->color = 0; // 형제를 검은색으로 변경
                x->p->color = 1; // 부모를 빨간색으로 변경
                LeftR(T, x->p); // 좌회전
                w = x->p->right; // 새로운 형제 설정
            }
            if (w->left->color == 0 && w->right->color == 0) { // 형제의 두 자식이 모두 검은색이면
                w->color = 1; // 형제를 빨간색으로 변경
                x = x->p; // x를 부모로 설정
            }
            else {
                if (w->right->color == 0) { // 형제의 오른쪽 자식이 검은색이면
                    w->left->color = 0; // 형제의 왼쪽 자식을 검은색으로 변경
                    w->color = 1; // 형제를 빨간색으로 변경
                    RightR(T, w); // 우회전
                    w = x->p->right; // 새로운 형제 설정
                }
                w->color = x->p->color; // 형제를 부모의 색으로 변경
                x->p->color = 0; // 부모를 검은색으로 변경
                w->right->color = 0; // 형제의 오른쪽 자식을 검은색으로 변경
                LeftR(T, x->p); // 좌회전
                x = T->root; // x를 루트로 설정
            }
        }
        else { // x가 부모의 오른쪽 자식이면
            struct node* w = x->p->left; // w는 x의 형제 노드
            if (w->color == 1) { // 형제 노드가 빨간색이면
                w->color = 0; // 형제를 검은색으로 변경
                x->p->color = 1; // 부모를 빨간색으로 변경
                RightR(T, x->p); // 우회전
                w = x->p->left; // 새로운 형제 설정
            }
            if (w->right->color == 0 && w->left->color == 0) { // 형제의 두 자식이 모두 검은색이면
                w->color = 1; // 형제를 빨간색으로 변경
                x = x->p; // x를 부모로 설정
            }
            else {
                if (w->left->color == 0) { // 형제의 왼쪽 자식이 검은색이면
                    w->right->color = 0; // 형제의 오른쪽 자식을 검은색으로 변경
                    w->color = 1; // 형제를 빨간색으로 변경
                    LeftR(T, w); // 좌회전
                    w = x->p->left; // 새로운 형제 설정
                }
                w->color = x->p->color; // 형제를 부모의 색으로 변경
                x->p->color = 0; // 부모를 검은색으로 변경
                w->left->color = 0; // 형제의 왼쪽 자식을 검은색으로 변경
                RightR(T, x->p); // 우회전
                x = T->root; // x를 루트로 설정
            }
        }
    }
    x->color = 0; // x를 검은색으로 설정
}

// 레드-블랙 트리에서 노드를 삭제하는 함수
void RBDelete(rbtree* T, struct node* z) {
    struct node* y = z; // y를 삭제할 노드로 설정
    struct node* x;
    int y_original_color = y->color; // y의 원래 색을 저장
    if (z->left == T->nil) { // z의 왼쪽 자식이 nil이면
        x = z->right; // x를 z의 오른쪽 자식으로 설정
        RBTransplant(T, z, z->right); // z를 z의 오른쪽 자식으로 교체
    }
    else if (z->right == T->nil) { // z의 오른쪽 자식이 nil이면
        x = z->left; // x를 z의 왼쪽 자식으로 설정
        RBTransplant(T, z, z->left); // z를 z의 왼쪽 자식으로 교체
    }
    else {
        y = TreeMinimum(T, z->right); // y를 z의 오른쪽 서브트리의 최소값으로 설정
        y_original_color = y->color; // y의 원래 색을 저장
        x = y->right; // x를 y의 오른쪽 자식으로 설정
        if (y->p == z) { // y의 부모가 z이면
            x->p = y; // x의 부모를 y로 설정
        }
        else {
            RBTransplant(T, y, y->right); // y를 y의 오른쪽 자식으로 교체
            y->right = z->right; // y의 오른쪽 자식을 z의 오른쪽 자식으로 설정
            y->right->p = y; // y의 오른쪽 자식의 부모를 y로 설정
        }
        RBTransplant(T, z, y); // z를 y로 교체
        y->left = z->left; // y의 왼쪽 자식을 z의 왼쪽 자식으로 설정
        y->left->p = y; // y의 왼쪽 자식의 부모를 y로 설정
        y->color = z->color; // y의 색을 z의 색으로 설정
    }
    free(z); // z의 메모리 해제
    if (y_original_color == 0) { // y의 원래 색이 검은색이면
        RBDeleteFixup(T, x); // 삭제 후 속성 복구 함수 호출
    }
}
void print_tree(rbtree* T) {
    struct node* stack[100]; // 스택을 사용할 배열
    int top = -1;
    struct node* current = T->root;

    while (current != T->nil || top != -1) {
        while (current != T->nil) {
            // 현재 노드 출력
            printf("%d(%s) ", current->data, current->color == 0 ? "B" : "R");
            stack[++top] = current; // 현재 노드를 스택에 저장
            current = current->left; // 왼쪽 자식으로 이동
        }
        current = stack[top--]; // 스택에서 노드를 꺼냄
        current = current->right; // 오른쪽 자식으로 이동
    }
    printf("\n"); // 줄바꿈
}
struct node* TreeSuccessor(struct rbtree* T, struct node* x) {
    if (x->right != T->nil) {//successor는 오른쪽 서브트리에서 가장 작은 수이므로
        return TreeMinimum(T,x->right);//오른쪽의 서브트리의 최솟값
    }
    struct node* y = x->p;
    while (y != NULL && x == y->right) {//만약 오른쪽 서브트리가 없다면 그 부모
        x = y;
        y = y->p;
    }
    return y;
}

struct node* TreePredecessor(struct rbtree* T, struct node* x) {
    if (x->left != T->nil) {//predecessor는 왼쪽 서브트리에서 가장 큰 수이므로
        return TreeMaximum(T, x->left);//오른쪽의 서브트리의 최솟값
    }
    struct node* y = x->p;
    while (y != NULL && x == y->left) {//만약 왼쪽 서브트리가 없다면 그 부모
        x = y;
        y = y->p;
    }
    return y;
}

void MS(struct rbtree* T,struct node* root, FILE* file) {
    if (root == T->nil) {
        return; // NULL인 경우 함수 종료
    }
    MS(T,root->left, file); // 왼쪽 서브트리를 중위 순회


    fprintf(file, "자신 %d  ", root->data);


    if (root->p != T->nil) {
        fprintf(file, "부모 %d  ", root->p->data);
    }
    else { fprintf(file, "부모 nil  "); }


    if (root->right != T->nil) {
        fprintf(file, "오른 자식%d  ", root->right->data);
    }
    else { fprintf(file, "오른 자식 nil  "); }


    if (root->left != T->nil) {
        fprintf(file, "왼 자식 %d  ", root->left->data);
    }
    else { fprintf(file, "왼 자식 nil  "); }




    if (root->color == 1) {
        fprintf(file, "빨강\n");
    }
    else { fprintf(file, "검정\n"); }

    // 현재 노드의 데이터를 파일에 저장
    MS(T,root->right, file); // 오른쪽 서브트리를 중위 순회
}

// 트리의 중위 순회를 호출하여 데이터를 파일에 저장하는 함수
void txtRB(rbtree* T, const char* filename) {
    FILE* file;
    fopen_s(&file, "202235440 전은섭.txt", "a"); // 파일을 쓰기 모드로 열기
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    MS(T,T->root, file); // 중위 순회 함수 호출
    fclose(file); // 파일 닫기
}


int main() {
    rbtree T;
    T.nil = (struct node*)malloc(sizeof(struct node));
    T.nil->color = 0;
    T.root = T.nil;

    char command[100];
    int value;
    struct node* next;
    struct node* prev;
    struct node* new_node;
    do {//do while문을 이용해 먼저 출력을 하고 작동후 정지 신호를 보고 정지 신호가 아닐시 다시 실행하도록
        printf("\ns,min,max,n,p,i,t\n");
        scanf_s("%s", command, (unsigned)sizeof(command));
        if (command[0] == 's') {
            printf("무엇을 찾으시겠습니까?: ");
            scanf_s("%d", &value, (unsigned)sizeof(value));
            if (SearchRBtree(&T, value) == NULL) { printf("없음"); }//함수 실행으로 없으면 없음
            else if (SearchRBtree(&T, value) != NULL) { printf("있음"); }//함수 실행으로 있으면 있음
        }
        if (command[0] == 'm') {
            if (command[1] == 'i') {
                if (T.root != T.nil) {
                    printf("최소값: %d\n", TreeMinimum(&T, T.root)->data);
                }
                else {
                    printf("트리가 비었습니다y.\n");
                }
            }
            if (command[1] == 'a') {
                if (T.root != T.nil) {
                    printf("최댓값: %d\n", TreeMaximum(&T, T.root)->data);
                }
                else {
                    printf("트리가 비었습니다.\n");
                }
            }
        }
        if (command[0] == 'n') {
        printf("어떤값의 다음값을 찾으시겠습니까?: ");
        scanf_s("%d", &value, (unsigned)sizeof(value));
        next = TreeSuccessor(&T, SearchRBtree(&T, value));
        if (next != T.nil) {
            printf(" % d의 다음 값은: % d\n", value, next->data);
        }
        else {
            printf("다음값이 존재하지 않습니다.\n");
            }
        }
        if (command[0] == 'p') {
        printf("어떤값의 이전값을 찾으시겠습니까?: ");
        scanf_s("%d", &value, (unsigned)sizeof(value));
        prev = TreePredecessor(&T, SearchRBtree(&T, value));
        if (prev != T.nil) {
            printf("%d의 이전값은: %d\n", value, prev->data);
        }
        else {
            printf("이전 값이 존재하지 않습니다.\n");
            }
        }
        if (command[0] == 'i') {
            printf("어떤값을 추가하시겠습니까?: ");
            scanf_s("%d", &value, (unsigned)sizeof(value));
            new_node = create_node(&T,value, 1);
            RBInsert(&T, new_node);
            printf("%d 를 트리에 넣었습니다.\n", value);
        }
        if (command[0] == 't') {
            printf("종료.\n");
            txtRB(&T, "전은섭");
    }
} while (command[0] != 't');

    free(T.nil);
    return 0;
}
