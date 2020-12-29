CREATE TABLE adresar
(
    jmeno TEXT NOT NULL,
    prijmeni TEXT NOT NULL,
    telefon TEXT CONSTRAINT (length(VALUE) = 9),
    email TEXT,
    web TEXT,
    narozeni TIMESTAMP,
    pohlavi TEXT CONSTRAINT (pohlavi = 'M' OR pohlavi = 'F'),
    deti INT CONSTRAINT (deti >= 0),
);

INSERT INTO adresar (jmeno, prijmeni, telefon, email, narozen, pohlavi, deti) VALUES
    ('Kamila', 'Sedlbauerova', '732852732', 'kocky123@gmail.com', '1995-02-16', 'F', 0),
    ('Roman', 'Valcik', '605785325', 'r.valcik@email.cz', '1965-05-22', 'M', 3),
    ('Patrik', 'Chudoba', '963258741', 'chodoba@seznam.cz', '2000-01-01', 'M', 0),
    ('Esmeralda', 'De Niro', '555777999', 'deniro@seznam.cz', '1987-05-05', 'F', 5);

UPDATE adresar SET deti = deti + 1 WHERE jmeno = 'Esmeralda';

DELETE FROM adresar WHERE pohlavi = 'M';