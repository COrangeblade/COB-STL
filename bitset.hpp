#ifndef BITSET_HPP
#define BITSET_HPP
namespace COB{
	using ullong=unsigned long long;
	using size_t=unsigned long;
	template<size_t N>
	class bitset{
		private:
			ullong bit[(N+63)>>6];
			struct reference{
				ullong* ptr;
				size_t pos;
				reference(size_t p):ptr(&bit[(p+63)>>6]),pos(p&63){}
				~reference()=default;
				reference& operator=(bool x){
					if(x) *ptr|=(1ull<<pos);
					else *ptr&=~(1ull<<pos);
					return *this;
				}
				reference& operator=(reference& _x){
					bool x=(*ptr)&(1ull<<pos);
					if(x) *ptr|=(1ull<<pos);
					else *ptr&=~(1ull<<pos);
					return *this;
				}
				reference& operator=(const reference& _x){
					bool x=(*ptr)&(1ull<<pos);
					if(x) *ptr|=(1ull<<pos);
					else *ptr&=~(1ull<<pos);
					return *this;
				}
			};
		public:
			size_t size()const{return N;}
			reference& operator[](size_t p){
				reference re(p);
				return re;
			}
	};
}
#endif
