-- Keep a log of any SQL queries you execute as you solve the mystery.
-- 1: selecting id and description to see what there is
SELECT id, description FROM crime_scene_reports
    WHERE year = '2023' AND month = '7' AND day = '28' AND street = 'Humphrey Street';
-- results:
--description for the id of 295 is the only one that matches the crime
--the time was at 10:15am
--interviews were conducted on the day of the crime with 3 witnesses (each of their interview transcripts mentions the bakery)
-- 2:
