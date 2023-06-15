-- Keep a log of any SQL queries you execute as you solve the mystery.

-- First query to identify crime, need to go witness log to find three witness reports
-- The theft took place at 10:15am
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- Query returns the three witness reports 
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- Check secury footage of baking parking lot from within 10mins of the theft 10:05 onwards
SELECT name, phone_number, passport_number, license_plate FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs 
    WHERE year=2021 AND month=7 AND day=28 AND hour=10 AND minute < 25 AND activity='exit'
);
-- ATM on Leggett street, withdrawal money, same date 28th July 2021 morning before 10:05am
SELECT * FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE day = 28 AND
        month = 7 AND
        year = 2021 AND
        atm_location = "Leggett Street" AND
        transaction_type = "withdraw"
    )
);
/* 395717|Kenny|(826) 555-1652|9878712108|30G67EN */
/* 396669|Iman|(829) 555-5269|7049073643|L93JTIZ */
/* 438727|Benista|(338) 555-6650|9586786673|8X428L0 */
/* 449774|Taylor|(286) 555-6063|1988161715|1106N58 */
/* 458378|Brooke|(122) 555-4581|4408372428|QX4YZN3 */
/* 467400|Luca|(389) 555-5198|8496433585|4328GD8 */
/* 514354|Diana|(770) 555-1861|3592750733|322W7JE */
/* 686048|Bruce|(367) 555-5533|5773159633|94KL13X */

-- Call happened after 10:15am, duration less than a minute
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
/* 221|(130) 555-0289|(996) 555-8899|2021|7|28|51 */
/* 224|(499) 555-9472|(892) 555-8872|2021|7|28|36 */
/* 233|(367) 555-5533|(375) 555-8161|2021|7|28|45 */
/* 251|(499) 555-9472|(717) 555-1342|2021|7|28|50 */
/* 254|(286) 555-6063|(676) 555-6554|2021|7|28|43 */
/* 255|(770) 555-1861|(725) 555-3243|2021|7|28|49 */
/* 261|(031) 555-6622|(910) 555-3251|2021|7|28|38 */
/* 279|(826) 555-1652|(066) 555-9701|2021|7|28|55 */
/* 281|(338) 555-6650|(704) 555-2131|2021|7|28|54 */

/* Thief to take flight on 29th July earliest flight out of Fiftyville */
SELECT * FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND
month = 7 AND
day = 29 AND
year = 2021
ORDER BY hour;
/* 36|8|4|2021|7|29|8|20 */
SELECT * FROM airports WHERE id = 4;
/* flight id 36, from Fiftyville to LaGuardia*/ 

/* People who took flight id 36 */
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
/* 395717|Kenny|(826) 555-1652|9878712108|30G67EN */
/* 398010|Sofia|(130) 555-0289|1695452385|G412CB7 */
/* 449774|Taylor|(286) 555-6063|1988161715|1106N58 */
/* 467400|Luca|(389) 555-5198|8496433585|4328GD8 */
/* 560886|Kelsey|(499) 555-9472|8294398571|0NTHK55 */
/* 651714|Edward|(328) 555-1152|1540955065|130LD9Z */
/* 686048|Bruce|(367) 555-5533|5773159633|94KL13X */
/* 953679|Doris|(066) 555-9701|7214083635|M51FA04 */

-- Accomplice to purchase flight ticket for that flight



