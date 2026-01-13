CREATE OR REPLACE FUNCTION trg_order_status_func()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO order_status_history(order_id, old_status, new_status, changed_by)
    VALUES (OLD.order_id, OLD.status, NEW.status, current_setting('app.user_id')::INT);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_order_status
AFTER UPDATE OF status ON orders
FOR EACH ROW
EXECUTE FUNCTION trg_order_status_func();

CREATE OR REPLACE FUNCTION trg_audit_func()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO audit_log(entity_type, entity_id, operation, performed_by)
    VALUES (TG_TABLE_NAME, NEW.order_id, TG_OP, current_setting('app.user_id')::INT);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_audit_orders
AFTER INSERT OR UPDATE OR DELETE ON orders
FOR EACH ROW
EXECUTE FUNCTION trg_audit_func();