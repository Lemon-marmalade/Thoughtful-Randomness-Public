SELECT DISTINCT name FROM people
WHERE NOT name = 'Kevin Bacon'
AND id IN
(SELECT person_id FROM stars WHERE stars.movie_id IN
(SELECT id FROM movies WHERE movies.id IN
(SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = '1958'))));
