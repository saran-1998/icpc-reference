//Segment Tree Range Minimum Solution

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//Segment Tree Represented in an Array (1 - based indexing)
ll tree[2000005];

//Function to build the tree (node -> current node that is being processed, start -> start index of the interval of current node, end -> end index of the interval of current node,  a -> original array)
void buildTree(ll node, ll start, ll end, ll a[])
{
    if(start == end)
    {
        tree[node] = a[start];
    }
    else
    {
        ll mid = (start+end)/2;
        buildTree(node*2, start, mid, a);
        buildTree(node*2 + 1, (mid + 1), end, a);
        tree[node] = min(tree[2*node], tree[2*node + 1]);
    }
}

//Function to update the tree (ind -> the index in original array whose value is changed, val -> new value)
void update(ll node, ll start, ll end, ll ind, ll val, ll a[])
{
    if(start == end)
    {
        a[ind] = val;
        tree[node] = val;
    }
    else
    {
        ll mid = (start+end)/2;
        if(ind >= start && ind <= mid)
        {
            update(2*node, start, mid, ind, val, a);
        }
        else
        {
            update(2*node + 1, (mid + 1), end, ind, val, a);
        }
        tree[node] = min(tree[2*node] , tree[2*node + 1]);
    }
}

//Function to perform the query (1st if -> completely inside the range, 2nd if completely outside the range) 
int rangeMinimum(ll node, ll start, ll end, ll l, ll r)
{
    if(start >= l && end <= r)
    {
        return tree[node];
    }
    
    if(start > r || end < l)
    {
        return 999999;
    }
    
    ll mid = (start+end)/2;
    ll left = rangeMinimum(2*node, start, mid, l, r);
    ll right = rangeMinimum(2*node + 1, mid + 1, end, l, r);
    return min(left, right);
}

int main()
{
    ll n,q;
    cin>>n>>q;
    ll a[n+1];
    for(ll i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    buildTree(1, 1, n, a);
    for(ll i=0; i<q; i++)
    {
        char param;
        cin>>param;
        if(param == 'u')
        {
            ll ind, val;
            cin>>ind>>val;
            update(1,1,n,ind,val,a);
        }
        else
        {
            ll l,r;
            cin>>l>>r;
            cout<<rangeMinimum(1,1,n,l,r)<<endl;
        }
    }
    return 0;
}