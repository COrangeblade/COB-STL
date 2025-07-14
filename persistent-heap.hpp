#ifndef PERSISTENT_HEAP_HPP
#define PERSISTENT_HEAP_HPP
#include<functional>
#include<vector>
namespace COB{
    template<typename T,typename CMP=std::less<T>>
    class persistent_heap{
        private:
            struct Node{
                Node* ch[2];
                T val;int dist;
                Node():ch{nullptr,nullptr},val(T()),dist(0){}
                Node(const T& v):ch{nullptr,nullptr},val(v),dist(0){}
            };
            std::vector<Node*> root;
            CMP cmp;
            int dist(Node* p)const{return p? p->dist:-1;}
            Node* clone(Node* p){
                if(!p) return nullptr;
                Node* q=new Node(p->val);
                q->ch[0]=p->ch[0];
                q->ch[1]=p->ch[1];
                q->dist=p->dist;
                return q;
            }
            Node* merge(Node* x,Node* y){
                if(!x||!y) return x? x:y;
                if(cmp(x->val,y->val)) std::swap(x,y);
                Node* z=clone(x);
                z->ch[1]=merge(z->ch[1],y);
                if(dist(z->ch[0])<dist(z->ch[1])) std::swap(z->ch[0],z->ch[1]);
                return z;
            }
            std::size_t size(Node* p)const{
                if(!p) return 0;
                return 1+size(p->ch[0])+size(p->ch[1]);
            }
        public:
            persistent_heap():root(1,nullptr),cmp(CMP()){}
            void push(const T& v,int ver){
                Node* new_node=new Node(v);
                root.push_back(merge(root[ver],new_node));
            }
            const T& top(int ver)const{
                if(!root[ver]) throw std::runtime_error("Heap is empty");
                return root[ver]->val;
            }
            void pop(int ver){
                if(!root[ver]) throw std::runtime_error("Heap is empty");
                root.push_back(merge(root[ver-1]->ch[0],root[ver-1]->ch[1]));
                return;
            }
            bool empty(int ver)const{return !root[ver];}
            std::size_t size(int ver)const{return size(root[ver]);}
            void clear(){
                root.push_back(nullptr);
                return;
            }
            void join(int ver1,int ver2){
                root.push_back(merge(root[ver1],root[ver2]));
                return;
            }
            std::size_t version()const{return root.size();}
    };
}
#endif