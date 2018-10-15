#include <iostream>
#include <malloc.h>
#include <stdio.h>
using namespace std;

#define MaxSize 50 // 顺序线性表的长度

typedef int ElemType; // 自定义类型，假设 ElemType 为 int 类型

typedef struct
{
    ElemType data[MaxSize]; // 存放顺序线性表中元素
    int length;             // 存放顺序线性表的长度
} SqList;                   // 顺序线性表的类型定义

/* 创建顺序线性表 */
void CreateList(SqList *&L, ElemType a[], int n) // 由 a 中的 n 个元素建立顺序线性表
{
    int i;
    L = (SqList *)malloc(sizeof(SqList)); // 分配存放顺序线性表的空间
    for (i = 0; i < n; i++)               // 放置数据元素
        L->data[i] = a[i];
    L->length = n; // 设置长度
}

/* 初始化顺序线性表 */
void InitList(SqList *&L)
{
    L = new SqList; // 分配存放顺序线性表的空间
    L->length = 0;  // 置空顺序线性表长度为 0
}

/* 销毁顺序线性表 */
void DestroyList(SqList *&L)
{
    free(L); // 释放顺序线性表 L 占用的内存空间
}

/* 判断顺序线性表是否为空表 */
bool ListEmpty(SqList *L)
{
    return (L->length == 0); // 如果 L 为空表，则返回 true，否则返回 false
}

/* 求顺序线性表长度 */
int ListLength(SqList *L)
{
    return (L->length); // 返回 length 域的值
}

/* 输出顺序线性表 */
void DispList(SqList *L)
{
    int i;
    for (i = 0; i < L->length; i++) // 扫描顺序线性表输出各元素值
        cout << L->data[i] << " ";
    cout << "\n";
}

/* 求顺序线性表中某个数据元素值 */
bool GetElem(SqList *L, int i, ElemType &e)
{
    if (i < 1 || i > L->length) // 参数错误时返回 false
        return false;
    e = L->data[i - 1]; // 取元素值
    return true;        // 成功找到元素时返回 true
}

/* 按元素值查找 */
int LocateElem(SqList *L, ElemType e)
{
    int i = 0;
    while (i < L->length && L->data[i] != e) // 循环查找元素 e
        i++;
    if (i > L->length) // 未查找到时返回 0
        return 0;
    else
        return i + 1; // 找到后返回其逻辑序号
}

/* 插入数据元素 */
bool ListInsert(SqList *&L, int i, ElemType e)
{
    int j;
    if (i < 1 || i > L->length + 1)
        return false;               // 参数错误时返回 false
    i--;                            // 将顺序线性表逻辑序号转化为物理序号
    for (j = L->length; j > i; j--) // 将 data[i] 及后面元素后移一个位置
        L->data[j] = L->data[j - 1];
    L->data[i] = e; // 插入元素 e
    L->length++;    // 顺序线性表长度 加1
    return true;    // 成功插入返回 true
}

/* 删除数据元素 */
bool ListDelete(SqList *&L, int i, ElemType &e)
{
    int j;
    if (i < 1 || i > L->length) // 参数错误时返回 false
        return false;
    i--; // 将逻辑序号转化为物理序号
    e = L->data[i];
    for (j = i; j < L->length; j++) // 将 data[i] 之后的元素前移一个位置
        L->data[j] = L->data[j + 1];
    L->length--; // 顺序线性表长度 减1
    return true; // 成功删除返回 true
}

/* 两个线性表元素的并集 */
void unionList(SqList *LA, SqList *LB, SqList *&LC)
{
    int lena, i;
    ElemType e;
    InitList(LC);
    for (i = 1; i <= ListLength(LA); i++) // 将 LA 的所有元素插入到 LC 中
    {
        GetElem(LA, i, e);
        ListInsert(LC, i, e);
    }
    lena = ListLength(LA); // 求线性表 LA 的长度
    for (i = 1; i <= ListLength(LB); i++)
    {
        GetElem(LB, i, e);      // 取 LB 中第 i 个元素赋给 e
        if (!LocateElem(LA, e)) // LA 中不存在和 e 相同的元素，则插入到 LC 中
            ListInsert(LC, ++lena, e);
    }
}

/* 方法1：删除 L 中所有等于 x 的元素 */
void delnode1(SqList *&L, ElemType x)
{
    int k = 0, i;
    for (i = 0; i < L->length; i++)
        if (L->data[i] != x)
        {
            L->data[k] = L->data[i];
            k++;
            // 可以简化
            // L->data[k++] = L->data[i];
        }
    L->length = k;
}

/* 方法2：删除 L 中所有等于 x 的元素 */
void delnode2(SqList *&L, ElemType x)
{
    int k = 0, i = 0; // k 记录值为 x 的元素个数
    while (i < L->length)
    {
        if (L->data[i] == x)
            k++;
        else
            L->data[i - k] = L->data[i]; // 当前元素前移 k 个位置
        i++;
    }
    L->length -= k; // 顺序表 L 的长度递减 k
}

/* 以第一个元素为分界线，小于的元素元素移到左边，大于的元素移到右边 */
void move1(SqList *&L)
{
    int i = 0, j = L->length - 1;
    ElemType pivot = L->data[0]; // 以 dta[0] 为基准
    ElemType tmp;
    while (i < j) // 从区间两端交替向中间扫描，直至 i=j 为止
    {
        while (i < j && L->data[j] > pivot)
            j--; // 从右向左扫描，找到第 1 个小于等于 pivot 的元素
        while (i < j && L->data[i] <= pivot)
            i++; // 从左向右扫描，找到第 1 个大于 pivot 的元素
        if (i < j)
        {
            tmp = L->data[i]; // L->data[i] 和 L->data[j] 进行交换
            L->data[i] = L->data[j];
            L->data[j] = tmp;
        }
        // 输出每一趟的结果
        for (int a = 0; a < L->length; a++)
            cout << L->data[a] << " ";
        cout << endl;
    }
    tmp = L->data[0]; // L->data[0] 和 L->data[j] 进行交换
    L->data[0] = L->data[j];
    L->data[j] = tmp;
    cout << "基准位置（下标） i=" << i << endl;
}

void move2(SqList *&L)
{
    int i = 0, j = L->length - 1;
    ElemType pivot = L->data[0]; // 以 data[0] 为基准
    while (i < j)                // 从顺序表两端交替向中间扫描，直至 i=j 为止
    {
        while (j > i && L->data[j] > pivot)
            j--;                 // 从右向左扫描，找一个小于等于 pivot 的 data[j]
        L->data[i] = L->data[j]; // 找到这样的 data[j]，放入 data[i] 处
        i++;
        while (i < j && L->data[i] <= pivot)
            i++;                 // 从左向右扫描，找一个大于 pivot 的 data[i]
        L->data[j] = L->data[i]; // 找到这样的 data[i],放入 data[j] 处
        j--;

        // 显示每一趟的结果
        for (int a = 0; a < L->length; a++)
            cout << L->data[a];
        cout << endl;
    }
    L->data[i] = pivot;
    cout << "基准位置（下标） i=" << i << endl;
}

/* 测试1 顺序表 */
void test01()
{
    SqList *L;
    ElemType e;
    InitList(L); // 初始化顺序线性表
    int i;
    for (i = 1; i <= 5; i++) // 依次插入 5 个元素
        ListInsert(L, i, i);
    cout << "ListLength(L) = " << ListLength(L) << endl; // 顺序线性表长度
    cout << "ListEmpty(L) = " << ListEmpty(L) << endl;   // 判断是否为空表
    GetElem(L, 3, e);                                    // 获取第3个元素值
    cout << "e = " << e << endl;
    cout << "LocateElem(L, 1) = " << LocateElem(L, 1) << endl; // 查找是否存在元素值1
    ListInsert(L, 4, 5);                                       // 在第4个位置插入5
    DispList(L);                                               // 输出顺序线性表 L 各元素值
    ListDelete(L, 3, e);                                       // 删除第3个元素值
    DispList(L);                                               // 输出顺序线性表 L 各元素值
    DestroyList(L);                                            // 销毁顺序线性表 L 所占用内存空间
}

/* 测试2 unionList */
void test02()
{
    SqList *LA, *LB, *LC;
    InitList(LA);
    InitList(LB);
    /* 构造LA = {1, 3, 2} */
    ListInsert(LA, 1, 1);
    ListInsert(LA, 2, 3);
    ListInsert(LA, 3, 2);
    cout << "LA:";
    DispList(LA);
    /* 构造LB = {1, 4, 2} */
    ListInsert(LB, 1, 1);
    ListInsert(LB, 2, 4);
    ListInsert(LB, 3, 2);
    cout << "LB:";
    DispList(LB);
    /* 将 LA 和 LB 元素值的并集插入到 LC */
    unionList(LA, LB, LC);
    cout << "LC=LA∪LB" << endl;
    cout << "LC:";
    DispList(LC);
    /* 销毁 LA, LB, LC 占用内存 */
    DestroyList(LA);
    DestroyList(LB);
    DestroyList(LC);
}

/* 测试3 delnode1 && delnode2 */
void test03()
{
    ElemType a[] = {1, 2, 2, 1, 0, 2, 4, 2, 3, 1};
    ElemType x = 2;
    SqList *L;
    CreateList(L, a, 10);
    cout << "L:";
    DispList(L);
    cout << "删除值为 " << x << " 的元素" << endl;
    // delnode1(L, x);
    delnode2(L, x);
    cout << "L:";
    DispList(L);
    DestroyList(L);
}

/* 测试4 move1 && move2 */
void test04()
{
    SqList *L;
    // ElemType a[] = {3, 8, 2, 7, 1, 5, 3, 4, 6, 0};
    ElemType a[] = {3, 8, 2, 7, 3, 5, 3, 4, 6, 0};
    CreateList(L, a, 10);
    cout << "L:";
    DispList(L);
    cout << "执行移动运算\n";
    // move1(L);
    move2(L);
    cout << "L:";
    DispList(L);
    DestroyList(L);
}

int main()
{
    // test01()；
    // test02()；
    // test03();
    test04();
    return 0;
}
