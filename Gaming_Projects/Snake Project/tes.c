#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int n;
#define sz 100000
int siv[sz], primes[sz];
void seive(){
    for(int i=2; i<=sz; siv[i++]=1);
    for(int i=2; i*i<=sz; i++)
        if(siv[i])
            for(int j=i*i; j<=sz; j+=i)
                siv[j] = 0;
    for(int i=2; i<=sz; i++)
        if(siv[i])primes[n++]=i;
    for(int i=0; i<n; i++)printf("%d ", primes[i]);
}
int main(){
    seive();
}