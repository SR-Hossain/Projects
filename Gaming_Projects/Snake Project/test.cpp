#include<bits/stdc++.h>

using namespace std;
typedef long long int ll;

int main(){
	ll t, n, k; 
	for(cin>>t; t-- and cin>>n; ){
		set<ll> rec;
		for(int i=0; i<n and cin>>k; i++)rec.insert(k);
		if(rec.size()<=n/2){cout<<-1<<'\n';continue;}
		set<ll> vec;
		auto it=rec.begin();
		auto itt = it; itt++;
		for(;itt!=rec.end();it++,itt++){
			vec.insert(*itt-*it);
		}
		ll ans = *vec.begin();
		for(it=vec.begin(); it!=vec.end(); it++)ans = __gcd(ans, *it);


		cout<<ans<<'\n';
	}
	
}