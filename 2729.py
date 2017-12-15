def mul(x, y):
	re = 1
	for i in range (x, y + 1):
		re = re * i
	return re

n, m = raw_input().split()
n = int(n); m = int(m)
#print(mul(1,n)*((n+1)*n*mul(n+3-m+1,n+3)+2*(n+1)*m*mul(n+2-m+2,n+2)))
print(mul(1,n+1)*mul(n+4-m,n+2)*(n*(n+3)+2*m))
