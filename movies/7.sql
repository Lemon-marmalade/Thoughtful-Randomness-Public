SELECT title, rating FROM movies
JOIN ratings ON ratings.movie_id = movies.id
ORDER BY rating DESC
