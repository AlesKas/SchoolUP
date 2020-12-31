((city RENAME {countrycode as code, name as cityname}) JOIN country {code,name}) {cityname, name}

((countrylanguage RENAME {countrycode as code}) JOIN country {name, code}) {name, language}

((countrylanguage RENAME {countrycode as code}) JOIN (country WHERE continent = 'Europe' ){name, code}) {name, language}

(((g7country JOIN capital) RENAME {countrycode as code}) JOIN city) {code, name}

((countrylanguage RENAME {countrycode as code} JOIN country WHERE continent = 'Asia') 
    INTERSECT (countrylanguage RENAME {countrycode as code} JOIN country WHERE region = 'Caribbean') ) {language}

(((((countrylanguage RENAME {countrycode as code}) WHERE isofficial = true ) JOIN (country WHERE region = "Southern Europe")) {name, language}) JOIN
((countrylanguage RENAME {countrycode as code, language as lan}) WHERE isofficial = true) JOIN ((country RENAME {name as nam}) WHERE region = "Southern Europe")
WHERE lan = language AND name <> nam AND name > nam) {name, language, nam}