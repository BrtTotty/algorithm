/*  description : subset tree (call back)solution of ship loading 
 *  version :     2014-6-3
 *  author :      brt
 *  note   ：     只修改了bound函数（上界函数） 和 showResult 函数 （对没有符合条件的方案作出提示），
 *		   		  增加了类变量remain，详情见注释 
 */ 
#include <iostream>
#include <vector>
using namespace std;

template < class Type >
void maxLoading (Type weight[], Type containFirstShip, int numContainer);

template < class Type >
class Loading{
	
    friend void maxLoading<Type> (Type weight[], Type containFirstShip, int numContainer);
    private:
        void backTrack(int depth);
        bool constraint(int depth);  //当前扩展节点处的条件约束函数
        bool bound(int depth);       //当前扩展节点处的限界函数
        void record();               //记录最佳方案
        void showResult();           //打印结果
        int numContainer;            //集装箱数目
        Type* weight,                //集装箱重量数组头指针（可用容器代替：但是比较浪费 
		      containFirstShip,      //第一艘船容量
			  currentLoading,        //当前载重量
			  remain,                //当前未讨论剩余集装箱的总重量 
			  bestLoading;           //最优（最多）载重量
        bool* select;                //选择集装箱的标志数组
        vector<int> bestSelect;      //最优选择方案的集装箱的标志数组（偷懒，选用顺序容器太浪费） 
};

template <class Type>
bool Loading <Type> ::  constraint(int depth)
{
	Type temp;
	if(select[depth] == true)
        temp = currentLoading + weight[depth];
	else
		temp = currentLoading;
	if(temp <= containFirstShip){
		return true;
	}else{
		return false;
	}
}

template <class Type>
bool Loading <Type> ::  bound(int depth)
{
	remain -= weight[depth]; 
    if(select[depth] == true)
            remain += weight[depth]; 
	if((currentLoading + remain) < bestLoading) //提前判断有木有更优解 
		    return false; 
	return true; 
}

template <class Type>
void Loading <Type> ::  record()
{
 	 if(currentLoading > bestLoading){
 	 	bestLoading = currentLoading;
 	 	//记录更优解 
 	 	if(bestSelect.size() > 0)
		    bestSelect.clear();
 	 	for(int i = 0; i < numContainer; ++i)
 	 	    if(select[i] == true)
 	 			bestSelect.push_back(i);
 	 }
} 
template < class Type >
void Loading < Type > :: backTrack(int depth)
{

    if(depth >= numContainer) {//轮询到最后一个集装箱 
        record();
        return; 
    }else{
	    for(int i = 1; i >= 0; --i){
	    	select[depth] = bool(i); //1 ：代表选择这条边，即第depth这个集装箱 
	    	if(constraint(depth) && bound(depth)){//2个限制函数即剪枝，不满足条件不继续沿这个深度搜索 
	    		if(select[depth] == true){ //进入深层子树，更新状态 : 下面两行
	    			currentLoading += weight[depth];
	    			backTrack(depth + 1);
					currentLoading -= weight[depth];//深度搜索，回溯时，状态还原 
					select[depth] = false; 
	    		}else{
	    			backTrack(depth + 1);
	    		}
	    	}
	    }
	}
}

template <class Type>
void Loading < Type > :: showResult()
{
	if(bestSelect.size() > 0){
		vector<int> :: iterator it;
		cout << "以下序号的集装箱将被选择 : " << endl;
		for(it = bestSelect.begin(); it != bestSelect.end(); ++it){
			cout << (*it) + 1 << " ";
		}
		cout << endl;
		cout << "第一个集装箱最大装载量 : " << bestLoading << endl;
	}else{
		cout << "没有适合的装载方案 !" << endl;
	}
}

template <class Type>
void maxLoading(Type weight[], Type containFirstShip, int numContainer)
{
    Loading <Type> x;
    bool *select = new bool[numContainer];
    memset(select, false, numContainer);
    x.select = select;
    x.weight = weight;
    for(int i = 0; i < numContainer; ++i){ //根据remain的定义进行初始化 
    	x.remain += weight[i];
    } 
    x.containFirstShip = containFirstShip;
    x.numContainer = numContainer;
    x.bestLoading = 0;
    x.currentLoading = 0;
    x.backTrack(0);
    x.showResult();
    delete [] select;
}


int main()
{
    Loading<int> testObj;
    int numContainer;
    cout << "请输入集装箱数目 : " << endl;
    cin >> numContainer;
    int * weight = new int[numContainer];
    cout << "输入各集装箱重量 : " << endl;
    for(int i = 0; i < numContainer; ++i)
        cin >> weight[i];
    int containFirstShip, containSecondShip;
    cout << "输入2 ship 的容量 : " << endl;
    cin >> containFirstShip >> containSecondShip;
    maxLoading(weight, containFirstShip, numContainer);
    delete [] weight;
    return 0;
}
