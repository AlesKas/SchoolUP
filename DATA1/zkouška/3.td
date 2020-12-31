VAR adresar BASE RELATION {
	jmeno Jmeno, narozen Datum, pohlavi Pohlavi, povolani CHAR, plat Plat, deti RELATION { jmeno_ditete CHAR, vek INT}} KEY {jmeno};

adresar := adresar UNION RELATION {
    TUPLE {
        jmeno Jmeno ('Adam', 'Horak'), narozen Datum (31, 5, 1983), pohlavi Pohlavi ('M'), povolani 'Svarec', plat Plat (23000), deti RELATION {
            TUPLE {
                jmeno_ditete 'Petr', vek 3
            }
        }
    }
};

adresar := adresar UNION RELATION {
    TUPLE {
        jmeno Jmeno ('Esmeralda', 'DeNiro'), narozen Datum (13, 1, 2000), pohlavi Pohlavi ('F'), povolani 'Prostitutka', plat Plat (45000), deti RELATION {
            jmeno_ditete CHAR, vek INT
        } {}
    } 
};
adresar := adresar UNION RELATION {
    TUPLE {
        jmeno Jmeno ('Petr', 'Klimek'), narozen Datum (1, 12, 1961), pohlavi Pohlavi ('M'), povolani 'Duchodce', plat Plat (17000), deti RELATION {
            TUPLE {
                jmeno_ditete 'Eliot', vek 33
            },
            TUPLE {
                jmeno_ditete 'Kamila', vek 40
            }
        }
    }
};
adresar := adresar UNION RELATION {
    TUPLE {
        jmeno Jmeno ('Lucie', 'Petrova'), narozen Datum (8, 4, 1994), pohlavi Pohlavi ('F'), povolani 'Asistentka', plat Plat (30000), deti RELATION {
            TUPLE {
                jmeno_ditete 'Jan', vek 3
            }, 
            TUPLE {
                jmeno_ditete 'Eva', vek 2
            },
            TUPLE {
                jmeno_ditete 'Jakub', vek 1
            }
        }
    }
};

adresar {povolani}

adresar  WHERE pohlavi = Pohlavi("M")

adresar WHERE THE_jmeno(jmeno) = 'Adam'

(adresar WHERE pohlavi = Pohlavi("M")) {povolani}

EXTEND adresar: {	
vek := 2020 - THE_rok(narozen)
}

EXTEND adresar: {
vek := 2020 - THE_rok(narozen)
} {jmeno, vek}

OPERATOR times (a Plat, b INT) RETURNS Plat;
    RETURN Plat(THE_x (a) * b);
    END OPERATOR;
UPDATE adresar WHERE (povolani = 'Duchodce') : {plat := plat * 2}

DELETE adresar WHERE (THE_x(plat) < 10000);