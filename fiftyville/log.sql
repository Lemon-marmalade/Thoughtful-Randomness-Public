-- Keep a log of any SQL queries you execute as you solve the mystery.
-- 1: selecting id and description to see what there is
SELECT id, description FROM crime_scene_reports
    WHERE year = '2023' AND month = '7' AND day = '28' AND street = 'Humphrey Street';
-- results:
    --description for the id of 295 is the only one that matches the crime
    --the time of crime was at 10:15am
    --interviews were conducted on the day of the crime with 3 witnesses (each of their interview transcripts mentions the bakery)
-- 2: selecting id, name and transcript from interviews on that same day (since information from previous query provided interviews were done the day of)
SELECT id, name, transcript FROM interviews
    WHERE year = '2023' AND month = '7' AND day = '28';
-- results: those that included mention of the bakery
    -- id: 161
    --name: Ruth
    -- transcript details:
        -- sometime within 10 minutes of theft, Ruth saw thief get into car in bakery parking lot and drive away
        -- advises interviewer to look in security footage from the parking lot in that time frame (check bakery_security logs)
    -- id: 162
    -- name: Eugene
    -- transcript details:
        -- doesn't know the theif's name, but recognized them
        -- that morning, before arriving at Emma's bakery, Eugene was walking by the ATM on Leggett Street and saw the theif there withdrawing money (check atm transactions and bank_ accounts)
    --id: 163
    --name: Raymond
    -- transcript details:
        -- as the thief was leaving the bakery, they called someone who talked to them for less than a minute
            -- in the call, Raymond heard the thief plan to take the earliest flight out of Fiftyville the next day
                -- thief asked person on other end of call to purchase a flight ticket (check phone_calls, airports, flights, passengers)
-- 3: (based on info from interview 161) selecting id, activity and license plate according to time frame
SELECT id, activity, license_plate FROM bakery_security_logs
    WHERE year = '2023' AND month = '7' AND day = '28' AND hour = '10' AND (minute BETWEEN 15 AND 25);
