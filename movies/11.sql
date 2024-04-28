SELECT title FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE id IN
(SELECT movie_id FROM stars WHERE stars.person_id = (SELECT id FROM people WHERE people.name = 'Chadwick Boseman'))
ORDER BY ratings.rating DESC
LIMIT 5;

