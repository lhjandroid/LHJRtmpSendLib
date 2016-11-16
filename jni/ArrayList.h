//ArrayList.h


/*-----------------------------
*
* For    算法数据结构
* IDE    DEV-CPP4.9.2
* Auhtor  Czp
* Date   2012/11/4
*------------------------------
*/
//防止重复导入
#ifndef       MY_ARRAY_LIST_H
#define       MY_ARRAY_LIST_H

/**
 * _NaluUnit
 * 内部结构体。该结构体主要用于存储和传递Nal单元的类型、大小和数据
 */
typedef struct _NaluUnit
{
	int type;
    int size;
	unsigned char *data;
}NaluUnit;

//如果C++里调用,采用C编译器
#ifdef __cplusplus
   extern "C" {
#endif

//检查是否成功申请内存
#define Asert(par) if(par==NULL) {\
                printf("%s,%d malloc null",__FILE__,__LINE__);\
                return NULL;}
#define INIT_SIZE 100    //默认的数组大小

typedef NaluUnit Element;    //定义List里的元素类型
typedef void (*PrtFun)(Element);//打印函数
typedef int  (*CmpFun)(Element,Element);//比较函数
typedef struct _ArrayList{ //定义ArrayList

      Element *data; //List的元素
      size_t   size; //List可以容纳个数
      size_t   index;//当前已有元素索引
      CmpFun   cmpFun;//比较函数指针
      PrtFun   ptrFun;//打印函数指针

}ArrayList;


/*********************************
*@desc:创建ArrayList
*@return: NULL->内存申请失败
          arr->指向ArrayList的指针
**********************************
*/
ArrayList *createArrayList(CmpFun cmp,PrtFun pfun)
{
      //申请数组的内存
      ArrayList *arr = (ArrayList *)malloc(sizeof(ArrayList));
      Asert(arr);
      Element *data = (Element *)malloc(INIT_SIZE*sizeof(Element));
      Asert(data);
      arr->data  = data;
      arr->index = 0;
      arr->size  = INIT_SIZE;
      arr->cmpFun = cmp;
      arr->ptrFun = pfun;
      return arr;
}
/*******************************
*@desc: 释放ArrayList占有的内存
******************************
*/
void desrotyArrList(ArrayList *arr)
{
     if(arr!=NULL)
     {
       free(arr->data); //释放数组占用的内存
       free(arr);       //释放结构体占用的内存
     }
}

/*************************************
*@desc: 检查链表的剩余空间,不够则申请
*@param: arr->要检查的链表
*@notice: 本函数不检查参数是否合法
*************************************
*/
static Element *checkAndPre(ArrayList *arr)
{
     size_t index = arr->index;
     size_t size  = arr->size;
     //没有足够的空间
     if(index>=size)
     {
        //申请size+INIT_SIZE
        size_t newSize = INIT_SIZE+size;
        Element *newData = (Element*)malloc(newSize*sizeof(Element));
        Asert(newData);
        Element *src = arr->data;
        //复制原来的数据
        size_t i;
        for(i=0;i<index;i++)
           newData[i] = src[i];
        //释放原来的数据占据的空间
        free(src);
        arr->data = newData;
        arr->size = newSize;
        return newData;
     }
     return arr->data;
}

/****************************
*@desc: 在末尾添加元素
*@param: arr->对那个arrlist添加
*@parm: elm->要添加的元素
*@return:1->成功
         0->失败
******************************
*/
int addElement(ArrayList *arr, Element elm)
{
    if(arr!=NULL)
    {
       //检查剩余空间
       if(checkAndPre(arr)!=NULL)
       {
          Element *els = arr->data;
          els[arr->index++] = elm;
          return 1;
       }
    }
    return 0;
}
/****************************
*@desc: 把指定的位置设置为elm
*@param: arr->待插入的列表
*@param: elm->待插入的元素
*@param: i->待设置的位置
*@return:1->成功
         0->失败
*****************************
*/
int setElement(ArrayList *arr,Element elm,size_t i)
{
     if(arr!=NULL||i>=arr->index)
     {
          Element *els = arr->data;
          els[i] = elm;
          return 1;
     }
     return 0;
}

/************************
*@desc: 打印ArrayList
*@param:arr->要打印的列表
*@param:fun->打印函数
*************************
**/
void printArrayList(ArrayList *arr)
{
   if(arr!=NULL)
   {
      Element *data = arr->data;
      if(data!=NULL)
       {
          size_t i;
          for(i=0;i<arr->index;i++)
               arr->ptrFun(*data++);
       }
   }
}
/************************
*@desc:列表是否为空
*param:arr->待检查的列表
*@return:1->非空 0->空
******************* ****
*/
int isEmpty(ArrayList *arr)
{
    if(arr!=NULL)
          return arr->index>0;
    return 0;
}

/**************************************
*@desc:获取指定位置的元素
*@param:arr->待查找的列表
*@param:index->索引
*@return:NULL->索引错误否则返回元素指针
***************************************
*/
Element getElement(ArrayList *arr,size_t index)
{
//     if(arr==NULL||index>=arr->index)
//         return NULL;
      return arr->data[index];
}

/**************************
*@desc:获取某个元素的位置
*@param:arr>列表
*@param:elm->元素
*@param:  fun->比较函数
*@return:-1->找不到
**************************
*/
int arrLstIndexof(ArrayList *arr,Element elm)
{
    if(arr!=NULL)
    {
         Element *data = arr->data;
         size_t i;
         for(i=0;i<arr->index;i++)
               if(arr->cmpFun(data[i],elm)==0)
                    return i;
    }
    return -1;
}


/*************************
*@desc：是否包含指定的元素
*@param: elm->元素
*@param:  arr->列表
*@param:  fun->比较函数
*return 0->包含 -1->不包含
****************************
*/
int  contains(ArrayList *arr,Element elm)
{
   return arrLstIndexof(arr,elm)>0?0:-1;
}


/************************
*@desc:移除指定的元素
*@param:arr->待操作的列表
*@param:elm->要移除的元素
*@param:fun->比较函数
*@return:0->失败1->成功
**************************
*/
int  removeElement(ArrayList *arr,Element elm)
{
     if(arr!=NULL&&arr->data!=NULL)
     {
        int i =  arrLstIndexof(arr,elm);
        if(i>0)
        {
           Element *data = arr->data;
           arr->index--;
           for(;i<arr->index;i++)
           {
               data[i] = data[i+1];
           }
           return 1;
        }
     }
     return 0;
}

/************************
*@desc:移除指定的元素
*@param:arr->待操作的列表
*@param:elm->要移除的元素
*@param:fun->比较函数
*@return:0->失败1->成功
**************************
*/
int  removeElement1(ArrayList *arr,int pos)
{
     if(arr!=NULL&&arr->data!=NULL)
     {
        int i =  pos;
        Element *data = arr->data;
        arr->index--;
        for(;i<arr->index;i++)
        {
        	data[i] = data[i+1];
        }
        return 1;
     }
     return 0;
}

int getListSize(ArrayList *arr) {
	return arr->size;
}

#ifdef __cplusplus
   }
#endif

#endif //end with ifndef ARRAY_LIST_H
