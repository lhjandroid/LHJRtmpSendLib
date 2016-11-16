//ArrayList.h


/*-----------------------------
*
* For    �㷨���ݽṹ
* IDE    DEV-CPP4.9.2
* Auhtor  Czp
* Date   2012/11/4
*------------------------------
*/
//��ֹ�ظ�����
#ifndef       MY_ARRAY_LIST_H
#define       MY_ARRAY_LIST_H

/**
 * _NaluUnit
 * �ڲ��ṹ�塣�ýṹ����Ҫ���ڴ洢�ʹ���Nal��Ԫ�����͡���С������
 */
typedef struct _NaluUnit
{
	int type;
    int size;
	unsigned char *data;
}NaluUnit;

//���C++�����,����C������
#ifdef __cplusplus
   extern "C" {
#endif

//����Ƿ�ɹ������ڴ�
#define Asert(par) if(par==NULL) {\
                printf("%s,%d malloc null",__FILE__,__LINE__);\
                return NULL;}
#define INIT_SIZE 100    //Ĭ�ϵ������С

typedef NaluUnit Element;    //����List���Ԫ������
typedef void (*PrtFun)(Element);//��ӡ����
typedef int  (*CmpFun)(Element,Element);//�ȽϺ���
typedef struct _ArrayList{ //����ArrayList

      Element *data; //List��Ԫ��
      size_t   size; //List�������ɸ���
      size_t   index;//��ǰ����Ԫ������
      CmpFun   cmpFun;//�ȽϺ���ָ��
      PrtFun   ptrFun;//��ӡ����ָ��

}ArrayList;


/*********************************
*@desc:����ArrayList
*@return: NULL->�ڴ�����ʧ��
          arr->ָ��ArrayList��ָ��
**********************************
*/
ArrayList *createArrayList(CmpFun cmp,PrtFun pfun)
{
      //����������ڴ�
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
*@desc: �ͷ�ArrayListռ�е��ڴ�
******************************
*/
void desrotyArrList(ArrayList *arr)
{
     if(arr!=NULL)
     {
       free(arr->data); //�ͷ�����ռ�õ��ڴ�
       free(arr);       //�ͷŽṹ��ռ�õ��ڴ�
     }
}

/*************************************
*@desc: ��������ʣ��ռ�,����������
*@param: arr->Ҫ��������
*@notice: ���������������Ƿ�Ϸ�
*************************************
*/
static Element *checkAndPre(ArrayList *arr)
{
     size_t index = arr->index;
     size_t size  = arr->size;
     //û���㹻�Ŀռ�
     if(index>=size)
     {
        //����size+INIT_SIZE
        size_t newSize = INIT_SIZE+size;
        Element *newData = (Element*)malloc(newSize*sizeof(Element));
        Asert(newData);
        Element *src = arr->data;
        //����ԭ��������
        size_t i;
        for(i=0;i<index;i++)
           newData[i] = src[i];
        //�ͷ�ԭ��������ռ�ݵĿռ�
        free(src);
        arr->data = newData;
        arr->size = newSize;
        return newData;
     }
     return arr->data;
}

/****************************
*@desc: ��ĩβ���Ԫ��
*@param: arr->���Ǹ�arrlist���
*@parm: elm->Ҫ��ӵ�Ԫ��
*@return:1->�ɹ�
         0->ʧ��
******************************
*/
int addElement(ArrayList *arr, Element elm)
{
    if(arr!=NULL)
    {
       //���ʣ��ռ�
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
*@desc: ��ָ����λ������Ϊelm
*@param: arr->��������б�
*@param: elm->�������Ԫ��
*@param: i->�����õ�λ��
*@return:1->�ɹ�
         0->ʧ��
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
*@desc: ��ӡArrayList
*@param:arr->Ҫ��ӡ���б�
*@param:fun->��ӡ����
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
*@desc:�б��Ƿ�Ϊ��
*param:arr->�������б�
*@return:1->�ǿ� 0->��
******************* ****
*/
int isEmpty(ArrayList *arr)
{
    if(arr!=NULL)
          return arr->index>0;
    return 0;
}

/**************************************
*@desc:��ȡָ��λ�õ�Ԫ��
*@param:arr->�����ҵ��б�
*@param:index->����
*@return:NULL->����������򷵻�Ԫ��ָ��
***************************************
*/
Element getElement(ArrayList *arr,size_t index)
{
//     if(arr==NULL||index>=arr->index)
//         return NULL;
      return arr->data[index];
}

/**************************
*@desc:��ȡĳ��Ԫ�ص�λ��
*@param:arr>�б�
*@param:elm->Ԫ��
*@param:  fun->�ȽϺ���
*@return:-1->�Ҳ���
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
*@desc���Ƿ����ָ����Ԫ��
*@param: elm->Ԫ��
*@param:  arr->�б�
*@param:  fun->�ȽϺ���
*return 0->���� -1->������
****************************
*/
int  contains(ArrayList *arr,Element elm)
{
   return arrLstIndexof(arr,elm)>0?0:-1;
}


/************************
*@desc:�Ƴ�ָ����Ԫ��
*@param:arr->���������б�
*@param:elm->Ҫ�Ƴ���Ԫ��
*@param:fun->�ȽϺ���
*@return:0->ʧ��1->�ɹ�
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
*@desc:�Ƴ�ָ����Ԫ��
*@param:arr->���������б�
*@param:elm->Ҫ�Ƴ���Ԫ��
*@param:fun->�ȽϺ���
*@return:0->ʧ��1->�ɹ�
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
