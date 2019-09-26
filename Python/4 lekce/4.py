import sys

for x in range(10):
    if (x % 2) == 0:
        print(x)
    else:
        pass

print(sys.platform)

st = ["vecer", "bude", "horko"]
nd = ["vcera", "dnes", "zitra"]
for x in zip(st, nd):
    print("{pr} {dr}".format(pr=x[0], dr=x[1]))

print("*")
print("* *")
print("*  *")
print("*   *")
print("*     *")
print("*      *")
print("*********")