set linesize 50;

create table hotel (
    hotel_no varchar2(5) check (hotel_no like 'H%') primary key,
    name varchar2(20) not null,
    address varchar2(20) not null
);
desc hotel;

create table room (
    room_no varchar2(5) check (room_no like 'R%') not null,
    hotel_no varchar2(5) references hotel (hotel_no) on delete cascade,
    primary key (hotel_no, room_no),
    type varchar2(20) not null,
    price number(7, 2) not null
);
desc room;

create table guest (
    guest_no varchar2(5) check (guest_no like 'G%') primary key,
    name varchar2(20) not null,
    address varchar2(20) not null
);
desc guest;

create table booking (
    hotel_no varchar2(5) not null,
    guest_no varchar2(5),
    date_from date not null,
    date_to date,
    room_no varchar2(5) not null,
    foreign key (hotel_no, room_no) references room (hotel_no, room_no) on delete cascade
);
desc booking;

set linesize 300;

insert all
    into hotel values ('H001', 'Grosvenor', 'London')
    into hotel values ('H002', 'Hotel2', 'London')
    into hotel values ('H003', 'Hotel3', 'New York')
    into hotel values ('H004', 'Hotel4', 'Kolkata')
    into hotel values ('H005', 'Hotel5', 'Mumbai')
select * from dual;
select * from hotel;

insert all
    into room values ('R001', 'H001', 'Double', 30.60)
    into room values ('R002', 'H001', 'Double', 25.00)
    into room values ('R003', 'H001', 'Family', 39.99)
    into room values ('R004', 'H001', 'Family', 50.70)
    into room values ('R005', 'H001', 'Single', 20.00)
    into room values ('R006', 'H001', 'Single', 15.00)
    into room values ('R001', 'H002', 'Family', 53.70)
    into room values ('R002', 'H002', 'Double', 40.50)
    into room values ('R001', 'H003', 'Double', 33.80)
select * from dual;
select * from room;

insert all
    into guest values ('G001', 'John', 'London')
    into guest values ('G002', 'Crish', 'London')
    into guest values ('G003', 'Joe', 'New York')
    into guest values ('G004', 'Arka', 'Kolkata')
    into guest values ('G005', 'Shyam', 'Mumbai')
select * from dual;
select * from guest;

insert all
    into booking values ('H001', 'G001', to_date('18-04-2025', 'DD-MM-YYYY'), null, 'R001')
    into booking values ('H001', 'G002', to_date('19-04-2025', 'DD-MM-YYYY'), to_date('23-04-2025', 'DD-MM-YYYY'), 'R002')
    into booking values ('H001', 'G003', to_date('20-04-2025', 'DD-MM-YYYY'), to_date('23-04-2025', 'DD-MM-YYYY'), 'R003')
    into booking values ('H002', 'G004', to_date('17-04-2025', 'DD-MM-YYYY'), to_date('19-04-2025', 'DD-MM-YYYY'), 'R001')
    into booking values ('H003', 'G005', to_date('20-08-2025', 'DD-MM-YYYY'), null, 'R001')
    into booking values ('H001', 'G006', to_date('05-08-2025', 'DD-MM-YYYY'), to_date('08-08-2025', 'DD-MM-YYYY'), 'R004')
select * from dual;
select * from booking;

-- SQL QUERIES

-- 1. List the names and addresses of all guests in London, alphabetically ordered by name.
select name, address from guest where address = 'London' order by name;

-- 2. List all double or family rooms with a price below £40.00 per night, in ascending order of price.
select * from room where type = 'Double' or type = 'Family' and price < 40.00 order by price;

-- 3. List the bookings for which no date_to has been specified.
select * from booking where date_to is null;

-- 4. How many hotels are there?
select count(*) as numofhotels from hotel;

-- 5. What is the average price of a room?
select avg(price) as avg_price from room;

-- 6. What is the total revenue per night from all double rooms?
select sum(price) from room where type = 'Double';

-- 7. How many different guests have made bookings for August?
select count(*) as booking_aug from booking where extract(month from date_from) = 8;

-- 8. List the details of all rooms at the Grosvenor Hotel, including the name of the guest staying in the room, if the room is occupied.
SELECT r.Room_No, r.Type, r.Price, g.Guest_No, g.Name, g.Address
FROM Hotel h JOIN Room r ON h.Hotel_No = r.Hotel_No
LEFT JOIN Booking b ON r.Room_No = b.Room_No AND r.Hotel_No = b.Hotel_No
LEFT JOIN Guest g ON b.Guest_No = g.Guest_No
WHERE h.Name = 'Grosvenor' and g.guest_no is not null;

-- 9. What is the total income from bookings for the Grosvenor Hotel today?
select sum (price) as revenue_today from room where room_no in (
    select room_no from booking where date_from <= (
        select sysdate from dual
    ) and date_to <= (
        select sysdate from dual
    )
);

-- 10. List the rooms that are currently unoccupied at the Grosvenor Hotel.
select * from room where hotel_no = (
    select hotel_no from hotel where name = 'Grosvenor'
) and room_no not in (
    select room_no from booking where hotel_no = (
        select hotel_no from hotel where name = 'Grosvenor'
    )
);
