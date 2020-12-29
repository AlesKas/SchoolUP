SELECT DISTINCT continent FROM country;

SELECT * FROM country WHERE governmentform = 'Republic';

SELECT COUNT(*) FROM country;

SELECT name, (population / surfacearea) as zalidneni FROM country;

SELECT COUNT(*) FROM country WHERE governmentform = 'Republic';

SELECT continent, COUNT(*) as pocet_zemi FROM country GROUP BY continent;

SELECT continent, SUM(population) as pocet_lidi FROM country GROUP BY continent;

SELECT headofstate, count(*) as pocet_zemi FROM country GROUP BY headofstate ORDER BY pocet_zemi DESC;

SELECT headofstate FROM country GROUP BY headofstate HAVING COUNT(DISTINCT continent) > 1;

SELECT DISTINCT headofstate FROM country WHERE continent = 'Europe' OR continent = 'North America';

SELECT DISTINCT headofstate FROM country WHERE continent = 'North America'
    EXCEPT
    SELECT DISTINCT headofstate FROM country WHERE continent = 'Europe';

SELECT DISTINCT headofstate FROM country WHERE continent = 'North America'
    INTERSECT
    SELECT DISTINCT headofstate FROM country WHERE continent = 'Europe';

SELECT name FROM country WHERE continent = 'Europe' ORDER BY surfacearea DESC LIMIT 1;

SELECT region FROM country GROUP BY region ORDER BY sum(population) DESC LIMIT 1;

SELECT headofstate FROM country GROUP BY headofstate HAVING sum(population) > 100000000;

SELECT region, avg(gnp) as AVGgnp FROM country WHERE indepyear > 1950 GROUP BY region;