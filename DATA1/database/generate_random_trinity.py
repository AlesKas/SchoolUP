import random

for _ in range(100):
    date = random.randint(1, 31)
    customer = random.randint(1, 14)
    item = random.randint(1, 24)

    print(f"({date}, {customer}, {item}),")