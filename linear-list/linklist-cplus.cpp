#include <iostream>
#include <malloc.h>
#include <stdio.h>
using namespace std;

typedef int ElemType; // 自定义类型，假设 ElemType 为 int 类型

typedef struct LNode // 定义单链表节点类型
{
    ElemType data;      // 存放元素值
    struct LNode *next; // 指向后继节点
} LinkList;

/* 头插法建立单链表 */
void CreateListF(LinkList *&L, ElemType a[], int n)
{
    LinkList *s;
    int i;
    L = (LinkList *)malloc(sizeof(LinkList)); // 创建头节点
    L->next = NULL;                           // 将 next 域置为 NULL
    for (i = 0; i < n; i++)                   // 循环建立数据节点
    {
        s = (LinkList *)malloc(sizeof(LinkList)); // 创建新数据节点 *s
        s->data = a[i];
        s->next = L->next; // 将 *s 插在原开始节点之前, 头节点之后
        L->next = s;
    }
}

/* 尾插法建立单链表 */
void CreateListR(LinkList *&L, ElemType a[], int n)
{
    LinkList *s, *r;
    int i;
    L = (LinkList *)malloc(sizeof(LinkList)); // 创建头节点
    L->next = NULL;
    r = L;                  // r 始终指向尾节点, 开始时指向头节点
    for (i = 0; i < n; i++) // 循环建立数据节点
    {
        s = (LinkList *)malloc(sizeof(LinkList)); // 创建新节点 *s
        s->data = a[i];
        r->next = s; // 将 *s 插入 *r 之后
        r = s;
    }
    r->next = NULL; // 尾节点 next 域置为 NULL
}

/* 初始化单链表 */
void InitList(LinkList *&L)
{
    L = (LinkList *)malloc(sizeof(LinkList)); // 创建头节点
    L->next = NULL;
}

/* 销毁单链表 */
void DestroyList(LinkList *&L)
{
    LinkList *p = L, *q = p->next; // p 指向 *q 的前驱节点
    while (q != NULL)              // 扫描单链表 L
    {
        free(p); // 释放 *p 节点
        p = q;   // p 和 q 同步后移一个节点
        q = p->next;
    }
    free(p); // 此时 q 为 NULL, p 指向尾节点, 释放它
}

/* 判断单链表是否为空 */
bool ListEmpty(LinkList *L)
{
    return (L->next == NULL); // 如果 单链表 L 没有数据节点，返回 true, 否则返回 false
}

/* 求单链表的长度 */
int ListLength(LinkList *L)
{
    LinkList *p = L; // p 指向头节点
    int i = 0;       // 头节点的序号
    while (p->next != NULL)
    {
        i++;
        p = p->next;
    }
    return (i); // 循环结束, p 指向尾节点，其序号 i 为节点个数
}

/* 输出单链表所有数据节点 */
void DispList(LinkList *L)
{
    LinkList *p = L->next; // p 指向开始节点
    while (p != NULL)      // p 不为 NULL, 输出 *p 节点的 data 域
    {
        cout << p->data << " ";
        p = p->next; // p 移向下一个节点
    }
    cout << endl;
}

/* 求单链表中某个数据元素值 */
bool GetElem(LinkList *L, int i, ElemType &e)
{
    int j = 0;
    LinkList *p = L;           // p 指向头节点，j 置为 0
    while (j < i && p != NULL) // 找到第 j 个节点
    {
        j++;
        p = p->next;
    }
    if (p == NULL) // 不存在第 i 个数据节点
        return false;
    else // 存在第 i 个数据节点
    {
        e = p->data;
        return true;
    }
}

/* 按元素查找 */
int LocateElem(LinkList *L, ElemType e)
{
    int n = 1;
    LinkList *p = L->next;            // p 指向开始节点，n 置为 1
    while (p != NULL && p->data != e) // 查找 data 值为 e 的节点，其序号为 n
    {
        p = p->next;
        n++;
    }
    if (p == NULL) // 不存在元素值为 e 的节点，返回 0
        return (0);
    else // 存在元素值为 e 的节点，返回其逻辑序号 n
        return (n);
}

/* 插入数据元素 */
bool ListInsert(LinkList *&L, int i, ElemType e)
{
    int j = 0;
    LinkList *p = L, *s;           // p 指向头节点, j 置为 0（即头节点的序号为 0）
    while (j < i - 1 && p != NULL) // 查找第 i-1 个节点
    {
        j++;
        p = p->next;
    }
    if (p == NULL) // 未找到第 i-1 个节点, 返回 false
        return false;
    else // 找到第 i-1 个节点 *p, 插入新节点并返回 false
    {
        s = (LinkList *)malloc(sizeof(LinkList)); // 创建新节点 *s, 其 data 域置为 e
        s->data = e;
        s->next = p->next; // 将 *s 插入到 *p 之后
        p->next = s;
        return true;
    }
}

/* 删除数据元素 */
bool ListDelete(LinkList *&L, int i, ElemType &e)
{
    int j = 0;
    LinkList *p = L, *q;
    while (j < i - 1 && p != NULL) // 查找第 i-1 个节点
    {
        j++;
        p = p->next;
    }
    if (p == NULL) // 未找到第 i-1 个节点, 返回 false
        return false;
    else // 找到第 i-1 个节点 *p
    {
        q = p->next; //q 指向要删除的节点（第 i 个节点）
        if (q == NULL)
            return false; // 若不存在第 i 个节点, 返回 false
        e = q->data;
        p->next = q->next; // 从单链表中删除 *q 节点
        free(q);           // 释放 *q 节点
        return true;       // 返回 true 表示成功删除第 i 个节点
    }
}

/* 将单链表 L 拆分成两个单链表 L1 和 L2 */
void split(LinkList *&L, LinkList *&L1, LinkList *&L2)
{
    LinkList *p = L->next, *q, *r1;            // p 指向第 1 个数据节点
    L1 = L;                                    // L1 利用原来 L 的头节点
    r1 = L1;                                   // r1 始终指向 L1 的尾节点
    L2 = (LinkList *)malloc(sizeof(LinkList)); // 创建 L2 的头节点
    L2->next = NULL;                           // 置 L2 的指针域为 NULL
    while (p != NULL)
    {
        /* 尾插法建立单链表 L1 */
        r1->next = p; // 采用尾插法将 *p (data 值为 ai) 插入 L1 中
        r1 = p;
        p = p->next; // p 移向下一个节点 (data 值为 bi)
        q = p->next; // 由于头插法修改 p 的 next 域, 故用 q 保存 * p 的后继节点
        /* 头插法建立单链表 L2 */
        p->next = L2->next; // 采用头插法将 *p 插入 L2 中
        L2->next = p;
        p = q; // p 重新指向 ai+1 的节点
    }
    r1->next = NULL; // 尾节点 next 置空
}

int main()
{
    LinkList *L, *L1, *L2;
    int n = 10;
    ElemType a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    InitList(L);
    InitList(L1);
    InitList(L2);
    CreateListR(L, a, n);
    cout << "L:";
    DispList(L);
    cout << "L->L1, L2\n";
    split(L, L1, L2);
    cout << "L1:";
    DispList(L1);
    cout << "L2:";
    DispList(L2);
    DestroyList(L1);
    DestroyList(L2);
    return 0;
}