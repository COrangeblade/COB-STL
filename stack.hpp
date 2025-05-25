#ifndef STACK_HPP
#define STACK_HPP
#include<cstdlib>
namespace COB{
template<typename T>
class stack{
	private:
		T* sta;
		unsigned Top,maxsize;
	public:
		stack():sta(new T[4096]),Top(0),maxsize(4096){}
		stack(const stack& oth):sta(new T[oth.maxsize]),Top(oth.Top),maxsize(oth.maxsize){
			for(unsigned i(1);i<=Top;++i) sta[i]=oth.sta[i];
		}
		~stack(){
			delete sta;
			sta=nullptr;
			maxsize=Top=0;
		}
		void clear(){
			Top=0;
			return;
		}
		bool empty()const{return Top==0;}
		unsigned size()const{return Top;}
		void push(const T& x){
			if(Top+1==maxsize){
				maxsize<<=1;
				T* tmp=new T[maxsize];
				T* swp=sta;
				sta=tmp;
				tmp=swp;
				for(unsigned i(1);i<=Top;++i) sta[i]=tmp[i];
				delete tmp;
				tmp=swp=nullptr;
			}
			sta[++Top]=x;
			return;
		}
		T& top(){
			if(!Top) exit(1);
			return sta[Top];
		}
		void pop(){
			if(!Top) exit(1);
			--Top;
			return;
		}
		void swap(stack& oth){
			T* swp_sta(this->sta);
			this->sta=oth.sta;
			oth.sta=swp_sta;
			unsigned swp_maxsize(this->maxsize);
			this->maxsize=oth.maxsize;
			oth.maxsize=swp_maxsize;
			unsigned swp_top(this->Top);
			this->Top=oth.Top;
			oth.Top=swp_top;
			return;
		}
};
}
#endif
