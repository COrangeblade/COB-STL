#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP
#include<functional>
#include<initializer_list>
#include<queue>
#include"queue.hpp"
namespace COB{
	template<typename _Tp,typename _Cmp=std::less<_Tp>>
	class priority_queue{
		private:
			struct Node{
				Node *ch[2];_Tp val;int dist;
				Node():ch{nullptr,nullptr},val(_Tp()),dist(0){}
				Node(_Tp v):ch{nullptr,nullptr},val(v),dist(0){}
				~Node(){ch[0]=ch[1]=nullptr;}
			};
			Node *root;_Cmp cmp;std::size_t sz;
			int dist(Node* p)const{return p==nullptr? -1:p->dist;}
			Node* merge(Node* x,Node* y){
				if(x==nullptr||y==nullptr) return x==nullptr? y:x;
				if(cmp(x->val,y->val)) std::swap(x,y);
				x->ch[1]=merge(x->ch[1],y);
				if(dist(x->ch[0])<dist(x->ch[1])) std::swap(x->ch[0],x->ch[1]);
				x->dist=dist(x->ch[1])+1;
				return x;
			}
			void build(const Node* p){
				if(!p) return;
				build(p->ch[0]);
				build(p->ch[1]);
				root=merge(root,new Node(p->val));
				return;
			}
			void clear(Node*& p){
				if(!p) return;
				clear(p->ch[0]);
				clear(p->ch[1]);
				delete p;p=nullptr;
				return;
			}
			bool erase(Node* p,const _Tp& k){
				queue<Node**> q;
				q.push(&p);
				while(!q.empty()){
					Node** u=q.front();q.pop();
					if(!*u) continue;
					if((*u)->val==k){
						Node *lc=(*u)->ch[0],*rc=(*u)->ch[1];
						delete *u;
						*u=merge(lc,rc);
						--sz;
						return true;
					}
					q.push((*u)->ch),q.push((*u)->ch+1);
				}
				return false;
			}
		public:
			typedef std::size_t size_type;
			typedef _Tp value_type;
			typedef _Tp& reference;
			typedef const _Tp& const_reference;
		public:
			priority_queue(_Cmp comp=_Cmp()):root(nullptr),sz(0),cmp(comp){}
			priority_queue(const priority_queue& oth,_Cmp comp=_Cmp()){
				root=nullptr,sz=oth.sz,cmp=comp;
				build(oth.root);
			}
			priority_queue(const std::initializer_list<_Tp>& init,_Cmp comp=_Cmp()){
				root=nullptr,sz=init.size(),cmp=comp;
				for(const auto& i:init) root=merge(root,new Node(i));
			}
			priority_queue(std::priority_queue<_Tp> q,_Cmp comp=_Cmp()){
				root=nullptr,sz=q.size(),cmp=comp;
				while(!q.empty()) root=merge(root,new Node(q.top())),q.pop();
			}
			~priority_queue(){
				clear(root);
			}
			priority_queue& operator=(const priority_queue& q){
				clear(root);
				build(q.root);
				sz=q.size();
				return *this;
			}
			const _Tp& top()const{return root->val;}
			void push(const _Tp& x){
				++sz;
				root=merge(root,new Node(x));
				return;
			}
			void pop(){
				--sz;
				Node *lc=root->ch[0],*rc=root->ch[1];
				delete root;
				root=merge(lc,rc);
				return;
			}
			void join(priority_queue& q){
				root=merge(root,q.root);
				q.root=nullptr,sz+=q.sz,q.sz=0;
				return;
			}
			void swap(priority_queue& q){
				std::swap(q.root,root);
				std::swap(q.sz,sz);
				std::swap(q.cmp,cmp);
				return;
			}
			std::size_t size()const{return sz;}
			bool empty()const{return sz==0;}
			void clear(){
				sz=0;
				clear(root);
				return;
			}
			bool erase(const _Tp& k){return erase(root,k);}
	};
}
#endif
