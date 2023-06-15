SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36)
INTERSECT 
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
