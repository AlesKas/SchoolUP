WITH RECURSIVE closed_contain(superpart, subpart) 
    AS (SELECT superpart, subpart FROM contain
         UNION
        SELECT contain.superpart,
               closed_contain.subpart
          FROM contain, closed_contain
         WHERE contain.subpart = closed_contain.superpart) 
SELECT sup.name, sub.name
  FROM closed_contain, part AS sup, part AS sub, atomic
 WHERE sup.id = superpart
   AND sub.id = subpart;