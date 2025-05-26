#ifndef ARRAY_HPP
#define ARRAY_HPP
#include<cstdlib>
#include<initializer_list>
namespace COB{
template<typename T,unsigned L>
class array{
	private:
		T* dt;
	public:
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef unsigned size_type;
		typedef T* iterator;
		typedef const T* const_iterator;
	public:
		array():dt(new T[L]){}
		array(const std::initializer_list<T>& init_list){
			unsigned i=0;
			for(const auto& e:init_list){
				if(i>=L) exit(1);
				dt[i++]=e;
			}
		}
		~array(){
			delete dt,dt=nullptr;
		}
		void fill(const T& x){
			for(unsigned i=0;i<L;++i) dt[i]=x;
			return;
		}
		void swap(array& oth){
			T* swp=this->dt;
			this->dt=oth.dt;
			oth.dt=swp;
		}
		auto begin(){return dt;}
		auto end(){return dt+L;}
		auto cbegin()const{return dt;}
		auto cend()const{return dt+L;}
		unsigned size()const{return L;}
		bool empty()const{return L==0;}
		T& operator[](unsigned p){return dt[p];}
		const T& operator[](unsigned p)const{return dt[p];}
		T& at(unsigned p){
			if(p>=L) exit(1);
			return dt[p];
		}
		const T& at(unsigned p)const{
			if(p>=L) exit(1);
			return dt[p];
		}
		T& front(){return dt[0];}
		T& back(){return dt[L-1];}
		const T& front()const{return dt[0];}
		const T& back()const{return dt[L-1];}
		T* data(){return dt;}
		const T* data()const{return dt;}
};
}
#endif
