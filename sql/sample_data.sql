INSERT INTO users (name, email, role) VALUES
    ('Иван Петров', 'admin@shop.com', 'admin'),
    ('Петр Сидоров', 'manager@shop.com', 'manager'),
    ('Александр Смирнов', 'alex@mail.com', 'customer'),
    ('Мария Иванова', 'maria@mail.com', 'customer');
	
INSERT INTO products (name, price, quantity_in_stock) VALUES
    ('Ноутбук Dell', 50000.00, 10),
    ('Мышка Logitech', 1500.00, 50),
    ('Клавиатура Keychron', 3000.00, 30),
    ('Монитор LG', 15000.00, 5),
    ('Наушники Sony', 8000.00, 20);

INSERT INTO orders (user_id, order_date, status, total_amount) VALUES
    (3, '2025-01-10', 'completed', 56000.00),
    (4, '2025-01-11', 'completed', 19000.00),
    (5, '2025-01-12', 'pending', 15000.00);

INSERT INTO order_items (order_id, product_id, quantity, unit_price) VALUES
    (1, 1, 1, 50000.00),
    (1, 2, 1, 1500.00),
    (1, 3, 2, 2000.00),
    (2, 4, 1, 15000.00),
    (4, 5, 1, 8000.00);
	
INSERT INTO order_status_history (order_id, old_status, new_status, changed_by) VALUES
    (1, 'pending', 'completed', 2),
    (2, 'pending', 'completed', 2);

SELECT 'Пользователи:' as info;
SELECT * FROM users;

SELECT 'Товары:' as info;
SELECT * FROM products;

SELECT 'Заказы:' as info;
SELECT * FROM orders;

SELECT 'Товары в заказах:' as info;
SELECT * FROM order_items;