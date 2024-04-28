SELECT title FROM movies
WHERE id IN stars.movie_id
AND stars.person_id IN people.id
AND people.name IN ('Jennifer Lawrence','Bradley Cooper');
