CREATE OR REPLACE PROCEDURE createOrder(p_user_id INT)
LANGUAGE plpgsql
AS $$
DECLARE
    new_order_id INT;
BEGIN
    BEGIN
        INSERT INTO orders(user_id, status, total_price)
        VALUES (p_user_id, 'pending', 0)
        RETURNING order_id INTO new_order_id;

        COMMIT;
    EXCEPTION
        WHEN OTHERS THEN
            ROLLBACK;
            RAISE;
    END;
END;
$$;
