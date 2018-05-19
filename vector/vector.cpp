// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Windows.h>

#define SUCCESS 1
#define ERROR -1
#define MALLOC_ERROR -2
#define INDEX_ERRC -3


template <class  T_ELE>
class Vector
{
	//构造、析构函数
public:
	Vector();
	Vector(DWORD dwSize);
	~Vector();
	//公有函数
public:
	DWORD    at(DWORD dwIndex, OUT T_ELE* pEle);        //根据给定的索引得到元素                    
	DWORD    push_back(T_ELE Element);                  //将元素存储到容器最后一个位置
	VOID     pop_back();                                //删除最后一个元素
	DWORD    insert(DWORD dwIndex, T_ELE Element);      //向指定位置新增一个元素
	DWORD    capacity();                                //返回 在不增容的情况下，还能存储多少个元素
	DWORD    clear();                                   //清空所有元素
	BOOL     empty();                                   //判断Vector是否为空 返回true为空
	VOID     erase(DWORD dwIndex);                      //删除指定元素
	DWORD    size();                                    //返回Vector元素数量大小
														//私有变量
private:
	BOOL expand();                                      //增容函数
private:
	DWORD m_dwIndex;                                   //下一个可用索引
	DWORD m_dwIncrement;                               //每次增容的大小
	DWORD m_dwLen;                                     //当前容器的长度
	DWORD m_dwIniSize;                                 //默认初始化大小
	T_ELE* m_pVector;                                  //容器指针
};




//无参构造函数
template<class T_ELE>
Vector<T_ELE>::Vector()
	:m_dwIniSize(10), m_dwIncrement(5)
{
	//1.创建初始长度为m_dwIniSize个T_ELE对象
	m_pVector = new T_ELE[m_dwIniSize];
	//2.将创建的空间初始化为0
	memset(m_pVector, 0, m_dwIniSize * sizeof(T_ELE));
	//3.设置其他值
	m_dwLen = m_dwIniSize;
	m_dwIndex = 0;

}



//有参构造函数
template<class T_ELE>
Vector<T_ELE>::Vector(DWORD dwSize)
	:m_dwIncrement(5)
{
	//堆中分配dwsize个T_ELE类型大小的字节
	m_pVector = new T_ELE[dwSize];
	//初始化
	memset(m_pVector, 0, dwSize * sizeof(T_ELE));
	//设置其他值
	m_dwLen = dwSize;
	m_dwIndex = 0;
}

//析构函数
template<class T_ELE>
Vector<T_ELE>::~Vector()
{
	delete[] m_pVector;
	m_pVector = NULL;
}

template<class T_ELE>
DWORD Vector<T_ELE>::at(DWORD dwIndex, OUT T_ELE* pEle)
{
	if (dwIndex < 0 || dwIndex >= m_dwIndex)
	{
		return INDEX_ERRC;
	}
	memcpy(pEle, &m_pVector[dwIndex], sizeof(T_ELE));
}

//将元素存储到容器最后一个位置
template<class T_ELE>
DWORD Vector<T_ELE>::push_back(T_ELE Element)
{
	//1.判断是否需要增容，如果需要就调用增容函数
	if (m_dwIndex >= m_dwLen)
	{
		expand();
	}
	//2.将新的元素复制到容器的最后一个位置
	memcpy(&m_pVector[m_dwIndex], &Element, sizeof(T_ELE));
	//3.修改属性
	m_dwIndex++;

	return SUCCESS;
}

template<class T_ELE>
VOID Vector<T_ELE>::pop_back()
{
	memset(&m_pVector[m_dwIndex - 1], 0, sizeof(T_ELE));
	m_dwIndex--;
	m_dwLen--;
	return;
}

//插入函数
template<class T_ELE>
DWORD Vector<T_ELE>::insert(DWORD dwIndex, T_ELE Element)
{
	//1.判断索引是否发生错误
	if (dwIndex < 0 || dwIndex > m_dwIndex)
	{
		return INDEX_ERRC;
	}
	//2.判断是否要进行增容
	if (m_dwIndex >= m_dwLen)
	{
		expand();
	}
	//3.将dwIndex之后的元素后移
	for (int i = m_dwIndex;i > dwIndex;i--)
	{
		memcpy(&m_pVector[i], &m_pVector[i - 1], sizeof(T_ELE));
	}
	//4.插入操作
	memcpy(&m_pVector[dwIndex], &Element, sizeof(T_ELE));
	//5.修改相应属性
	m_dwIndex++;
	m_dwLen++;
}

//返回 在不增容的情况下，还能存储多少个元素
template<class T_ELE>
DWORD Vector<T_ELE>::capacity()
{
	DWORD space = 0;
	space = m_dwLen - m_dwIndex;
	printf("未增容时可用空间：%x\n", space);
	return space;

}

template<class T_ELE>
DWORD Vector<T_ELE>::clear()
{
	for (int i = m_dwIndex; i > 0; i--)
	{
		memset(&m_pVector[i - 1], 0, sizeof(T_ELE));
	}

	m_dwIndex = 0;
	return SUCCESS;
}

template<class T_ELE>
BOOL Vector<T_ELE>::empty()
{
	BOOL sign;
	for (int k = m_dwIndex;; k--)
	{
		if (k == 0)
		{
			sign = true;
			return sign;
		}
		if (m_pVector[k - 1] != NULL)
		{
			sign = false;
			break;
		}

	}
	return sign;
}

template<class T_ELE>
VOID Vector<T_ELE>::erase(DWORD dwIndex)
{
	if (dwIndex < 0 || dwIndex > m_dwIndex)
	{
		return;
	}

	memset(&m_pVector[dwIndex], 0, sizeof(T_ELE));

	for (int m = dwIndex + 1;m<m_dwLen;m++)
	{
		memcpy(&m_pVector[m - 1], &m_pVector[m], sizeof(T_ELE));
	}
	memset(&m_pVector[m_dwIndex - 1], 0, sizeof(T_ELE));
	m_dwIndex--;
	m_dwLen--;
}

template<class T_ELE>
DWORD Vector<T_ELE>::size()
{
	return m_dwIndex;
}

//增容函数
template<class T_ELE>
BOOL Vector<T_ELE>::expand()
{
	DWORD dwNewLen = 0;

	//1.计算新的数组长度
	dwNewLen = m_dwLen + m_dwIncrement;

	//2.根据新的长度分配空间
	T_ELE* pTemp = new T_ELE[dwNewLen];

	//3.对新申请的内存初始化
	memset(pTemp, 0, dwNewLen * sizeof(T_ELE));

	//4.把原来数组的指针拷贝至新分配的内存中
	memcpy(pTemp, m_pVector, m_dwLen * sizeof(T_ELE));

	//5.删除原来的数组
	delete[] m_pVector;

	//6.把新的数组指针指向结构体内的指针
	m_pVector = pTemp;
	pTemp = NULL;

	//7.修改属性
	m_dwLen += m_dwIncrement;


	return true;
}







//测试函数
void TestVector()
{
	Vector<char>* pVector = new Vector<char>(5);

	pVector->push_back(1);
	pVector->push_back(2);
	pVector->push_back(3);
	pVector->push_back(4);
	pVector->push_back(5);

	pVector->capacity();
	pVector->erase(2);
	pVector->size();





}


int main()
{
	TestVector();

	return 0;
}

