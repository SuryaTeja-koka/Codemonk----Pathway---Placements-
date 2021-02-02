def maxAndXor(arr, n):
    ans = float('inf')
    arr.sort()


    for i in range(n - 1):
        ans = min(ans, arr[i] ^ arr[i + 1])
    return ans

for i in range(int(input())):

    n=int(input())

    a=list(map(int,input().split()))

    print(maxAndXor(a,n))
