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
--results: id 260-267 were all exiting. license plates noted
-- 4: figuring out the types of transactions
SELECT transaction_type FROM atm_transactions;
-- results: 2 types are 'withdraw' and 'deposit'
-- 5: (based on info from interview 162) selecting id, account number, and amount from atm_transactions given the date, withdrawal and street
SELECT id, account_number, amount FROM atm_transactions
    WHERE year = '2023' AND month = '7' AND day = '28' AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street';
-- results: 8 ids, account numbers, and amounts. Table has been noted
-- 6: scoping out the unit of measurement for duration
SELECT duration FROM phone_calls;
-- result: mostly in hundreds and two hundreds, so will assume duration is measured in seconds
-- 7:select id, caller, receiver from phone_calls with date and duration less than a minute
SELECT id, caller, receiver, duration FROM phone_calls
    WHERE year = '2023' AND month = '7' AND day = '28' AND duration < 60;
-- results: 9 calls. Table has been noted
-- 8: find airports in fiftyville
SELECT id, abbreviation, full_name FROM airports
    WHERE city = 'Fiftyville';
-- results: one airport, id = 8, abbreviation = CSF, full name = Fiftyville Regional Airport
-- 9: select from flights: id, destination, hour and minute for earliest flight out of fiftyville the next day
SELECT id, destination_airport_id, hour, minute FROM flights
    WHERE origin_airport_id = 8 AND year = 2023 AND month = 7 AND day = 29;
-- results: the ids are not in order. earliest flight is at 8:20, id = 36, destination airport id = 4
-- 10: join tables... selecting name from people where flights, phone number, bank info, and license plate all line up
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE passengers.flight_id = 36 AND year = 2023 AND month = 7 AND day = 29
    AND flights.origin_airport_id = 8 AND flights.destination_airport_id = 4
AND (people.phone_number IN (SELECT caller FROM phone_calls
        WHERE phone_calls.year = '2023'
        AND phone_calls.month = '7'
        AND phone_calls.day = '28'
        AND phone_calls.duration < 60))

AND bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
    WHERE year = '2023'
    AND month = '7'
    AND day = '28'
    AND transaction_type = 'withdraw'
    AND atm_location = 'Leggett Street')

AND (people.license_plate IN (SELECT license_plate FROM bakery_security_logs
        WHERE bakery_security_logs.year = '2023'
        AND bakery_security_logs.month = '7'
        AND bakery_security_logs.day = '28'
        AND bakery_security_logs.hour = '10'
        AND (minute BETWEEN 15 AND 25)));
--results!!! BRUCE!
-- 11: finding accomplice through the phone call
SELECT name FROM people
WHERE phone_number = (SELECT receiver FROM phone_calls
    WHERE year = '2023'
    AND month = '7'
    AND day = '28'
    AND duration < 60
    AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce'));
-- result: Robin
-- 12: finding destination city
SELECT destination

