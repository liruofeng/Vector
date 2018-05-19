
========================================================================
vector class
========================================================================
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
