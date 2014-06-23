import random
import sys
N = int(sys.argv[1])
x = [0.0] * N
for i in range(N):
    x[i] = random.random()
with open('truex.dat', 'w') as xfile:
    for i in range(N):
        xfile.write(str(x[i]))
        xfile.write('\t')

A = []
for i in range(N):
    A.append([0] * N)
for i in range(N):
    for j in range(N):
        A[i][j] = random.random()
for i in range(N):
    for j in range(N):
        if j > i:
            A[i][j] = A[j][i]

with open("A.dat", 'w') as Afile:
    for i in range(N):
        for j in range(N):
            Afile.write(str(A[i][j]))
            Afile.write('\t')
        Afile.write('\n')


with open("b.dat", 'w') as bfile:
    for i in range(N):
        bi = 0.0
        for j in range(N):
            bi += A[i][j] * x[j]
        bfile.write(str(bi))
        bfile.write('\t')


