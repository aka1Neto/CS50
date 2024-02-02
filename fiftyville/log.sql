-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Finding the correct crime by date and place
SELECT description FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2021
    AND street LIKE "Humphrey Street";

-- Picking the witnesses interviews
SELECT name, transcript FROM interviews
WHERE day = 28 AND month = 7 AND year = 2021;

-- The theft last 10 minutes and the thief parked at the bakery
-- The thief withdrew money at Leggett Street before the theft
-- The thief took the earliest flight out of Fiftyville on the robbery's next day

--Keep tracking of the bakery parker
SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
    AND hour = 10 AND minute >= 15 AND minute <=25
    AND activity = "exit";

--Keep tracking of the money withdraw
SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
    AND atm_location LIKE "Leggett Street";

SELECT DISTINCT(name), transaction_type FROM atm_transactions AS atm
    JOIN bank_accounts AS ba ON ba.account_number = atm.account_number
    JOIN people on people.id = ba.person_id
WHERE atm.day = 28 AND atm.month = 7 AND atm.year = 2021
    AND atm.atm_location LIKE "Leggett Street";

-- Keep tracking of the call
SELECT caller FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021
    AND duration < 60;

-- Locating the city where the thief escaped to
SELECT city FROM airports
WHERE id = (SELECT destination_airport_id FROM flights
WHERE day = 29 AND month = 7 AND year = 2021
ORDER BY hour, minute)
LIMIT 1;
-- New York

-- Discovering the thief
SELECT name FROM people
    JOIN bank_accounts AS ba ON ba.person_id = people.id
WHERE passport_number IN (SELECT passport_number FROM passengers
    WHERE flight_id = (SELECT id FROM flights
        WHERE day = 29 AND month = 7 AND year = 2021
        ORDER BY hour, minute
        LIMIT 1))
    AND license_plate IN (SELECT license_plate FROM bakery_security_logs
        WHERE day = 28 AND month = 7 AND year = 2021
            AND hour = 10 AND minute >= 15 AND minute <=25
            AND activity = "exit")
    AND phone_number IN (SELECT caller FROM phone_calls
        WHERE day = 28 AND month = 7 AND year = 2021
            AND duration < 60)
    AND account_number IN (SELECT account_number FROM atm_transactions
        WHERE day = 28 AND month = 7 AND year = 2021
            AND atm_location LIKE "Leggett Street");
-- Bruce

-- Discovering the accomplice
SELECT name FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2021
        AND duration < 60
        AND caller = (SELECT phone_number FROM people
        WHERE name LIKE "Bruce"));
-- Robin