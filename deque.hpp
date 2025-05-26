#ifndef DEQUE_HPP
#define DEQUE_HPP
#include<cstdlib>
namespace COB{
template<typename T>
class deque{
	private:
		T* data;
		unsigned head,tail,maxsize;
	public:
		deque():data(new T[4096]),head(0),tail(1),maxsize(4096){}
		deque(const deque& oth):data(new T[oth.maxsize]),head(oth.head),tail(oth.tail),maxsize(oth.maxsize){
			for(unsigned i=head;i!=tail;i=(i+1)%maxsize) data[i]=oth.data[i];
		}
		~deque(){
			delete data,data=nullptr;
			head=tail=maxsize;
		}
		void push_back(const T& x){
			if(tail==head){
				tail+=maxsize;
				unsigned len=maxsize;
				maxsize<<=1;
				T* tmp=new T[maxsize];
				T* swp=data;
				data=tmp,tmp=swp;
				for(unsigned i=head+1;i!=tail;++i) data[i]=tmp[i%len];
				delete tmp,tmp=swp=nullptr;
			}
			data[tail]=x;
			(++tail)%=maxsize;
			return;
		}
		void push_front(const T& x){
			if(head==tail){
				tail+=maxsize;
				unsigned len=maxsize;
				maxsize<<=1;
				T* tmp=new T[maxsize];
				T* swp=data;
				data=tmp,tmp=swp;
				for(unsigned i=head+1;i!=tail;++i) data[i]=tmp[i%len];
				delete tmp,tmp=swp=nullptr;
			}
			data[head]=x;
			head=(head+maxsize-1)%maxsize;
			return;
		}
		void clear(){
			tail=1+(head=0);
			return;
		}
		bool empty()const{return (head+1)%maxsize==tail;}
		unsigned size()const{return (tail+maxsize-head-1)%maxsize;}
		void pop_front(){
			if(empty()) exit(1);
			(++head)%=maxsize;
		}
		void pop_back(){
			if(empty()) exit(1);
			(tail+=maxsize-1)%=maxsize;
		}
		T& front(){
			if(empty()) exit(1);
			return data[(head+1)%maxsize];
		}
		T& back(){
			if(empty()) exit(1);
			return data[(tail+maxsize-1)%maxsize];
		}
		operator[](unsigned p){
			return data[(head+1+p)%maxsize];
		}
};
}
#endif
