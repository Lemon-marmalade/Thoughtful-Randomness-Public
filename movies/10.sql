SELECT DISTINCT name FROM people
WHERE id IN
(SELECT person_id FROM directors directors.movie_id = (SELECT id FROM movies WHERE movies.rating >= 9.0));
