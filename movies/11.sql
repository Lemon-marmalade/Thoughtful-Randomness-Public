SELECT title FROM movies
WHERE id IN
(SELECT movie_id FROM stars WHERE stars.person_id = (SELECT id FROM people WHERE people.name = 'Chadwick Boseman'))
JOIN ratings ON ratings.movie_id = movies.id
ORDER BY rating DESC
LIMIT 5;
