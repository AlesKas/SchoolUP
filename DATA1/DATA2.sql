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
