SELECT title FROM movies
WHERE id IN (SELECT movie_id FROM stars
WHERE stars.person_id IN
(SELECT id from people WHERE people.name IN ('Jennifer Lawrence','Bradley Cooper')));
