import random
import sys
N = int(sys.argv[1])
x = [0.0] * N
for i in range(N):
    x[i] = random.uniform(-10, 10)
with open('truex.dat', 'w') as xfile:
    for i in range(N):
        xfile.write(str(x[i]))
        xfile.write('\t')

A = [[0.0] * N] * N
with open("A.dat", 'w') as Afile:
    for i in range(N):
        for j in range(N):
            A[i][j] = random.random()
            Afile.write(str(A[i][j]))
            Afile.write('\t')
        Afile.write('\n')


with open("b.dat", 'w') as bfile:
    for i in range(N):
        bi = 0.0
        for j in range(N):
            bi += A[i][j] * x[i]
        bfile.write(str(bi))
        bfile.write('\t')


