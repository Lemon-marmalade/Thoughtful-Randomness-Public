SELECT title FROM movies
WHERE id IN
(SELECT movie_id FROM stars WHERE stars.person_id IN
(SELECT id FROM people WHERE people.name = 'Jennifer Lawrence') AND (SELECT id FROM people WHERE people.name = 'Bradley Cooper'));
