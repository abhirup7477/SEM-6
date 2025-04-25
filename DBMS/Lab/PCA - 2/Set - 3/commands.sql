create table customer (
	cust_id varchar2(5) check(cust_id like 'C%') primary key,
	CUST_NAME varchar2(20) not null
);

create table item (
	item_id varchar2(5) check(item_id like 'I%') primary key,
	item_name varchar2(15) not null,
	price number(10,2)
);

create table bill (
	bill_no number,
	bill_date date,
	cust_id varchar2(5) references customer(cust_id) on delete cascade,
	item_id varchar2(5) references item(item_id) on delete cascade,
	qty_sold int,
	bill_amt number(10,2)
);

insert all
	into customer values ('C001', 'Alice')
	into customer values ('C002', 'Bob')
	into customer values ('C003', 'John')
	into customer values ('C004', 'Matrin')
	into customer values ('C005', 'Joey')
select * from dual;

insert all
	into item values ('I001', 'ice-creams', 20)
	into item values ('I002', 'cold drinks', 30)
	into item values ('I003', 'chips', 10)
	into item values ('I004', 'Salad', 50)
	into item values ('I005', 'Soup', 100)
select * from dual;

insert all
	into bill values (2, to_date('12-04-2016', 'dd-mm-yyyy') ,'C001', 'I004', 2, 200)
	into bill values (1, to_date('12-04-2016', 'dd-mm-yyyy') ,'C001', 'I001', 1, 20)
	into bill values (3, to_date('20-04-2016', 'dd-mm-yyyy') ,'C003', 'I001', 1, 20)
	into bill values (4, to_date('15-04-2016', 'dd-mm-yyyy') ,'C003', 'I002', 2, 40)
	into bill values (5, to_date('22-04-2016', 'dd-mm-yyyy') ,'C002', 'I001', 1, 20)
	into bill values (6, to_date('17-04-2016', 'dd-mm-yyyy') ,'C002', 'I002', 1, 30)
select * from dual;

-- 1. List the details of the customers who bought "ice-cream" but not "cold drinks".
select distinct c.* from customer c join bill b on c.cust_id = b.cust_id join item i on i.item_id = b.item_id where i.item_name = 'ice-creams' and c.cust_id not in (select cust_id from bill where item_id = (select item_id from item where item_name = 'cold drinks'));
--or,
select distinct c.* from customer c join bill b on c.cust_id = b.cust_id join item i on i.item_id = b.item_id where i.item_name = 'ice-creams' and c.cust_id not in (select b1.cust_id from bill b1 join item i1 on b1.item_id = i1.item_id where i1.item_name = 'cold drinks');

-- 2. Print the total bill amount for everyday of the week starting on 11/04/16 and ending on 16/04/16, for items whose names start with 'S'.
select distinct bill_date, sum(bill_amt) as total_bill  from bill b join item i on b.item_id = i.item_id where i.item_name like 'S%' and bill_date between to_date('11-04-2016', 'dd-mm-yyyy') and to_date('16-04-2016', 'dd-mm-yyyy') group by bill_date order by bill_date;


-- 3. For every item sold to "Alice", find the total quantity sold.
select distinct b.item_id, sum(b.qty_sold) as toal_qty_sold from customer c join bill b on c.cust_id = b.cust_id where c.cust_name = 'Alice' group by item_id;

-- 4. Find the number of customers who have purchased an item that is costlier than the costliest item purchased by "Bob".
SELECT COUNT(DISTINCT b.cust_ID) AS num_customers
FROM Bill b
JOIN Item i ON b.item_ID = i.item_ID
WHERE i.price > (
    SELECT MAX(i2.price)
    FROM Bill b2
    JOIN Customer c2 ON b2.cust_ID = c2.cust_ID
    JOIN Item i2 ON b2.item_ID = i2.item_ID
    WHERE c2.cust_name = 'Bob'
);
