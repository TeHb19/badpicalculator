#include <iostream>
#include <chrono>
const short len = 2048;
const short loops=30;
const short lim=1;
class Num{
public:
    bool x[len];
    Num(){
        for(short i=0;i<len;i++) x[i]=0;
    }
    Num(bool ax[]){
    for(short i=0;i<len;i++) x[i]=ax[i];
    }
    void display(){
    short st=len-1;
    for(short i=0;i<len;i++) if(x[i]) {st=i;break;}
    for(short i=st;i<len;i++) std::cout<<x[i];

    }
    Num operator<<(short n){
    Num ans;
    for(short i=0;i<len-n;i++) ans.x[i]=x[i+n];
    return ans;
    }

    Num operator>>(short n){
    Num ans;
    for(short i=len-1;i>n-1;i--) ans.x[i]=x[i-n];
    return ans;
    }

    Num operator+(Num n){
    Num ans;
    bool tmp=0;
    for(short i=len-1;i>0;i--){
        bool tmp1=0;
        tmp1=(n.x[i] && x[i])^(n.x[i] && tmp)^(tmp && x[i]);
        ans.x[i]= (n.x[i] ^ x[i]) ^ tmp;
        tmp=tmp1;
    }
    ans.x[0]= (n.x[0] ^ x[0]) ^ tmp;
    return ans;
    }

    Num operator^(Num n){
        Num ans;
        for(short i=0;i<len;i++) ans.x[i]=x[i] ^ n.x[i];
        return ans;
    }

    Num operator|(Num n){
    Num ans;
    for(short i=0;i<len;i++) ans.x[i] = x[i] || n.x[i];
    return ans;
    }

    Num operator&(Num n){
    Num ans;
    for(short i=0;i<len;i++) ans.x[i]=x[i] && n.x[i];
    return ans;
    }

    Num operator!(){
    Num ans;
    for(short i=0;i<len;i++) ans.x[i]= ! x[i];
    return ans;
    }

    Num operator-(){
    Num ans;
    for(short i=0;i<len;i++) ans.x[i]= ! x[i];
    ans++;
    return ans;
    }

    Num operator*(Num n){
    Num ans,tmp,tmp1;
    for(short i=0;i<len;i++) tmp.x[i]=x[i];
    bool neg=0;
    if(n.x[0]) {tmp1=-n;neg=1;}
    else tmp1=n;
    if(x[0]) {tmp=-tmp;neg=!neg;}
    for(short i=0;i<len;i++) if(tmp.x[len-i-1]) ans=ans+(tmp1<<i);
    if(neg) return -ans;
    else return ans;
    }

    bool operator<=(Num n){
    for(short i=0;i<len;i++) if(x[i]^n.x[i]) return n.x[i];
    return 1;
    }

    bool operator>=(Num n){
    for(short i=0;i<len;i++) if(x[i]^n.x[i]) return x[i];
    return 1;
    }

    bool operator==(Num n){
    for(short i=0;i<len;i++) if(x[i]^n.x[i]) return 0;
    return 1;
    }

    bool operator!=(Num n){
    for(short i=0;i<len;i++) if(x[i]^n.x[i]) return 1;
    return 0;
    }

    void operator++(int){
    short tmp=-1;
    for(short i=len-1;i>=0;i--) if(x[i]==0){tmp=i;x[i]=1;break;}
    for(short i=tmp+1;i<len;i++) x[i]=0;
    }

    void operator--(int){
    short tmp=-1;
    for(short i=len-1;i>=0;i--) if(x[i]==1){tmp=i;x[i]=0;break;}
    for(short i=tmp+1;i<len;i++) x[i]=1;
    }

    bool operator<(Num n){
    for(short i=0;i<len;i++) if(x[i]^n.x[i]) return !x[i];
    return 0;
    }

    bool operator>(Num n){
    for(short i=0;i<len;i++) if(x[i]^n.x[i]) return !x[i];
    return 0;
    }

    short ln(){
    short ans=1;
    for(short i=0;i<len-1;i++) if(x[i]) {ans=len-i;break;}
    return ans;
    }

};



Num karatsuba(Num n1, Num n2,short rec){
//std::cout<<"Doing karatsuba for ";
//n1.display();
//std::cout<<" and ";
//n2.display();
//std::cout<<" with limit in "<<rec<<" steps"<<'\n';
Num ans;
if(rec==0) return n1*n2;
short l1=n1.ln();
short l2=n2.ln();
if(l1<3){ans=n1*n2;return ans;}
if(l2<3){ans=n1*n2;return ans;}
if(l1<l2) l2=l1;
else l1=l2;
Num high1=n1>>(l1>>1);
Num high2=n2>>(l2>>1);
Num low1=n1+((-high1)<<(l1>>1));
Num low2=n2+((-high2)<<(l1>>1));
//std::cout<<"First number separated into ";
//high1.display();
//std::cout<<" and ";
//low1.display();
//std::cout<<'\n';
//std::cout<<"Second number separated into ";
//high2.display();
//std::cout<<" and ";
//low2.display();
//std::cout<<'\n';
Num tmp1=karatsuba(high1,high2,rec-1);
//std::cout<<"Multiplication for high parts is ";
//tmp1.display();
//std::cout<<'\n';
Num tmp2=karatsuba(low1,low2,rec-1);
//std::cout<<"Multiplication for low parts is ";
//tmp2.display();
//std::cout<<'\n';
Num tmp3=karatsuba(high1+low1,high2+low2,rec-1)+(-tmp1)+(-tmp2);
//std::cout<<"wtf is ";
//tmp3.display();
//std::cout<<'\n';
ans=(tmp1<<((l1>>1)+(l1>>1)))+tmp2+(tmp3<<(l1>>1));
//std::cout<<"The result of karatsuba for ";
//n1.display();
//std::cout<<" and ";
//n2.display();
//std::cout<<" with limit in "<<rec<<" steps is ";
//ans.display();
//std::cout<<"\n";
return ans;
}

Num pow(Num num,short n){
Num ans;
if(n==0){ans.x[len-1]=1;}
else{
    Num tmp=pow(num,n>>1);
    ans=karatsuba(tmp,tmp,lim);
    if(n%2) ans=karatsuba(ans,num,lim);
}
return ans;
}

Num diva(Num big,Num small){
Num ans;
if(big<small) return ans;
Num tmp=small;
ans++;
while(1){
    if(tmp<=big) {tmp=tmp<<1;ans=ans<<1;}
    else {tmp=tmp>>1;ans=ans>>1;break;}
}
ans=diva(big+(-tmp),small)+ans;
return ans;
}

Num mod(Num big,Num small){
return big+(-(karatsuba(small,diva(big,small),lim)));
}

Num gcd(Num n1,Num n2){
Num ans;
if((ans==n2)&&(n1==ans)) return ans;
if(n1<n2) return gcd(n2,n1);
if(mod(n1,n2)==ans) return n2;
return gcd(n2,mod(n1,n2));
}

class Frac{
 public:
     Num num;
     Num den;

     Frac(){
     bool tmp[len];
     for(short i=0;i<len;i++) tmp[i]=0;
     Num n(tmp);
     tmp[len-1]=1;
     Num n1(tmp);
     num=n;
     den=n1;
     }


     Frac(Num anum,Num aden){
     num=anum;
     den=aden;
     }

     Frac operator+(Frac frac){
     Frac ans;
     ans.num=karatsuba(num,frac.den,lim)+karatsuba(den,frac.num,lim);
     ans.den=karatsuba(den,frac.den,lim);
     Num tmp=gcd(ans.num,ans.den);
     Num tmp1;
     tmp1++;
     if(tmp!=tmp1){
     ans.num=diva(ans.num,tmp);
     ans.den=diva(ans.den,tmp);}

     return ans;
     }

     Frac operator-(){
     Frac ans(-num,den);
     return ans;
     }
void display(){
     num.display();
     std::cout<<'/';
     den.display();
     }

};
void spitoutdecimal(Num n1,Num n2){
for(short i=0;i<100;i++){
short j=0;
while(n1>=n2){j++;n1=n1+(-n2);}
n1=n1+n1+n1+n1+n1;
n1=n1+n1;
std::cout<<j;
}
}

int main(){
Frac f1,f2,f;
Num c1,c2,de,one,den1,den2,four,bruh;
one.x[len-1]=1;
four.x[len-3]=1;
for(short i=0;i<5;i++) c1++;
for(short i=0;i<239;i++) c2++;
for(short i=0;i<len;i++) std::cout<<bruh.x[i];
de=one;
den1=c1;
den2=c2;
c1=karatsuba(c1,c1,lim);
c2=karatsuba(c2,c2,lim);
for(short i=0;i<loops;i++){
auto start = std::chrono::steady_clock::now();
Frac tmp1(four,karatsuba(de,den1,lim));
Frac tmp2(one,karatsuba(de,den2,lim));
if(i%2) {tmp1=-tmp1;tmp2=-tmp2;}
f1=f1+tmp1;
f2=f2+tmp2;
den1=karatsuba(den1,c1,lim);
den2=karatsuba(den2,c2,lim);
de++;
de++;
auto end = std::chrono::steady_clock::now();
std::cout<<"Finished iteration #" <<i<<'/'<<loops-1<<'\n';
std::cout<<"Time elapsed for this loop in ns: "<< std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
std::cout<<'\n';
}
f=f1+(-f2);
f.num=f.num+f.num;
f.num=f.num+f.num;
std::cout<<std::endl;
spitoutdecimal(f.num,f.den);

}
