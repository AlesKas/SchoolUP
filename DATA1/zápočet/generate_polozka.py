import random

for _ in range(250):
    faktura = random.randint(1, 100)
    zbozi = random.randint(1, 25)
    mnozstvi = random.randint(1, 10)

    print(f"({faktura}, {zbozi}, {mnozstvi}),")