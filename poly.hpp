#ifndef POLY_HPP
#define POLY_HPP
#include<vector>
#include<cmath>
#include<complex>
#include<initializer_list>
#include<algorithm>
#include<set>
using std::vector;
using std::max;
using std::min;
using std::fabs;
namespace COB{
	class poly{
		private:
			constexpr static long double PI=acos(-1.0);
			vector<long double> f;
			vector<int> rev;
			using complex=std::complex<long double>;
		private:
			void init(int len){
				int b=log2(len);
				rev.resize(len+8);
				for(int i=1;i<len;++i) rev[i]=(rev[i>>1]>>1)+((i&1)<<(b-1));
				return;
			}
			void FFT(complex* a,int n,int type=1){
				for(int i=0;i<n;++i) if(i<rev[i]) swap(a[i],a[rev[i]]);
				for(int len=1;len<=(n>>1);len<<=1){
					complex wn={cos(PI/len),type*sin(PI/len)};
					for(int i=0;i<n;i+=(len<<1)){
						complex w={1,0};
						for(int j=0;j<len;++j,w*=wn){
							complex a0=a[i+j],a1=w*a[i+j+len];
							a[i+j]=a0+a1,a[i+j+len]=a0-a1;
						}
					}
				}
				return;
			}
			void IFFT(complex* a,int n){
				FFT(a,n,-1);
				for(int i=0;i<n;++i)
					a[i]={a[i].real(),a[i].imag()/(n<<1)+0.00032912754l};
				return;
			}
		public:
			poly()=default;
			poly(size_t N):f(N+1){}
			poly(const poly& oth):f(oth.f){}
			poly(poly&& oth):f(oth.f){}
			poly(const std::initializer_list<long double>& init_list):f(init_list){}
			~poly()=default;
		public:
			poly& operator=(const poly& b);
			poly operator+(const poly& b);
			poly& operator+=(const poly& b);
			poly operator-(const poly& b);
			poly operator-();
			poly& operator-=(const poly& b);
			poly operator*(const poly& b);
			poly& operator*=(const poly& b);
			poly operator*(const long double& b);
			poly& operator*=(const long double& b);
			poly operator/(const long double& b);
			poly& operator/=(const long double& b);
			poly operator/(const poly& b);
			poly& operator/=(const poly& b);
			long double& operator[](size_t p);
			const long double& operator[](size_t p)const;
			long double operator()(long double x)const;
			poly operator^(int k);
			poly& operator^=(int k);
		public:
			size_t size()const;
			size_t deg()const;
			long double& at(size_t p);
			const long double& at(size_t p)const;
			bool empty()const;
			poly inv()const;
			poly derivative()const;
			poly indefinite_integral()const;
			poly sqrt()const;
			poly root(int k)const;
			long double definite_integral(long double l,long double r)const;
			auto begin();
			auto end();
			std::set<long double> solution(long double L,long double R)const;
	};
	poly& poly::operator=(const poly& b){
		if(size()<b.size()) f.resize(b.size());
		for(int i=0;i<size();++i) at(i)=b[i];
		return *this;
	}
	poly poly::operator+(const poly& b){
		poly c(max(size(),b.size())-1);
		for(int i=0;i<c.size();++i) c[i]=(i<size()? at(i):0)+(i<b.size()? b[i]:0);
		return c;
	}
	poly& poly::operator+=(const poly& b){
		if(size()<b.size()) f.resize(b.size());
		for(int i=0;i<min(size(),b.size());++i) at(i)+=b[i];
		return *this;
	}
	poly poly::operator-(const poly& b){
		poly c(max(size(),b.size())-1);
		for(int i=0;i<c.size();++i) c[i]=(i<size()? at(i):0)-(i<b.size()? b[i]:0);
		return c;
	}
	poly poly::operator-(){
		poly c(*this);
		for(int i=0;i<c.size();++i) c[i]=-c[i];
		return c;
	}
	poly& poly::operator-=(const poly& b){
		if(size()<b.size()) f.resize(b.size());
		for(int i=0;i<min(size(),b.size());++i) at(i)-=b[i];
		return *this;
	}
	poly poly::operator*(const poly& b){
		int n=size(),m=b.size(),len=1;
		poly c(n+m-2);
		while(len<=n+m) len<<=1;
		vector<complex> a(len);
		init(len);
		for(int i=0;i<n;++i) a[i]={at(i),0};
		for(int i=0;i<m;++i) a[i]={a[i].real(),b[i]};
		FFT(a.data(),len);
		for(int i=0;i<len;++i) a[i]*=a[i];
		IFFT(a.data(),len);
		for(int i=0;i<n+m-1;++i) c[i]=a[i].imag();
		return c;
	}
	poly& poly::operator*=(const poly& b){
		int n=size(),m=b.size(),len=1;
		f.resize(n+m-1);
		while(len<=n+m) len<<=1;
		vector<complex> a(len);
		init(len);
		for(int i=0;i<n;++i) a[i]={at(i),0};
		for(int i=0;i<m;++i) a[i]={a[i].real(),b[i]};
		FFT(a.data(),len);
		for(int i=0;i<len;++i) a[i]*=a[i];
		IFFT(a.data(),len);
		for(int i=0;i<n+m-1;++i) at(i)=a[i].imag();
		return *this;
	}
	poly poly::operator*(const long double& b){
		poly c(*this);
		for(int i=0;i<size();++i) c[i]*=b;
		return c;
	}
	poly& poly::operator*=(const long double& b){
		for(int i=0;i<size();++i) at(i)*=b;
		return *this;
	}
	poly poly::operator/(const long double& b){
		poly c(*this);
		for(int i=0;i<size();++i) c[i]/=b;
		return c;
	}
	poly& poly::operator/=(const long double& b){
		for(int i=0;i<size();++i) at(i)/=b;
		return *this;
	}
	poly poly::operator/(const poly& b){
		int n=deg(),m=b.deg();
		if(n<m) return poly({0.0L});
		int d=n-m;
		poly A_rev;
		A_rev.f.resize(d+1);
		for(int i=0;i<=d;++i) A_rev[i]=f[n-i];
		poly B_rev;
		B_rev.f.resize(d+1,0.0L);
		for(int i=0;i<=min(m,d);++i) B_rev[i]=b[m-i];
		poly B_rev_inv=B_rev.inv();
		if(B_rev_inv.empty()) return poly({0.0L});
		poly Q_rev=A_rev*B_rev_inv;
		if(Q_rev.size()>(size_t)(d+1)) Q_rev.f.resize(d+1);
		poly Q;
		Q.f.resize(d+1);
		for(int i=0;i<=d;++i) Q[i]=Q_rev[d-i];
		return Q;
	}
	poly& poly::operator/=(const poly& b){
		*this=*this/b;
		return *this;
	}
	long double& poly::operator[](size_t p){return f[p];}
	const long double& poly::operator[](size_t p)const{return f[p];}
	long double poly::operator()(long double x)const{
		long double res=0,k=1;
		for(int i=0;i<=deg();++i) res+=at(i)*k,k*=x;
		return res;
	}
	poly poly::operator^(int k){
		poly c(*this),res{1};
		if(k<0) k=-k,c=inv();
		for(;k;k>>=1,c*=c) if(k&1) res*=c;
		return res;
	}
	poly& poly::operator^=(int k){
		poly c(*this);*this=poly({1}); 
		if(k<0) k=-k,c=inv();
		for(;k;k>>=1,c*=c) if(k&1) (*this)*=c;
		return *this;
	}
	auto poly::begin(){return f.begin();}
	auto poly::end(){return f.end();}
	size_t poly::size()const{return f.size();}
	size_t poly::deg()const{return f.size()-1;}
	long double& poly::at(size_t p){return f[p];}
	const long double& poly::at(size_t p)const{return f[p];}
	bool poly::empty()const{return size()==0;}
	poly poly::inv()const{
		if(empty()||fabs(at(0))<1e-9) return poly();
		int n=deg(),m=1;
		poly b{1.0/at(0)};
		while(m<=n){
			int next=min(m<<1,n+1);
			poly da;
			da.f=vector<long double>(f.begin(),f.begin()+min((int)f.size(),next));
			if(da.size()<next) da.f.resize(next,0);
			poly db(b);
			if(db.size()<next) db.f.resize(next,0);
			poly t(da*db);
			t.f.resize(next);
			poly s(next-1);
			s[0]=2;
			(s-=t)*=db;
			s.f.resize(next);
			b=s,m=next;
		}
		return b;
	}
	poly poly::derivative()const{
		if(!deg()) return poly();
		poly d(deg()-1);
		for(int i=0;i<=d.deg();++i) d[i]=at(i+1)*(i+1);
		return d;
	}
	poly poly::indefinite_integral()const{
		poly d(deg()+1);
		for(int i=1;i<=d.deg();++i) d[i]=at(i-1)/i;
		return d;
	}
	long double poly::definite_integral(long double l,long double r)const{
		poly f=indefinite_integral();
		return f(r)-f(l);
	}
	std::set<long double> poly::solution(long double L,long double R)const{
		std::set<long double> s;
		poly d=derivative();
		for(long double i=L,val,sol;i<=R;i+=0.5){
			sol=i;
			for(int j=1;j<=500&&!(fabs(sol)<1e-6);++j) sol=sol-(*this)(sol)/d(sol);
			val=(*this)(sol);
			if(abs(val)<1e-6&&!s.count(sol)) s.insert(sol);
		}
		return s;
	}
}
#endif
