import random
s = "dones pivo"
p = s[:5] + " mi" + s[5:]
print(p)

# pocet = int(input("Kolik chces kopecku? "))
# print("Za" ,pocet,"kopecku zaplatis: ")
# print(pocet * 25,"korun.")5

# def get_rid_of_number():
#     names = []
#     for name in open("C:\\Users\\Aleš\\Documents\\GitHub\\SchoolUP\\Python\\data\\prijmeni.txt", encoding="utf8"):
#         surename = name.split("\t")
#         names.append(surename[0])
#     fh = open("C:\\Users\\Aleš\\Documents\\GitHub\\SchoolUP\\Python\\data\\surenames.txt", "w", encoding="utf8")
#     for i in names:
#         line = "{0}\n".format(i)
#         fh.write(line)
        
# get_rid_of_number()

def get_forenames_and_surnames():
    forenames = []
    surnames = []
    for names, filename in ((forenames, "C:\\Users\\Aleš\\Documents\\GitHub\\SchoolUP\\Python\\data\\jmena.txt"),
                            (surnames, "C:\\Users\\Aleš\\Documents\\GitHub\\SchoolUP\\Python\\data\\surenames.txt")):
        for name in open(filename, encoding="utf8"):
            names.append(name.rstrip())
    return forenames, surnames

forenames, surenames = get_forenames_and_surnames()
fh = open("C:\\Users\\Aleš\\Documents\\GitHub\\SchoolUP\\Python\\data\\test-names1.txt", "w", encoding="utf8")
for _ in range(100):
    line = "{0} {1}\n".format(random.choice(forenames), random.choice(surenames))
    fh.write(line)

fh2 = open("C:\\Users\\Aleš\\Documents\\GitHub\\SchoolUP\\Python\\data\\test-names2.txt", "w", encoding="utf8")
limit = 100
years = list(range(1970, 2013)) * 3
for year, forename, surename in zip(random.sample(years, limit), random.sample(forenames, limit), random.sample(surenames, limit)):
    name = "{0} {1}".format(forename, surename)
    fh2.write("{0:.<25}.{1}\n".format(name, year))