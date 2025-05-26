#ifndef List_HPP
#define List_HPP
#include<functional>
#include<vector>
#include<algorithm>
#include<initializer_list>
#include<stdexcept>
namespace COB{
template<typename T>
inline void Free(T*&p)noexcept{*p=T();delete p;p=nullptr;return;}
template<typename T>
class list{
	private:
		struct Node{
			Node *pre,*next;T val;
			Node(const T& v=T(),Node* p=nullptr,Node* n=nullptr)noexcept:val(v),pre(p),next(n){}
			friend bool operator==(const Node& a,const Node& b)noexcept{return a.next==b.next&&a.pre==b.pre&&a.val==b.val;}
			friend bool operator!=(const Node& a,const Node& b)noexcept{return !(a==b);}
		};
		Node *head,*tail;std::size_t l;
	public:
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef std::size_t size_type;
		struct iterator;
		struct r_iterator;
	public:
		struct iterator{
			Node* ptr;
			iterator(Node* p=nullptr)noexcept:ptr(p){}
			iterator(const iterator& p=iterator())noexcept:ptr(p.ptr){}
			iterator(const r_iterator& p=r_iterator())noexcept:ptr(p.ptr){}
			iterator& operator=(const iterator p)noexcept{ptr=p.ptr;return *this;}
			iterator& operator=(const r_iterator p)noexcept{ptr=p.ptr;return *this;}
			iterator& operator++()noexcept{ptr=ptr->next;return *this;}
			iterator operator++(signed)noexcept{iterator tmp=*this;ptr=ptr->next;return tmp;}
			iterator& operator--()noexcept{ptr=ptr->pre;return *this;}
			iterator operator--(signed)noexcept{iterator tmp=*this;ptr=ptr->pre;return tmp;}
			friend iterator operator+(iterator it,int n)noexcept{
				while(it.ptr&&n--) ++it;
				return it;
			}
			friend iterator operator-(iterator it,int n)noexcept{
				while(it.ptr&&n--) --it;
				return it;
			}
			T& operator*()noexcept{return ptr->val;}
			bool operator!=(const iterator& other)noexcept{return this->ptr!=other.ptr;}
			bool operator!=(const r_iterator& other)noexcept{return this->ptr!=other.ptr;}
			bool operator==(const iterator& other)noexcept{return this->ptr==other.ptr;}
			bool operator==(const r_iterator& other)noexcept{return this->ptr==other.ptr;}
			T* operator->()noexcept{return &(ptr->val);}
			friend iterator& operator+=(iterator&it,int n)noexcept{it=it+n;return it;}
			friend iterator& operator-=(iterator&it,int n)noexcept{it=it-n;return it;}
		};
	public:
		struct r_iterator{
			Node* ptr;
			r_iterator(Node*p=nullptr)noexcept:ptr(p){}
			r_iterator(const iterator& p=iterator())noexcept:ptr(p.ptr){}
			r_iterator(const r_iterator& p=r_iterator())noexcept:ptr(p.ptr){}
			r_iterator& operator=(const iterator p)noexcept{ptr=p.ptr;return *this;}
			r_iterator& operator=(const r_iterator p)noexcept{ptr=p.ptr;return *this;}
			r_iterator& operator++()noexcept{ptr=ptr->pre;return *this;}
			r_iterator operator++(signed)noexcept{r_iterator tmp=*this;ptr=ptr->pre;return tmp;}
			r_iterator& operator--()noexcept{ptr=ptr->next;return *this;}
			r_iterator operator--(signed)noexcept{r_iterator tmp=*this;ptr=ptr->next;return tmp;}
			friend r_iterator operator+(r_iterator it,int n)noexcept{
				while(it.ptr&&n--) ++it;
				return it;
			}
			friend r_iterator operator-(r_iterator it,int n)noexcept{
				while(it.ptr&&n--) --it;
				return it;
			}
			T& operator*()noexcept{return ptr->val;}
			bool operator!=(const r_iterator& other)noexcept{return this->ptr!=other.ptr;}
			bool operator!=(const iterator& other)noexcept{return this->ptr!=other.ptr;}
			bool operator==(const r_iterator& other)noexcept{return this->ptr==other.ptr;}
			bool operator==(const iterator& other)noexcept{return this->ptr==other.ptr;}
			T* operator->()noexcept{return &(ptr->val);}
			friend r_iterator& operator+=(r_iterator&it,int n)noexcept{it=it+n;return it;}
			friend r_iterator& operator-=(r_iterator&it,int n)noexcept{it=it-n;return it;}
		};
	public:
		list()noexcept:head(new Node()),tail(new Node()),l(0){head->pre=head->next=tail,tail->next=tail->pre=head;}
		list(const list& other)noexcept:head(new Node()),tail(new Node()),l(0){
			head->next=tail,tail->pre=head;
			if(this==&other) return;
			for(auto it=other.cbegin();it!=other.cend();++it) this->push_back(*it);
		}
		list(const std::initializer_list<T>& init_list)noexcept:head(new Node()),tail(new Node()),l(0){
			head->next=tail,tail->pre=head;
			for(const auto& i:init_list) this->push_back(i);
		}
		~list()noexcept{
			while(head!=tail){
				head=head->next;
				Free(head->pre);
			}
			delete head;head=tail=nullptr;
		}
		list& operator=(const list& other)noexcept{
			if(this==&other) return *this;
			if(!this->empty()) this->clear();
			for(auto it=other.cbegin();it!=other.cend();++it) this->push_back(*it);
			return *this;
		}
		list& operator=(const std::initializer_list<T>& init_list)noexcept{
			this->clear();
			for(auto i:init_list) this->push_back(i);
			return *this;
		}
		T& operator[](const std::size_t& p)noexcept{return *(this->begin()+p);}
		friend bool operator==(const list&l1,const list&l2)noexcept{
			if(l1.size()!=l2.size()) return false;
			for(auto it1=l1.cbegin(),it2=l2.cbegin();it1!=l1.cend()&&it2!=l2.cend();++it1,++it2) if(*it1!=*it2) return false;
			return true;
		}
		friend bool operator!=(const list& l1,const list& l2)noexcept{return !(l1==l2);}
		friend bool operator<(const list& l1,const list& l2)noexcept{
			for(auto it1=l1.cbegin(),it2=l2.cbegin();it1!=l1.cend()&&it2!=l2.cend();++it1,++it2) if(*it1>*it2) return false;
			return l1.size()<l2.size();
		}
		friend bool operator<=(const list& l1,const list& l2)noexcept{return (l1<l2||l1==l2);}
		friend bool operator>(const list& l1,const list& l2)noexcept{return !(l1<=l2);}
		friend bool operator>=(const list& l1,const list& l2)noexcept{return !(l1<l2);}
		T& at(const std::size_t& p)noexcept;
		void clear()noexcept;
		void push_front(const T& v)noexcept;
		void push_back(const T& v)noexcept;
		T pop_front()noexcept;
		T pop_back()noexcept;
		void insert(iterator it,const T& val)noexcept;
		void insert(r_iterator it,const T& val)noexcept;
		T erase(auto it)noexcept;
		T& front()noexcept;
		T& back()noexcept;
		std::size_t size()const noexcept;
		bool empty()const noexcept;
		auto begin()noexcept;
		auto end()noexcept;
		const auto cbegin()const noexcept;
		const auto cend()const noexcept;
		auto rbegin()noexcept;
		auto rend()noexcept;
		const auto crbegin()const noexcept;
		const auto crend()const noexcept;
		void sort(iterator b,iterator e,const std::function<bool(const T&,const T&)>&comp=std::less<T>())noexcept;
		void sort(r_iterator b,r_iterator e,const std::function<bool(const T&,const T&)>&comp=std::less<T>())noexcept;
		void sort(const std::function<bool(const T&,const T&)>&comp=std::less<T>())noexcept;
		void merge(list<T>& other,const std::function<bool(const T&,const T&)>& comp=std::less<T>())noexcept;
		void reverse()noexcept;
		void reverse(auto b,auto e)noexcept;
		list<T> split(iterator ptr)noexcept;
		std::size_t unique()noexcept;
		void swap(list<T>& other)noexcept;
		void resize(const std::size_t len,T val=T())noexcept;
		std::size_t remove(const T& v)noexcept;
		std::size_t remove_if(const std::function<bool(const T&)>& comp)noexcept;
		void merge_front(list<T>& other)noexcept;
		void merge_back(list<T>& other)noexcept;
};
template<typename T>
T& list<T>::at(const std::size_t& p)noexcept{
	if(p>=l) throw std::out_of_range("list::_M_range_check: __n (which is "+std::to_string(p)+") >= this->size() (which is "+std::to_string(l)+")");
	return *(begin()+p);
}
template<typename T>
void list<T>::clear()noexcept{
	while(!empty()) pop_front(),pop_back();
	return;
}
template<typename T>
void list<T>::push_front(const T& v)noexcept{
	Node*newnode=new Node(v,head,head->next);++l;
	head->next->pre=newnode;head->next=newnode;
	return;
}
template<typename T>
void list<T>::push_back(const T& v)noexcept{
	Node*newnode=new Node(v,tail->pre,tail);++l;
	tail->pre->next=newnode;tail->pre=newnode;
	return;
}
template<typename T>
T list<T>::pop_front()noexcept{
	if(empty()) return T();
	Node*cur=head->next;--l;
	head->next->next->pre=head;head->next=head->next->next;
	T v=cur->val;Free(cur);return v;
}
template<typename T>
T list<T>::pop_back()noexcept{
	if(empty()) return T();
	Node*cur=tail->pre;--l;
	tail->pre->pre->next=tail;tail->pre=tail->pre->pre;
	T v=cur->val;Free(cur);return v;
}
template<typename T>
void list<T>::insert(iterator it,const T& val)noexcept{
	Node*cur=it.ptr;++l;
	Node*newnode=new Node(val,cur->pre,cur);
	cur->pre->next=newnode;cur->pre=newnode;
	return;
}
template<typename T>
void list<T>::insert(r_iterator it,const T& val)noexcept{
	Node*cur=it.ptr;++l;
	Node*newnode=new Node(val,cur,cur->next);
	cur->next->pre=newnode;cur->next=newnode;
	return;
}
template<typename T>
T list<T>::erase(auto it)noexcept{
	if(empty()) return T();
	Node*cur=it.ptr;
	if(cur==nullptr||cur==head||cur==tail) return T();
	cur->pre->next=cur->next;cur->next->pre=cur->pre;
	T v=cur->val;Free(cur);--l;
	return v;
}
template<typename T>
T& list<T>::front()noexcept{return head->next->val;}
template<typename T>
T& list<T>::back()noexcept{return tail->pre->val;}
template<typename T>
std::size_t list<T>::size()const noexcept{return l;}
template<typename T>
bool list<T>::empty()const noexcept{return (!l)||(head==nullptr&&tail==nullptr)||head->next==tail;}
template<typename T>
auto list<T>::begin()noexcept{return iterator(head->next);}
template<typename T>
auto list<T>::end()noexcept{return iterator(tail);}
template<typename T>
const auto list<T>::cbegin()const noexcept{return iterator(head->next);}
template<typename T>
const auto list<T>::cend()const noexcept{return iterator(tail);}
template<typename T>
auto list<T>::rbegin()noexcept{return r_iterator(tail->pre);}
template<typename T>
auto list<T>::rend()noexcept{return r_iterator(head);}
template<typename T>
const auto list<T>::crbegin()const noexcept{return r_iterator(tail->pre);}
template<typename T>
const auto list<T>::crend()const noexcept{return r_iterator(head);}
template<typename T>
void list<T>::sort(const std::function<bool(const T&,const T&)>&comp)noexcept{
	this->sort(this->begin(),this->end(),comp);
	return;
}
template<typename T>
void list<T>::sort(iterator b,iterator e,const std::function<bool(const T&,const T&)>&comp)noexcept{
	std::vector<T> arr;
	while(b!=e){
		auto it=b++;
		arr.push_back(erase(it));
	}
	std::sort(arr.begin(),arr.end(),comp);
	for(auto i:arr) this->insert(b,i);
	return;
}
template<typename T>
void list<T>::sort(r_iterator b,r_iterator e,const std::function<bool(const T&,const T&)>&comp)noexcept{
	std::vector<T> arr;
	while(b!=e){
		auto it=b++;
		arr.push_back(erase(it));
	}
	std::sort(arr.begin(),arr.end(),comp);
	for(auto i:arr) this->insert(b,i);
	return;
}
template<typename T>
void list<T>::merge(list<T>& other,const std::function<bool(const T&,const T&)>& comp)noexcept{
	if(this==&other||other.empty()) return;
	Node *curr=head->next,*o_curr=other.head->next;
	while(curr!=tail&&o_curr!=other.tail){
		if(comp(o_curr->val,curr->val)){
			Node* next_o=o_curr->next;
			o_curr->pre->next=next_o;
			next_o->pre=o_curr->pre;
			o_curr->pre=curr->pre;
			o_curr->next=curr;
			curr->pre->next=o_curr;
			curr->pre=o_curr;
			o_curr=next_o;
			l++;other.l--;
		}else curr=curr->next;
	}
	if(o_curr!=other.tail){
		Node* last=tail->pre;
		last->next=o_curr;
		o_curr->pre=last;
		Node* o_last=other.tail->pre;
		tail->pre=o_last;
		o_last->next=tail;
		l+=other.l;other.l=0;
		other.head->next=other.tail;
		other.tail->pre=other.head;
	}
	return;
}
template<typename T>
void list<T>::reverse()noexcept{
	reverse(iterator(this->head->next),iterator(this->tail));
	return;
}
template<typename T>
void list<T>::reverse(auto b,auto e)noexcept{
	--e;
	while(b!=e&&*(e.ptr->next)!=*(b.ptr)) std::swap(*b,*e),++b,--e;
	return;
}
template<typename T>
list<T> list<T>::split(iterator ptr)noexcept{
	if(empty()||ptr==end()) return list<T>();
	std::size_t _l=0;list<T> ll;
	for(auto it=ptr;it!=end();++it,++_l);
	ll.l=_l;l-=_l;
	auto it_o=end()-1,it=ptr-1;
	Node*cur=it.ptr;cur->next=tail;tail->pre=cur;
	cur=ptr.ptr;ll.head->next=cur;cur->pre=ll.head;
	cur=it_o.ptr;cur->next=ll.tail;ll.tail->pre=cur;
	return ll;
}
template<typename T>
std::size_t list<T>::unique()noexcept{
	std::size_t x=0;
	for(auto it=begin()+1;it!=end();++it){
		if(*it==*(it-1)){
			auto del_it=--it;
			erase(del_it);++x;
		}
	}
	return x;
}
template<typename T>
void list<T>::swap(list<T>&other)noexcept{std::swap(*this,other);return;}
template<typename T>
void list<T>::resize(const std::size_t len,T val)noexcept{
	if(size()==len) return;
	while(size()<len) this->push_back(val);
	while(size()>len) this->pop_back();
	return;
}
template<typename T>
std::size_t list<T>::remove(const T& v)noexcept{
	std::size_t x=0;
	for(auto it=begin();it!=end();++it){
		if(*it==v){
			auto del_it=it--;
			erase(del_it);
		}
	}
	return x;
}
template<typename T>
std::size_t list<T>::remove_if(const std::function<bool(const T&)>& comp)noexcept{
	std::size_t x=0;
	for(auto it=begin();it!=end();++it){
		if(comp(*it)){
			auto del_it=it--;
			erase(del_it);
		}
	}
	return x;
}
template<typename T>
void list<T>::merge_front(list<T>& other)noexcept{
	if(this==&other) return;
	head->next->pre=other.tail->pre;
	other.tail->pre->next=head->next;
	head->next=other.head->next;
	other.head->next->pre=head;
	other.tail->pre=other.head;
	other.head->next=other.tail;
	l+=other.l;other.l=0;
	return;
}
template<typename T>
void list<T>::merge_back(list<T>& other)noexcept{
	if(this==&other) return;
	tail->pre->next=other.head->next;
	other.head->next->pre=tail->pre;
	tail->pre=other.tail->pre;
	other.tail->pre->next=tail;
	other.tail->pre=other.head;
	other.head->next=other.tail;
	l+=other.l;other.l=0;
	return;
}
}
#endif
