SELECT name FROM country WHERE continent = 'Europe' GROUP BY name, gnp HAVING gnp > ALL(SELECT gnp FROM country WHERE continent = 'Africa');

SELECT name FROM country WHERE continent = 'Europe' GROUP BY name, gnp HAVING gnp > SOME(SELECT gnp FROM country WHERE continent = 'Africa');

SELECT name FROM country WHERE continent = 'Europe' GROUP BY name, gnp HAVING gnp > (SELECT sum(gnp) FROM country WHERE continent = 'Africa');

SELECT DISTINCT continent, name FROM country INNER JOIN (SELECT max(population) FROM country GROUP BY continent) as max on max = country.population;

SELECT ROW_NUMBER() OVER(ORDER BY population DESC) as num, name, population FROM country ORDER BY population DESC;

SELECT ROW_NUMBER() OVER(PARTITION BY continent ORDER BY population DESC) as num, name, continent,  population FROM country ORDER BY continent;