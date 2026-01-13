CREATE OR REPLACE FUNCTION getOrderStatus(order_id INT)
RETURNS VARCHAR AS $$
BEGIN
    RETURN (SELECT status FROM orders WHERE orders.order_id = order_id);
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getOrderStatusHistory(order_id INT)
RETURNS TABLE(old_status VARCHAR, new_status VARCHAR, changed_at TIMESTAMP) AS $$
BEGIN
    RETURN QUERY
    SELECT old_status, new_status, changed_at
    FROM order_status_history
    WHERE order_id = getOrderStatusHistory.order_id
    ORDER BY changed_at;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getUserOrderCount(user_id INT)
RETURNS INT AS $$
DECLARE cnt INT;
BEGIN
    SELECT COUNT(*) INTO cnt FROM orders WHERE user_id = user_id;
    RETURN cnt;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getTotalSpentByUser(user_id INT)
RETURNS DECIMAL AS $$
DECLARE total DECIMAL;
BEGIN
    SELECT SUM(total_price) INTO total FROM orders WHERE user_id = user_id;
    RETURN COALESCE(total,0);
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION canReturnOrder(order_id INT)
RETURNS BOOLEAN AS $$
DECLARE status_now VARCHAR;
DECLARE order_date TIMESTAMP;
BEGIN
    SELECT status, order_date INTO status_now, order_date FROM orders WHERE order_id = order_id;
    RETURN status_now = 'completed' AND (CURRENT_DATE - order_date::date) <= 30;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getAuditLogByUser(user_id INT)
RETURNS TABLE(entity_type VARCHAR, entity_id INT, operation VARCHAR, performed_at TIMESTAMP) AS $$
BEGIN
    RETURN QUERY
    SELECT entity_type, entity_id, operation, performed_at
    FROM audit_log
    WHERE performed_by = user_id
    ORDER BY performed_at;
END;
$$ LANGUAGE plpgsql;
