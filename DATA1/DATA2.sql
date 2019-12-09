--Vyberte země světa, které mají větší HDP (GNP) než všechny země v Africe.
SELECT name FROM country WHERE gnp > (SELECT MAX(gnp) FROM country WHERE continent = 'Africa');

--Vyberte země Evropy, které mají větší HDP (GNP) než všechny země v Africe.
SELECT name FROM country WHERE gnp > (SELECT MAX(gnp) FROM country WHERE continent = 'Africa') and name = 'Europe';

--Vyberte země Evropy, které mají menší HDP (GNP) než některé země v Africe.
SELECT name FROM country WHERE gnp > (SELECT gnp FROM country WHERE continent = 'Africa' ORDER BY RANDOM() LIMIT 1) and continent = 'Europe';

--Vyberte země světa, které mají větší HDP (GNP) než všechny země v Africe dohromady.
SELECT name FROM country WHERE gnp > (SELECT SUM(gnp) FROM country WHERE continent = 'Africa') and continent = 'Europe';

--Vytvořte dotaz, který vrátí seznam kontinentů a pro každý kontinent nejlidnatější stát.
SELECT DISTINCT continent, name FROM country INNER JOIN (SELECT max(population) FROM country GROUP BY continent) as max on max = country.population;

--Vytvořte dotaz, který očísluje jednotlivé země podle počtu obyvatel.
SELECT ROW_NUMBER() OVER (ORDER BY population), name FROM country;