import random

zbozis = ['iphone', 'macbook', 'PC', 'fen', 'kartacek', 'sklenice', 'miska', 'kebab', 'notebook', 'mys','klavesnice','sluchatka','triko','teplaky',
    'pracka','lednicka','zamek', 'pasta','papir','skrin','stul','blah','foo','bar','qux']

for zbozi in zbozis:
    cena = random.randint(0, 9999)
    skladem = random.randint(0, 100)

    print(f"('{zbozi}', {cena}, {skladem}),")