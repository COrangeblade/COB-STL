#ifndef QUEUE_HPP
#define QUEUE_HPP
#include<cstdlib>
namespace COB{
template<typename T>
class queue{
	private:
		T* que;
		unsigned head,tail,maxsize;
	public:
		queue():que(new T[4096]),head(0),tail(0),maxsize(4096){}
		queue(const queue& oth):que(new T[oth.maxsize]),head(oth.head),tail(oth.tail),maxsize(oth.maxsize){
			for(unsigned i=head;i!=tail;i=(i+1)%maxsize) que[i]=oth.que[i];
		}
		~queue(){
			delete que,que=nullptr,head=tail=maxsize=0;
		}
		void clear(){
			head=tail=0;
			return;
		}
		bool empty()const{return head==tail;}
		unsigned size()const{return ((tail-head)%maxsize+maxsize)%maxsize;}
		void push(const T& x){
			if((tail+1)%maxsize==head){
				unsigned len=maxsize;
				maxsize<<=1;
				T* tmp=new T[maxsize];
				T* swp=que;
				que=tmp;
				tmp=swp;
				for(unsigned i=head;i!=tail;++i) que[i]=tmp[i%len];
				delete tmp;
				tmp=swp=nullptr;
			}
			que[tail++]=x;
			return;
		}
		void pop(){
			if(head==tail) exit(1);
			++head;
			return;
		}
		T& front(){
			if(head==tail) exit(1);
			return que[head];
		}
		T& back(){
			if(head==tail) exit(1);
			return que[(tail+maxsize-1)%maxsize];
		}
		void swap(queue& oth){
			T* swp_que=this->que;
			this->que=oth.que;
			oth.que=swp_que;
			unsigned swp_maxsize=this->maxsize;
			this->maxsize=oth.maxsize;
			oth.maxsize=swp_maxsize;
			unsigned swp_head=this->head;
			this->head=oth.head;
			oth.head=swp_head;
			unsigned swp_tail=this->tail;
			this->tail=oth.tail;
			oth.tail=swp_tail;
			return;
		}
};
}
#endif
