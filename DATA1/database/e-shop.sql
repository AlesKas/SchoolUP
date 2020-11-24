CREATE TABLE store(
    id SERIAL PRIMARY KEY,
    item_name TEXT UNIQUE NOT NULL,
    price INT NOT NULL
);

INSERT INTO store (item_name, price) VALUES 
    ('iphone', 666),
    ('macbook', 456),
    ('PC', 4864),
    ('fen', 126),
    ('kartacek', 789),
    ('sklenice', 45),
    ('miska', 30),
    ('kebab', 150),
    ('notebook', 66666),
    ('mys', 1111),
    ('klavesnice', 1234),
    ('sluchatka', 5432),
    ('triko', 621),
    ('teplaky', 158),
    ('pracka', 4757),
    ('lednicka', 1287),
    ('zamek', 10),
    ('pasta', 75),
    ('papir', 10),
    ('skrin', 5000),
    ('stul', 2059),
    ('blah', 628),
    ('foo', 987),
    ('bar', 567);

CREATE TABLE customer(
    id SERIAL PRIMARY KEY,
    customer_name TEXT NOT NULL
);

INSERT INTO customer (customer_name) VALUES 
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

CREATE TABLE objednavka(
    id SERIAL PRIMARY KEY,
    datum INT,
    customer_id INT REFERENCES customer (id),
    item_id INT REFERENCES store (id)
);

INSERT INTO objednavka (datum, customer_id, item_id) VALUES
    (24, 5, 14),
    (21, 9, 18),
    (7, 3, 10),
    (29, 10, 7),
    (19, 12, 21),
    (30, 2, 22),
    (21, 14, 9),
    (15, 1, 21),
    (11, 6, 17),
    (18, 1, 6),
    (21, 9, 2),
    (3, 11, 8),
    (21, 8, 18),
    (2, 1, 20),
    (25, 9, 15),
    (14, 3, 1),
    (30, 13, 3),
    (7, 9, 24),
    (7, 3, 18),
    (26, 4, 4),
    (5, 11, 18),
    (8, 13, 9),
    (9, 5, 11),
    (10, 2, 2),
    (3, 6, 1),
    (9, 14, 22),
    (7, 4, 9),
    (12, 4, 14),
    (3, 12, 17),
    (14, 2, 21),
    (26, 7, 11),
    (7, 5, 4),
    (9, 2, 16),
    (21, 12, 8),
    (9, 4, 19),
    (7, 1, 10),
    (29, 8, 17),
    (29, 9, 24),
    (16, 12, 7),
    (10, 9, 22),
    (30, 4, 9),
    (20, 3, 11),
    (10, 1, 21),
    (14, 9, 18),
    (10, 10, 3),
    (12, 3, 22),
    (20, 11, 3),
    (28, 5, 14),
    (12, 12, 5),
    (5, 9, 22),
    (5, 14, 6),
    (14, 4, 2),
    (5, 13, 19),
    (13, 8, 6),
    (22, 8, 10),
    (9, 6, 6),
    (25, 2, 19),
    (12, 11, 16),
    (15, 3, 10),
    (23, 4, 17),
    (8, 13, 22),
    (17, 10, 12),
    (13, 2, 22),
    (14, 2, 5),
    (21, 11, 3),
    (26, 14, 22),
    (25, 13, 2),
    (25, 9, 19),
    (28, 9, 24),
    (8, 7, 2),
    (26, 12, 4),
    (12, 7, 6),
    (22, 1, 10),
    (4, 6, 15),
    (19, 14, 23),
    (3, 5, 1),
    (29, 9, 12),
    (4, 2, 21),
    (5, 14, 24),
    (3, 14, 17),
    (5, 13, 22),
    (22, 12, 4),
    (4, 5, 11),
    (22, 13, 18),
    (14, 7, 23),
    (9, 4, 3),
    (15, 4, 12),
    (1, 5, 23),
    (25, 6, 6),
    (4, 3, 1),
    (16, 3, 10),
    (13, 10, 10),
    (22, 2, 15),
    (26, 10, 2),
    (19, 1, 13),
    (29, 4, 15),
    (21, 10, 16),
    (31, 12, 20),
    (21, 7, 8),
    (1, 7, 5);

CREATE OR REPLACE VIEW customer_and_order AS
    SELECT objednavka.datum, customer.customer_name, store.item_name, store.price FROM objednavka JOIN customer ON objednavka.customer_id = customer.id
    JOIN store ON objednavka.item_id = store.id;

-- Předpokládejte, že máte proměnné count a batch_index typu integer. Potřebujete vybrat produkty setřízené podle jména, 
-- ale nejdřív jen prvních count, pak dalších count, atd. První bude znamenat, že batch_index=0, pak batch_index=1, atd.

CREATE OR REPLACE FUNCTION get_store_items(count_param int, batch_index int) RETURNS TABLE (id INT, name TEXT, price INT)
as $$
BEGIN 
RETURN QUERY SELECT * FROM store LIMIT count_param OFFSET batch_index * count_param;
END; 
$$ LANGUAGE plpgsql;

-- Předpokládejte, že máte proměnné from a to a pro jednoduchost řekněme, že jsou typu integer. 
-- Potřebujete vybrat zákazníky a jejich celkovou utracenou částku za produkty za období mezi from a to. 
-- Navíc je střiďte podle utracené částky.

CREATE OR REPLACE FUNCTION get_orders(from_param int, to_param int) RETURNS TABLE (customer_name TEXT, price_sum BIGINT)
as $$
BEGIN 
RETURN QUERY SELECT t1.customer_name, SUM(t1.price) as price_sum FROM (
    SELECT t1.customer_name, t1.price
        FROM customer_and_order as t1 WHERE t1.datum > from_param AND t1.datum < to_param
) AS t1 GROUP BY t1.customer_name ORDER BY price_sum DESC;
END; 
$$ LANGUAGE plpgsql;

-- Potřebujete vybrat zákazníky a jejich největší utracenou částku za produkty v jedné objednávce za období mezi from a to. 
-- Navíc je střiďte podle utracené částky.

CREATE OR REPLACE FUNCTION get_max_order(from_param int, to_param int) RETURNS TABLE (customer_name TEXT, price_sum INT)
as $$
BEGIN 
RETURN QUERY SELECT t1.customer_name, t1.price as price_sum FROM (
    SELECT t1.customer_name, t1.price, row_number() over (partition by t1.customer_name ORDER BY t1.price DESC) as rownum FROM customer_and_order as t1
    WHERE t1.datum > 1 AND t1.datum < 5
) AS t1 WHERE t1.rownum < 2 ORDER BY price_sum DESC;
END; 
$$ LANGUAGE plpgsql;