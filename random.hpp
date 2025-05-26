#ifndef RANDOM_HPP
#define RANDOM_HPP
namespace COB{
class integer_rand{
	private:
		static constexpr int mod1=998244353,mod2=100000007,g1=3,g2=5;
		unsigned a,b,c;
	public:
		integer_rand():a(1),b(1),c(2){}
		integer_rand(unsigned seed){
			seed%=10007;a=b=1,c=2;
			while(seed--) c=(a%mod2+b%mod2),a=b,b=c;
		}
		unsigned operator()(){
			unsigned res=(a*g2%mod1+b*g1%mod1)%mod1;
			c=(a%mod2+b%mod2)%mod2,a=b,b=c;
			return res;
		}
};
class realnum_rand{
	private:
		integer_rand r1,r2;
	public:
		realnum_rand():r1(114313),r2(r1()){}
		realnum_rand(unsigned seed):r1(seed+5),r2(seed-5){}
		double operator()(){
			return (1.618*r1()*3.1415)/(2.718*r2()+1.0);
		}
};
}
#endif 
