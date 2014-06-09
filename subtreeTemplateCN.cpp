/*  description : subset tree (call back)solution of ship loading 
 *  version :     2014-6-3
 *  author :      brt
 *  note   ��     ֻ�޸���bound�������Ͻ纯���� �� showResult ���� ����û�з��������ķ���������ʾ����
 *		   		  �����������remain�������ע�� 
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
        bool constraint(int depth);  //��ǰ��չ�ڵ㴦������Լ������
        bool bound(int depth);       //��ǰ��չ�ڵ㴦���޽纯��
        void record();               //��¼��ѷ���
        void showResult();           //��ӡ���
        int numContainer;            //��װ����Ŀ
        Type* weight,                //��װ����������ͷָ�루�����������棺���ǱȽ��˷� 
		      containFirstShip,      //��һ�Ҵ�����
			  currentLoading,        //��ǰ������
			  remain,                //��ǰδ����ʣ�༯װ��������� 
			  bestLoading;           //���ţ���ࣩ������
        bool* select;                //ѡ��װ��ı�־����
        vector<int> bestSelect;      //����ѡ�񷽰��ļ�װ��ı�־���飨͵����ѡ��˳������̫�˷ѣ� 
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
	if((currentLoading + remain) < bestLoading) //��ǰ�ж���ľ�и��Ž� 
		    return false; 
	return true; 
}

template <class Type>
void Loading <Type> ::  record()
{
 	 if(currentLoading > bestLoading){
 	 	bestLoading = currentLoading;
 	 	//��¼���Ž� 
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

    if(depth >= numContainer) {//��ѯ�����һ����װ�� 
        record();
        return; 
    }else{
	    for(int i = 1; i >= 0; --i){
	    	select[depth] = bool(i); //1 ������ѡ�������ߣ�����depth�����װ�� 
	    	if(constraint(depth) && bound(depth)){//2�����ƺ�������֦������������������������������ 
	    		if(select[depth] == true){ //�����������������״̬ : ��������
	    			currentLoading += weight[depth];
	    			backTrack(depth + 1);
					currentLoading -= weight[depth];//�������������ʱ��״̬��ԭ 
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
		cout << "������ŵļ�װ�佫��ѡ�� : " << endl;
		for(it = bestSelect.begin(); it != bestSelect.end(); ++it){
			cout << (*it) + 1 << " ";
		}
		cout << endl;
		cout << "��һ����װ�����װ���� : " << bestLoading << endl;
	}else{
		cout << "û���ʺϵ�װ�ط��� !" << endl;
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
    for(int i = 0; i < numContainer; ++i){ //����remain�Ķ�����г�ʼ�� 
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
    cout << "�����뼯װ����Ŀ : " << endl;
    cin >> numContainer;
    int * weight = new int[numContainer];
    cout << "�������װ������ : " << endl;
    for(int i = 0; i < numContainer; ++i)
        cin >> weight[i];
    int containFirstShip, containSecondShip;
    cout << "����2 ship ������ : " << endl;
    cin >> containFirstShip >> containSecondShip;
    maxLoading(weight, containFirstShip, numContainer);
    delete [] weight;
    return 0;
}
