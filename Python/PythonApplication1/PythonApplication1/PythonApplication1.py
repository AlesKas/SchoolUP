import sys
print("Hello", "world!")
x = 0
while (x < 5):
    print(x)
    x += 1
for x in ["A", "B", "C", "D", "E"]:
    print(x)
#x = input("Zadej cislo: ")
#try:
#    i = int(x)
#    print("Platne cislo: ", i)
#except ValueError as err:
#    print(err)
seeds = ["seznam", "pro", "neco"]
print(seeds)
seeds += ["idk"]
print(seeds)
for x in seeds:
    print(x)
print("--------------")
for x in range(len(seeds)):
    print(seeds[x])
seeds.append("nibba")
print(seeds)
if "x" in "abyz":
    print("yes")
else:
    print("no")

#total = 0
#count = 0
#while True:
#    line = input("cislo: ")
#    if line:
#        try:
#            num = int(line)
#        except ValueError as err:
#            print(err)
#            continue
#        except EOFerror:
#            break
#        total += num
#        count += 1
#    else:
#        break
#if count:
#    print("pocet = ", count, "celkem =", total)

def get_int(msg):
    while True:
        try:
            i = int(input(msg))
            return i
        except ValueError as err:
            print(err)
#age = get_int("Zadej vek: ")
#print(age)
print(sys.argv)
import random
x = random.randint(3, 7)
print(x)
x = random.choice(["jablko", "banan", "hruska"])
print(x)

total = 0
count = 0
max = 0
min
numbers = []
while True:
    line = input("cislo: ")
    if line:
        try:
            num = int(line)
            min = num
        except ValueError as err:
            print(err)
            continue
        except EOFerror:
            break
        total += num
        count += 1
        numbers.append(num)
        if (num > max):
            max = num
        elif (num < min):
            min = num
    else:
        break
if count:
    print("pocet =", count, "celkem =", total, "max =", max, "min =", min, "cisla:", numbers)