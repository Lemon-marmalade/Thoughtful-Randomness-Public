JOIN movies ON movies.id = ratings.movie_id
SELECT AVG(rating) FROM ratings
WHERE year = 2012;
