SELECT name FROM people
WHERE id IN
(SELECT person_id FROM stars WHERE stars.movie_id = (SELECT id FROM movies WHERE movies.title = 'Toy Story'));
