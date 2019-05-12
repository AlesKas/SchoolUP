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

def get_int(msg, min, default):
    while True:
        try:
            line = input(msg)
            if not line and default is not None:
                return default
            i = int(line)
            if i < min:
                print("musi byt >=", min)
            else:
                return i
        except ValueError as err:
            printf(err)

#rows = get_int("rows: ", 1, None)
#col = get_int("columns: ", 1, None)
#min = get_int("min: ", -10000000, 0)
#default = 1000
#if default < min:
#    default = 2 * min
#max = get_int("maximum:", min, default)

#row = 0
#while row < rows:
#    line = ""
#    column = 0
#    while column < col:
#        i = random.randint(min, max)
#        s = str(i)
#        while len(s) < 10:
#            s = " " + s
#        line += s
#        column += 1
#    print(line)
#    row += 1

print("-------------------")

zajmena = ["muj", "tvuj", "jeji", "jeho"]
pods = ["kočka", "pes", "kůň", "muž", "žena", "kluk", "holka"]
slovesa = ["zpívá", "běží", "skáče", "říka", "bojuje", "plave", "vidí",
         "slyší", "cítí", "spí", "hopká", "doufá", "pláče",
         "se směje", "kráčí"]
prislovce = ["hlasitě", "tiše", "rychle", "pomalu", "kvalitně", "hrozně",
           "hrubě", "zdvořile"]
lines = 5
if len(sys.argv) > 1:
    try:
        temp = int(sys.argv[1])
        if 1 <= temp <= 10:
            lines = temp
        else:
            print("řádků musí být 1-10 včetně")
    except ValueError:
        print("použití: badpoetry.py [řádky]")

while lines:
    article = random.choice(zajmena)
    subject = random.choice(pods)
    verb = random.choice(slovesa)
    if random.randint(0, 1) == 0:
        print(article, subject, verb)
    else:
        adverb = random.choice(prislovce)
        print(article, subject, adverb, verb)
    lines -= 1