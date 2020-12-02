import random

for _ in range(100):
    customer = random.randint(1, 14)
    day = random.randint(1, 30)
    month = random.randint(1,12)
    year = random.randint(1990, 2020)

    hour = random.randint(0,23)
    minute = random.randint(0,59)
    sec = random.randint(0,59)

    print(f"({customer}, '{month}/{day}/{year} {hour}:{minute}:{sec}'),")