#ifndef MONOTONIC_STACK_HPP
#define MONOTONIC_STACK_HPP
#include"stack.hpp"
namespace COB{
template<typename T,typename Compare>
class monotonic_stack{
	private:
		Compare cmp;
		T* data;
		unsigned maxsize,tp;
	public:
		monotonic_stack():data(new T[4096]),cmp(Compare()),maxsize(4096),tp(0){}
		monotonic_stack(const monotonic_stack& oth):data(new T[oth.maxsize]),cmp(oth.cmp),maxsize(oth.maxsize),tp(oth.tp){
			for(unsigned i=1;i<=tp;++i) this->data[i]=oth.data[i];
		}
		bool empty()const{return !tp;}
		unsigned size()const{return tp;}
		void clear(){
			tp=0;
			return;
		}
		void push(const T& x){
			if(!empty()&&!cmp(x,data[tp])) --tp;
			if(tp+1==maxsize){
				maxsize<<=1;
				T* tmp=new T[maxsize];
				T* swp=data;
				data=tmp;
				tmp=swp;
				for(unsigned i=1;i<=tp;++i) data[i]=tmp[i];
				delete tmp,tmp=swp=nullptr;
			}
			data[++tp]=x;
			return;
		}
		void pop(){
			if(empty()) exit(1);
			--tp;
			return;
		}
		const T top()const{
			if(empty()) exit(1);
			return data[tp];
		}
		void swap(monotonic_stack& oth){
			T* swp_data=this->data;
			this->data=oth.data;
			oth.data=swp_data;
			unsigned swp_maxsize=this->maxsize;
			this->maxsize=oth.maxsize;
			oth.maxsize=swp_maxsize;
			unsigned swp_tp=this->tp;
			this->tp=oth.tp;
			oth.tp=swp_tp;
			return;
		}
};
}
#endif
