#1
cena = 79
druha = 2 * cena + 5
zaplatil = 3 * druha + 17
dohromady = cena + druha + zaplatil

#2
x = 2
y = 3
x = y
y = x
print(x, y) #vypise 3 3

#3
x = 5
print(x, ">", 3) #vypise 5 > 3

#4
puvodni_cena = 199
sleva = (199 / 100) * 20
po_sleve = puvodni_cena - sleva
print("Cena alba je ", puvodni_cena, "korun")
print("Sleva činí 20 procent")
print("Zaplatíš", po_sleve, "korun")

#5
peníze = 500
platim = input("Kolik budu platit? ")
zbytek = peníze - int(platim)
print("Mam", peníze, "korun")
print("Platim", platim, "korun")
print("Zbyde mi", zbytek, "korun")