SELECT title FROM movies
WHERE id IN
((SELECT movie_id FROM stars WHERE person_id IN
(SELECT id from people WHERE people.name = 'Jennifer Lawrence'))
AND
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id from people WHERE people.name = 'Bradley Cooper')));
