CREATE TABLE rel1 (
    foo INT,
    bar TEXT,
    baz INT
);

CREATE TABLE rel2 (
    bar TEXT,
    baz INT,
    qux TEXT
);

INSERT INTO rel1 VALUES 
    (444, 'ghi', 103),
    (555, 'def', 102),
    (555, 'ghi', 103),
    (666, 'abc', 101);

INSERT INTO rel2 VALUES
    ('abc', 111, 'zzz'),
    ('def', 102, 'www'),
    ('def', 102, 'yyy'),
    ('ghx', 103, 'xxx'),
    ('ghi', 103, 'ttt'),
    ('ghi', 103, 'uuu'),
    ('ghi', 103, 'vvv');
