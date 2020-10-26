--Navrhněte tabulku pro jednoduchý adresář
CREATE TABLE adresar
    (jmeno TEXT NOT NULL,
    prijmeni TEXT NOT NULL,
    telefon varchar(9) NOT NULL,
    email varchar(50) PRIMARY KEY,
    web varchar(25),
    narozen DATE NOT NULL,
    pohlavi varchar(1) NOT NULL CHECK ((pohlavi = 'M') OR (pohlavi = 'F')),
    deti INT NOT NULL CHECK (deti >= 0));

--aplňte předchozí tabulku alespoň pěti záznamy.
INSERT INTO adresar (jmeno, prijmeni, telefon, email, narozen, pohlavi, deti) VALUES
    ('Kamila', 'Sedlbauerova', '732852732', 'kocky123@gmail.com', '1995-02-16', 'F', 0),
    ('Roman', 'Valcik', '605785325', 'r.valcik@email.cz', '1965-05-22', 'M', 3),
    ('Patrik', 'Chudoba', '963258741', 'chodoba@seznam.cz', '2000-01-01', 'M', 0),
    ('Esmeralda', 'De Niro', '555777999', 'deniro@seznam.cz', '1987-05-05', 'F', 5);

--Vybrané osobě přidejte jedno dítě.
UPDATE adresar SET deti = deti + 1 WHERE jmeno = 'Esmeralda';

--Odstraňte všechny muže z adresáře.
DELETE FROM adresar WHERE pohlavi = 'M';

--seznam všech kontinentů (bez duplicit)
SELECT DISTINCT continent FROM country;

--země, kde je státní zřízení republika
SELECT name FROM country WHERE governmentform = 'Republic';

--počet všech zemí v tabulce
SELECT COUNT(*) FROM country;

--počet obyvatel na km2 v každé zemi
SELECT name, population / surfacearea AS density FROM country;

--počet všech zemí v tabulce, kde je státní zřízení republika
SELECT COUNT(*) FROM country WHERE governmentform = 'Republic';

--počet zemí na každém kontinentu
SELECT continent, count(*) FROM country GROUP BY continent;

--velikost populace na každém kontinentě
SELECT continent, SUM(population) FROM country GROUP BY continent;

--seznam vládců a počet zemí, ve kterých působí, setříděný podle počtu zemí sestupně
SELECT headofstate, count(*), SUM(population) FROM country GROUP BY headofstate ORDER BY SUM(population) DESC;

--vládce, kteří působí minimálně na dvou světových kontinentech
SELECT headofstate FROM country GROUP BY headofstate HAVING count(continent) > 1;

--vládce, kteří působí v Severní Americe nebo Evropě
SELECT headofstate FROM country GROUP BY headofstate, continent HAVING continent = 'Europe' or continent = 'North America';
SELECT headofstate FROM count WHERE continent = 'Eruope' or continent = 'North America';

--vládce, kteří působí současně v Severní Americe i Evropě
SELECT headofstate FROM country GROUP BY headofstate, continent HAVING continent = 'Europe' AND continent = 'North America';
SELECT headofstate FROM country WHERE continent = 'Eruope'
  INTERSECT
  SELECT headofstate FROM country WHERE continent = 'North America';

--vládce, kteří působí v Severní Americe, ale nepůsobí v Evropě
SELECT headofstate FROM country GROUP BY headofstate, continent HAVING  continent = 'North America' AND continent <> 'Europe';
SELECT headofstate FROM country WHERE continent = 'North America' INTERSECT SELECT headofstate FROM country WHERE continent <> 'Europe';

--co je největší evropská země dle rozlohy
SELECT name FROM country WHERE continent = 'Europe'  ORDER BY surfacearea DESC LIMIT 1;

--co je nejlidnatější region
SELECT region FROM country GROUP BY region ORDER BY sum(population) DESC LIMIT 1;
SELECT SUM(population) AS populace, region FROM country GROUP BY region ORDER BY populace DESC LIMIT 1;

--seznam všech vládců, kteří vládnou alespoň 100 000 000 obyvatel
SELECT headofstate FROM country GROUP BY headofstate HAVING SUM(population) > 100000000;

--průměrný hrubý národní produkt (gnp) zemí podle regionu, které získaly nezávislost po roce 1950.
SELECT region, AVG(gnp) AS average_gnp FROM country WHERE indepyear > 1950 GROUP BY region;

--Názvy měst a k nim příslušné názvy zemí.
SELECT city.name, country.name FROM city JOIN country ON city.countrycode = country.code;
SELECT city.name, country.name FROM city, country WHERE city.countrycode = country.code;

--Řeč, kterou se mluví v jednotlivých zemích.
SELECT name, language FROM country JOIN countrylanguage ON country.code = countrylanguage.countrycode AND isofficial;
SELECT name, language FROM countrylanguage, country WHERE country.code = countrylanguage.countrycode;

--Řeč, kterou se mluví v jednotlivých městech.
SELECT name, language FROM city JOIN countrylanguage ON city.countrycode = countrylanguage.countrycode;

--Řeči, kterými se mluví v Evropě.
SELECT DISTINCT  language FROM countrylanguage NATURAL JOIN (SELECT code FROM country WHERE continent = 'Europe') as TMP;
SELECT name, language FROM countrylanguage, country WHERE country.code = countrylanguage.countrycode AND continent = 'Europe';

--Informace o zemích z G7 ("USA", "FRA", "ITA", "CAN", "DEU", "GBR", "JPN")
SELECT * FROM country JOIN g7country ON country.code = g7country.countrycode;

--Hlavní města zemí z G7.
SELECT DISTINCT name FROM city JOIN ( SELECT capital FROM country JOIN g7country ON country.code = g7country.countrycode) as TMP on TMP.capital = city.id;
SELECT city.name FROM city, (SELECT capital FROM country, g7country WHERE country.code = g7country.countrycode) as citycode WHERE city.id = citycode.capital;

--Názvy hlavních měst v jednotlivých zemích.
SELECT DISTINCT city.name, country.name FROM city JOIN country ON city.id = country.capital;

-- Řeči, kterými se mluví v Karibiku i v Asii.
SELECT country.region, countrylanguage.language FROM country, countrylanguage WHERE country.code = countrylanguage.countrycode AND (region = 'Caribbean' OR continent = 'Asia');

-- Největší město světa (nikoliv maximální).
SELECT name, population FROM city ORDER BY population DESC LIMIT 1;

-- Nejmenší hlavní město Evropy (nikoliv minimální).
SELECT city.name, country.name, city.population FROM city, country WHERE country.capital = city.id AND country.continent = 'Europe' ORDER BY city.population ASC LIMIT 1;

-- Dvojce různých států jižní Evropy, které mají stejný oficiální jazyk. (Každá dvojce by měla být ve výsledku pouze jednou)
SELECT countrylanguage.language, foo.name FROM countrylanguage NATURAL JOIN (SELECT name, code as countrycode  FROM country WHERE region = 'Southern Europe') as foo WHERE countrylanguage.isofficial = True;

/*Ověřte, jakými kroky byly provedeny dotazy, které byly provedeny v tomto a na posledních cvičeních věnovaných práci s DB. 
Je možné, že DB použije operace, které nebyly zmíněny.
Z názvu se pokuste odhadnout, jak data zpracovávájí.*/
--EXPLAIN ANALYZE + prikaz

--Zkuste navrhnout vhodné indexy pro tabulky z předchozích cvičení. Ověřte, jak se změní průběh provádění dotazů po vytvoření indexů.
CREATE UNIQUE INDEX country_code ON country(code);

/* 
Použijte následující dotaz, který vám tabulku foo naplní násobky čísel tří od 1 do 100000.

INSERT INTO foo (a,b)
SELECT generate_series, generate_series * 3
  FROM (SELECT * FROM generate_series(1,100000,1)) as q;
Zkuste navrhnout dotazy pracující s touto tabulku. 
Zaměřte se na to, jak budou dotazy zpracovány před naplněním tabulky a po jejím naplnění. 
Porovnejte, jestli se průběh dotazu změní po provedení příkazu ANALYZE. 
(Poznámka: mezi vhodné dotazy mohout patřit výběry podle kritérií, operace UNION, EXCEPT, atd.)
*/

--Vyberte jména kusů a jména jejich atomických podčástí. Atomická část je ta, která se z ničeho neskládá a podčást kusu je částí kusu nebo částí podčásti kusu.
WITH RECURSIVE
    sub_without (super, sub)
     AS (SELECT superpart, subpart FROM contain
       UNION DISTINCT
       SELECT superpart, sub FROM contain, sub_without WHERE subpart = super),
    all_super AS (SELECT superpart FROM contain),
    sup_sub AS (SELECT * FROM sub_without EXCEPT (SELECT sub_without.* FROM sub_without JOIN all_super ON sub = all_super.superpart))
    SELECT (SELECT name FROM part WHERE id = super) AS superpart, (SELECT name FROM part WHERE id = sub) AS subpart FROM sup_sub ORDER BY super;

--Vyberte jména kusů, jména jeho atomických podčástí a celkový počet atomických podčástí potřebný pro sestavení kusu.
WITH RECURSIVE
    sub_with (super, sub, quantity)
     AS (SELECT * FROM contain
       UNION DISTINCT
       SELECT superpart, sub, contain.quantity * sub_with.quantity FROM contain, sub_with WHERE subpart = super),
    all_super AS (SELECT superpart FROM contain),
    sup_sub AS (SELECT * FROM sub_with EXCEPT (SELECT sub_with.* FROM sub_with JOIN all_super ON sub = all_super.superpart)),
    sup_acum AS (SELECT super, sub, SUM(quantity) AS quantity FROM sup_sub GROUP BY sub, super)
    SELECT (SELECT name FROM part WHERE id = super) AS superpart, (SELECT name FROM part WHERE id = sub) AS subpart, quantity FROM sup_acum ORDER BY super;

--Vyberte země světa, které mají větší HDP (GNP) než všechny země v Africe.
SELECT name FROM country WHERE gnp > (SELECT MAX(gnp) FROM country WHERE continent = 'Africa');

--Vyberte země Evropy, které mají větší HDP (GNP) než všechny země v Africe.
SELECT name FROM country WHERE gnp > (SELECT MAX(gnp) FROM country WHERE continent = 'Africa') and name = 'Europe';

--Vyberte země Evropy, které mají menší HDP (GNP) než některé země v Africe.
SELECT name FROM country WHERE gnp < (SELECT gnp FROM country WHERE continent = 'Africa' ORDER BY RANDOM() LIMIT 1) and continent = 'Europe';

--Vyberte země světa, které mají větší HDP (GNP) než všechny země v Africe dohromady.
SELECT name FROM country WHERE gnp > (SELECT SUM(gnp) FROM country WHERE continent = 'Africa') and continent = 'Europe';

--Vytvořte dotaz, který vrátí seznam kontinentů a pro každý kontinent nejlidnatější stát.
SELECT DISTINCT continent, name FROM country INNER JOIN (SELECT max(population) FROM country GROUP BY continent) as max on max = country.population;

--Vytvořte dotaz, který očísluje jednotlivé země podle počtu obyvatel.
SELECT ROW_NUMBER() OVER (ORDER BY population), name FROM country;

--Vytvořte dotaz, který očísluje jednotlivé země na kontinentu podle počtu obyvatel.
SELECT continent,ROW_NUMBER() OVER (PARTITION BY continent ORDER BY population), name FROM country;

--Pohled: faktura + její celková cena
CREATE VIEW cena AS SELECT numberoffact, quantity * price AS cena FROM fact, item WHERE fact.numberoffact = item.unit;

--Pohled: odběratelé a celková zaplacená částka
CREATE VIEW subsprice AS SELECT subscriber.name, quantity * price AS cena FROM subscriber, fact, item WHERE subscriber.id = fact.subscriber and fact.numberoffact = item.unit;

--Dotaz: na kterém zboží bylo nejvíc utrženo
SELECT name FROM item ORDER BY quantity * price DESC LIMIT 1;

--Dotaz: na kterém zboží bylo nejvíc utrženo podle města

--Aby byla záznamenávána historie cen zboží.
CREATE OR REPLACE FUNCTION zmena_zbozi() RETURNS TRIGGER AS $$
BEGIN
IF (new.cenaZaKus > old.cenaZaKus) THEN INSERT INTO log VALUES (now(), new.nazev, 'Zdrazeni', new.cenaZaKus - old.cenaZaKus);
end if;
if (new.cenaZaKus < old.cenaZaKus) THEN INSERT INTO log VALUES (now(), new.nazev, 'Slevneni', old.cenaZaKus - new.cenaZaKus);
end if;
return new;
end;
$$ LANGUAGE 'plpgsql';

CREATE TRIGGER zmena_ceny AFTER UPDATE ON zbozi FOR EACH ROW EXECUTE PROCEDURE zmena_zbozi();

--Pokud bude zboží odstraněno, bude odstraněna i historie jeho cen.
CREATE OR REPLACE FUNCTION delete_from_log() RETURNS TRIGGER AS $$
BEGIN
DELETE FROM log WHERE log.jmeno = old.nazev;
return new;
end;
$$LANGUAGE 'plpgsql';
CREATE TRIGGER delete_log AFTER DELETE ON zbozi FOR EACH ROW EXECUTE PROCEDURE delete_from_log();

--Abyste měli uloženou informaci o celkové ceně zboží na skladu.
CREATE OR REPLACE FUNCTION celkova() RETURNS TRIGGER AS $$
DECLARE sum_ceny int;
r RECORD;
BEGIN
sum_ceny := 0;
FOR r IN SELECT * FROM zbozi
LOOP
sum_ceny := sum_ceny + r.cenaZaKus * r.mnozstvi;
end loop;
UPDATE zbozi set celkova_cena = sum_ceny;
return NEW;
end;
$$ LANGUAGE 'plpgsql';

CREATE TRIGGER update_max_cena AFTER  INSERT OR UPDATE OR DELETE ON zbozi FOR EACH ROW EXECUTE PROCEDURE celkova();

--Abyste měli uloženou informaci o průměrné ceně za zboží.
CREATE OR REPLACE FUNCTION median() RETURNS TRIGGER AS $$
BEGIN
UPDATE catalog SET prumerna_cena = (SELECT celkova_cena / SUM(mnozstvi) FROM zbozi, catalog GROUP BY celkova_cena);
return new;
end;
$$ language 'plpgsql';
CREATE TRIGGER update_median AFTER  INSERT OR UPDATE OR DELETE ON zbozi FOR EACH ROW EXECUTE PROCEDURE median();
