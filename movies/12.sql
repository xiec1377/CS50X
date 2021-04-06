SELECT title
FROM movies
--JOIN stars ON people.id = stars.person_id
--JOIN movies ON movies.id = stars.movie_id
--WHERE name = "Johnny Depp" AND "Helena Bonham Carter";
WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Johnny Depp"))
AND id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Helena Bonham Carter"));