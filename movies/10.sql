SELECT DISTINCT name FROM people
WHERE id IN
(SELECT person_id FROM stars stars.movie_id = (SELECT id FROM movies WHERE movies.year = 2004))
