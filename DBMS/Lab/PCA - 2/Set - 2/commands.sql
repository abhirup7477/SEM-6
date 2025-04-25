create table person(
	driver_id varchar2(5) check (driver_id like 'D%') primary key,
	name varchar2(20) not null,
	address varchar2(20) not null
);

create table car(
	registration_number varchar2(10) primary key,
	model varchar2(20) not null,
	year number
);

create table accident (
	report_no varchar2(5) check (report_no like 'R%') primary key,
	adate date not null,
	location varchar2(20) not null
);

create table owns (
	driver_id varchar2(5) references person(driver_id) on delete cascade,
	registration_number varchar2(10) references car(registration_number) on delete cascade
);

create table participated_in (
	driver_id varchar2(5) references person(driver_id) on delete cascade,
	registration_number varchar2(10) references car(registration_number) on delete cascade,
	report_no varchar2(5) references accident(report_no) on delete cascade,
    damage_amount number(10, 2) not null
);

insert all
	into person values ('D001', 'Ram', 'Kolkata')
	into person values ('D002', 'Shyam', 'Kolkata')
	into person values ('D003', 'John', 'Delhi')
	into person values ('D004', 'Arpan', 'Pune')
	into person values ('D005', 'Huffman', 'Mumbai')
select * from dual;

insert all
	into car values ('AB12345678', 'Toyota', 2005)
	into car values ('CD12345678', 'Toyota', 2006)
	into car values ('MN12345678', 'Alto', 2004)
	into car values ('PQ12345678', 'Scorpio', 2005)
	into car values ('RS12345678', 'Fortuner', 2015)
    into car values ('RS12345698', 'Fortuner', 2000)
select * from dual;

insert all
	into accident values ('R001', to_date('17-04-2005', 'DD-MM-YYYY'), 'Mumbai')
	into accident values ('R002', to_date('14-04-2005', 'DD-MM-YYYY'), 'Kolkata')
	into accident values ('R003', to_date('17-04-2010', 'DD-MM-YYYY'), 'Kolkata')
	into accident values ('R004', to_date('17-04-2016', 'DD-MM-YYYY'), 'Mumbai')
	into accident values ('R005', to_date('17-04-2020', 'DD-MM-YYYY'), 'Delhi')
	into accident values ('R006', to_date('15-06-2001', 'DD-MM-YYYY'), 'Pune')
	into accident values ('R007', to_date('15-06-2005', 'DD-MM-YYYY'), 'Pune')
select * from dual;

insert all
	into owns values ('D001', 'MN12345678')
	into owns values ('D005', 'AB12345678')
	into owns values ('D005', 'RS12345698')
	into owns values ('D005', 'CD12345678')
	into owns values ('D002', 'RS12345678')
	into owns values ('D002', 'PQ12345678')
select * from dual;

insert all
	into participated_in values ('D005', 'AB12345678', 'R001', 40000)
	into participated_in values ('D005', 'AB12345678', 'R005', 3500.50)
	into participated_in values ('D001', 'MN12345678', 'R002', 4000)
	into participated_in values ('D002', 'RS12345678', 'R003', 4000)
	into participated_in values ('D005', 'CD12345678', 'R004', 2400)
	into participated_in values ('D004', 'RS12345698', 'R004', 2400)
	into participated_in values ('D005', 'RS12345698', 'R007', 60000)
select * from dual;

-- 1. Find the number of people who owned new cars that were involved in accidents in the year 2005 at "Mumbai"
select count(distinct p.driver_id) as num_people from 
person p join owns o on p.driver_id = o.driver_id
join participated_in pi on pi.driver_id = o.driver_id and pi.registration_number = o.registration_number
join accident a on a.report_no = pi.report_no
where a.location = 'Mumbai'
and extract(year from adate) = 2005;

-- 2. For every accident that look place in "Kolkata" and on "15-06-2001" retrieve the driver details, and the amount of damage.
select p.*, pi.damage_amount from 
person p join participated_in pi on pi.driver_id = p.driver_id
join accident a on a.report_no = pi.report_no
where a.location = 'Kolkata'
and a.adate = to_date('15-06-2001', 'DD-MM-YYYY');

-- 3. For the "Toyota" belonging to "Huffman", find the accidents that took place in "Delhi" but not in "Pune".
select a.* from 
person p join owns o on p.driver_id = o.driver_id
join participated_in pi on pi.driver_id = o.driver_id and pi.registration_number = o.registration_number
join accident a on a.report_no = pi.report_no
join car c on c.registration_number = o.registration_number
where c.model = 'Toyota' and p.name = 'Huffman'
and a.location = 'Delhi'
and a.report_no not in (
	select report_no from accident where location = 'Pune'
);

-- 4. For every person who owns more than 2 cars, find the details for those cars which incurred a damage of Rs.50000 and above for accidents that took place in 2005.
SELECT DISTINCT p.driver_id, p.name, c.registration_number, c.model, pi.damage_amount
FROM Person p
JOIN Owns o ON p.driver_id = o.driver_id
JOIN Car c ON o.registration_number = c.registration_number
JOIN Participated_in pi ON o.driver_id = pi.driver_id AND o.registration_number = pi.registration_number
JOIN Accident a ON pi.report_no = a.report_no
WHERE pi.damage_amount >= 50000
  AND extract(year from a.adate) = 2005
  AND p.driver_id IN (
      SELECT driver_id
      FROM Owns
      GROUP BY driver_id
      HAVING COUNT(DISTINCT registration_number) >= 2
  );
