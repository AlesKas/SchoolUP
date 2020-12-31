SELECT city.name, country.name FROM city JOIN country ON city.countrycode = country.code;

SELECT countrylanguage.language, country.name FROM countrylanguage JOIN country ON countrylanguage.countrycode = country.code;

SELECT DISTINCT countrylanguage.language FROM countrylanguage JOIN country ON countrylanguage.countrycode = country.code WHERE country.continent = 'Europe';

SELECT DISTINCT language FROM countrylanguage NATURAL JOIN g7country WHERE isofficial = True;

SELECT city.name FROM city, country, g7country WHERE country.capital = city.id AND country.code = g7country.countrycode;

SELECT DISTINCT language FROM country JOIN countrylanguage ON code = countrycode WHERE continent = 'Asia' INTERSECT
    SELECT DISTINCT language FROM country JOIN countrylanguage ON code = countrycode WHERE region = 'Caribbean';

SELECT c1.name, c2.name FROM country as c1, country as c2, countrylanguage as l1, countrylanguage as l2 WHERE c1.code = l1.countrycode
    AND c2.code = l2.countrycode
    AND l1.language = l2.language 
    AND l1.isofficial = True
    AND l2.isofficial = True
    AND c1.name < c2.name
    AND c1.region = 'Southern Europe'
    AND c2.region = 'Southern Europe';

SELECT c1.name FROM city as c1, city as c2 WHERE c1.population > c2.population
    EXCEPT SELECT c2.name FROM city as c1, city as c2 where c1.population > c2.population;

SELECT c1.name FROM city as c1, city as c2, country
    WHERE c1.population < c2.population 
    AND c1.id = country.capital
    AND country.continent = 'Europe'
    EXCEPT
    SELECT c2.name FROM city as c1, city as c2, country
    WHERE c1.population < c2.population 
    AND c1.id = country.capital
    AND country.continent = 'Europe';
