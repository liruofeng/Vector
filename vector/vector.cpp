// test.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//���졢��������
public:
	Vector();
	Vector(DWORD dwSize);
	~Vector();
	//���к���
public:
	DWORD    at(DWORD dwIndex, OUT T_ELE* pEle);        //���ݸ����������õ�Ԫ��                    
	DWORD    push_back(T_ELE Element);                  //��Ԫ�ش洢���������һ��λ��
	VOID     pop_back();                                //ɾ�����һ��Ԫ��
	DWORD    insert(DWORD dwIndex, T_ELE Element);      //��ָ��λ������һ��Ԫ��
	DWORD    capacity();                                //���� �ڲ����ݵ�����£����ܴ洢���ٸ�Ԫ��
	DWORD    clear();                                   //�������Ԫ��
	BOOL     empty();                                   //�ж�Vector�Ƿ�Ϊ�� ����trueΪ��
	VOID     erase(DWORD dwIndex);                      //ɾ��ָ��Ԫ��
	DWORD    size();                                    //����VectorԪ��������С
														//˽�б���
private:
	BOOL expand();                                      //���ݺ���
private:
	DWORD m_dwIndex;                                   //��һ����������
	DWORD m_dwIncrement;                               //ÿ�����ݵĴ�С
	DWORD m_dwLen;                                     //��ǰ�����ĳ���
	DWORD m_dwIniSize;                                 //Ĭ�ϳ�ʼ����С
	T_ELE* m_pVector;                                  //����ָ��
};




//�޲ι��캯��
template<class T_ELE>
Vector<T_ELE>::Vector()
	:m_dwIniSize(10), m_dwIncrement(5)
{
	//1.������ʼ����Ϊm_dwIniSize��T_ELE����
	m_pVector = new T_ELE[m_dwIniSize];
	//2.�������Ŀռ��ʼ��Ϊ0
	memset(m_pVector, 0, m_dwIniSize * sizeof(T_ELE));
	//3.��������ֵ
	m_dwLen = m_dwIniSize;
	m_dwIndex = 0;

}



//�вι��캯��
template<class T_ELE>
Vector<T_ELE>::Vector(DWORD dwSize)
	:m_dwIncrement(5)
{
	//���з���dwsize��T_ELE���ʹ�С���ֽ�
	m_pVector = new T_ELE[dwSize];
	//��ʼ��
	memset(m_pVector, 0, dwSize * sizeof(T_ELE));
	//��������ֵ
	m_dwLen = dwSize;
	m_dwIndex = 0;
}

//��������
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

//��Ԫ�ش洢���������һ��λ��
template<class T_ELE>
DWORD Vector<T_ELE>::push_back(T_ELE Element)
{
	//1.�ж��Ƿ���Ҫ���ݣ������Ҫ�͵������ݺ���
	if (m_dwIndex >= m_dwLen)
	{
		expand();
	}
	//2.���µ�Ԫ�ظ��Ƶ����������һ��λ��
	memcpy(&m_pVector[m_dwIndex], &Element, sizeof(T_ELE));
	//3.�޸�����
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

//���뺯��
template<class T_ELE>
DWORD Vector<T_ELE>::insert(DWORD dwIndex, T_ELE Element)
{
	//1.�ж������Ƿ�������
	if (dwIndex < 0 || dwIndex > m_dwIndex)
	{
		return INDEX_ERRC;
	}
	//2.�ж��Ƿ�Ҫ��������
	if (m_dwIndex >= m_dwLen)
	{
		expand();
	}
	//3.��dwIndex֮���Ԫ�غ���
	for (int i = m_dwIndex;i > dwIndex;i--)
	{
		memcpy(&m_pVector[i], &m_pVector[i - 1], sizeof(T_ELE));
	}
	//4.�������
	memcpy(&m_pVector[dwIndex], &Element, sizeof(T_ELE));
	//5.�޸���Ӧ����
	m_dwIndex++;
	m_dwLen++;
}

//���� �ڲ����ݵ�����£����ܴ洢���ٸ�Ԫ��
template<class T_ELE>
DWORD Vector<T_ELE>::capacity()
{
	DWORD space = 0;
	space = m_dwLen - m_dwIndex;
	printf("δ����ʱ���ÿռ䣺%x\n", space);
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

//���ݺ���
template<class T_ELE>
BOOL Vector<T_ELE>::expand()
{
	DWORD dwNewLen = 0;

	//1.�����µ����鳤��
	dwNewLen = m_dwLen + m_dwIncrement;

	//2.�����µĳ��ȷ���ռ�
	T_ELE* pTemp = new T_ELE[dwNewLen];

	//3.����������ڴ��ʼ��
	memset(pTemp, 0, dwNewLen * sizeof(T_ELE));

	//4.��ԭ�������ָ�뿽�����·�����ڴ���
	memcpy(pTemp, m_pVector, m_dwLen * sizeof(T_ELE));

	//5.ɾ��ԭ��������
	delete[] m_pVector;

	//6.���µ�����ָ��ָ��ṹ���ڵ�ָ��
	m_pVector = pTemp;
	pTemp = NULL;

	//7.�޸�����
	m_dwLen += m_dwIncrement;


	return true;
}







//���Ժ���
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

