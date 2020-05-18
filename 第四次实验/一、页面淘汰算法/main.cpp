#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;


const int MAXN = 320;	// 总共320条指令
const int VP_SIZE = 10;	// 每个页面的大小为10
const int PF_NUMS = 8;	// 页框（内存）为4个页面
const int VP_NUMS = 32;	// 32个页面
const int MAX_INF = 0x3f3f3f3f;
struct Command
{
	int id;
	int pageID;
	int offSet;
	void setData()
	{
		this->pageID = id / VP_SIZE;
		this->offSet = id % VP_SIZE;
	}
}command[MAXN];

struct PageFrame
{
	int pageID;
	int lastUse;
	PageFrame(int x = -1, int lastUse = -1)
	{
		this->pageID = x;
		this->lastUse = lastUse;
	}
};

void creatCommandList()
{
	for (int i = 0; i < MAXN; i++)
	{
		command[i].id = rand() % MAXN;
		command[i].setData();
		//cout << command[i].id << " " << command[i].pageID << endl;
	}
	//int a[MAXN] = { 0,1,2,3,0,1,4,0,1,2,3,4 };
	//for (int i = 0; i < MAXN; i++)
	//{
	//	command[i].id = a[i];
	//	command[i].setData();
	//}
}

double FIFO()
{
	vector<PageFrame> q;
	int front = 0;
	int existNum = 0;
	for (int i = 0; i < MAXN; i++)
	{
		bool flag = false;
		for (int j = front; j < q.size(); j++)
		{
			if (q[j].pageID == command[i].pageID)
			{
				flag = true;
				break;
			}
		}
		if (flag) existNum++;
		else
		{
			if (q.size() - front == PF_NUMS) front++;
			else q.push_back(PageFrame(command[i].pageID));
		}
	}
	return existNum * 1.0 / MAXN;
}

double LRU()
{
	PageFrame pf[PF_NUMS];
	int size = 0, existNum = 0;
	for (int i = 0; i < MAXN; i++)
	{
		// 是否存在，存在更新时间，不存在则插入
		bool flag = false;
		for (int j = 0; j < PF_NUMS; j++)
		{
			if (command[i].pageID == pf[j].pageID)
			{
				flag = true;
				pf[j].lastUse = i;
				break;
			}
		}

		if (flag)
		{
			existNum++;
			continue;
		}
		else
		{
			// 不存在，插入
			if (size < PF_NUMS)	// 没有满
			{
				for (int j = 0; j < PF_NUMS; j++)
				{
					if (pf[j].pageID == -1)
					{
						pf[j] = PageFrame(command[i].pageID, i);
						size++;
						break;
					}
				}
			}
			else	// 满了，淘汰
			{
				int index = 0;
				for (int j = 1; j < PF_NUMS; j++)
				{
					if (pf[j].lastUse < pf[index].lastUse)
					{
						index = j;
					}
				}
				pf[index] = PageFrame(command[i].pageID, i);
			}
		}
	}
	return existNum * 1.0 / MAXN;
}

double OPT()
{
	int existNum = 0, size = 0;
	PageFrame pf[PF_NUMS];
	for (int i = 0; i < MAXN; i++)
	{
		// 是否存在，存在更新时间，不存在则插入
		bool flag = false;
		for (int j = 0; j < PF_NUMS; j++)
		{
			if (command[i].pageID == pf[j].pageID)
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{
			existNum++;
			continue;
		}
		if (size < PF_NUMS)
		{
			for (int j = 0; j < PF_NUMS; j++)
			{
				if (pf[j].pageID == -1)
				{
					pf[j] = PageFrame(command[i].pageID);
					size++;
					break;
				}
			}
		}
		else
		{
			int index = 0;
			bool flag = false;
			for (int j = MAXN - 1; j >= i; j--)
			{
				for (int k = 0; k < PF_NUMS; k++)
				{
					if (command[j].pageID == pf[k].pageID)
					{
						index = k;
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
			pf[index] = PageFrame(command[i].pageID);
		}
	}

	return existNum * 1.0 / MAXN;
}

int main()
{
	srand((unsigned int)time(NULL));
	creatCommandList();
	cout << "FIFO:" << FIFO() << endl;
	cout << "LRU:" << LRU() << endl;
	cout << "OPT:" << OPT() << endl;
	return 0;
}