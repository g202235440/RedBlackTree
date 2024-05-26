#include <stdio.h>
#include <stdlib.h>


struct node {
    int color; // red = 1, black = 0
    int data; // data �� key ��
    struct node* p, * left, * right;
};

typedef struct rbtree {//root�� nil����ü
    struct node* root;
    struct node* nil;
} rbtree;


struct node* create_node(rbtree* T, int data, int color) {//��常 ��� ����
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data = data;//������ �� 
    n->color = color;//��
    n->p = T->nil;//�⺻������ ������� ���� nil�� ����Ų��
    n->left = T->nil; //�⺻������ ������� ���� nil�� ����Ų��
    n->right = T->nil; //�⺻������ ������� ���� nil�� ����Ų�� ���߿� ��������
    return n;
}


void LeftR(rbtree* T, struct node* x) {//��ȸ�� �Լ�
    struct node* y = x->right;//y�� x�� ������ ���� ���ؼ� x�� ���� �ִٴ� ��
    x->right = y->left;//x�������� y�� ���� (��ȸ�� �غ� ���� y�� ������ x�� ������ ���� ����)
    if (y->left != T->nil) {//y�� ������ T->nill�� �ƴϸ� (�ƹ��͵� ���� ������) 
        y->left->p = x;//y�� ������ �θ�� (���� y�� ����Ű�� ����) x�� ����Ų��
    }
    y->p = x->p;//y�� �θ�� x�� �θ� �ȴ� ���� y�� �� ���� �ְ� ��
    if (x->p == T->nil) {//x�� �θ� nill�̸�
        T->root = y;//���� y�� ��Ʈ��尡 �ȴ�
    }
    else if (x == x->p->left) {//���� x�� x�� �θ��� ������ ������
        x->p->left = y;//x�� �θ��� ������ y�̴�
    }
    else {
        x->p->right = y;//x�� �θ��� �������� y�̴�
    }
    y->left = x;//y�� ���ʰ��� x�� ����
    x->p = y;//���������� x�� �θ�� y�� �����Ѵ�
}


void RightR(rbtree* T, struct node* y) {//��ȸ�� �Լ�
    struct node* x = y->left;//x�� y�� ���� ���� ���ؼ� y�� ���� �ִٴ� ��
    y->left = x->right;//y������ x�� ������ (��ȸ�� �غ� ���� x�� �������� y�ǿ��� ���� ����)
    if (x->right != T->nil) {//x�� �������� T->nill�� �ƴϸ� (�ƹ��͵� ���� ������) 
        x->right->p = y;//x�� �������� �θ�� (���� x�� ����Ű�� ����) y�� ����Ų��
    }
    x->p = y->p;//x�� �θ�� y�� �θ� �ȴ� ���� x�� �� ���� �ְ� ��
    if (y->p == T->nil) {//y�� �θ� nill�̸�
        T->root = x;//���� x�� ��Ʈ��尡 �ȴ�
    }
    else if (y == y->p->right) {//���� y�� y�� �θ��� �������� ������
        y->p->right = x;//y�� �θ��� ������ x�̴�
    }
    else {
        y->p->left = x;//y�� �θ��� �������� y�̴�
    }
    x->right = y;//x�� �����ʰ��� y�� ����
    y->p = x;//���������� y�� �θ�� x�� �����Ѵ�
}


void RBInsertFixup(rbtree* T, struct node* z) {//RBinsertFixup�Լ�
    while (z->p->color == 1) { //������ ����� �θ� ���� �����϶� ( �ֳĸ� ������ �������� ��尡 ���� ������ �̶� ������ ����)
        if (z->p == z->p->p->left) {//z�� �θ� z�� �θ��� �θ��� ���� �� ��� 
            struct node* y = z->p->p->right; //y�� ����� y�� z�� �θ��� ������ ������ (����?)
            if (y->color == 1) { // ������ ���� ������ ���
                z->p->color = 0; //z�� �θ��� ���� �������� �ٲٰ�
                y->color = 0;//������ ������ �������� �ٲ�
                z->p->p->color = 1;//z�� �θ��� �θ��� ���� �������� �ٲ�
                z = z->p->p;//���� �Ʒ��ʿ��� ������ �ذ�Ǿ����Ƿ� z�� ���θ� z�� ����� �ݺ����� �ٽ� �����Ѵ�
            }
            else {
                if (z == z->p->right) { //z�� z�� �θ��� �������ϰ��
                    z = z->p;// z�� z�� �θ� �ȴ�
                    LeftR(T, z);// ��ȸ�� 
                }
                z->p->color = 0;//z�� �θ��� ���� ������ ��
                z->p->p->color = 1;//z�� �θ��� �θ��� ���� ������ �ȴ�
                RightR(T, z->p->p);//z�� �θ��� �θ� ��ȸ��
            }
        }
        else {
            struct node* y = z->p->p->left; //z�� �θ��� �θ��� ������ y��� ��� ����
            if (y->color == 1) { //y�� ���� ����
                z->p->color = 0;//z�� �θ��� ���� ����
                y->color = 0;//y�� ���� ����
                z->p->p->color = 1;//z�� �θ��� �θ��� ���� ����
                z = z->p->p;//���� �Ʒ��ʿ��� ������ �ذ�Ǿ����Ƿ� z�� ���θ� z�� ����� �ݺ����� �ٽ� �����Ѵ�
            }
            else {
                if (z == z->p->left) { //z�� z�� �θ��� ����
                    z = z->p;//z�� z�� �θ�� �ٲ�
                    RightR(T, z); //��ȸ��
                }
                z->p->color = 0;//z�� �θ��� ���� ���� 
                z->p->p->color = 1;//z�� �θ��� �θ��� ���� ����
                LeftR(T, z->p->p);//z�� �θ��� �θ� ��ȸ��
            }
        }
    }
    T->root->color = 0; //RBTREE�� ��Ʈ�� ���� �������� �ٲ�
}
////////////////////////////////////////�������� ����  ����
// 
// 
// 
// 
// ����-�� Ʈ���� ��带 �����ϴ� �Լ�
void RBInsert(rbtree* T, struct node* z) {
    struct node* y = T->nil; // y�� nil�� �ʱ�ȭ
    struct node* x = T->root; // x�� ��Ʈ ���� �ʱ�ȭ
    while (x != T->nil) { // x�� nil�� �ƴ� ���� �ݺ�
        y = x; // y�� x�� ����
        if (z->data < x->data) { // z�� �����Ͱ� x�� �����ͺ��� ������
            x = x->left; // x�� ���� �ڽ����� ����
        }
        else {
            x = x->right; // x�� ������ �ڽ����� ����
        }
    }
    z->p = y; // z�� �θ� y�� ����
    if (y == T->nil) { // y�� nil�̸�
        T->root = z; // z�� ��Ʈ ���� ����
    }
    else if (z->data < y->data) { // z�� �����Ͱ� y�� �����ͺ��� ������
        y->left = z; // y�� ���� �ڽ��� z�� ����
    }
    else {
        y->right = z; // y�� ������ �ڽ��� z�� ����
    }
    z->left = T->nil; // z�� ���� �ڽ��� nil�� ����
    z->right = T->nil; // z�� ������ �ڽ��� nil�� ����
    z->color = 1; // z�� ���������� ����
    RBInsertFixup(T, z); // ���� �� �Ӽ� ���� �Լ� ȣ��
}

//��ü �Լ�
void RBTransplant(rbtree* T, struct node* u, struct node* v) {
    if (u->p == T->nil) { // u�� �θ� nil�̸�
        T->root = v; // v�� ��Ʈ ���� ����
    }
    else if (u == u->p->left) { // u�� �θ��� ���� �ڽ��̸�
        u->p->left = v; // �θ��� ���� �ڽ��� v�� ����
    }
    else {
        u->p->right = v; // �θ��� ������ �ڽ��� v�� ����
    }
    v->p = u->p; // v�� �θ� u�� �θ�� ����
}

// ����Ʈ������ �ּҰ��� ã�� �Լ�
struct node* TreeMinimum(rbtree* T, struct node* x) {
    while (x->left != T->nil) { // x�� ���� �ڽ��� nil�� �ƴ� ���� �ݺ�
        x = x->left; // x�� ���� �ڽ����� ����
    }
    return x; // �ּҰ� ��� ��ȯ
}
struct node* TreeMaximum(rbtree* T, struct node* x) {
    while (x->right != T->nil) { // x�� ���� �ڽ��� nil�� �ƴ� ���� �ݺ�
        x = x->right; // x�� ���� �ڽ����� ����
    }
    return x; // �ִ밪 ��� ��ȯ
}

struct node* SearchRBtree(rbtree* T, int value) {
    struct node* x = T->root;//��Ʈ���� ã�� ����
    while (x != T->nil && x->data != value) {//x�� nil�� �ƴϰ� x�� value �� ã�� �ʾ�����
        if (x->data < value) {//ũ��
            x = x->right;//����������
        }
        else {
            x = x->left;//�ƴϸ� ��������
        }
    }
    if (x != T->nil) {//ã������ �� node ����
        return x;
    }
    else {//������ NULL
        return NULL;
    }
}

// ����-�� Ʈ�� ���� �� �Ӽ� ���� �Լ�
void RBDeleteFixup(rbtree* T, struct node* x) {
    while (x != T->root && x->color == 0) { // x�� ��Ʈ�� �ƴϰ� �������� ���� �ݺ�
        if (x == x->p->left) { // x�� �θ��� ���� �ڽ��̸�
            struct node* w = x->p->right; // w�� x�� ���� ���
            if (w->color == 1) { // ���� ��尡 �������̸�
                w->color = 0; // ������ ���������� ����
                x->p->color = 1; // �θ� ���������� ����
                LeftR(T, x->p); // ��ȸ��
                w = x->p->right; // ���ο� ���� ����
            }
            if (w->left->color == 0 && w->right->color == 0) { // ������ �� �ڽ��� ��� �������̸�
                w->color = 1; // ������ ���������� ����
                x = x->p; // x�� �θ�� ����
            }
            else {
                if (w->right->color == 0) { // ������ ������ �ڽ��� �������̸�
                    w->left->color = 0; // ������ ���� �ڽ��� ���������� ����
                    w->color = 1; // ������ ���������� ����
                    RightR(T, w); // ��ȸ��
                    w = x->p->right; // ���ο� ���� ����
                }
                w->color = x->p->color; // ������ �θ��� ������ ����
                x->p->color = 0; // �θ� ���������� ����
                w->right->color = 0; // ������ ������ �ڽ��� ���������� ����
                LeftR(T, x->p); // ��ȸ��
                x = T->root; // x�� ��Ʈ�� ����
            }
        }
        else { // x�� �θ��� ������ �ڽ��̸�
            struct node* w = x->p->left; // w�� x�� ���� ���
            if (w->color == 1) { // ���� ��尡 �������̸�
                w->color = 0; // ������ ���������� ����
                x->p->color = 1; // �θ� ���������� ����
                RightR(T, x->p); // ��ȸ��
                w = x->p->left; // ���ο� ���� ����
            }
            if (w->right->color == 0 && w->left->color == 0) { // ������ �� �ڽ��� ��� �������̸�
                w->color = 1; // ������ ���������� ����
                x = x->p; // x�� �θ�� ����
            }
            else {
                if (w->left->color == 0) { // ������ ���� �ڽ��� �������̸�
                    w->right->color = 0; // ������ ������ �ڽ��� ���������� ����
                    w->color = 1; // ������ ���������� ����
                    LeftR(T, w); // ��ȸ��
                    w = x->p->left; // ���ο� ���� ����
                }
                w->color = x->p->color; // ������ �θ��� ������ ����
                x->p->color = 0; // �θ� ���������� ����
                w->left->color = 0; // ������ ���� �ڽ��� ���������� ����
                RightR(T, x->p); // ��ȸ��
                x = T->root; // x�� ��Ʈ�� ����
            }
        }
    }
    x->color = 0; // x�� ���������� ����
}

// ����-�� Ʈ������ ��带 �����ϴ� �Լ�
void RBDelete(rbtree* T, struct node* z) {
    struct node* y = z; // y�� ������ ���� ����
    struct node* x;
    int y_original_color = y->color; // y�� ���� ���� ����
    if (z->left == T->nil) { // z�� ���� �ڽ��� nil�̸�
        x = z->right; // x�� z�� ������ �ڽ����� ����
        RBTransplant(T, z, z->right); // z�� z�� ������ �ڽ����� ��ü
    }
    else if (z->right == T->nil) { // z�� ������ �ڽ��� nil�̸�
        x = z->left; // x�� z�� ���� �ڽ����� ����
        RBTransplant(T, z, z->left); // z�� z�� ���� �ڽ����� ��ü
    }
    else {
        y = TreeMinimum(T, z->right); // y�� z�� ������ ����Ʈ���� �ּҰ����� ����
        y_original_color = y->color; // y�� ���� ���� ����
        x = y->right; // x�� y�� ������ �ڽ����� ����
        if (y->p == z) { // y�� �θ� z�̸�
            x->p = y; // x�� �θ� y�� ����
        }
        else {
            RBTransplant(T, y, y->right); // y�� y�� ������ �ڽ����� ��ü
            y->right = z->right; // y�� ������ �ڽ��� z�� ������ �ڽ����� ����
            y->right->p = y; // y�� ������ �ڽ��� �θ� y�� ����
        }
        RBTransplant(T, z, y); // z�� y�� ��ü
        y->left = z->left; // y�� ���� �ڽ��� z�� ���� �ڽ����� ����
        y->left->p = y; // y�� ���� �ڽ��� �θ� y�� ����
        y->color = z->color; // y�� ���� z�� ������ ����
    }
    free(z); // z�� �޸� ����
    if (y_original_color == 0) { // y�� ���� ���� �������̸�
        RBDeleteFixup(T, x); // ���� �� �Ӽ� ���� �Լ� ȣ��
    }
}
void print_tree(rbtree* T) {
    struct node* stack[100]; // ������ ����� �迭
    int top = -1;
    struct node* current = T->root;

    while (current != T->nil || top != -1) {
        while (current != T->nil) {
            // ���� ��� ���
            printf("%d(%s) ", current->data, current->color == 0 ? "B" : "R");
            stack[++top] = current; // ���� ��带 ���ÿ� ����
            current = current->left; // ���� �ڽ����� �̵�
        }
        current = stack[top--]; // ���ÿ��� ��带 ����
        current = current->right; // ������ �ڽ����� �̵�
    }
    printf("\n"); // �ٹٲ�
}
struct node* TreeSuccessor(struct rbtree* T, struct node* x) {
    if (x->right != T->nil) {//successor�� ������ ����Ʈ������ ���� ���� ���̹Ƿ�
        return TreeMinimum(T,x->right);//�������� ����Ʈ���� �ּڰ�
    }
    struct node* y = x->p;
    while (y != NULL && x == y->right) {//���� ������ ����Ʈ���� ���ٸ� �� �θ�
        x = y;
        y = y->p;
    }
    return y;
}

struct node* TreePredecessor(struct rbtree* T, struct node* x) {
    if (x->left != T->nil) {//predecessor�� ���� ����Ʈ������ ���� ū ���̹Ƿ�
        return TreeMaximum(T, x->left);//�������� ����Ʈ���� �ּڰ�
    }
    struct node* y = x->p;
    while (y != NULL && x == y->left) {//���� ���� ����Ʈ���� ���ٸ� �� �θ�
        x = y;
        y = y->p;
    }
    return y;
}

void MS(struct rbtree* T,struct node* root, FILE* file) {
    if (root == T->nil) {
        return; // NULL�� ��� �Լ� ����
    }
    MS(T,root->left, file); // ���� ����Ʈ���� ���� ��ȸ


    fprintf(file, "�ڽ� %d  ", root->data);


    if (root->p != T->nil) {
        fprintf(file, "�θ� %d  ", root->p->data);
    }
    else { fprintf(file, "�θ� nil  "); }


    if (root->right != T->nil) {
        fprintf(file, "���� �ڽ�%d  ", root->right->data);
    }
    else { fprintf(file, "���� �ڽ� nil  "); }


    if (root->left != T->nil) {
        fprintf(file, "�� �ڽ� %d  ", root->left->data);
    }
    else { fprintf(file, "�� �ڽ� nil  "); }




    if (root->color == 1) {
        fprintf(file, "����\n");
    }
    else { fprintf(file, "����\n"); }

    // ���� ����� �����͸� ���Ͽ� ����
    MS(T,root->right, file); // ������ ����Ʈ���� ���� ��ȸ
}

// Ʈ���� ���� ��ȸ�� ȣ���Ͽ� �����͸� ���Ͽ� �����ϴ� �Լ�
void txtRB(rbtree* T, const char* filename) {
    FILE* file;
    fopen_s(&file, "202235440 ������.txt", "a"); // ������ ���� ���� ����
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }
    MS(T,T->root, file); // ���� ��ȸ �Լ� ȣ��
    fclose(file); // ���� �ݱ�
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
    do {//do while���� �̿��� ���� ����� �ϰ� �۵��� ���� ��ȣ�� ���� ���� ��ȣ�� �ƴҽ� �ٽ� �����ϵ���
        printf("\ns,min,max,n,p,i,t\n");
        scanf_s("%s", command, (unsigned)sizeof(command));
        if (command[0] == 's') {
            printf("������ ã���ðڽ��ϱ�?: ");
            scanf_s("%d", &value, (unsigned)sizeof(value));
            if (SearchRBtree(&T, value) == NULL) { printf("����"); }//�Լ� �������� ������ ����
            else if (SearchRBtree(&T, value) != NULL) { printf("����"); }//�Լ� �������� ������ ����
        }
        if (command[0] == 'm') {
            if (command[1] == 'i') {
                if (T.root != T.nil) {
                    printf("�ּҰ�: %d\n", TreeMinimum(&T, T.root)->data);
                }
                else {
                    printf("Ʈ���� ������ϴ�y.\n");
                }
            }
            if (command[1] == 'a') {
                if (T.root != T.nil) {
                    printf("�ִ�: %d\n", TreeMaximum(&T, T.root)->data);
                }
                else {
                    printf("Ʈ���� ������ϴ�.\n");
                }
            }
        }
        if (command[0] == 'n') {
        printf("����� �������� ã���ðڽ��ϱ�?: ");
        scanf_s("%d", &value, (unsigned)sizeof(value));
        next = TreeSuccessor(&T, SearchRBtree(&T, value));
        if (next != T.nil) {
            printf(" % d�� ���� ����: % d\n", value, next->data);
        }
        else {
            printf("�������� �������� �ʽ��ϴ�.\n");
            }
        }
        if (command[0] == 'p') {
        printf("����� �������� ã���ðڽ��ϱ�?: ");
        scanf_s("%d", &value, (unsigned)sizeof(value));
        prev = TreePredecessor(&T, SearchRBtree(&T, value));
        if (prev != T.nil) {
            printf("%d�� ��������: %d\n", value, prev->data);
        }
        else {
            printf("���� ���� �������� �ʽ��ϴ�.\n");
            }
        }
        if (command[0] == 'i') {
            printf("����� �߰��Ͻðڽ��ϱ�?: ");
            scanf_s("%d", &value, (unsigned)sizeof(value));
            new_node = create_node(&T,value, 1);
            RBInsert(&T, new_node);
            printf("%d �� Ʈ���� �־����ϴ�.\n", value);
        }
        if (command[0] == 't') {
            printf("����.\n");
            txtRB(&T, "������");
    }
} while (command[0] != 't');

    free(T.nil);
    return 0;
}
