SELECT title FROM movies
WHERE id IN
movie_id FROM stars
WHERE stars.person_id IN
(SELECT id FROM people WHERE people.name = 'Jennifer Lawrence'))
AND
(SELECT movie_id FROM stars WHERE stars.person_id =
(SELECT id FROM people WHERE people.name = 'Bradley Cooper'));
