CREATE TABLE zakaznik(
    id SERIAL PRIMARY KEY,
    jmeno TEXT
);

INSERT INTO zakaznik (jmeno) VALUES 
    ('Petr'),
    ('Tomas'),
    ('Jan'),
    ('Jakub'),
    ('Vladimir'),
    ('Ales'),
    ('Radim'),
    ('Jachym'),
    ('Jana'),
    ('Barbora'),
    ('Adam'),
    ('Anna'),
    ('Xenie'),
    ('Lenka');

-- DROP TABLE zakaznik;

CREATE INDEX ON zakaznik(id);

CREATE TABLE faktura(
    id SERIAL PRIMARY KEY,
    zakaznik_id INT REFERENCES zakaznik(id),
    vystaveni TIMESTAMP
);

INSERT INTO faktura (zakaznik_id, vystaveni) VALUES
    (7, '2/23/2003 6:25:44'),
    (5, '12/8/2005 8:33:39'),
    (9, '3/13/2020 4:8:31'),
    (1, '1/7/2017 13:50:49'),
    (3, '2/21/2013 18:47:8'),
    (14, '9/13/2001 2:41:34'),
    (8, '10/6/1990 7:55:58'),
    (11, '4/6/2017 3:46:21'),
    (13, '5/26/2006 10:16:53'),
    (5, '1/23/2018 22:33:15'),
    (12, '7/26/2011 16:54:13'),
    (13, '9/15/2019 19:18:1'),
    (9, '5/19/1998 0:56:49'),
    (1, '8/14/1993 14:26:8'),
    (8, '1/21/2007 6:26:4'),
    (5, '6/17/2012 11:27:44'),
    (10, '4/6/1997 6:44:51'),
    (1, '11/10/1993 8:10:9'),
    (2, '10/15/2002 18:18:8'),
    (9, '5/10/2002 13:32:43'),
    (10, '1/11/1998 16:31:45'),
    (5, '10/23/1999 13:51:1'),
    (9, '8/2/2001 5:47:9'),
    (14, '8/21/2017 12:0:30'),
    (10, '7/3/2005 17:57:26'),
    (1, '1/15/2015 7:17:58'),
    (2, '7/15/1991 5:8:24'),
    (2, '9/18/2009 14:20:38'),
    (3, '10/19/2017 15:12:11'),
    (13, '9/2/2014 9:42:11'),
    (14, '5/4/2018 4:23:45'),
    (4, '8/26/2007 3:13:8'),
    (5, '12/12/2011 5:3:9'),
    (2, '12/19/2008 2:33:54'),
    (7, '1/23/2006 19:18:23'),
    (10, '9/26/1994 3:59:2'),
    (7, '5/27/1993 15:20:54'),
    (10, '2/16/2002 23:8:27'),
    (10, '7/5/1995 11:36:58'),
    (8, '8/9/2005 23:14:26'),
    (7, '4/18/2011 21:44:0'),
    (10, '5/18/2011 2:3:30'),
    (3, '12/20/2013 7:5:34'),
    (13, '7/16/2017 11:33:32'),
    (6, '6/19/2020 16:52:17'),
    (8, '12/9/2019 2:45:17'),
    (5, '4/12/2012 20:17:56'),
    (4, '7/10/1994 19:41:50'),
    (5, '11/20/1990 10:7:23'),
    (2, '2/8/2000 16:8:27'),
    (11, '10/17/2009 0:28:35'),
    (9, '6/30/2013 7:13:58'),
    (8, '1/24/2007 11:19:16'),
    (7, '1/10/2000 11:37:14'),
    (4, '7/26/2019 10:6:45'),
    (2, '11/6/2002 16:24:51'),
    (10, '12/26/1995 9:27:55'),
    (1, '2/5/2002 1:10:6'),
    (14, '3/19/1990 14:47:21'),
    (9, '8/27/1993 4:11:5'),
    (13, '2/26/2013 5:59:33'),
    (14, '10/19/2000 1:50:7'),
    (5, '11/14/1994 21:3:11'),
    (5, '6/1/1993 22:55:33'),
    (13, '1/23/2000 9:55:22'),
    (6, '5/22/2020 15:17:7'),
    (6, '8/30/1998 0:51:44'),
    (10, '10/24/2019 0:38:20'),
    (8, '4/20/2020 17:48:38'),
    (13, '6/12/1990 11:11:5'),
    (14, '12/7/1998 19:35:42'),
    (4, '5/29/1991 1:24:11'),
    (14, '9/21/2004 7:1:57'),
    (3, '8/30/1998 6:30:10'),
    (8, '10/22/2004 23:41:24'),
    (13, '6/22/2011 7:22:12'),
    (13, '4/18/2001 22:28:21'),
    (14, '11/27/1990 16:26:18'),
    (6, '3/29/2017 22:28:35'),
    (3, '5/17/2012 18:32:26'),
    (4, '3/18/2014 20:36:4'),
    (4, '2/23/1993 10:28:31'),
    (13, '2/25/1992 14:1:40'),
    (6, '1/23/2012 14:26:44'),
    (9, '10/24/2007 2:14:48'),
    (7, '6/8/2018 15:19:18'),
    (13, '3/14/2008 8:48:52'),
    (7, '5/4/2004 17:49:19'),
    (3, '11/21/2013 10:41:34'),
    (12, '2/7/2009 2:41:6'),
    (10, '5/2/2013 6:26:33'),
    (1, '3/5/2004 3:8:20'),
    (5, '11/12/2002 21:46:50'),
    (4, '8/27/1993 15:4:29'),
    (5, '1/15/2005 9:23:26'),
    (1, '7/9/2004 3:40:21'),
    (4, '1/9/1991 14:9:35'),
    (3, '2/26/1996 5:10:2'),
    (12, '11/11/2008 20:10:13'),
    (13, '8/27/1991 1:35:58');


CREATE INDEX ON faktura(id);

CREATE TABLE zbozi(
    id SERIAL PRIMARY KEY, 
    jmeno TEXT NOT NULL,
    cena NUMERIC CONSTRAINT positivni_cena CHECK (cena >= 0),
    skladem INT CONSTRAINT na_sklade CHECK (skladem >= 0)
);

INSERT INTO zbozi (jmeno, cena, skladem) VALUES 
    ('iphone', 2345, 17),
    ('macbook', 5400, 29),
    ('PC', 7184, 23),
    ('fen', 6577, 69),
    ('kartacek', 4168, 21),
    ('sklenice', 5487, 86),
    ('miska', 9612, 34),
    ('kebab', 1088, 38),
    ('notebook', 6529, 59),
    ('mys', 7938, 89),
    ('klavesnice', 2408, 72),
    ('sluchatka', 7402, 97),
    ('triko', 5344, 55),
    ('teplaky', 8113, 53),
    ('pracka', 9807, 92),
    ('lednicka', 5095, 34),
    ('zamek', 9369, 81),
    ('pasta', 6700, 98),
    ('papir', 7336, 26),
    ('skrin', 8638, 79),
    ('stul', 4362, 93),
    ('blah', 1790, 25),
    ('foo', 3627, 11),
    ('bar', 2203, 97),
    ('qux', 3071, 58);


CREATE TABLE polozka(
    faktura_id INT REFERENCES faktura(id),
    zbozi_id INT REFERENCES zbozi(id),
    mnozstvi INT CONSTRAINT vetsi_nez_nula CHECK (mnozstvi > 0)
);

INSERT INTO polozka (faktura_id, zbozi_id, mnozstvi) VALUES
    (23, 2, 6),
    (64, 7, 4),
    (5, 13, 10),
    (42, 19, 4),
    (8, 3, 7),
    (68, 4, 8),
    (53, 12, 2),
    (17, 23, 3),
    (75, 19, 5),
    (18, 13, 5),
    (38, 8, 5),
    (69, 12, 3),
    (62, 18, 5),
    (100, 10, 9),
    (67, 11, 1),
    (64, 9, 7),
    (56, 20, 7),
    (30, 13, 3),
    (84, 5, 3),
    (21, 11, 9),
    (11, 2, 3),
    (59, 9, 5),
    (85, 10, 8),
    (59, 4, 5),
    (50, 2, 7),
    (24, 6, 3),
    (42, 14, 2),
    (25, 10, 3),
    (97, 19, 1),
    (23, 21, 1),
    (91, 14, 1),
    (60, 15, 3),
    (49, 11, 9),
    (69, 18, 6),
    (60, 7, 4),
    (1, 18, 3),
    (60, 1, 1),
    (29, 18, 9),
    (15, 13, 3),
    (97, 17, 2),
    (63, 2, 7),
    (85, 18, 7),
    (80, 21, 2),
    (95, 3, 5),
    (25, 11, 10),
    (43, 3, 2),
    (72, 17, 5),
    (46, 6, 3),
    (95, 7, 2),
    (11, 21, 5),
    (68, 15, 5),
    (84, 20, 7),
    (90, 12, 5),
    (82, 19, 8),
    (96, 2, 1),
    (7, 24, 3),
    (46, 3, 10),
    (67, 24, 6),
    (58, 25, 4),
    (30, 7, 3),
    (88, 9, 1),
    (21, 8, 5),
    (43, 13, 8),
    (1, 6, 2),
    (94, 6, 6),
    (64, 4, 1),
    (51, 15, 7),
    (26, 18, 8),
    (21, 22, 3),
    (21, 15, 4),
    (47, 16, 6),
    (21, 21, 6),
    (76, 4, 8),
    (58, 23, 10),
    (46, 12, 10),
    (32, 4, 4),
    (42, 6, 10),
    (10, 16, 5),
    (55, 24, 8),
    (54, 1, 4),
    (81, 24, 2),
    (51, 19, 9),
    (14, 10, 9),
    (7, 6, 2),
    (37, 24, 10),
    (46, 16, 8),
    (92, 14, 8),
    (89, 24, 1),
    (31, 19, 10),
    (78, 17, 1),
    (5, 10, 4),
    (54, 14, 4),
    (49, 2, 3),
    (38, 7, 8),
    (27, 24, 10),
    (89, 4, 5),
    (9, 13, 2),
    (68, 9, 5),
    (6, 1, 3),
    (87, 14, 8),
    (71, 7, 10),
    (52, 16, 1),
    (56, 16, 10),
    (37, 23, 5),
    (66, 7, 1),
    (77, 22, 5),
    (55, 23, 4),
    (75, 24, 8),
    (80, 6, 9),
    (19, 17, 4),
    (86, 24, 9),
    (2, 2, 2),
    (4, 7, 4),
    (53, 21, 8),
    (69, 10, 3),
    (47, 19, 6),
    (80, 11, 10),
    (38, 16, 3),
    (54, 2, 6),
    (98, 7, 8),
    (22, 9, 1),
    (18, 13, 1),
    (18, 14, 10),
    (78, 11, 6),
    (26, 18, 1),
    (90, 3, 7),
    (14, 24, 8),
    (81, 20, 2),
    (77, 11, 5),
    (93, 6, 8),
    (80, 2, 9),
    (28, 13, 3),
    (3, 5, 5),
    (10, 17, 3),
    (90, 11, 1),
    (59, 17, 10),
    (75, 11, 6),
    (7, 18, 9),
    (44, 13, 2),
    (28, 5, 4),
    (100, 20, 5),
    (4, 22, 4),
    (41, 16, 10),
    (19, 22, 3),
    (5, 22, 4),
    (55, 5, 9),
    (11, 10, 3),
    (56, 8, 2),
    (99, 12, 1),
    (21, 24, 10),
    (63, 4, 2),
    (39, 17, 10),
    (78, 6, 9),
    (8, 3, 10),
    (100, 6, 4),
    (38, 25, 3),
    (60, 3, 2),
    (28, 13, 10),
    (25, 22, 9),
    (27, 25, 1),
    (63, 9, 2),
    (21, 1, 4),
    (93, 11, 1),
    (73, 23, 4),
    (66, 6, 1),
    (35, 9, 10),
    (13, 6, 3),
    (60, 18, 6),
    (16, 23, 8),
    (19, 13, 7),
    (93, 9, 6),
    (41, 1, 8),
    (77, 4, 8),
    (75, 7, 6),
    (48, 15, 2),
    (58, 18, 9),
    (45, 21, 9),
    (6, 25, 4),
    (31, 21, 1),
    (37, 15, 9),
    (83, 4, 7),
    (9, 14, 8),
    (57, 16, 10),
    (52, 2, 2),
    (20, 4, 9),
    (44, 10, 8),
    (7, 6, 6),
    (6, 13, 10),
    (97, 2, 3),
    (58, 21, 6),
    (33, 12, 5),
    (80, 20, 10),
    (47, 7, 5),
    (64, 1, 5),
    (78, 18, 8),
    (63, 13, 3),
    (11, 22, 10),
    (53, 25, 8),
    (91, 16, 3),
    (25, 17, 2),
    (72, 7, 7),
    (99, 14, 1),
    (73, 14, 8),
    (9, 1, 5),
    (34, 8, 4),
    (12, 13, 2),
    (67, 7, 7),
    (39, 5, 4),
    (56, 8, 6),
    (37, 16, 2),
    (4, 3, 7),
    (4, 1, 3),
    (57, 17, 2),
    (17, 23, 8),
    (10, 15, 9),
    (10, 25, 8),
    (100, 18, 1),
    (87, 18, 5),
    (20, 7, 2),
    (50, 5, 9),
    (6, 23, 3),
    (51, 13, 2),
    (33, 6, 1),
    (60, 11, 3),
    (7, 22, 7),
    (84, 10, 5),
    (75, 17, 2),
    (88, 18, 2),
    (28, 20, 9),
    (99, 22, 9),
    (41, 25, 7),
    (10, 14, 1),
    (43, 16, 9),
    (45, 8, 9),
    (94, 6, 4),
    (3, 1, 3),
    (16, 18, 3),
    (99, 11, 6),
    (11, 21, 3),
    (92, 4, 9),
    (24, 9, 1),
    (46, 6, 4),
    (24, 23, 8),
    (36, 2, 8),
    (51, 9, 6),
    (55, 16, 8),
    (20, 21, 1),
    (91, 4, 5),
    (4, 23, 9),
    (3, 15, 2);




-- Pohled: faktura a její celková částka za zboží
CREATE OR REPLACE VIEW faktura_cena AS 
    SELECT faktura.id, SUM(zbozi_polozka.mnozstvi * zbozi_polozka.cena) as utraceno FROM faktura JOIN 
    (SELECT * FROM polozka JOIN zbozi ON polozka.zbozi_id = zbozi.id) AS zbozi_polozka 
    ON faktura.id = zbozi_polozka.faktura_id GROUP BY faktura.id ORDER BY faktura.id ASC;
-- Spíše bych řešil přes funkci, jelikož si nejsem vědom, že by se pohledu daly předávat argumenty, aby to nebyl pohled pouze pro jednu fakturu

-- Dotaz: jméno zákazníka a jeho maximalní utracená částka na jedné faktuře

SELECT DISTINCT ON (jmeno) zakaznik.jmeno as jmeno, faktura.id as id_faktura, SUM(polozka.mnozstvi * zbozi.cena) as utraceno
    FROM zakaznik 
    JOIN faktura ON zakaznik.id = faktura.zakaznik_id 
    JOIN polozka ON polozka.faktura_id = faktura.id 
    JOIN zbozi ON polozka.zbozi_id = zbozi.id 
    GROUP BY faktura.id, zakaznik.jmeno ORDER BY jmeno, utraceno DESC;

-- Transakci: vystavení faktury zákazníkovi a úprava zboží skladem

CREATE TABLE faktura_zakaznikovi(
    id_faktury INT REFERENCES faktura(id),
    produkt TEXT,
    id_polozky INT REFERENCES zbozi(id),
    mnozstvi TEXT,
    celkova_cena  NUMERIC
);

CREATE OR REPLACE FUNCTION fakturizace(input_faktura_id INT) RETURNS TABLE (id_faktury INT, produkt TEXT, id_polozky INT, mnozstvi INT, cena NUMERIC)
as $$
BEGIN
RETURN QUERY SELECT faktura.id as id_faktury, zbozi_polozka.jmeno as produkt, 
    zbozi_polozka.id as id_polozky, zbozi_polozka.mnozstvi, zbozi_polozka.cena FROM faktura JOIN 
    (SELECT * FROM polozka JOIN zbozi ON polozka.zbozi_id = zbozi.id) AS zbozi_polozka 
    ON faktura.id = zbozi_polozka.faktura_id WHERE faktura.id = input_faktura_id;
END; 
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION upravit_zbozi() RETURNS VOID
as $$
DECLARE
    r RECORD;
    id_faktury INT;
BEGIN
    id_faktury := (SELECT id FROM faktura ORDER BY vystaveni DESC LIMIT 1);
    FOR r IN select * FROM fakturizace(id_faktury)
    LOOP
    INSERT INTO faktura_zakaznikovi VALUES (r.id_faktury, r.produkt, r.id_polozky, r.mnozstvi, r.cena);
    RAISE NOTICE 'Odecitam % zbozi %', r.mnozstvi, r.produkt;
    UPDATE zbozi SET skladem = skladem - r.mnozstvi WHERE zbozi.jmeno = r.produkt;
    END LOOP;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION insert_zbozi_do_faktury(id_zbozi INT) RETURNS VOID
as $$
DECLARE
    id_faktury INT;
BEGIN
    id_faktury := (SELECT id FROM faktura ORDER BY vystaveni DESC LIMIT 1);
    INSERT INTO polozka(faktura_id, zbozi_id, mnozstvi) VALUES (id_faktury, id_zbozi, floor(random() * 10) + 1);
END;
$$ LANGUAGE plpgsql;

BEGIN;
INSERT INTO faktura(vystaveni, zakaznik_id) VALUES (now(), floor(random() * 14) + 1);
SELECT * FROM insert_zbozi_do_faktury(floor(random() * 25 + 1)::int);
SELECT * FROM insert_zbozi_do_faktury(floor(random() * 25 + 1)::int);
SELECT * FROM upravit_zbozi();
COMMIT;

-- Backend by pro každou položku zavolal insert zbozi do faktury

-- trigger a tabulku: zaznamenávání historie ceny zboží

CREATE TABLE log(
    zbozi TEXT,
    msg TEXT,
    zmena NUMERIC,
    cas TIMESTAMP
);

CREATE OR REPLACE FUNCTION log_zmena_ceny() RETURNS TRIGGER AS $$
BEGIN
    IF (new.cena > old.cena) THEN
    INSERT INTO log (zbozi, msg, zmena, cas) VALUES
        (old.jmeno, 'Zvyseni ceny', new.cena - old.cena, now());
    END IF;
    IF (new.cena < old.cena) THEN
    INSERT INTO log (zbozi, msg, zmena, cas) VALUES
        (old.jmeno, 'Snizeni ceny', old.cena - new.cena, now());
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER zmena_ceny AFTER UPDATE OF cena ON zbozi FOR EACH ROW EXECUTE PROCEDURE log_zmena_ceny();

-- Doufam že je vše v pořádku. Kdyby něco nebylo podle Vašich představ tak se neváhejte ozvat.